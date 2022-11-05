// HMDIContainer.cpp : implementation file
//

#include "stdafx.h"
#include "TabbedViewPrj.h"
#include "HMDIContainer.h"


// HsMDIContainer

IMPLEMENT_DYNAMIC(HsMDIContainer, HsWindow)

HsMDIContainer::HsMDIContainer()
{

}

HsMDIContainer::~HsMDIContainer()
{
}


BEGIN_MESSAGE_MAP(HsMDIContainer, HsWindow)
	ON_WM_CREATE()	
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// HsMDIContainer message handlers



int HsMDIContainer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here		
	RECT rc;
	GetClientRect(&rc);
	rc.bottom = rc.top + GetTabContainer()->GetHeight();
	BOOL bCreated = GetTabContainer()->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
								 rc, this, ID_HSTABCONTAINER_DEFAULT);
	ASSERT(bCreated);	
	

	return bCreated ? 0 : -1;
}

//COLORREF colors[] = { RGB(200, 30, 2), RGB(100, 40, 96), RGB(20, 160, 103), RGB(20, 230, 2), RGB(200, 40, 96), RGB(120, 90, 103), RGB(200, 30, 200), RGB(90, 140, 26), RGB(201, 190, 10)};
BOOL HsMDIContainer::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	GetClientRect(rc);
	
	pDC->FillSolidRect(rc, RGB(220, 130, 240));
	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}


void HsMDIContainer::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
}

void HsMDIContainer::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	lpwndpos->hwndInsertAfter= HWND_BOTTOM;
	CWnd::OnWindowPosChanging(lpwndpos);	
	// TODO: Add your message handler code here
}

void HsMDIContainer::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	cy = GetTabContainer()->GetHeight();
	GetTabContainer()->ResizeWindow(cx, cy);
	
}
