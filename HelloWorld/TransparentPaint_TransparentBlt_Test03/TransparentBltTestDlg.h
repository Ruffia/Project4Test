#pragma once
#include "afxwin.h"
#include "TransparentImage.h"


// CTransparentBltTestDlg �Ի���

class CTransparentBltTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTransparentBltTestDlg)

public:
	CTransparentBltTestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTransparentBltTestDlg();

// �Ի�������
	enum { IDD = IDD_TRANSPARENTPAINT_TRANSPARENTBLT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedBtnTest();

	DECLARE_MESSAGE_MAP()
public:
	CTransparentImage m_bmpStatic;
	CButton m_btnTest;
};
