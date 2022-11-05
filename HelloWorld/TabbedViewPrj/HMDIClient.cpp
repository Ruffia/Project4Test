// HMDIClient.cpp : implementation file
//

#include "stdafx.h"
#include "TabbedViewPrj.h"
#include "HMDIClient.h"


// HsMDIClient

IMPLEMENT_DYNAMIC(HsMDIClient, CWnd)

HsMDIClient::HsMDIClient()
{
	m_lastFocussedWnd = NULL;
	m_bTiling = false;
}

HsMDIClient::~HsMDIClient()
{
}


BEGIN_MESSAGE_MAP(HsMDIClient, CWnd)
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_MDISETMENU, OnMDISetMenu)	
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// HsMDIClient message handlers



BOOL HsMDIClient::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	/*CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, RGB(220, 230, 240));
	return TRUE;*/
	return CWnd::OnEraseBkgnd(pDC);
}

void HsMDIClient::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	/*RECT rc;
	GetClientRect(&rc);
	BOOL bCreated = GetDefaultMDIContainer()->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		rc, this, ID_HSMDICONTAINER_DEFAULT);
	ASSERT(bCreated);	*/
	
	CWnd::PreSubclassWindow();
}

LRESULT HsMDIClient::OnMDISetMenu(WPARAM wParam, LPARAM lParam)
{
//	GetDefaultMDIContainer()->SetWindowPos(&wndBottom, 0, 0, 0, 0,
//		SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE | SWP_NOSENDCHANGING);	
	((CMDIFrameWnd*)AfxGetMainWnd())->RecalcLayout();
	return Default();
}


void HsMDIClient::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{	
	CWnd::OnWindowPosChanging(lpwndpos);	
}

void HsMDIClient::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	CRect rc;
	//GetDefaultMDIContainer()->ResizeWindow(cx, cy);	
	m_cx = cx;
	m_cy = cy;		
	//ArrangeWindows();
	// TODO: Add your message handler code here
}

void HsMDIClient::ArrangeWindows()
{
	
	UINT size = (UINT) m_arrayViews.GetSize();
	CRect rc;
	GetDefaultMDIContainer()->GetTabContainer()->GetClientRect(rc);
	for(UINT i = 0; i < size; i++)
	{
		m_arrayViews[i]->GetParentFrame()->MoveWindow(0, rc.bottom, m_cx, m_cy);
	}
}

void HsMDIClient::AddView(CView* pView)
{
	m_arrayViews.Add(pView);
	//GetViewsArray(GetDefaultMDIContainer()->GetTabContainer()->GetTabCtrl());
	//GetDefaultMDIContainer()->GetTabContainer()->GetTabCtrl()->NotifyNewViewAdded(pView);
	//ArrangeWindows();
	GetViewsArray(GetTabBar()->GetTabCtrl());
	GetTabBar()->GetTabCtrl()->NotifyNewViewAdded(pView);
}

void HsMDIClient::RemoveView(CView* pView)
{
	UINT i = 0;
	for(i = 0; i < m_arrayViews.GetSize(); i++)
	{
		if(pView == ((CView*)m_arrayViews[i]))
		{
			GetTabBar()->GetTabCtrl()->NotifyViewDeleted(i);
			m_arrayViews.RemoveAt(i);
			break;
		}
	}

	for(i = 0; i < m_arrayTiledViews.GetSize(); i++)
	{
		if(pView == ((CView*)m_arrayTiledViews[i]))
		{
			m_arrayTiledViews.RemoveAt(i);
			break;
		}
	}

	for(i = 0; i < m_arrayUnTiledViews.GetSize(); i++)
	{
		if(pView == ((CView*)m_arrayUnTiledViews[i]))
		{
			m_arrayUnTiledViews.RemoveAt(i);
			break;
		}
	}
}

void HsMDIClient::GetViewsArray(IViewsAccessor* pViewsAccessor)
{
	pViewsAccessor->AccessViewsArray(&m_arrayViews);
}

void HsMDIClient::UpdateTileInfo(bool bHideUntiledWindow)
{
	m_arrayTiledViews.RemoveAll();
	m_arrayUnTiledViews.RemoveAll();

	int win_index = 0;				
	for(win_index = 0; win_index < m_arrayViews.GetSize(); win_index++)
	{
		CView* pView = (CView*)(m_arrayViews[win_index]);
			
		if(GetTabBar()->GetTabCtrl()->IsViewTiled(win_index))
		{
			m_arrayTiledViews.Add(pView);			
		}
		else
		{
			m_arrayUnTiledViews.Add(pView);
			if(bHideUntiledWindow)
			{
				//pView->GetParentFrame()->ShowWindow(SW_HIDE);
				pView->GetParentFrame()->MoveWindow(0, 0, 0, 0);
			}
		}
	}
}