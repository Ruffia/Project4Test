// CustomTabCtrlDemoSDI.h : main header file for the CUSTOMTABCTRLDEMOSDI application
//

#if !defined(AFX_CUSTOMTABCTRLDEMOSDI_H__3CB6EC92_9070_4396_89E9_C8FB5A4D0203__INCLUDED_)
#define AFX_CUSTOMTABCTRLDEMOSDI_H__3CB6EC92_9070_4396_89E9_C8FB5A4D0203__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIApp:
// See CustomTabCtrlDemoSDI.cpp for the implementation of this class
//

class CCustomTabCtrlDemoSDIApp : public CWinApp
{
public:
	CCustomTabCtrlDemoSDIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomTabCtrlDemoSDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCustomTabCtrlDemoSDIApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTABCTRLDEMOSDI_H__3CB6EC92_9070_4396_89E9_C8FB5A4D0203__INCLUDED_)
