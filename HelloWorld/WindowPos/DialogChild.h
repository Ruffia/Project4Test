#pragma once


// CDialogChild �Ի���

class CDialogChild : public CDialog
{
	DECLARE_DYNAMIC(CDialogChild)

public:
	CDialogChild(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogChild();

// �Ի�������
	enum { IDD = IDD_DIALOG_Child };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
