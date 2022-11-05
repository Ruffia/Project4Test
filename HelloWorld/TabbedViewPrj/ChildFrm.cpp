// ChildFrm.cpp : implementation of the CChildFrame class
//
#include "stdafx.h"
#include "TabbedViewPrj.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)	
	ON_WM_SYSCOMMAND()
	ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_HORZ, &CChildFrame::OnUpdateWindowTileHorz)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_VERT, &CChildFrame::OnUpdateWindowTileVert)
END_MESSAGE_MAP()


// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	//cs.style = WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	//cs.style &= ~WS_CAPTION;
	//cs.style &= ~WS_SYSMENU;	
	m_nSettings = 0;
	
	try
	{
		m_fp = NULL;
		errno_t err = fopen_s(&m_fp, "Settings.dat", "rb");
		if(err == 0)
		{		
			fscanf_s(m_fp, "%d", &m_nSettings);
			fclose(m_fp);
		}
	}
	catch(...)
	{
		OutputDebugString(_T("\r\nAccess Violation While Reading File\r\n"));
	}

	if(m_nSettings == 0)
	{
		cs.style &= ~WS_CAPTION;
		cs.style &= ~WS_SYSMENU;	
	}
			

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
		// default create client will create a view if asked for it
	if (pContext != NULL && pContext->m_pNewViewClass != NULL)
	{
		if (CreateView(pContext, AFX_IDW_PANE_FIRST) == NULL)
			return FALSE;
	}
	return TRUE;
	//return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}

CWnd* CChildFrame::CreateView(CCreateContext* pContext, UINT nID)
{
	ASSERT(m_hWnd != NULL);
	ASSERT(::IsWindow(m_hWnd));
	ENSURE_ARG(pContext != NULL);
	ENSURE_ARG(pContext->m_pNewViewClass != NULL);

	// Note: can be a CWnd with PostNcDestroy self cleanup
	CWnd* pView = (CWnd*)pContext->m_pNewViewClass->CreateObject();
	if (pView == NULL)
	{
		TRACE(traceAppMsg, 0, "Warning: Dynamic create of view type %hs failed.\n",
			pContext->m_pNewViewClass->m_lpszClassName);
		return NULL;
	}
	ASSERT_KINDOF(CWnd, pView);

	// views are always created with a border!
	if (!pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0,0,0,0), this, nID, pContext))
	{
		TRACE(traceAppMsg, 0, "Warning: could not create view for frame.\n");
		return NULL;        // can't continue without a view
	}

	if (pView->GetExStyle() & WS_EX_CLIENTEDGE)
	{
		// remove the 3d style from the frame, since the view is
		//  providing it.
		// make sure to recalc the non-client area
		//pView->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
		ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
		
	}
	return pView;
}



void CChildFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	switch(nID)
	{
		case SC_NEXTWINDOW:
			// LUC
			// Need to do some special handling here						
			//return;
			break;
	}
	CMDIChildWnd::OnSysCommand(nID, lParam);
}

void CChildFrame::OnUpdateWindowTileHorz(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nSettings);
}

void CChildFrame::OnUpdateWindowTileVert(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nSettings);
}
