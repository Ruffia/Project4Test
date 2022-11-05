// TabbedViewPrjView.cpp : implementation of the CTabbedViewPrjView class
//

#include "stdafx.h"
#include "TabbedViewPrj.h"

#include "TabbedViewPrjDoc.h"
#include "TabbedViewPrjView.h"
#include "MainFrm.h"

#include "HsAlgorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTabbedViewPrjView

IMPLEMENT_DYNCREATE(CTabbedViewPrjView, CView)

BEGIN_MESSAGE_MAP(CTabbedViewPrjView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_WINDOW_TILE, &CTabbedViewPrjView::OnWindowTile)
	ON_COMMAND(ID_WINDOW_CASCADE, &CTabbedViewPrjView::OnWindowCascade)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CTabbedViewPrjView construction/destruction

CTabbedViewPrjView::CTabbedViewPrjView()
{
	// TODO: add construction code here

}

CTabbedViewPrjView::~CTabbedViewPrjView()
{
}

BOOL CTabbedViewPrjView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTabbedViewPrjView drawing

void CTabbedViewPrjView::OnDraw(CDC *pDC)
{
	CTabbedViewPrjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, m_color);		
	CFont font;
	font.CreateStockObject(DEFAULT_GUI_FONT);
	CFont* pOldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->TextOut(0, 0, this->GetDocument()->GetTitle());
	pDC->SelectObject(pOldFont);
	

	// TODO: add draw code for native data here
}


// CTabbedViewPrjView printing

BOOL CTabbedViewPrjView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTabbedViewPrjView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTabbedViewPrjView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTabbedViewPrjView diagnostics

#ifdef _DEBUG
void CTabbedViewPrjView::AssertValid() const
{
	CView::AssertValid();
}

void CTabbedViewPrjView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTabbedViewPrjDoc* CTabbedViewPrjView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabbedViewPrjDoc)));
	return (CTabbedViewPrjDoc*)m_pDocument;
}
#endif //_DEBUG


// CTabbedViewPrjView message handlers

BOOL CTabbedViewPrjView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

static COLORREF colors[] = { RGB(200, 30, 2), RGB(100, 40, 96), RGB(20, 160, 103), RGB(20, 230, 2), RGB(200, 40, 96), RGB(120, 90, 103), RGB(200, 30, 200), RGB(90, 140, 26), RGB(201, 190, 10)};
void CTabbedViewPrjView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	((CMainFrame*)AfxGetMainWnd())->GetMDIClient()->AddView(this);
	GetParentFrame()->ShowWindow(SW_MAXIMIZE);
	static int colorIndex = 0;
	m_color = colors[colorIndex];
	colorIndex = (colorIndex + 1) % 10;	
	// TODO: Add your specialized code here and/or call the base class
}

void CTabbedViewPrjView::OnSetFocus(CWnd* pOldWnd)
{	
	CView::OnSetFocus(pOldWnd);
	HsMDIClient* pMDIClient = ((CMainFrame*)AfxGetMainWnd())->GetMDIClient();
	pMDIClient->GetTabBar()->GetTabCtrl()->NotifyActiveViewChanged(this);
	// TODO: Add your message handler code here
	if(this != (pMDIClient->m_lastFocussedWnd))
	{
		for(int i = 0; i < pMDIClient->m_arrayUnTiledViews.GetSize(); i++)
		{
			if(this == pMDIClient->m_arrayUnTiledViews[i])
			{
				CRect rc;
				pMDIClient->GetClientRect(rc);
				//this->GetParentFrame()->MoveWindow(rc);
				//this->GetParentFrame()->ShowWindow(SW_HIDE);
				this->GetParentFrame()->ModifyStyle(0, WS_MAXIMIZE, 0);
				this->GetParentFrame()->ShowWindow(SW_SHOW);
				break;
			}
		}
		for(int i = 0; i < pMDIClient->m_arrayTiledViews.GetSize(); i++)
		{
			if(this == pMDIClient->m_arrayTiledViews[i])
			{
				AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_WINDOW_TILE, 0);
				break;
			}
		}

		pMDIClient->m_lastFocussedWnd = this;
	}
}

void CTabbedViewPrjView::OnWindowTile()
{
	// probably unnecessary.. just extra caution
	HsMDIClient* pMDIClient = ((CMainFrame*)AfxGetMainWnd())->GetMDIClient();
	if(pMDIClient == NULL || pMDIClient->m_bTiling)
	{
		return;
	}
	pMDIClient->m_bTiling = true;	

	BOOL bSetFocusToFirstTiledWnd = FALSE;
	// if this current window is not in the list of tiled windows then send to back
	for(int i = 0; i < pMDIClient->m_arrayUnTiledViews.GetSize(); i++)
	{
		if(this == pMDIClient->m_arrayUnTiledViews[i])
		{			
			this->GetParentFrame()->SetWindowPos(&CWnd::wndBottom, 0, 0, 0, 0,
				SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

			bSetFocusToFirstTiledWnd = TRUE;
		}
	}

	RECT rc;
	::GetClientRect(::GetParent(::GetParent(m_hWnd)), &rc);
	CRect cr = rc;
		
	size_t count = pMDIClient->m_arrayViews.GetSize();

	if(count == 0)
		return;

	HsAreaAlgorithm alg;
	int num_sections = 0;
	int* section_infos = NULL;

	UINT num_rects = 0;

	pMDIClient->UpdateTileInfo(true);
	
	num_rects = (UINT) pMDIClient->m_arrayTiledViews.GetSize();

	if(alg.DivideRectangularArea(num_rects, num_sections, section_infos))
	{		
		int rows = num_sections;
		int cols = 0;
		
		int left = 0;
		int top = 0;
		int frame_width = 0;
		int frame_height = cr.Height() / rows;

		int tiled_win_index = 0;				
		for(int i = 0; i < rows; i++)
		{
			cols = section_infos[i];
			frame_width = cr.Width() / cols;
			
			left = 0;
			for(int j = 0; j < cols; j++)
			{
				CView* pView = (CView*)(pMDIClient->m_arrayTiledViews[tiled_win_index]);
				pView->GetParentFrame()->ModifyStyle(WS_MAXIMIZE, 0);
				pView->GetParentFrame()->MoveWindow(left, top, frame_width, frame_height);				
				pView->GetParentFrame()->ShowWindow(SW_SHOW);
				left += frame_width + 1;
				tiled_win_index++;
			}
			top += frame_height + 1;
		}	
	}

	alg.ReleaseSectionInfo(section_infos);

	if(bSetFocusToFirstTiledWnd && pMDIClient->m_arrayTiledViews.GetSize() > 0)
	{
		CFrameWnd* pFrame = pMDIClient->m_arrayTiledViews[0]->GetParentFrame();
		if(pFrame != NULL)
		{
			pFrame->SetFocus();
		}
	}
	
	pMDIClient->m_bTiling = false;	
}

void CTabbedViewPrjView::OnWindowCascade()
{
	// TODO: Add your command handler code here
	this->GetParentFrame()->ShowWindow(SW_MAXIMIZE);
}

void CTabbedViewPrjView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->GetMDIClient()->RemoveView(this);
	//OnWindowTile();
}
