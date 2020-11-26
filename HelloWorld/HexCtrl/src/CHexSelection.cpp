/****************************************************************************************
* Copyright © 2018-2020 Jovibor https://github.com/jovibor/                             *
* This is a Hex Control for MFC/Win32 applications.                                     *
* Official git repository: https://github.com/jovibor/HexCtrl/                          *
* This software is available under the "MIT License modified with The Commons Clause".  *
* https://github.com/jovibor/HexCtrl/blob/master/LICENSE                                *
* For more information visit the project's official repository.                         *
****************************************************************************************/
#include "stdafx.h"
#include "CHexSelection.h"
#include <algorithm>

using namespace HEXCTRL;
using namespace HEXCTRL::INTERNAL;

void CHexSelection::Attach(CHexCtrl* pHex)
{
	m_pHex = pHex;
}

void CHexSelection::ClearAll()
{
	m_vecSelection.clear();
	m_vecSelHighlight.clear();
	m_ullMarkSelStart = 0xFFFFFFFFFFFFFFFFULL;
	m_ullMarkSelEnd = 0xFFFFFFFFFFFFFFFFULL;
}

void CHexSelection::ClearSelHighlight()
{
	m_vecSelHighlight.clear();
}

CHexCtrl* CHexSelection::GetHexCtrl()const
{
	return m_pHex;
}

bool CHexSelection::HasSelection()const
{
	return !m_vecSelection.empty();
}

bool CHexSelection::HasSelHighlight() const
{
	return !m_vecSelHighlight.empty();
}

bool CHexSelection::HitTest(ULONGLONG ullOffset)const
{
	return std::any_of(m_vecSelection.begin(), m_vecSelection.end(),
		[ullOffset](const HEXSPANSTRUCT& ref)
		{ return ullOffset >= ref.ullOffset && ullOffset < (ref.ullOffset + ref.ullSize); });
}

bool CHexSelection::HitTestHighlight(ULONGLONG ullOffset) const
{
	return std::any_of(m_vecSelHighlight.begin(), m_vecSelHighlight.end(),
		[ullOffset](const HEXSPANSTRUCT& ref)
		{ return ullOffset >= ref.ullOffset && ullOffset < (ref.ullOffset + ref.ullSize); });
}

bool CHexSelection::HitTestRange(const HEXSPANSTRUCT& hss)const
{
	return std::any_of(m_vecSelection.begin(), m_vecSelection.end(),
		[&](const HEXSPANSTRUCT& ref)
		{
			return (hss.ullOffset >= ref.ullOffset && hss.ullOffset < (ref.ullOffset + ref.ullSize))
				|| (ref.ullOffset >= hss.ullOffset && ref.ullOffset < (hss.ullOffset + hss.ullSize))
				|| (hss.ullOffset + hss.ullSize > ref.ullOffset && hss.ullOffset + hss.ullSize <= (ref.ullOffset + ref.ullSize));
		});
}

ULONGLONG CHexSelection::GetSelectionEnd()const
{
	if (!HasSelection())
		return 0xFFFFFFFFFFFFFFFFULL;

	return m_vecSelection.back().ullOffset + m_vecSelection.back().ullSize;
}

ULONGLONG CHexSelection::GetSelectionSize()const
{
	if (!HasSelection())
		return 0;

	return 	m_vecSelection.size() * m_vecSelection.at(0).ullSize;
}

ULONGLONG CHexSelection::GetSelectionStart()const
{
	if (!HasSelection())
		return 0xFFFFFFFFFFFFFFFFULL;

	return m_vecSelection.front().ullOffset;
}

DWORD CHexSelection::GetLineLength()const
{
	if (!HasSelection())
		return 0;

	return static_cast<DWORD>(m_vecSelection.front().ullSize);
}

ULONGLONG CHexSelection::GetOffsetByIndex(ULONGLONG ullIndex)const
{
	ULONGLONG ullOffset { 0xFFFFFFFFFFFFFFFFULL };

	if (ullIndex >= GetSelectionSize())
		return ullOffset;

	ULONGLONG ullTotal { };
	for (const auto& i : m_vecSelection)
	{
		ullTotal += i.ullSize;
		if (ullIndex < ullTotal)
		{
			ullOffset = i.ullOffset + (ullIndex - (ullTotal - i.ullSize));
			break;
		}
	}
	return ullOffset;
}

auto CHexSelection::GetData()const ->std::vector<HEXSPANSTRUCT>
{
	return m_vecSelection;
}

void CHexSelection::SetSelection(const std::vector<HEXSPANSTRUCT>& vecSelect)
{
	//On new selection clear all highlights.
	ClearSelHighlight();

	m_vecSelection = vecSelect;
}

void CHexSelection::SetSelHighlight(const std::vector<HEXSPANSTRUCT>& vecSelHighlight)
{
	m_vecSelHighlight = vecSelHighlight;
}

void CHexSelection::SetSelectionEnd(ULONGLONG ullOffset)
{
	m_ullMarkSelEnd = ullOffset;
	if (m_ullMarkSelStart == 0xFFFFFFFFFFFFFFFFULL || m_ullMarkSelEnd < m_ullMarkSelStart)
		return;

	ULONGLONG ullSize = m_ullMarkSelEnd - m_ullMarkSelStart + 1;
	m_vecSelection.clear();
	m_vecSelection.emplace_back(HEXSPANSTRUCT { m_ullMarkSelStart, ullSize });

	auto pHex = GetHexCtrl();
	if (pHex)
		pHex->UpdateInfoText();
}

void CHexSelection::SetSelectionStart(ULONGLONG ullOffset)
{
	m_ullMarkSelStart = ullOffset;
	if (m_ullMarkSelEnd == 0xFFFFFFFFFFFFFFFFULL || m_ullMarkSelStart > m_ullMarkSelEnd)
		return;

	ULONGLONG ullSize = m_ullMarkSelEnd - m_ullMarkSelStart + 1;
	m_vecSelection.clear();
	m_vecSelection.emplace_back(HEXSPANSTRUCT { m_ullMarkSelStart, ullSize });

	auto pHex = GetHexCtrl();
	if (pHex)
		pHex->UpdateInfoText();
}