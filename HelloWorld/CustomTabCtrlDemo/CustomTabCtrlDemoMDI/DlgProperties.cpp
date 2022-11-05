// DlgProperties.cpp : implementation file
//

#include "stdafx.h"
#include "customtabctrldemomdi.h"
#include "DlgProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProperties dialog


CDlgProperties::CDlgProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProperties)
	//}}AFX_DATA_INIT
}


void CDlgProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProperties)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProperties, CDialog)
	//{{AFX_MSG_MAP(CDlgProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProperties message handlers

BOOL CDlgProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_LABELED)->SetWindowText(m_sLabel);
	GetDlgItem(IDC_TOOLTIPED)->SetWindowText(m_sTooltip);
	GetDlgItem(IDC_URLED)->SetWindowText(m_sUrl);
	return TRUE;
}

void CDlgProperties::OnOK() 
{
	GetDlgItem(IDC_LABELED)->GetWindowText(m_sLabel);
	GetDlgItem(IDC_TOOLTIPED)->GetWindowText(m_sTooltip);
	GetDlgItem(IDC_URLED)->GetWindowText(m_sUrl);
	CDialog::OnOK();
}
