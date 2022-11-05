// CustomTabCtrlDemoSDIView.cpp : implementation of the CCustomTabCtrlDemoSDIView class
//

#include "stdafx.h"
#include "CustomTabCtrlDemoSDI.h"

#include "CustomTabCtrlDemoSDIDoc.h"
#include "CustomTabCtrlDemoSDIView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_MYINITIALUPDATE (WM_USER + 1)

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIView

IMPLEMENT_DYNCREATE(CCustomTabCtrlDemoSDIView, CHtmlView)

BEGIN_MESSAGE_MAP(CCustomTabCtrlDemoSDIView, CHtmlView)
	//{{AFX_MSG_MAP(CCustomTabCtrlDemoSDIView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
	ON_MESSAGE(WM_MYINITIALUPDATE, OnMyInitialUpdate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIView construction/destruction

CCustomTabCtrlDemoSDIView::CCustomTabCtrlDemoSDIView()
{
	// TODO: add construction code here
	m_sLabel = _T("Right click for menu");
}

CCustomTabCtrlDemoSDIView::~CCustomTabCtrlDemoSDIView()
{
}

BOOL CCustomTabCtrlDemoSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIView drawing

void CCustomTabCtrlDemoSDIView::OnDraw(CDC* /*pDC*/)
{
	CCustomTabCtrlDemoSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CCustomTabCtrlDemoSDIView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	PostMessage(WM_MYINITIALUPDATE);
}

LRESULT CCustomTabCtrlDemoSDIView::OnMyInitialUpdate(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	CStringArray& a = GetDocument()->m_aStrings;
	if(a.GetSize())
	{
		CCustomTabCtrlDemoSDIView* pView = this;
		for(int i=0; i<a.GetSize(); i++)
		{
			if(i==0) // use a current view and set m_sLabel
				pView->m_sLabel = a[i];
			else if(i%3==0) // add a new view and set m_sLabel
			{
				pView = new CCustomTabCtrlDemoSDIView;
				pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
				CRect(0,0,0,0), AfxGetApp()->GetMainWnd(), AFX_IDW_PANE_FIRST, NULL);
				pView->m_sLabel = a[i];
			}
			else if(i%3==1) // set m_sUrl
				pView->m_sUrl = a[i];
			else // set m_sTooltip
			{
				pView->m_sTooltip = a[i];
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->AddView(pView->m_sLabel,pView,pView->m_sTooltip);
				pView->Navigate2(pView->m_sUrl,NULL,NULL);
			}
		}
		a.RemoveAll();
	}
	else
	{
		m_sTooltip = _T("");
		m_sUrl = _T("");
		m_sLabel = _T("Right click for menu");
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->AddView(m_sLabel,this,m_sTooltip);
		Navigate2(m_sUrl,NULL,NULL);
	}
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->SetCurView(0);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIView printing


/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIView diagnostics

#ifdef _DEBUG
void CCustomTabCtrlDemoSDIView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CCustomTabCtrlDemoSDIView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CCustomTabCtrlDemoSDIDoc* CCustomTabCtrlDemoSDIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustomTabCtrlDemoSDIDoc)));
	return (CCustomTabCtrlDemoSDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIView message handlers

