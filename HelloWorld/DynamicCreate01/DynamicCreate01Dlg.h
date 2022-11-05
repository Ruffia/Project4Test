
// DynamicCreate01Dlg.h : 头文件
//

#pragma once


// CDynamicCreate01Dlg 对话框
class CDynamicCreate01Dlg : public CDialogEx
{
// 构造
public:
	CDynamicCreate01Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DYNAMICCREATE01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void _CreateButton();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();

	void _DrawCircle();

	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonClick(UINT uID);
	DECLARE_MESSAGE_MAP()
};
