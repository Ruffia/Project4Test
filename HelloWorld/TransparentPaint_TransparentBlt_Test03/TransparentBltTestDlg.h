#pragma once
#include "afxwin.h"
#include "TransparentImage.h"


// CTransparentBltTestDlg 对话框

class CTransparentBltTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTransparentBltTestDlg)

public:
	CTransparentBltTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTransparentBltTestDlg();

// 对话框数据
	enum { IDD = IDD_TRANSPARENTPAINT_TRANSPARENTBLT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedBtnTest();

	DECLARE_MESSAGE_MAP()
public:
	CTransparentImage m_bmpStatic;
	CButton m_btnTest;
};
