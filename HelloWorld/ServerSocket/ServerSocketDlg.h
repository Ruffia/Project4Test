
// ServerSocketDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ListenSocket.h"

// CServerSocketDlg �Ի���
class CServerSocketDlg : public CDialogEx
{
// ����
public:
	CServerSocketDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVERSOCKET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
