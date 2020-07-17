
// ServerSocketDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerSocket.h"
#include "ServerSocketDlg.h"
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


// CServerSocketDlg 对话框



CServerSocketDlg::CServerSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerSocketDlg::IDD, pParent)
	, m_nPort(5678)
	, m_strBroadcast(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_LIST_Content, m_lstContent);
	DDX_Text(pDX, IDC_EDIT_Broadcast, m_strBroadcast);
}

BEGIN_MESSAGE_MAP(CServerSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_STARTLISTEN, &CServerSocketDlg::OnBnClickedButtonStartlisten)
	ON_MESSAGE(WM_SOCKET_ACCEPT_CLIENT,&CServerSocketDlg::OnClientConnectIn)
	ON_MESSAGE(WM_SOCKET_RECEIVE_MSG,&CServerSocketDlg::OnReveiveClientMessage)
	ON_BN_CLICKED(ID_BTN_RESET, &CServerSocketDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(ID_BTN_Broadcast, &CServerSocketDlg::OnBnClickedBtnBroadcast)
END_MESSAGE_MAP()


// CServerSocketDlg 消息处理程序

BOOL CServerSocketDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CServerSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerSocketDlg::OnPaint()
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
HCURSOR CServerSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerSocketDlg::OnBnClickedButtonStartlisten()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_pSocket = new CListenSocket(m_nPort,this->m_hWnd);
	BOOL bRet = m_pSocket->Create(m_nPort);
	if (!bRet)
	{
		char szError[256] = {0};
		sprintf(szError, "Create Faild: %d", GetLastError());
		MessageBox(szError);
		return;
	}

	bRet = m_pSocket->Listen(10);
	if (!bRet)
	{
		char szError[256] = {0};
		sprintf(szError, "Listen Faild: %d", GetLastError());
		MessageBox(szError);
		return;
	}

	GetDlgItem(ID_BUTTON_STARTLISTEN)->EnableWindow(FALSE);	
}


HRESULT CServerSocketDlg::OnClientConnectIn(WPARAM w, LPARAM l)
{
	char* s = (char*)w;
	m_lstContent.AddString(s);
	UpdateData(FALSE);
	return 0L;
}


HRESULT CServerSocketDlg::OnReveiveClientMessage(WPARAM w, LPARAM l)
{
	char* s = (char*)w;
	m_lstContent.AddString(s);
	UpdateData(FALSE);
	return 0L;
}


void CServerSocketDlg::OnBnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pSocket->Close();
	delete m_pSocket;
	m_pSocket = NULL;

	m_lstContent.ResetContent();
	m_strBroadcast = "";
	GetDlgItem(ID_BUTTON_STARTLISTEN)->EnableWindow(TRUE);	
}


void CServerSocketDlg::OnBnClickedBtnBroadcast()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
   map<CSocket*,CSocket*>& mapClient = m_pSocket->GetClient();
   for (map<CSocket*,CSocket*>::iterator it = mapClient.begin();it != mapClient.end();it++ )
   {
	   CSocket* pSock = it->first;
	   int nRet = pSock->Send(m_strBroadcast.GetBuffer(0),m_strBroadcast.GetLength());  
	   if (-1 == nRet)
	   {
		   char szError[256] = {0};
		   sprintf(szError, "Send Faild: %d", GetLastError());
		   MessageBox(szError);
		   return;
	   }
   }
}
