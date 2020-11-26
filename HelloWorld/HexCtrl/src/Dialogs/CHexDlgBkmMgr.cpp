/****************************************************************************************
* Copyright © 2018-2020 Jovibor https://github.com/jovibor/                             *
* This is a Hex Control for MFC/Win32 applications.                                     *
* Official git repository: https://github.com/jovibor/HexCtrl/                          *
* This software is available under the "MIT License modified with The Commons Clause".  *
* https://github.com/jovibor/HexCtrl/blob/master/LICENSE                                *
* For more information visit the project's official repository.                         *
****************************************************************************************/
#include "stdafx.h"
#include "../../res/HexCtrlRes.h"
#include "CHexDlgBkmMgr.h"
#include <algorithm>
#include <numeric>

using namespace HEXCTRL;
using namespace HEXCTRL::INTERNAL;

BEGIN_MESSAGE_MAP(CHexDlgBkmMgr, CDialogEx)
	ON_WM_ACTIVATE()
	ON_NOTIFY(LVN_GETDISPINFOW, IDC_HEXCTRL_BKMMGR_LIST, &CHexDlgBkmMgr::OnListGetDispInfo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_HEXCTRL_BKMMGR_LIST, &CHexDlgBkmMgr::OnListItemChanged)
	ON_NOTIFY(NM_CLICK, IDC_HEXCTRL_BKMMGR_LIST, &CHexDlgBkmMgr::OnListItemLClick)
	ON_NOTIFY(NM_DBLCLK, IDC_HEXCTRL_BKMMGR_LIST, &CHexDlgBkmMgr::OnListDblClick)
	ON_NOTIFY(NM_RCLICK, IDC_HEXCTRL_BKMMGR_LIST, &CHexDlgBkmMgr::OnListRClick)
	ON_NOTIFY(LISTEX_MSG_CELLCOLOR, IDC_HEXCTRL_BKMMGR_LIST, &CHexDlgBkmMgr::OnListCellColor)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CHexDlgBkmMgr::Create(UINT nIDTemplate, CWnd* pParent, CHexBookmarks* pBookmarks)
{
	m_pBookmarks = pBookmarks;

	return CDialogEx::Create(nIDTemplate, pParent);
}

void CHexDlgBkmMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CHexDlgBkmMgr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pListMain->CreateDialogCtrl(IDC_HEXCTRL_BKMMGR_LIST, this);
	m_pListMain->SetSortable(true);
	m_pListMain->InsertColumn(0, L"\u2116", LVCFMT_RIGHT, 40);
	m_pListMain->InsertColumn(1, L"Offset", LVCFMT_RIGHT, 80);
	m_pListMain->InsertColumn(2, L"Size", LVCFMT_RIGHT, 80);
	m_pListMain->InsertColumn(3, L"Description", LVCFMT_LEFT, 210);
	m_pListMain->InsertColumn(4, L"Bk color", LVCFMT_LEFT, 65);
	m_pListMain->SetExtendedStyle(LVS_EX_HEADERDRAGDROP);

	m_stMenuList.CreatePopupMenu();
	m_stMenuList.AppendMenuW(MF_BYPOSITION, IDC_HEXCTRL_BKMMGR_MENU_NEW, L"New");
	m_stMenuList.AppendMenuW(MF_BYPOSITION, IDC_HEXCTRL_BKMMGR_MENU_EDIT, L"Edit");
	m_stMenuList.AppendMenuW(MF_BYPOSITION, IDC_HEXCTRL_BKMMGR_MENU_REMOVE, L"Remove");
	m_stMenuList.AppendMenuW(MF_SEPARATOR);
	m_stMenuList.AppendMenuW(MF_BYPOSITION, IDC_HEXCTRL_BKMMGR_MENU_CLEARALL, L"Clear all");

	return TRUE;
}

void CHexDlgBkmMgr::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if (nState == WA_INACTIVE)
		SetLayeredWindowAttributes(0, 150, LWA_ALPHA);
	else
	{
		SetLayeredWindowAttributes(0, 255, LWA_ALPHA);
		if (!m_time || m_time != m_pBookmarks->GetTouchTime())
			UpdateList();

		m_pListMain->SetItemState(-1, 0, LVIS_SELECTED);
		m_pListMain->SetItemState(static_cast<int>(m_pBookmarks->GetCurrent()), LVIS_SELECTED, LVIS_SELECTED);
		m_pListMain->EnsureVisible(static_cast<int>(m_pBookmarks->GetCurrent()), FALSE);
	}

	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
}

