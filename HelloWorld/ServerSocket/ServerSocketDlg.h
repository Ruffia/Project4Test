
// ServerSocketDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "ListenSocket.h"

// CServerSocketDlg 对话框
class CServerSocketDlg : public CDialogEx
{
// 构造
public:
	CServerSocketDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVERSOCKET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonStartlisten();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HRESULT OnClientConnectIn(WPARAM w, LPARAM l);
	afx_msg HRESULT OnReveiveClientMessage(WPARAM w, LPARAM l);
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnBroadcast();
	DECLARE_MESSAGE_MAP()
public:
	int m_nPort;
	CListBox m_lstContent;	
	CString m_strBroadcast;
	CListenSocket* m_pSocket;
};
