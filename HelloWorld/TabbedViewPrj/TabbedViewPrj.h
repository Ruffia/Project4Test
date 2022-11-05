// TabbedViewPrj.h : main header file for the TabbedViewPrj application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTabbedViewPrjApp:
// See TabbedViewPrj.cpp for the implementation of this class
//

class CTabbedViewPrjApp : public CWinApp
{
public:
	CTabbedViewPrjApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTabbedViewPrjApp theApp;