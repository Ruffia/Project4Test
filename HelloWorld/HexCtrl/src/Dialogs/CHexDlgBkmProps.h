/****************************************************************************************
* Copyright © 2018-2020 Jovibor https://github.com/jovibor/                             *
* This is a Hex Control for MFC/Win32 applications.                                     *
* Official git repository: https://github.com/jovibor/HexCtrl/                          *
* This software is available under the "MIT License modified with The Commons Clause".  *
* https://github.com/jovibor/HexCtrl/blob/master/LICENSE                                *
* For more information visit the project's official repository.                         *
****************************************************************************************/
#pragma once
#include "../../HexCtrl.h"
#include "../../res/HexCtrlRes.h"
#include <afxcontrolbars.h>  //Standard MFC's controls header.

namespace HEXCTRL::INTERNAL
{
	class CHexDlgBkmProps final : public CDialogEx
	{
	public:
		explicit CHexDlgBkmProps(CWnd* pParent = nullptr) : CDialogEx(IDD_HEXCTRL_BKMPROPS, pParent) {}
		INT_PTR DoModal(HEXBKMSTRUCT& hbs);
	protected:
		void DoDataExchange(CDataExchange* pDX)override;
		BOOL OnInitDialog()override;
		void OnOK()override;
		DECLARE_MESSAGE_MAP()
	private:
		HEXBKMSTRUCT* m_pHBS { };
		ULONGLONG m_ullOffset { };  //Current offset to compare on exit.
		ULONGLONG m_ullSize { };
	};
}