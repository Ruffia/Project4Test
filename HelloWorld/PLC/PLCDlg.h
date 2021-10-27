
// PLCDlg.h : ͷ�ļ�
//

#pragma once
#include <string>
#include "Resource.h"
#include "afxwin.h"
#include "CommSocket.h"
#include "PLCResponseReceiveThread.h"
#include "PLCQueryCommandThread.h"


// CPLCDlg �Ի���
class CPLCDlg : public CDialogEx
{
// ����
public:
	CPLCDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CPLCDlg();

// �Ի�������
	enum { IDD = IDD_PLC_DIALOG };

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
	afx_msg LRESULT OnReceiveDataFromPLC(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveDataFromQueryThread(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnMotorPowerOn();
	afx_msg void OnBnClickedBtnMotorEnable();
	afx_msg void OnBnClickedBtnPositionparameterReq();
	afx_msg void OnBnClickedBtnSendwaferInitial();
	afx_msg void OnBnClickedBtnTakingwafer();
	DECLARE_MESSAGE_MAP()

public:
	void OnReceive(CString sText);
	void OnConnect(bool bConnect);

private:
	void _AppendTimePrefix(CString& strCommand);
	void _SendCommand( const std::string strCmd );

	//���ֲ���ָ����Ҫͨ��ѭ����ѯ�ķ�ʽ�����ݷ��ص�ָ���ж�
	//����ָ��ִ�еĽ��
	void _CheckQueyCommand( IPLCCommand* pCommand );

public:
	//Peer IP
	CString m_strServerIP;
	//Peer Port
	int m_nPort;
	CString m_strTxt2Send;
	CListBox m_lstRecv;
	CComboBox m_comboxWafer;

	//��PLC����ͨ�ŵ��׽���
	CCommSocket* m_pSocket;

	//Ӧ����Ϣ�����߳�
	CPLCResponseReceiveThread*  m_pCommThread;

	//ĳЩָ����Ҫ��ϲ�ѯָ����ܵõ�ִ�еĽ�����˴����ò�ѯ�߳�
	CPLCQueryCommandThread*    m_pQueryCommandThread;

	//��ǰ����ִ�еĲ�ѯָ��
	CQueryCommandBase*         m_pQueryCommand;

	//��ǰ����ִ�е�ָ��
	std::string  m_strCurCmd;
};
