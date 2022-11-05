// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CustomTabCtrlDemoMDI.h"
#include "CustomTabCtrlDemoMDIDoc.h"
#include "DlgProperties.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CTabMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CTabMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_DECHEIGHT, OnDecheight)
	ON_UPDATE_COMMAND_UI(ID_DECHEIGHT, OnUpdateDecheight)
	ON_COMMAND(ID_INCHEIGHT, OnIncheight)
	ON_UPDATE_COMMAND_UI(ID_INCHEIGHT, OnUpdateIncheight)
	ON_COMMAND(ID_BOTTOM, OnBottom)
	ON_UPDATE_COMMAND_UI(ID_BOTTOM, OnUpdateBottom)
	ON_COMMAND(ID_LEFT, OnLeft)
	ON_UPDATE_COMMAND_UI(ID_LEFT, OnUpdateLeft)
	ON_COMMAND(ID_RIGHT, OnRight)
	ON_UPDATE_COMMAND_UI(ID_RIGHT, OnUpdateRight)
	ON_COMMAND(ID_TOP, OnTop)
	ON_UPDATE_COMMAND_UI(ID_TOP, OnUpdateTop)
	//}}AFX_MSG_MAP
	ON_NOTIFY(CTCN_DBLCLK, IDC_TABCTRL, OnDblclickTabctrl)
	ON_MESSAGE(WM_SETCURSELMSG, OnSelectTab)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nHeight = 20;
	m_orientation = ID_TOP;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{	
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	if (!m_wndToolBar.CreateEx(this/*, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY*/) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	
	if(!m_wndTab.Create(WS_CHILD|WS_VISIBLE|/*CTCS_AUTOHIDEBUTTONS|*/CTCS_FOURBUTTONS|CTCS_DRAGMOVE|CTCS_TOOLTIPS|CTCS_TOP|CTCS_CLOSEBUTTON,CRect(0,0,0,m_nHeight),this,IDC_TABCTRL))
	{
		TRACE0("Failed to create tab control\n");
		return -1;
	}

	m_wndTab.SetDragCursors(AfxGetApp()->LoadCursor(IDC_CURSORMOVE),NULL);

	m_wndTab.SetItemTooltipText(CTCID_FIRSTBUTTON,"First");
	m_wndTab.SetItemTooltipText(CTCID_PREVBUTTON,"Prev");
	m_wndTab.SetItemTooltipText(CTCID_NEXTBUTTON,"Next");
	m_wndTab.SetItemTooltipText(CTCID_LASTBUTTON,"Last");
	m_wndTab.SetItemTooltipText(CTCID_CLOSEBUTTON,"Close");

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


LRESULT CMainFrame::OnSelectTab(WPARAM wParam, LPARAM)
{
	return SetCurView(wParam);
}

void CMainFrame::OnDecheight() 
{
	m_nHeight--;
	m_wndTab.MoveWindow(0,0,m_nHeight,m_nHeight);
	RecalcLayout();
}

void CMainFrame::OnUpdateDecheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nHeight>=18);	
}

void CMainFrame::OnIncheight() 
{
	m_nHeight++;
	m_wndTab.MoveWindow(0,0,m_nHeight,m_nHeight);
	RecalcLayout();
}

void CMainFrame::OnUpdateIncheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nHeight<=30);	
}

void CMainFrame::OnDblclickTabctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int ndx = ((CTC_NMHDR*)pNMHDR)->nItem;
	if(ndx>=0)
	{
		CView* pView = (CView*)((CTC_NMHDR*)pNMHDR)->lParam;

		CDlgProperties dlg;
		dlg.m_sLabel = ((CCustomTabCtrlDemoMDIDoc*)pView->GetDocument())->m_sLabel;
		dlg.m_sTooltip = ((CCustomTabCtrlDemoMDIDoc*)pView->GetDocument())->m_sTooltip;
		dlg.m_sUrl = ((CCustomTabCtrlDemoMDIDoc*)pView->GetDocument())->m_sUrl;
		if(dlg.DoModal()==IDOK)
		{
			if(dlg.m_sLabel!=((CCustomTabCtrlDemoMDIDoc*)pView->GetDocument())->m_sLabel)
			{
				((CCustomTabCtrlDemoMDIDoc*)pView->GetDocument())->m_sLabel = dlg.m_sLabel;
				m_wndTab.SetItemText(ndx,dlg.m_sLabel);
			}
			if(dlg.m_sTooltip!=((CCustomTabCtrlDemoMDIDoc*)pView->GetDocument())->m_sTooltip)
			{
				((CCustomTabCtrlDemoMDIDoc*)pView->GetDocument())->m_sTooltip = dlg.m_sTooltip;
				m_wndTab.SetItemTooltipText(ndx,dlg.m_sTooltip);
			}
			if(dlg.m_sUrl!=((CCustomTabCtrlDemoMDIDoc*)pView->GetDocument())->m_sUrl)
			{
				((CCustomTabCtrlDemoMDIDoc*)pView->GetDocument())->m_sUrl = dlg.m_sUrl;
				((CHtmlView*)pView)->Navigate2(dlg.m_sUrl,NULL,NULL);
			}
		}
	}
	*pResult = 0;
}

void CMainFrame::OnBottom() 
{
	m_orientation = ID_BOTTOM;
	m_wndTab.ModifyStyle(CTCS_LEFT,0,0);
	m_wndTab.MoveWindow(0,0,m_nHeight,m_nHeight);
	RecalcLayout();	
}

void CMainFrame::OnUpdateBottom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_orientation==ID_BOTTOM);		
}

void CMainFrame::OnLeft() 
{
	m_orientation = ID_LEFT;
	m_wndTab.ModifyStyle(0,CTCS_LEFT,0);
	m_wndTab.MoveWindow(0,0,m_nHeight,m_nHeight);
	RecalcLayout();		
}

void CMainFrame::OnUpdateLeft(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_orientation==ID_LEFT);		
}

void CMainFrame::OnRight() 
{
	m_orientation = ID_RIGHT;
	m_wndTab.ModifyStyle(CTCS_TOP,CTCS_RIGHT,0);
	m_wndTab.MoveWindow(0,0,m_nHeight,m_nHeight);
	RecalcLayout();	
}

void CMainFrame::OnUpdateRight(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_orientation==ID_RIGHT);
}

void CMainFrame::OnTop() 
{
	m_orientation = ID_TOP;
	m_wndTab.ModifyStyle(CTCS_RIGHT,CTCS_TOP,0);
	m_wndTab.MoveWindow(0,0,m_nHeight,m_nHeight);
	RecalcLayout();	
}

void CMainFrame::OnUpdateTop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_orientation==ID_TOP);
}
