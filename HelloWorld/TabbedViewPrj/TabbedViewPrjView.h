// TabbedViewPrjView.h : interface of the CTabbedViewPrjView class
//


#pragma once


class CTabbedViewPrjView : public CView
{
protected: // create from serialization only
	CTabbedViewPrjView();
	DECLARE_DYNCREATE(CTabbedViewPrjView)

// Attributes
public:
	CTabbedViewPrjDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTabbedViewPrjView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	COLORREF m_color;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	virtual void OnInitialUpdate();
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
public:
	afx_msg void OnWindowTile();
public:
	afx_msg void OnWindowCascade();
public:
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // debug version in TabbedViewPrjView.cpp00................................................................
inline CTabbedViewPrjDoc* CTabbedViewPrjView::GetDocument() const
   { return reinterpret_cast<CTabbedViewPrjDoc*>(m_pDocument); }
#endif

