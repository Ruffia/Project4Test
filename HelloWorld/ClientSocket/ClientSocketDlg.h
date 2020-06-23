
// ClientSocketDlg.h : ͷ�ļ�
//

#pragma once
#include "Resource.h"
#include "ConnSocket.h"

// CClientSocketDlg �Ի���
class CClientSocketDlg : public CDialogEx
{
// ����
public:
	CClientSocketDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENTSOCKET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
