/**********************************************************************
**
**	TabMDIFrameWnd.h : include file
**
**	by Andrzej Markowski July 2005
**
**********************************************************************/

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CustomTabCtrl.h"

#define IDC_TABCTRL		100

/////////////////////////////////////////////////////////////////////////////
// CTabMDIFrameWnd frame

class CTabMDIFrameWnd : public CMDIFrameWnd
{
	DECLARE_DYNCREATE(CTabMDIFrameWnd)
protected:
	CTabMDIFrameWnd();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	CCustomTabCtrl& GetTabCtrl() {return m_wndTab;}
	BOOL AddView(CString sLabel, CView* pView, CString sTooltip);
	BOOL DeleteView(CView *pView);
	BOOL OnActivateView(CView *pView);
	BOOL SetCurView(int nNdx);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabMDIFrameWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTabMDIFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(CTabMDIFrameWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnSelchangeTabctrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTabctrl(NMHDR* pNMHDR, LRESULT* pResult) ;
	DECLARE_MESSAGE_MAP()

protected:
	CCustomTabCtrl	m_wndTab;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
