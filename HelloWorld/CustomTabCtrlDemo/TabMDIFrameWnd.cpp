/**********************************************************************
**
**	TabMDIFrameWnd.cpp : implementation file of CTabMDIFrameWnd class
**
**	by Andrzej Markowski July 2005
**
**********************************************************************/

#include "stdafx.h"
#include "TabMDIFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabMDIFrameWnd

IMPLEMENT_DYNCREATE(CTabMDIFrameWnd, CMDIFrameWnd)

CTabMDIFrameWnd::CTabMDIFrameWnd()
{
}

CTabMDIFrameWnd::~CTabMDIFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CTabMDIFrameWnd, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CTabMDIFrameWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_NOTIFY(CTCN_SELCHANGE, IDC_TABCTRL, OnSelchangeTabctrl)
	ON_NOTIFY(CTCN_CLICK, IDC_TABCTRL, OnClickTabctrl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabMDIFrameWnd message handlers

void CTabMDIFrameWnd::OnSelchangeTabctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SetCurView(((CTC_NMHDR*)pNMHDR)->nItem);
	*pResult = 0;
}

void CTabMDIFrameWnd::OnClickTabctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(((CTC_NMHDR*)pNMHDR)->nItem==CTCHT_ONCLOSEBUTTON)
	{
		CMDIChildWnd* p = MDIGetActive();
		if(p)
			::PostMessage(p->m_hWnd,WM_CLOSE,0,0);
	}
	*pResult = 0;
}

BOOL CTabMDIFrameWnd::AddView(CString sLabel, CView *pView, CString sTooltip)
{	
	int ndx = m_wndTab.InsertItem(m_wndTab.GetItemCount(),sLabel,(DWORD)pView);
	if(ndx>=0)
	{
		m_wndTab.SetCurSel(ndx);
		m_wndTab.SetItemTooltipText(ndx,sTooltip);
		MDIActivate(pView->GetParentFrame());
		return TRUE;
	}
	return FALSE;
}

BOOL CTabMDIFrameWnd::DeleteView(CView *pView)
{
	for(int i=0; i<m_wndTab.GetItemCount(); i++)
	{
		DWORD dwData;
		m_wndTab.GetItemData(i,dwData);
		if(dwData==(DWORD)pView)
		{
			m_wndTab.DeleteItem(i);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTabMDIFrameWnd::OnActivateView(CView *pView)
{
	for(int i=0; i<m_wndTab.GetItemCount(); i++)
	{
		DWORD dwData;
		m_wndTab.GetItemData(i,dwData);
		if(dwData==(DWORD)pView)
		{
			if(i!=m_wndTab.GetCurSel())
				m_wndTab.SetCurSel(i);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTabMDIFrameWnd::SetCurView(int nNdx)
{
	if(nNdx>=0 && nNdx<m_wndTab.GetItemCount())
	{
		if(nNdx!=m_wndTab.GetCurSel())
			m_wndTab.SetCurSel(nNdx);
		DWORD dwData;
		m_wndTab.GetItemData(nNdx,dwData);
		MDIActivate(((CView*)dwData)->GetParentFrame());
		return TRUE;
	}
	return FALSE;
}

