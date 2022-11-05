
// UDPServerSocketDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDPServerSocket.h"
#include "UDPServerSocketDlg.h"
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


// CUDPServerSocketDlg 对话框



CUDPServerSocketDlg::CUDPServerSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDPServerSocketDlg::IDD, pParent)
	, m_nPort(5678)
	, m_strText2Send(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDPServerSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_LIST_Content, m_lstContent);
	DDX_Text(pDX, IDC_EDIT_Broadcast, m_strText2Send);
}

BEGIN_MESSAGE_MAP(CUDPServerSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_STARTLISTEN, &CUDPServerSocketDlg::OnBnClickedButtonStartlisten)
	ON_MESSAGE(WM_SOCKET_ACCEPT_CLIENT,&CUDPServerSocketDlg::OnClientConnectIn)
	ON_MESSAGE(WM_SOCKET_RECEIVE_MSG,&CUDPServerSocketDlg::OnReveiveClientMessage)
	ON_BN_CLICKED(ID_BTN_RESET, &CUDPServerSocketDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(ID_BTN_Send, &CUDPServerSocketDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CUDPServerSocketDlg 消息处理程序

BOOL CUDPServerSocketDlg::OnInitDialog()
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

void CUDPServerSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUDPServerSocketDlg::OnPaint()
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
HCURSOR CUDPServerSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUDPServerSocketDlg::OnBnClickedButtonStartlisten()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_pSocket = new CUDPSocket(m_hWnd);
	BOOL bRet = m_pSocket->Create(AF_INET,SOCK_DGRAM,0);
	if(!bRet)
	{
		return;
	}

	SOCKADDR_IN addrSrv ;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY) ;
	addrSrv.sin_family = AF_INET ;
	addrSrv.sin_port = htons(m_nPort) ;
	m_pSocket->Bind((SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	if (!bRet)
	{
		char szError[256] = {0};
		sprintf(szError, "Create Faild: %d", GetLastError());
		MessageBox(szError);
		return;
	}

	GetDlgItem(ID_BUTTON_STARTLISTEN)->EnableWindow(FALSE);	
}


HRESULT CUDPServerSocketDlg::OnClientConnectIn(WPARAM w, LPARAM l)
{
	char* s = (char*)w;
	m_lstContent.AddString(s);
	UpdateData(FALSE);
	return 0L;
}


HRESULT CUDPServerSocketDlg::OnReveiveClientMessage(WPARAM w, LPARAM l)
{
	char* s = (char*)w;
	m_lstContent.AddString(s);
	UpdateData(FALSE);
	return 0L;
}


void CUDPServerSocketDlg::OnBnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pSocket->Close();
	delete m_pSocket;
	m_pSocket = NULL;

	m_lstContent.ResetContent();
	m_strText2Send = "";
	GetDlgItem(ID_BUTTON_STARTLISTEN)->EnableWindow(TRUE);	
}


void CUDPServerSocketDlg::OnBnClickedBtnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_pSocket->SendTo(m_strText2Send,m_strText2Send.GetLength(),6900,"127.0.0.1",0);
}
