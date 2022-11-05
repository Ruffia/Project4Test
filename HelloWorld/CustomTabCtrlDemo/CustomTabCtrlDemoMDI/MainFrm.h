// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__2AD6C5E8_CEBC_4CEF_A9C9_32B470DDDA4E__INCLUDED_)
#define AFX_MAINFRM_H__2AD6C5E8_CEBC_4CEF_A9C9_32B470DDDA4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\TabMDIFrameWnd.h"

#define WM_SETCURSELMSG	(WM_USER + 1)

class CMainFrame : public CTabMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
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
	CReBar      m_wndReBar;
	int m_nHeight;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDecheight();
	afx_msg void OnUpdateDecheight(CCmdUI* pCmdUI);
	afx_msg void OnIncheight();
	afx_msg void OnUpdateIncheight(CCmdUI* pCmdUI);
	afx_msg void OnBottom();
	afx_msg void OnUpdateBottom(CCmdUI* pCmdUI);
	afx_msg void OnLeft();
	afx_msg void OnUpdateLeft(CCmdUI* pCmdUI);
	afx_msg void OnRight();
	afx_msg void OnUpdateRight(CCmdUI* pCmdUI);
	afx_msg void OnTop();
	afx_msg void OnUpdateTop(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnDblclickTabctrl(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg LRESULT OnSelectTab(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	int m_orientation;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__2AD6C5E8_CEBC_4CEF_A9C9_32B470DDDA4E__INCLUDED_)
