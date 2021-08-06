// TransparentBltTestDlg02.cpp : 实现文件
//

#include "stdafx.h"
#include "TransparentPaint_TransparentBlt_Test03.h"
#include "TransparentBltTestDlg02.h"
#include "afxdialogex.h"


// CTransparentBltTestDlg02 对话框

IMPLEMENT_DYNAMIC(CTransparentBltTestDlg02, CDialogEx)

CTransparentBltTestDlg02::CTransparentBltTestDlg02(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTransparentBltTestDlg02::IDD, pParent)
{

}

CTransparentBltTestDlg02::~CTransparentBltTestDlg02()
{
}

void CTransparentBltTestDlg02::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTransparentBltTestDlg02, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_Test02, &CTransparentBltTestDlg02::OnBnClickedBtnTest02)
END_MESSAGE_MAP()


// CTransparentBltTestDlg02 消息处理程序


void CTransparentBltTestDlg02::OnBnClickedBtnTest02()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("Test02"));
}
