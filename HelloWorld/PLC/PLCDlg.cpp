
// PLCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PLC.h"
#include "PLCDlg.h"
#include "afxdialogex.h"
#include "BaseCommand.h"
#include "Factory.h"
#include <string>
#include "OperateCommandBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPLCDlg 对话框



CPLCDlg::CPLCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPLCDlg::IDD, pParent)
	, m_strServerIP(_T("127.0.0.1"))
	, m_nPort(5678)
	, m_strTxt2Send(_T(""))
	, m_strCurCmd("")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSocket = new CCommSocket();
	m_pCommThread = new CPLCResponseReceiveThread(m_pSocket);
	m_pQueryCommandThread = NULL;
}

CPLCDlg::~CPLCDlg()
{
	if (m_pSocket)
	{
		delete m_pSocket;
	}

	if (m_pCommThread)
	{
		m_pCommThread->End();
		delete m_pCommThread;
		m_pCommThread = NULL;
	}
}

void CPLCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IP, m_strServerIP);
	DDV_MaxChars(pDX, m_strServerIP, 128);
	DDX_Text(pDX, IDC_Port, m_nPort);
	DDX_Text(pDX, IDC_Txt2Send, m_strTxt2Send);
	DDV_MaxChars(pDX, m_strTxt2Send, 2048);
	DDX_Control(pDX, IDC_LIST_RECV, m_lstRecv);
	DDX_Control(pDX, IDC_COMBO_Wafer, m_comboxWafer);
}

BEGIN_MESSAGE_MAP(CPLCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnConnect, &CPLCDlg::OnBnClickedBtnconnect)
	ON_BN_CLICKED(IDC_BtnReset, &CPLCDlg::OnBnClickedBtnreset)
	ON_BN_CLICKED(IDC_BtnSend, &CPLCDlg::OnBnClickedBtnsend)
	ON_BN_CLICKED(IDOK, &CPLCDlg::OnBnClickedOk)
	ON_MESSAGE(WM_PLC_THREAD_DATA, &CPLCDlg::OnReceiveDataFromPLC)
	ON_MESSAGE(WM_PLC_THREAD_DATA, &CPLCDlg::OnReceiveDataFromQueryThread)
	ON_BN_CLICKED(IDC_Btn_Motor_Power_On, &CPLCDlg::OnBnClickedBtnMotorPowerOn)
	ON_BN_CLICKED(IDC_Btn_SendWafer_Initial, &CPLCDlg::OnBnClickedBtnSendwaferInitial)
	ON_BN_CLICKED(IDC_Btn_TakingWafer, &CPLCDlg::OnBnClickedBtnTakingwafer)
	ON_BN_CLICKED(IDC_Btn_Motor_Enable, &CPLCDlg::OnBnClickedBtnMotorEnable)
	ON_BN_CLICKED(IDC_Btn_Position_parameter_Req, &CPLCDlg::OnBnClickedBtnPositionparameterReq)
END_MESSAGE_MAP()


// CPLCDlg 消息处理程序

BOOL CPLCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_comboxWafer.ResetContent();
	for (int i = 1;i< 12;i++)
	{
		CString strNumber = _T("");
		strNumber.Format("%d",i);
		m_comboxWafer.AddString(strNumber);
	}

	m_comboxWafer.SetCurSel(0);
	UpdateData(FALSE);
	OnConnect(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPLCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPLCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPLCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPLCDlg::OnReceive(CString sText)
{
	m_lstRecv.AddString(sText);
	//UpdateData(FALSE);
}

void CPLCDlg::OnConnect(bool bConnect)
{
	GetDlgItem(IDC_BtnConnect)->EnableWindow(!bConnect);
	GetDlgItem(IDC_BtnReset)->EnableWindow(bConnect);
	GetDlgItem(IDC_BtnSend)->EnableWindow(bConnect);
}

void CPLCDlg::OnBnClickedBtnconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_pSocket->Init(m_strServerIP,m_nPort);
	m_pCommThread->Attach(m_hWnd);
	m_pCommThread->Start();
	OnConnect(true);
}


void CPLCDlg::OnBnClickedBtnreset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strTxt2Send = "";
	UpdateData(FALSE);
}


void CPLCDlg::OnBnClickedBtnsend()
{
	// TODO: 在此添加控件通知处理程序代码
	//if(!m_pSocket) return;
	//UpdateData(TRUE);

	//char* src =(LPSTR)(LPCTSTR)m_strTxt2Send;
	//char* sz = new char[1024];
	//memcpy(sz,src,strlen(src)+ 1);
	//int nRet = m_pSocket->Send(m_strTxt2Send.GetBuffer(0),m_strTxt2Send.GetLength());
	//if (-1 == nRet)
	//{
	//	char szError[256] = {0};
	//	sprintf_s(szError, 256,"Send Faild: %d", GetLastError());
	//	MessageBox(szError);
	//	return;
	//}

	IPLCCommand* pCommand = Factory<IPLCCommand,std::string>::Instance().BuildProduct("SendWafer_Cassette2PA");
	if (!pCommand) return;
	pCommand->BuildCommand();
	char* sCommand = pCommand->GetCommand();

	CString strCommand   =   (CString)(LPCTSTR)sCommand; 
	_AppendTimePrefix(strCommand);
	m_lstRecv.AddString(strCommand);

	//byte a = 0xAF;
	//byte* pCommd = new byte[4];
	//pCommd[0] = 0xA0;
	//pCommd[1] = 0xA1;
	//pCommd[2] = 0x13;
	//pCommd[3] = 0x88;
	int nRet = m_pSocket->Send(pCommand->m_pCommand);
	if (-1 == nRet)
	{
		char szError[256] = {0};
		sprintf_s(szError, 256,"Send Faild: %d", GetLastError());
		MessageBox(szError);
		return;
	}

	delete pCommand;
	pCommand = NULL;
}


void CPLCDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


LRESULT CPLCDlg::OnReceiveDataFromPLC(WPARAM wParam, LPARAM lParam)
{
	byte* bData = (byte*)(char*)(WPARAM)wParam;
	int nLen = (int)lParam;
	CString sMsg = _T("");
	for (int i = 0; i < nLen;i++)
	{
		CString sByte = _T("");
		sByte.Format(_T("%X "), bData[i]);
		sMsg += sByte;
	}

	if (m_strCurCmd == "SendWafer_Initial")
	{
		if (m_pQueryCommand && m_pQueryCommandThread)
		{
			m_pQueryCommand->m_pResp = bData;
			m_pQueryCommandThread->m_bTaskDone = m_pQueryCommand->CheckResponse();
			if (m_pQueryCommandThread->m_bTaskDone)
			{
				Sleep(200);
				m_pQueryCommandThread->End();
				delete m_pQueryCommandThread;
				m_pQueryCommandThread = NULL;

				m_strCurCmd = "SendWafer_PAReady";
				_SendCommand("m_strCurCmd");
			}
		}
	}

	delete bData;
	bData = NULL;
	
	_AppendTimePrefix(sMsg);
	OnReceive(sMsg);
	return 0L;
}


LRESULT CPLCDlg::OnReceiveDataFromQueryThread(WPARAM wParam, LPARAM lParam)
{
	byte* bData = (byte*)(char*)(WPARAM)wParam;
	int nLen = (int)lParam;
	CString sMsg = _T("");
	for (int i = 0; i < nLen;i++)
	{
		CString sByte = _T("");
		sByte.Format(_T("%X "), bData[i]);
		sMsg += sByte;
	}

	delete bData;
	bData = NULL;

	_AppendTimePrefix(sMsg);
	OnReceive(sMsg);
	return 0L;
}


void CPLCDlg::_AppendTimePrefix( CString& strCommand ) 
{
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	strDate.Format("%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
	strTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);

	strCommand = strDate + " " + strTime + "  " + strCommand;
}


void CPLCDlg::_SendCommand(const std::string strCmd )
{
	IPLCCommand* pCommand = Factory<IPLCCommand,std::string>::Instance().BuildProduct(strCmd);
	if (!pCommand) return;
	pCommand->BuildCommand();
	char* sCommand = pCommand->GetCommand();

	CString strCommand   =   (CString)(LPCTSTR)sCommand; 
	_AppendTimePrefix(strCommand);
	m_lstRecv.AddString(strCommand);

	int nRet = m_pSocket->Send(pCommand->m_pCommand);
	if (-1 == nRet)
	{
		char szError[256] = {0};
		sprintf_s(szError, 256,"Send Faild: %d", GetLastError());
		MessageBox(szError);
		return;
	}

	_CheckQueyCommand(pCommand);

	delete pCommand;
	pCommand = NULL;
}


void CPLCDlg::OnBnClickedBtnMotorPowerOn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strCurCmd = "Motor_Power_On";
	_SendCommand(m_strCurCmd);
}


void CPLCDlg::OnBnClickedBtnMotorEnable()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strCurCmd = "Motor_Enable";
	_SendCommand(m_strCurCmd);
}


void CPLCDlg::OnBnClickedBtnPositionparameterReq()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strCurCmd = "Position parameter_Req";
	_SendCommand(m_strCurCmd);
}


void CPLCDlg::OnBnClickedBtnSendwaferInitial()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strCurCmd = "SendWafer_Initial";
	_SendCommand(m_strCurCmd);
}


void CPLCDlg::OnBnClickedBtnTakingwafer()
{
	// TODO: 在此添加控件通知处理程序代码
	int nPos = ((CComboBox*)GetDlgItem(IDC_COMBO_Wafer))->GetCurSel();
	CString strWaferNumber = _T("");
	strWaferNumber.Format("%d",nPos + 1);
	strWaferNumber = "TakingWafer_" + strWaferNumber;
	std::string strCmd(strWaferNumber.GetBuffer(0));
	_SendCommand(strCmd);
}


void CPLCDlg::_CheckQueyCommand( IPLCCommand* pCommand )
{
	COperateCommandBase* pOperateCommand = dynamic_cast<COperateCommandBase*>(pCommand);
	if(pOperateCommand)
	{
		m_pQueryCommand = pOperateCommand->m_pQueryCommand;
		m_pQueryCommandThread = new CPLCQueryCommandThread(m_pSocket,m_pQueryCommand);
		m_pQueryCommandThread->Start();
	}
}


