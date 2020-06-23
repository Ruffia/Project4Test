
// ClientSocketDlg.h : 头文件
//

#pragma once
#include "Resource.h"
#include "ConnSocket.h"

// CClientSocketDlg 对话框
class CClientSocketDlg : public CDialogEx
{
// 构造
public:
	CClientSocketDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENTSOCKET_DIALOG };

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
	afx_msg void OnBnClickedBtnconnect();
	afx_msg void OnBnClickedBtnreset();
	afx_msg void OnBnClickedBtnsend();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strServerIP;
	int m_nPort;
	CString m_strTxt2Send;
	CConnSocket* m_pSocket;

public:
	void OnReceive(CString sText);
	void OnConnect(bool bConnect);
};
