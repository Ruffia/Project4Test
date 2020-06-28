// FastProcessing.h : main header file for the FASTPROCESSING application
//

#if !defined(AFX_FASTPROCESSING_H__602913F3_5E8D_4809_A85E_D18F84DEA8ED__INCLUDED_)
#define AFX_FASTPROCESSING_H__602913F3_5E8D_4809_A85E_D18F84DEA8ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFastProcessingApp:
// See FastProcessing.cpp for the implementation of this class
//

class CFastProcessingApp : public CWinApp
{
public:
	CFastProcessingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFastProcessingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFastProcessingApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASTPROCESSING_H__602913F3_5E8D_4809_A85E_D18F84DEA8ED__INCLUDED_)
