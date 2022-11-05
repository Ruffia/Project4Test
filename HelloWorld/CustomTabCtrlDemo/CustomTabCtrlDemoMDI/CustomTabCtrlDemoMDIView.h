// CustomTabCtrlDemoMDIView.h : interface of the CCustomTabCtrlDemoMDIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMTABCTRLDEMOMDIVIEW_H__6F782437_2854_4DF8_A70D_E85D748DEE09__INCLUDED_)
#define AFX_CUSTOMTABCTRLDEMOMDIVIEW_H__6F782437_2854_4DF8_A70D_E85D748DEE09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCustomTabCtrlDemoMDIView : public CHtmlView
{
protected: // create from serialization only
	CCustomTabCtrlDemoMDIView();
	DECLARE_DYNCREATE(CCustomTabCtrlDemoMDIView)

// Attributes
public:
	CCustomTabCtrlDemoMDIDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomTabCtrlDemoMDIView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomTabCtrlDemoMDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomTabCtrlDemoMDIView)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // debug version in CustomTabCtrlDemoMDIView.cpp
inline CCustomTabCtrlDemoMDIDoc* CCustomTabCtrlDemoMDIView::GetDocument()
   { return (CCustomTabCtrlDemoMDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTABCTRLDEMOMDIVIEW_H__6F782437_2854_4DF8_A70D_E85D748DEE09__INCLUDED_)
