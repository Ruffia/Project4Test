// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CustomTabCtrlDemoSDI.h"

#include "MainFrm.h"
#include "CustomTabCtrlDemoSDIDoc.h"
#include "CustomTabCtrlDemoSDIView.h"

#include "DlgProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CTabSDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CTabSDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_DECHEIGHT, OnDecheight)
	ON_UPDATE_COMMAND_UI(ID_DECHEIGHT, OnUpdateDecheight)
	ON_COMMAND(ID_INHEIGHT, OnInheight)
	ON_UPDATE_COMMAND_UI(ID_INHEIGHT, OnUpdateInheight)
	ON_COMMAND(ID_BOTTOM, OnBottom)
	ON_COMMAND(ID_LEFT, OnLeft)
	ON_COMMAND(ID_RIGHT, OnRight)
	ON_COMMAND(ID_TOP, OnTop)
	ON_UPDATE_COMMAND_UI(ID_BOTTOM, OnUpdateBottom)
	ON_UPDATE_COMMAND_UI(ID_LEFT, OnUpdateLeft)
	ON_UPDATE_COMMAND_UI(ID_RIGHT, OnUpdateRight)
	ON_UPDATE_COMMAND_UI(ID_TOP, OnUpdateTop)
	//}}AFX_MSG_MAP
	ON_NOTIFY(CTCN_RCLICK, IDC_TABCTRL, OnRclickTabctrl)
	ON_NOTIFY(CTCN_CLICK, IDC_TABCTRL, OnClickTabctrl)
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
	// TODO: add member initialization code here
	m_nHeight = 20;
	m_orientation = ID_LEFT;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if(!m_wndTab.Create(WS_CHILD|WS_VISIBLE|CTCS_FOURBUTTONS|CTCS_DRAGMOVE|CTCS_TOOLTIPS|CTCS_CLOSEBUTTON|CTCS_LEFT,CRect(0,0,m_nHeight,m_nHeight),this,IDC_TABCTRL))
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
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


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

void CMainFrame::OnInheight() 
{
	m_nHeight++;
	m_wndTab.MoveWindow(0,0,m_nHeight,m_nHeight);
	RecalcLayout();
}

void CMainFrame::OnUpdateInheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nHeight<=30);		
}

void CMainFrame::OnClickTabctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTabSDIFrameWnd::OnClickTabctrl(pNMHDR, pResult);
	if(((CTC_NMHDR*)pNMHDR)->nItem==CTCHT_ONCLOSEBUTTON)
		GetActiveDocument()->SetModifiedFlag();
}

void CMainFrame::OnRclickTabctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu menu;
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING,1,_T("Add View"));
	menu.AppendMenu(MF_STRING,2,_T("Delete View"));
	menu.AppendMenu(MF_STRING,3,_T("Properties"));

	if(((CTC_NMHDR*)pNMHDR)->nItem>=0)
		SetCurView(((CTC_NMHDR*)pNMHDR)->nItem);
	
	if(m_wndTab.GetItemCount()<2)
		menu.EnableMenuItem(2,MF_GRAYED);
	
	CPoint pt(((CTC_NMHDR*)pNMHDR)->ptHitTest);
	m_wndTab.ClientToScreen(&pt);

	int nRet = menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_RETURNCMD|TPM_NONOTIFY, pt.x, pt.y, this);
	switch(nRet)
	{
	case 1:
		{
			CCustomTabCtrlDemoSDIView* pView = new CCustomTabCtrlDemoSDIView;
			if(!pView)
				break;
			if(!pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,CRect(0,0,0,0), AfxGetApp()->GetMainWnd(), AFX_IDW_PANE_FIRST, NULL))
				break;
			AddView(pView->m_sLabel,pView,pView->m_sTooltip);
			pView->Navigate2(pView->m_sUrl,NULL,NULL);
			GetActiveDocument()->SetModifiedFlag();
		}
		break;
	case 2:
		{
			if(DeleteActiveView())
				GetActiveDocument()->SetModifiedFlag();
		}
		break;
	case 3:
		{
			DWORD dwData;
			int ndx = m_wndTab.GetCurSel();
			m_wndTab.GetItemData(ndx,dwData);

			CCustomTabCtrlDemoSDIView* pView = (CCustomTabCtrlDemoSDIView*)dwData;

			CDlgProperties dlg;
			dlg.m_sLabel = pView->m_sLabel;
			dlg.m_sTooltip = pView->m_sTooltip;
			dlg.m_sUrl = pView->m_sUrl;
			if(dlg.DoModal()==IDOK)
			{
				pView->m_sLabel = dlg.m_sLabel;
				m_wndTab.SetItemText(ndx,dlg.m_sLabel);
				pView->m_sTooltip = dlg.m_sTooltip;
				m_wndTab.SetItemTooltipText(ndx,dlg.m_sTooltip);
				pView->m_sUrl = dlg.m_sUrl;
				pView->Navigate2(dlg.m_sUrl,NULL,NULL);
				pView->GetDocument()->SetModifiedFlag();
			}	
		}
		break;
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

void CMainFrame::OnLeft() 
{
	m_orientation = ID_LEFT;
	m_wndTab.ModifyStyle(0,CTCS_LEFT,0);
	m_wndTab.MoveWindow(0,0,m_nHeight,m_nHeight);
	RecalcLayout();	
}

void CMainFrame::OnRight() 
{
	m_orientation = ID_RIGHT;
	m_wndTab.ModifyStyle(CTCS_TOP,CTCS_RIGHT,0);
	m_wndTab.MoveWindow(0,0,m_nHeight,m_nHeight);
	RecalcLayout();	
}

void CMainFrame::OnTop() 
{
	m_orientation = ID_TOP;
	m_wndTab.ModifyStyle(CTCS_RIGHT,CTCS_TOP,0);
	m_wndTab.MoveWindow(0,0,m_nHeight,m_nHeight);
	RecalcLayout();	
}

void CMainFrame::OnUpdateBottom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_orientation==ID_BOTTOM);	
}

void CMainFrame::OnUpdateLeft(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_orientation==ID_LEFT);		
}

void CMainFrame::OnUpdateRight(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_orientation==ID_RIGHT);		
}

void CMainFrame::OnUpdateTop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_orientation==ID_TOP);		
}
