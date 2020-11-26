/****************************************************************************************
* Copyright © 2018-2020 Jovibor https://github.com/jovibor/                             *
* This is a Hex Control for MFC/Win32 applications.                                     *
* Official git repository: https://github.com/jovibor/HexCtrl/                          *
* This software is available under the "MIT License modified with The Commons Clause".  *
* https://github.com/jovibor/HexCtrl/blob/master/LICENSE                                *
* For more information visit the project's official repository.                         *
****************************************************************************************/
#pragma once
#include "CHexCtrl.h"
#include <ctime>
#include <optional>
#include <vector>

namespace HEXCTRL::INTERNAL
{
	class CHexBookmarks
	{
	public:
		ULONGLONG Add(const HEXBKMSTRUCT& hbs, bool fRedraw = true); //Returns new bookmark Id.
		void Attach(CHexCtrl* pHex);
		void ClearAll();
		[[nodiscard]] auto GetByID(ULONGLONG ullID)->HEXBKMSTRUCT*;       //Bookmark by ID.
		[[nodiscard]] auto GetByIndex(ULONGLONG ullIndex)->HEXBKMSTRUCT*; //Bookmark by index (in inner list).
		[[nodiscard]] auto GetData()->std::deque<HEXBKMSTRUCT>*;
		[[nodiscard]] ULONGLONG GetCount()const;
		[[nodiscard]] ULONGLONG GetCurrent()const;
		[[nodiscard]] auto GetTouchTime()const->__time64_t;
		void GoBookmark(ULONGLONG ullIndex);
		void GoNext();
		void GoPrev();
		[[nodiscard]] bool HasBookmarks()const;
		[[nodiscard]] auto HitTest(ULONGLONG ullOffset)->HEXBKMSTRUCT*;
		[[nodiscard]] bool IsVirtual()const;
		void Remove(ULONGLONG ullOffset);
		void RemoveByID(ULONGLONG ullID);
		void SetVirtual(bool fEnable, IHexVirtBkm* pVirtual = nullptr);
		void Update(ULONGLONG ullID, const HEXBKMSTRUCT& stBookmark);
	private:
		std::deque<HEXBKMSTRUCT> m_deqBookmarks;
		CHexCtrl* m_pHex { };
		IHexVirtBkm* m_pVirtual { };
		LONGLONG m_llCurrent { };  //Current bookmark position, to move next/prev.
		__time64_t m_time { };     //Last modification time.
		bool m_fVirtual { false }; //Working in Virtual mode or not.
	};
}