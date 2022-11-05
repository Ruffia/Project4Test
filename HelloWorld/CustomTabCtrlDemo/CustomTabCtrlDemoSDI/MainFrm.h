// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__5AC80900_43AE_449E_89FB_5CB290CE16CC__INCLUDED_)
#define AFX_MAINFRM_H__5AC80900_43AE_449E_89FB_5CB290CE16CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\TabSDIFrameWnd.h"

class CMainFrame : public CTabSDIFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	int			m_nHeight;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDecheight();
	afx_msg void OnUpdateDecheight(CCmdUI* pCmdUI);
	afx_msg void OnInheight();
	afx_msg void OnUpdateInheight(CCmdUI* pCmdUI);
	afx_msg void OnBottom();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnTop();
	afx_msg void OnUpdateBottom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLeft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTop(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnRclickTabctrl(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnClickTabctrl(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

private:
	int m_orientation;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__5AC80900_43AE_449E_89FB_5CB290CE16CC__INCLUDED_)
