
// ClientSocketAutoReconnectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientSocketAutoReconnect.h"
#include "ClientSocketAutoReconnectDlg.h"
#include "ReconnectThread.h"
#include "afxdialogex.h"

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


// CClientSocketDlg 对话框



CClientSocketAutoReconnectDlg::CClientSocketAutoReconnectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientSocketAutoReconnectDlg::IDD, pParent)
	, m_strServerIP(_T("127.0.0.1"))
	, m_nPort(3000)
	, m_strTxt2Send(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSocket = new CConnSocket(this);
}

void CClientSocketAutoReconnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IP, m_strServerIP);
	DDV_MaxChars(pDX, m_strServerIP, 128);
	DDX_Text(pDX, IDC_Port, m_nPort);
	DDX_Text(pDX, IDC_Txt2Send, m_strTxt2Send);
	DDV_MaxChars(pDX, m_strTxt2Send, 2048);
	DDX_Control(pDX, IDC_LIST_RECV, m_lstRecv);
}

BEGIN_MESSAGE_MAP(CClientSocketAutoReconnectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnConnect, &CClientSocketAutoReconnectDlg::OnBnClickedBtnconnect)
	ON_BN_CLICKED(IDC_BtnReset, &CClientSocketAutoReconnectDlg::OnBnClickedBtnreset)
	ON_BN_CLICKED(IDC_BtnSend, &CClientSocketAutoReconnectDlg::OnBnClickedBtnsend)
	ON_BN_CLICKED(IDOK, &CClientSocketAutoReconnectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CClientSocketAutoReconnectDlg 消息处理程序

BOOL CClientSocketAutoReconnectDlg::OnInitDialog()
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
	WSADATA wsaData;
	int nRet  = WSAStartup(MAKEWORD(2,2),&wsaData);
	if(nRet != 0)
	{
		TRACE("WSAStartup failed");
		return FALSE;
	}

	UpdateData(FALSE);
	OnConnect(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientSocketAutoReconnectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientSocketAutoReconnectDlg::OnPaint()
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
HCURSOR CClientSocketAutoReconnectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientSocketAutoReconnectDlg::OnReceive(CString sText)
{
	m_lstRecv.AddString(sText);
	UpdateData(FALSE);
}

void CClientSocketAutoReconnectDlg::OnConnect(bool bConnect)
{
	GetDlgItem(IDC_BtnConnect)->EnableWindow(!bConnect);
	GetDlgItem(IDC_BtnReset)->EnableWindow(bConnect);
	GetDlgItem(IDC_BtnSend)->EnableWindow(bConnect);
}

void CClientSocketAutoReconnectDlg::OnBnClickedBtnconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CSocketConnector::Instance().Init(m_hWnd,m_strServerIP.GetBuffer(),m_nPort);
	OnConnect(TRUE);
	CSocketConnector::Instance().Start();
}


void CClientSocketAutoReconnectDlg::OnBnClickedBtnreset()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_pSocket) return;
	m_pSocket->Close();
	m_strTxt2Send = "";
	UpdateData(FALSE);
}


void CClientSocketAutoReconnectDlg::OnBnClickedBtnsend()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_pSocket) return;
	UpdateData(TRUE);

	char* src =(LPSTR)(LPCTSTR)m_strTxt2Send;
	char* sz = new char[1024];
	memcpy(sz,src,strlen(src)+ 1);
	int nRet = m_pSocket->Send(m_strTxt2Send.GetBuffer(0),m_strTxt2Send.GetLength());
	if (-1 == nRet)
	{
		char szError[256] = {0};
		sprintf_s(szError, 256,"Send Faild: %d", GetLastError());
		MessageBox(szError);
		return;
	}
}


void CClientSocketAutoReconnectDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}