// TransparentBltTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TransparentPaint_TransparentBlt_Test03.h"
#include "TransparentBltTestDlg.h"
#include "afxdialogex.h"


// CTransparentBltTestDlg �Ի���

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


// CTransparentBltTestDlg ��Ϣ�������


void CTransparentBltTestDlg::OnBnClickedBtnTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("AAAAA"));
}
