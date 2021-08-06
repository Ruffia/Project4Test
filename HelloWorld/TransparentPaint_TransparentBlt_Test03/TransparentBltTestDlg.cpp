// TransparentBltTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TransparentPaint_TransparentBlt_Test03.h"
#include "TransparentBltTestDlg.h"
#include "afxdialogex.h"


// CTransparentBltTestDlg 对话框

IMPLEMENT_DYNAMIC(CTransparentBltTestDlg, CDialogEx)

CTransparentBltTestDlg::CTransparentBltTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTransparentBltTestDlg::IDD, pParent)
{

}

CTransparentBltTestDlg::~CTransparentBltTestDlg()
{
}

void CTransparentBltTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TransparentImage, m_bmpStatic);
	DDX_Control(pDX, IDC_BTN_Test, m_btnTest);
}


BEGIN_MESSAGE_MAP(CTransparentBltTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_Test, &CTransparentBltTestDlg::OnBnClickedBtnTest)
END_MESSAGE_MAP()


// CTransparentBltTestDlg 消息处理程序


void CTransparentBltTestDlg::OnBnClickedBtnTest()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("AAAAA"));
}
