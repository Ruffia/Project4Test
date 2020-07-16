
// GetDeviceCapsDlg.cpp : 实现文件
//

#include "stdafx.h"
 #include <math.h> 
#include <WinUser.h>
#include "GetDeviceCaps.h"
#include "GetDeviceCapsDlg.h"
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


// CGetDeviceCapsDlg 对话框



CGetDeviceCapsDlg::CGetDeviceCapsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetDeviceCapsDlg::IDD, pParent)
	, m_nWidth(0)
	, m_nHeight(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetDeviceCapsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Width, m_nWidth);
	DDX_Text(pDX, IDC_EDIT_Height, m_nHeight);
}

BEGIN_MESSAGE_MAP(CGetDeviceCapsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGetDeviceCapsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_DEBUG, &CGetDeviceCapsDlg::OnBnClickedButtonDebug)
	ON_BN_CLICKED(IDC_BUTTON_INCH, &CGetDeviceCapsDlg::OnBnClickedButtonInch)
END_MESSAGE_MAP()


// CGetDeviceCapsDlg 消息处理程序

BOOL CGetDeviceCapsDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGetDeviceCapsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetDeviceCapsDlg::OnPaint()
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
HCURSOR CGetDeviceCapsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGetDeviceCapsDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	HDC hScreenDC = ::GetDC(NULL);
	::SetMapMode(hScreenDC,MM_LOMETRIC);
	int hSizeInPixel = ::GetDeviceCaps(hScreenDC,HORZSIZE);
	int vSizeInPixel=::GetDeviceCaps(hScreenDC,VERTSIZE);
	m_nWidth = hSizeInPixel;
	m_nHeight = vSizeInPixel;
	UpdateData(FALSE);
	POINT pt={hSizeInPixel,vSizeInPixel};
	BOOL b = ::DPtoLP(hScreenDC,&pt,1);

	HDC desktopDc = ::GetDC(NULL);
	// Get native resolution
    int horizontalDPI = ::GetDeviceCaps(desktopDc,LOGPIXELSX);
	int verticalDPI = ::GetDeviceCaps(desktopDc,LOGPIXELSY);

	::ReleaseDC(NULL,hScreenDC);
	::ReleaseDC(NULL,desktopDc);
}


void CGetDeviceCapsDlg::OnBnClickedButtonDebug()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加额外的初始化代码
	HWND hd = ::GetDesktopWindow();	
	// 方法一	
	RECT rect;	
	// 只获得窗口客户区的大小	
	::GetClientRect(hd, &rect);	
	int client_width = (rect.right - rect.left);	
	int client_height = (rect.bottom - rect.top);	
	// 获取到的是窗口在屏幕上的位置	
	::GetWindowRect(hd, &rect);	
	int window_width = (rect.right - rect.left);	
	int window_height = (rect.bottom - rect.top);	


	// 方法二	
	// 不带菜单栏的大小	
	int no_menu_bar_width = GetSystemMetrics(SM_CXFULLSCREEN);	
	int no_menu_bar__height = GetSystemMetrics(SM_CYFULLSCREEN);

	// 带标题栏和菜单栏	
	int have_menu_bar_width = GetSystemMetrics(SM_CXSCREEN);	
	int have_menu_bar_height = GetSystemMetrics(SM_CYSCREEN); 	

	//方法三	
	HDC hdc = ::GetDC(NULL);                           
	// 得到屏幕DC  	
	client_width = GetDeviceCaps(hdc, HORZRES);      
	// 宽  	
	client_height = GetDeviceCaps(hdc, VERTRES);     
	// 高   	
	::ReleaseDC(NULL, hdc);   
	// 释放DC	

	//方法四	
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, SPIF_SENDCHANGE);	
	client_width = (rect.right - rect.left);	
	client_height = (rect.bottom - rect.top);		

	//方法五	
	hdc = ::GetDC(NULL);	
	client_width = GetDeviceCaps(hdc, DESKTOPHORZRES);	
	client_height = GetDeviceCaps(hdc, DESKTOPVERTRES);	
	::ReleaseDC(NULL, hdc);

	{
		HWND hd = ::GetDesktopWindow();
		//int zoom = ::GetDpiForWindow(hd);
	}

}


void CGetDeviceCapsDlg::OnBnClickedButtonInch()
{
	// TODO: 在此添加控件通知处理程序代码

	int nScreenWidth, nScreenHeight;  
	HDC hdcScreen = ::GetDC(NULL);   //获取屏幕的HDC  
	nScreenWidth = GetDeviceCaps(hdcScreen, HORZSIZE);  
	nScreenHeight = GetDeviceCaps(hdcScreen, VERTSIZE);  

	const double MILLIMETRE_TO_INCH = 0.03937;  
	double fDiagonalLen = sqrt((double(nScreenHeight * nScreenHeight + nScreenWidth * nScreenWidth)));
	float fInch = fDiagonalLen * MILLIMETRE_TO_INCH; 

	float f = sqrt(double((448 - 16)*(448 - 16) + (257 - 16)*(257 - 16)));
	float fInch2 = f * MILLIMETRE_TO_INCH;

}
