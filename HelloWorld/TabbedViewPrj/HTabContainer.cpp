// HTabContainer.cpp : implementation file
//

#include "stdafx.h"
#include "TabbedViewPrj.h"
#include "HTabContainer.h"


// HsTabContainer

IMPLEMENT_DYNAMIC(HsTabContainer, HsWindow)

HsTabContainer::HsTabContainer()
{

}

HsTabContainer::~HsTabContainer()
{
}


BEGIN_MESSAGE_MAP(HsTabContainer, HsWindow)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SIZEPARENT, OnSizeParent)
END_MESSAGE_MAP()



// HsTabContainer message handlers



int HsTabContainer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	RECT rc;
	GetClientRect(&rc);
	rc.top += 2;
	rc.bottom = GetTabCtrl()->GetHeight();
	BOOL bCreated = GetTabCtrl()->Create(NULL,  NULL, WS_CHILD | WS_VISIBLE,								 
								 rc, this, ID_HSTABCTRL_DEFAULT);
	ASSERT(bCreated);	

	return bCreated ? 0 : -1;		
}

BOOL HsTabContainer::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default		
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, ::GetSysColor(COLOR_3DFACE));	
	pDC->MoveTo(rc.left, rc.top );
	pDC->LineTo(rc.right, rc.top );
	
	//pDC->MoveTo(rc.left, rc.bottom - 1);
	//pDC->LineTo(rc.right, rc.bottom - 1);
	
	return TRUE;
	
}

void HsTabContainer::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CWnd::OnLButtonDown(nFlags, point);
}

void HsTabContainer::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
	// TODO: Add your message handler code here
}

void HsTabContainer::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	cy = GetTabCtrl()->GetHeight();
	GetTabCtrl()->ResizeWindow(cx, cy);
}

LRESULT HsTabContainer::OnSizeParent(WPARAM, LPARAM lParam)
{
	AFX_SIZEPARENTPARAMS* layout = (AFX_SIZEPARENTPARAMS*)lParam;	
	CRect rect;
	rect.left = layout->rect.left;
	rect.top = layout->rect.top;
	rect.right = layout->rect.right;
	rect.bottom = rect.top + GetHeight();	
	layout->rect.top+= GetHeight();
	MoveWindow(rect);
	
    return 0;
}
