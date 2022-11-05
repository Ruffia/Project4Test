// CustomTabCtrlDemoSDIView.h : interface of the CCustomTabCtrlDemoSDIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMTABCTRLDEMOSDIVIEW_H__32F3DE95_C9E3_4D95_A56C_C2F794D39CCE__INCLUDED_)
#define AFX_CUSTOMTABCTRLDEMOSDIVIEW_H__32F3DE95_C9E3_4D95_A56C_C2F794D39CCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCustomTabCtrlDemoSDIView : public CHtmlView
{
public:
	CCustomTabCtrlDemoSDIView();
protected: // create from serialization only
	//CCustomTabCtrlDemoSDIView();
	DECLARE_DYNCREATE(CCustomTabCtrlDemoSDIView)

// Attributes
public:
	CCustomTabCtrlDemoSDIDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomTabCtrlDemoSDIView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomTabCtrlDemoSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomTabCtrlDemoSDIView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString m_sLabel;
	CString m_sTooltip;
	CString m_sUrl;

private:
	afx_msg LRESULT OnMyInitialUpdate(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // debug version in CustomTabCtrlDemoSDIView.cpp
inline CCustomTabCtrlDemoSDIDoc* CCustomTabCtrlDemoSDIView::GetDocument()
   { return (CCustomTabCtrlDemoSDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTABCTRLDEMOSDIVIEW_H__32F3DE95_C9E3_4D95_A56C_C2F794D39CCE__INCLUDED_)
