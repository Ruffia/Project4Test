
// PLCDlg.h : 头文件
//

#pragma once
#include <string>
#include "Resource.h"
#include "afxwin.h"
#include "CommSocket.h"
#include "PLCResponseReceiveThread.h"
#include "PLCQueryCommandThread.h"


// CPLCDlg 对话框
class CPLCDlg : public CDialogEx
{
// 构造
public:
	CPLCDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CPLCDlg();

// 对话框数据
	enum { IDD = IDD_PLC_DIALOG };

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
	afx_msg LRESULT OnReceiveDataFromPLC(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveDataFromQueryThread(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnMotorPowerOn();
	afx_msg void OnBnClickedBtnMotorEnable();
	afx_msg void OnBnClickedBtnPositionparameterReq();
	afx_msg void OnBnClickedBtnSendwaferInitial();
	afx_msg void OnBnClickedBtnTakingwafer();
	afx_msg void OnBnClickedButtonCassette2PA();
	afx_msg void OnBnClickedButtonLaywaferOnPA();
	afx_msg void OnBnClickedButtonG2openIn();
	afx_msg void OnBnClickedButtonG1openIn();
	afx_msg void OnBnClickedButtonStageLiftWafer();
	afx_msg void OnBnClickedButtonCV2SEM();
	afx_msg void OnBnClickedButtonReturnWafer2LoadLock();
	afx_msg void OnBnClickedButtonG2Open();
	DECLARE_MESSAGE_MAP()

public:
	void OnReceive(CString sText);
	void OnConnect(bool bConnect);

private:
	void _AppendTimePrefix(CString& strCommand,bool bSend);
	void _SendCommand( const std::string strCmd );
	void _SendCommand( const std::string strCmd,const int nValue );

	//部分操作指令需要通过循环查询的方式，根据返回的指令判断
	//操作指令执行的结果
	void _CheckQueyCommand( IPLCCommand* pCommand );

	void _CheckResponse( int nLen, byte* bData );

	//创建Log文本
	void _CreateLogFile();

	void _AddLog( char * szBuff );

public:
	//Peer IP
	CString m_strServerIP;
	//Peer Port
	int m_nPort;
	CString m_strTxt2Send;
	CListBox m_lstRecv;
	CComboBox m_comboxWafer;

	//与PLC进行通信的套接字
	CCommSocket* m_pSocket;

	//应答消息接收线程
	CPLCResponseReceiveThread*  m_pCommThread;

	//某些指令需要配合查询指令才能得到执行的结果，此次设置查询线程
	CPLCQueryCommandThread*    m_pQueryCommandThread;

	//当前正在执行的查询指令
	CQueryCommandBase*         m_pQueryCommand;

	//当前正在执行的指令
	std::string  m_strCurCmd;

	//log
	HANDLE	m_hFileLog;
	afx_msg void OnBnClickedButtonXWafertakingPositin();
	afx_msg void OnBnClickedButtonZWafertakingPositin();
	afx_msg void OnBnClickedButtonRWafertakingPositin();
	afx_msg void OnBnClickedButtonXTopaPositon();
	afx_msg void OnBnClickedButtonZTopaPositon();
	afx_msg void OnBnClickedButtonRtopaPosition();
	afx_msg void OnBnClickedButtonXToloadlockPositon();
	afx_msg void OnBnClickedButtonZToloadlockPositon();
	afx_msg void OnBnClickedButtonRToloadlockPositon();
};
