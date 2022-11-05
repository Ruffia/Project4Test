#pragma once


// HsTabCtrl
#include "afxpriv.h"

#include "HsWindow.h"
#include "IViewsAccessor.h"

#include "HsButton.h"
#include "HsListTiledWindows.h"

class HsTabCtrl : public HsWindow, public IViewsAccessor, public HsButtonEventHandler
{
	DECLARE_DYNAMIC(HsTabCtrl)

public:
	HsTabCtrl();
	virtual ~HsTabCtrl();
	// Get/Set
public:
	UINT GetHeight() { return m_uHeight; }

	void SetHeight( UINT uHeight );
	void SetModified() { m_bTabModified = TRUE; }
	void SetFont( CFont* pFont ) { m_pFont = pFont; }   

	// Operations
public:
	void DrawTab( CDC* pDC );
	void DrawSelectedTab( CDC* pD );
	void UpdateTabWidth( CDC* pDC );	

	void SelectView(UINT uIndex);

	//void AddView(CView* view);
	void NotifyNewViewAdded(CView* pNewView);
	void NotifyViewDeleted(UINT uIndex);	
	void NotifyActiveViewChanged(CView* pActiveView, bool bRepaint = TRUE);		

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HsTabCtrl)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(HsTabCtrl)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	UINT m_uSelectedViewIndex;	
	DWORD            m_dwFlag;             // for various things

	UINT             m_uHeight;            // the height for tabs
	int              m_iOffsetToLeft;      // distance from left side to first tab
	UINT             m_uOffsetFontGap;     // gap between font boundary and tab
	BOOL             m_bTabModified;       // if tabs are modified

	CDWordArray      m_dwarrayTabWidth;    // the size of each tab
	CFont*           m_pFont;              // text font on the tabs

	static CString   m_stringWindowClass;
	
private:
	void CreateFont();
	CStringArray m_sarrayViewName;

	afx_msg void OnSize(UINT nType, int cx, int cy);

	LRESULT OnSizeParent(WPARAM, LPARAM lParam);	
	afx_msg void OnSetFocus(CWnd* pOldWnd);
protected:
	virtual void PreSubclassWindow();

	HsButton m_btnListTiledWnds;
	HsListTiledWindows m_wndListTiledWnds;
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int OnLHsButtonDown (HsButton* sender, UINT nFlags, CPoint point);
    int OnLHsButtonUp (HsButton* sender, UINT nFlags, CPoint point);

	int IsViewTiled(int nIndex)
	{
		int nTiled = 1;
		if(m_wndListTiledWnds.GetSafeHwnd() != NULL)
		{
			nTiled = m_wndListTiledWnds.m_listTiledWnds.GetCheck(nIndex);
		}		

		return nTiled;
	}
};



