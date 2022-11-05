
// UDPServerSocketDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ListenSocket.h"

// CUDPServerSocketDlg �Ի���
class CUDPServerSocketDlg : public CDialogEx
{
// ����
public:
	CUDPServerSocketDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UDPServerSocket_DIALOG };

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
	afx_msg void OnBnClickedBtnSend();
	DECLARE_MESSAGE_MAP()
public:
	int m_nPort;
	CListBox m_lstContent;	
	CString m_strText2Send;
	CUDPSocket* m_pSocket;
};