BOOL CHexDlgBkmMgr::OnCommand(WPARAM wParam, LPARAM lParam)
{
	bool fHere { true }; //Process message here, and not pass further, to parent.
	switch (LOWORD(wParam))
	{
	case IDC_HEXCTRL_BKMMGR_MENU_NEW:
	{
		HEXBKMSTRUCT hbs;
		CHexDlgBkmProps dlgBkmEdit;
		if (dlgBkmEdit.DoModal(hbs) == IDOK)
		{
			m_pBookmarks->Add(hbs);
			UpdateList();
		}
	}
	break;
	case IDC_HEXCTRL_BKMMGR_MENU_EDIT:
	{
		if (auto pBkm = m_pBookmarks->GetByIndex(m_ullCurrBkmIndex); pBkm != nullptr)
		{
			CHexDlgBkmProps dlgBkmEdit;
			auto stBkm = *pBkm; //Pass a copy to dlgBkmEdit to avoid changing the original, from list.
			if (dlgBkmEdit.DoModal(stBkm) == IDOK)
			{
				m_pBookmarks->Update(pBkm->ullID, stBkm);
				UpdateList();
			}
		}
	}
	break;
	case IDC_HEXCTRL_BKMMGR_MENU_REMOVE:
		if (auto pBkm = m_pBookmarks->GetByIndex(m_ullCurrBkmIndex); pBkm != nullptr)
		{
			m_pBookmarks->RemoveByID(pBkm->ullID);
			UpdateList();
		}
		break;
	case IDC_HEXCTRL_BKMMGR_MENU_CLEARALL:
		m_pBookmarks->ClearAll();
		UpdateList();
		break;
	default:
		fHere = false;
	}

	if (fHere)
		return TRUE;

	return CDialogEx::OnCommand(wParam, lParam);
}

BOOL CHexDlgBkmMgr::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if (const auto pNMI = reinterpret_cast<LPNMITEMACTIVATE>(lParam); pNMI->hdr.idFrom == IDC_HEXCTRL_BKMMGR_LIST)
	{
		switch (pNMI->hdr.code)
		{
		case LVN_COLUMNCLICK: //ON_NOTIFY(LVN_COLUMNCLICK...) macro doesn't seem work, for no obvious reason.
			if (!m_pBookmarks->IsVirtual())
				SortBookmarks();
			break;
		}
	}

	return CDialogEx::OnNotify(wParam, lParam, pResult);
}

void CHexDlgBkmMgr::OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
	const auto pDispInfo = reinterpret_cast<NMLVDISPINFOW*>(pNMHDR);
	const auto pItem = &pDispInfo->item;

	if (pItem->mask & LVIF_TEXT)
	{
		const auto iItemID = pItem->iItem;
		const auto iMaxLengh = pItem->cchTextMax;
		const auto pBkm = m_pBookmarks->GetByIndex(static_cast<ULONGLONG>(iItemID));
		if (pBkm == nullptr)
			return;

		ULONGLONG ullOffset { 0 };
		ULONGLONG ullSize { 0 };
		switch (pItem->iSubItem)
		{
		case 0: //Index number.
			swprintf_s(pItem->pszText, static_cast<size_t>(iMaxLengh), L"%d", iItemID + 1);
			break;
		case 1: //Offset
			if (!pBkm->vecSpan.empty())
				ullOffset = pBkm->vecSpan.front().ullOffset;
			swprintf_s(pItem->pszText, static_cast<size_t>(iMaxLengh), L"0x%llX", ullOffset);
			break;
		case 2: //Size.
			if (!pBkm->vecSpan.empty())
				ullSize = std::accumulate(pBkm->vecSpan.begin(), pBkm->vecSpan.end(), 0ULL,
					[](auto ullTotal, const HEXSPANSTRUCT& ref) {return ullTotal + ref.ullSize; });
			swprintf_s(pItem->pszText, static_cast<size_t>(iMaxLengh), L"0x%llX", ullSize);
			break;
		case 3: //Description
			pItem->pszText = const_cast<wchar_t*>(pBkm->wstrDesc.data());
			break;
		}
	}
}

void CHexDlgBkmMgr::OnListItemChanged(NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
	//Go selected bookmark only with keyboard arrows and lmouse clicks.
	//Does not trigger (LVN_ITEMCHANGED event) when updating bookmark: !(pNMI->uNewState & LVIS_SELECTED)
	if (const auto pNMI = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		pNMI->iItem != -1 && pNMI->iSubItem != -1 && (pNMI->uNewState & LVIS_SELECTED))
		m_pBookmarks->GoBookmark(static_cast<ULONGLONG>(pNMI->iItem));
}

