#pragma once


// CTransparentBltTestDlg02 �Ի���

class CTransparentBltTestDlg02 : public CDialogEx
{
	DECLARE_DYNAMIC(CTransparentBltTestDlg02)

public:
	CTransparentBltTestDlg02(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTransparentBltTestDlg02();

// �Ի�������
	enum { IDD = IDD_TRANSPARENTPAINT_TRANSPARENTBLT_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnTest02();
};
