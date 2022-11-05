// MainFrm.h : interface of the CMainFrame class
//


#pragma once

#include "HMDIClient.h"
#include "HTabContainer.h"
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	HsMDIClient* GetMDIClient()
	{
		return &m_wndMDIClient;
	}
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

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
	HsMDIClient	m_wndMDIClient;
	HsTabContainer m_wndTabContainer;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	virtual void RecalcLayout(BOOL bNotify = TRUE);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};


