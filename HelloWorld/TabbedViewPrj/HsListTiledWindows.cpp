// HsListTiledWindows.cpp : implementation file
//

#include "stdafx.h"
#include "TabbedViewPrj.h"
#include "HsListTiledWindows.h"

#include "MainFrm.h"




// HsListTiledWindows dialog

IMPLEMENT_DYNAMIC(HsListTiledWindows, CDialog)

HsListTiledWindows::HsListTiledWindows(CWnd* pParent /*=NULL*/)
	: CDialog(HsListTiledWindows::IDD, pParent)
{

}

HsListTiledWindows::~HsListTiledWindows()
{
}

void HsListTiledWindows::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TILEDWINDOWS, m_listTiledWnds);
	DDX_Control(pDX, IDOK, m_btnOk);
}


BEGIN_MESSAGE_MAP(HsListTiledWindows, CDialog)
	ON_BN_CLICKED(IDOK, &HsListTiledWindows::OnBnClickedOk)
	ON_WM_KILLFOCUS()
	ON_WM_SHOWWINDOW()
	ON_CLBN_CHKCHANGE(IDC_LIST_TILEDWINDOWS, &HsListTiledWindows::OnCheckchangeListTiledWindows)
	ON_LBN_SELCHANGE(IDC_LIST_TILEDWINDOWS, &HsListTiledWindows::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// HsListTiledWindows message handlers

void HsListTiledWindows::OnBnClickedOk()
{
	AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_WINDOW_TILE, 0);
	OnOK();
}

BOOL HsListTiledWindows::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_btnOk.setType(HsButton::hotPushButton);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void HsListTiledWindows::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here
}

void HsListTiledWindows::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	HsMDIClient* pWndMDIClient = ((CMainFrame*)AfxGetMainWnd())->GetMDIClient();
	
	m_listTiledWnds.ResetContent();
	for(int i = 0; i < pWndMDIClient->m_arrayViews.GetSize(); i++)
	{
		m_listTiledWnds.AddString(pWndMDIClient->m_arrayViews[i]->GetDocument()->GetTitle());
		for(int index = 0; index < pWndMDIClient->m_arrayTiledViews.GetSize(); index++)
		{
			if(pWndMDIClient->m_arrayViews[i] == pWndMDIClient->m_arrayTiledViews[index])
			{
				m_listTiledWnds.SetCheck(i, 1);
				break;
			}
		}
	}

	// TODO: Add your message handler code here
}

void HsListTiledWindows::OnLbnSelchangeList2()
{
	// TODO: Add your control notification handler code here
}

void HsListTiledWindows::OnCheckchangeListTiledWindows() 
{
	// TODO: Add your control notification handler code here
	HsMDIClient* pWndMDIClient = ((CMainFrame*)AfxGetMainWnd())->GetMDIClient();
	pWndMDIClient->UpdateTileInfo(false);
		
}