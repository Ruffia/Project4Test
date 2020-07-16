
// GetDeviceCapsDlg.h : 头文件
//

#pragma once


// CGetDeviceCapsDlg 对话框
class CGetDeviceCapsDlg : public CDialogEx
{
// 构造
public:
	CGetDeviceCapsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GETDEVICECAPS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_nWidth;
	int m_nHeight;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonDebug();
	afx_msg void OnBnClickedButtonInch();
};