void CHexDlgBkmMgr::OnListItemLClick(NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
	if (const auto pNMI = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); pNMI->iItem != -1 && pNMI->iSubItem != -1)
		m_pBookmarks->GoBookmark(static_cast<ULONGLONG>(pNMI->iItem));
}

void CHexDlgBkmMgr::OnListDblClick(NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
	if (const auto pNMI = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); pNMI->iItem != -1 && pNMI->iSubItem != -1)
	{
		m_ullCurrBkmIndex = static_cast<ULONGLONG>(pNMI->iItem);
		SendMessageW(WM_COMMAND, IDC_HEXCTRL_BKMMGR_MENU_EDIT);
	}
}

void CHexDlgBkmMgr::OnListRClick(NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
	bool fEnabled { false };
	if (const auto pNMI = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); pNMI->iItem != -1 && pNMI->iSubItem != -1)
	{
		fEnabled = true;
		m_ullCurrBkmIndex = static_cast<ULONGLONG>(pNMI->iItem);
	}
	m_stMenuList.EnableMenuItem(IDC_HEXCTRL_BKMMGR_MENU_EDIT, (fEnabled ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND);
	m_stMenuList.EnableMenuItem(IDC_HEXCTRL_BKMMGR_MENU_REMOVE, (fEnabled ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND);
	m_stMenuList.EnableMenuItem(IDC_HEXCTRL_BKMMGR_MENU_CLEARALL,
		(m_pListMain->GetItemCount() > 0 ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND);

	POINT pt;
	GetCursorPos(&pt);
	m_stMenuList.TrackPopupMenuEx(TPM_LEFTALIGN, pt.x, pt.y, this, nullptr);
}

void CHexDlgBkmMgr::OnListCellColor(NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
	if (const auto pNMI = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); pNMI->iSubItem == 4)
	{
		if (auto pBkm = m_pBookmarks->GetByIndex(static_cast<size_t>(pNMI->iItem)); pBkm != nullptr)
		{
			static LISTEXCELLCOLOR stCellClr;
			stCellClr.clrBk = pBkm->clrBk;
			stCellClr.clrText = pBkm->clrText;
			pNMI->lParam = reinterpret_cast<LPARAM>(&stCellClr);
		}
	}
}

void CHexDlgBkmMgr::UpdateList()
{
	m_pListMain->SetItemCountEx(static_cast<int>(m_pBookmarks->GetCount()), LVSICF_NOSCROLL);
	m_time = m_pBookmarks->GetTouchTime();
}

void CHexDlgBkmMgr::SortBookmarks()
{
	auto pData = m_pBookmarks->GetData();
	const auto iColumn = m_pListMain->GetSortColumn();
	const auto fAscending = m_pListMain->GetSortAscending();

	//Sorts bookmarks according to clicked column.
	std::sort(pData->begin(), pData->end(),
		[iColumn, fAscending](const HEXBKMSTRUCT& st1, const HEXBKMSTRUCT& st2)
		{
			int iCompare { };
			switch (iColumn)
			{
			case 0:
				break;
			case 1: //Offset.
			{
				ULONGLONG ullOffset1 { 0 };
				ULONGLONG ullOffset2 { 0 };
				if (!st1.vecSpan.empty() && !st2.vecSpan.empty())
				{
					ullOffset1 = st1.vecSpan.front().ullOffset;
					ullOffset2 = st2.vecSpan.front().ullOffset;
					iCompare = ullOffset1 != ullOffset2 ? (ullOffset1 < ullOffset2 ? -1 : 1) : 0;
				}
			}
			break;
			case 2: //Size.
			{
				ULONGLONG ullSize1 { 0 };
				ULONGLONG ullSize2 { 0 };
				if (!st1.vecSpan.empty() && !st2.vecSpan.empty())
				{
					ullSize1 = std::accumulate(st1.vecSpan.begin(), st1.vecSpan.end(), 0ULL,
						[](auto ullTotal, const HEXSPANSTRUCT& ref) {return ullTotal + ref.ullSize; });
					ullSize2 = std::accumulate(st2.vecSpan.begin(), st2.vecSpan.end(), 0ULL,
						[](auto ullTotal, const HEXSPANSTRUCT& ref) {return ullTotal + ref.ullSize; });
					iCompare = ullSize1 != ullSize2 ? (ullSize1 < ullSize2 ? -1 : 1) : 0;
				}
			}
			break;
			case 3: //Description.
				iCompare = st1.wstrDesc.compare(st2.wstrDesc);
				break;
			}

			return fAscending ? iCompare < 0 : iCompare > 0;
		});

	m_pListMain->RedrawWindow();
}

void CHexDlgBkmMgr::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_pListMain->DestroyWindow();
	m_stMenuList.DestroyMenu();
}