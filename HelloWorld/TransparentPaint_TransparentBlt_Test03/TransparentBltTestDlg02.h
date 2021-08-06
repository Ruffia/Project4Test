#pragma once


// CTransparentBltTestDlg02 对话框

class CTransparentBltTestDlg02 : public CDialogEx
{
	DECLARE_DYNAMIC(CTransparentBltTestDlg02)

public:
	CTransparentBltTestDlg02(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTransparentBltTestDlg02();

// 对话框数据
	enum { IDD = IDD_TRANSPARENTPAINT_TRANSPARENTBLT_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnTest02();
};
