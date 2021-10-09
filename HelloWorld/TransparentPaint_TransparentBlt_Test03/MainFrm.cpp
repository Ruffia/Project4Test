
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "TransparentPaint_TransparentBlt_Test03.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (!m_dlgTransparentBltTest.Create( CTransparentBltTestDlg::IDD, this ))
	{
		return -1;       // fail to create
	}

	m_dlgTransparentBltTest.ShowWindow(SW_SHOW);

	//if (!m_dlgTransparentBltTest02.Create( CTransparentBltTestDlg02::IDD, this ))
	//{
	//	return -1;       // fail to create
	//}

	//m_dlgTransparentBltTest02.ShowWindow(SW_SHOW);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������
void CMainFrame::AdjustPanelPos()
{
	CRect rect;
	GetClientRect( &rect );
	ClientToScreen( &rect );

	CRect rcToolBar;
	m_wndToolBar.GetClientRect(&rcToolBar);

	//int nHeight = rect.bottom -rect.top;

	//m_dlgTransparentBltTest.GetClientRect( &rectCtrl );
	//ClientToScreen( &rectCtrl );
	//m_dlgTransparentBltTest.SetWindowPos(NULL,
	//	rect.right - rectCtrl.Width(),
	//	rect.top,
	//	rectCtrl.Width(),
	//	nHeight,
	//	SWP_NOZORDER );

	CRect clientRect; 
	m_dlgTransparentBltTest.GetClientRect(&clientRect); 
	m_dlgTransparentBltTest.MoveWindow(rect.right - clientRect.Width() - 5, rect.top + rcToolBar.Height() + 5, clientRect.Width(), clientRect.Height(), TRUE);

	//DWORD dwStyle = GetWindowLong(m_dlgTransparentBltTest02.m_hWnd,GWL_STYLE);
	//if(dwStyle && WS_CHILD)
	//{
	//	//dwStyle &= ~WS_CHILD;// ȥ��WS_CHILD���
	//	//dwStyle |= WS_POPUP;// ����WS_POPUP���
	//}
	//else
	//{
	//	dwStyle &= ~WS_POPUP;
	//	dwStyle |= WS_CHILD;
	//}
	//SetWindowLong(m_dlgTransparentBltTest02.m_hWnd,GWL_STYLE,dwStyle);

	//CRect clientRect02; 
	//m_dlgTransparentBltTest02.GetClientRect(&clientRect02); 
	//m_dlgTransparentBltTest02.MoveWindow(rect.right - clientRect.Width() - clientRect02.Width() - 5 - 5, rect.top + rcToolBar.Height() + 5, clientRect02.Width(), clientRect02.Height(), TRUE);
}
