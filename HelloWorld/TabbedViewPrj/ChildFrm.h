// ChildFrm.h : interface of the CChildFrame class
//


#pragma once


class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CWnd* CreateView(CCreateContext* pContext, UINT nID);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
public:
	afx_msg void OnUpdateWindowTileHorz(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateWindowTileVert(CCmdUI *pCmdUI);

	int m_nSettings;
	FILE* m_fp;
};
