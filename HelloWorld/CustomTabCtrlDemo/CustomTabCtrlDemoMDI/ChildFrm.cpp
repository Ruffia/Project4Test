// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "CustomTabCtrlDemoMDI.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
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
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style = WS_CHILD | /*WS_VISIBLE | WS_SYSMENU |*/ WS_OVERLAPPED | WS_CAPTION| FWS_ADDTOTITLE | WS_MAXIMIZEBOX;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers


LRESULT CChildFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message==WM_NCPAINT || message==WM_SIZE)
	{
		BOOL bMax;
		CMDIFrameWnd* pParentFrame = (CMDIFrameWnd*)GetParentFrame();
		if(pParentFrame)
		{
			CMDIChildWnd* pChildFrame = pParentFrame->MDIGetActive(&bMax);
			if(bMax)
			{	
				if(message==WM_NCPAINT) // non client area
					return 0;
				
				if(message==WM_SIZE) // client area
				{
					if(pChildFrame==this && (wParam==SIZE_MAXIMIZED  || wParam==SIZE_RESTORED))// active and maximized
						return CMDIChildWnd::WindowProc(message, wParam, lParam);

					SetRedraw(FALSE);
					LRESULT ret = CMDIChildWnd::WindowProc(message, wParam, lParam);
					SetRedraw();
					return  ret;
				}
			}
		}
	}
	return CMDIChildWnd::WindowProc(message, wParam, lParam);
}

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}
