// CustomTabCtrlDemoMDIView.cpp : implementation of the CCustomTabCtrlDemoMDIView class
//

#include "stdafx.h"
#include "CustomTabCtrlDemoMDI.h"

#include "CustomTabCtrlDemoMDIDoc.h"
#include "CustomTabCtrlDemoMDIView.h"
#include "DlgProperties.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIView

IMPLEMENT_DYNCREATE(CCustomTabCtrlDemoMDIView, CHtmlView)

BEGIN_MESSAGE_MAP(CCustomTabCtrlDemoMDIView, CHtmlView)
	//{{AFX_MSG_MAP(CCustomTabCtrlDemoMDIView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIView construction/destruction

CCustomTabCtrlDemoMDIView::CCustomTabCtrlDemoMDIView()
{
}

CCustomTabCtrlDemoMDIView::~CCustomTabCtrlDemoMDIView()
{
}

BOOL CCustomTabCtrlDemoMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIView drawing

void CCustomTabCtrlDemoMDIView::OnDraw(CDC* /*pDC*/)
{
	CCustomTabCtrlDemoMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CCustomTabCtrlDemoMDIView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	
	static int start_view_number = 0;
	switch(start_view_number)
	{
	case 0:
		GetDocument()->m_sLabel = _T("CCustomTabCtrl");
		GetDocument()->m_sUrl = _T("http://www.codeproject.com/tabctrl/AMCustomTabCtrlDemo.asp");
		GetDocument()->m_sTooltip = _T("MFC Tab Control - a clone of the Excel Tab Sheet Control");
		start_view_number++;
		AfxGetApp()->GetMainWnd()->PostMessage(WM_COMMAND,ID_FILE_NEW);
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->MDIMaximize(GetParentFrame());
		break;
	case 1:
		GetDocument()->m_sLabel = _T("CCustomBitmapButton");
		GetDocument()->m_sUrl = _T("http://www.codeproject.com/buttonctrl/CustomBitmapButtonDemo.asp");
		GetDocument()->m_sTooltip = _T("An owner-draw bitmap button and a frame for the caption bar, in one class");
		start_view_number++;
		AfxGetApp()->GetMainWnd()->PostMessage(WM_COMMAND,ID_FILE_NEW);
		break;
	case 2:
		GetDocument()->m_sLabel = _T("MDIFlick");
		GetDocument()->m_sUrl = _T("http://www.codeproject.com/buglist/MDIFlick.asp");
		GetDocument()->m_sTooltip = _T("Provides a fix to the flicker problem in MDI applications");
		start_view_number++;
		break;
	}
	Navigate2(GetDocument()->m_sUrl,NULL,NULL);
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->AddView(GetDocument()->m_sLabel,this,GetDocument()->m_sTooltip);
	GetDocument()->SetTitle(GetDocument()->m_sLabel);
	if(start_view_number==3)
	{
		start_view_number++;
		AfxGetApp()->GetMainWnd()->PostMessage(WM_SETCURSELMSG,0);
	}
}

void CCustomTabCtrlDemoMDIView::OnDestroy() 
{
	CHtmlView::OnDestroy();
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->DeleteView(this);
}

void CCustomTabCtrlDemoMDIView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{	
	CHtmlView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	if(bActivate)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->OnActivateView(pActivateView);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIView printing


/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIView diagnostics

#ifdef _DEBUG
void CCustomTabCtrlDemoMDIView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CCustomTabCtrlDemoMDIView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CCustomTabCtrlDemoMDIDoc* CCustomTabCtrlDemoMDIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustomTabCtrlDemoMDIDoc)));
	return (CCustomTabCtrlDemoMDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIView message handlers


