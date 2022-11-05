// DialogChild.cpp : 实现文件
//

#include "stdafx.h"
#include "WindowPos.h"
#include "DialogChild.h"
#include "afxdialogex.h"


// CDialogChild 对话框

IMPLEMENT_DYNAMIC(CDialogChild, CDialog)

CDialogChild::CDialogChild(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogChild::IDD, pParent)
{

}

CDialogChild::~CDialogChild()
{
}

void CDialogChild::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogChild, CDialog)
END_MESSAGE_MAP()


// CDialogChild 消息处理程序
