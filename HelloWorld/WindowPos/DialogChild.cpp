// DialogChild.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WindowPos.h"
#include "DialogChild.h"
#include "afxdialogex.h"


// CDialogChild �Ի���

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


// CDialogChild ��Ϣ�������
