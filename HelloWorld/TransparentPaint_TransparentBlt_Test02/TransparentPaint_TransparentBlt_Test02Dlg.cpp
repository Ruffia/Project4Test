
// TransparentPaint_TransparentBlt_Test02Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TransparentPaint_TransparentBlt_Test02.h"
#include "TransparentPaint_TransparentBlt_Test02Dlg.h"
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


// CTransparentPaint_TransparentBlt_Test02Dlg 对话框



CTransparentPaint_TransparentBlt_Test02Dlg::CTransparentPaint_TransparentBlt_Test02Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTransparentPaint_TransparentBlt_Test02Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransparentPaint_TransparentBlt_Test02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TransparentImage, m_staticPneumaticDiagram);
}

BEGIN_MESSAGE_MAP(CTransparentPaint_TransparentBlt_Test02Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTransparentPaint_TransparentBlt_Test02Dlg 消息处理程序

BOOL CTransparentPaint_TransparentBlt_Test02Dlg::OnInitDialog()
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

void CTransparentPaint_TransparentBlt_Test02Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

BOOL PaintTransparentBmp(HWND hWnd,char* sImage)
{
	// 获取窗口的客户区域的显示设备上下文环境的句柄
	HDC hDC = ::GetDC(hWnd);
	// 创建一个与hDC兼容的内存设备上下文环境
	HDC hBuf = ::CreateCompatibleDC(hDC);
 
	CString strImage = CString(sImage);
	USES_CONVERSION;
	LPCWSTR wszClassName = new WCHAR[strImage.GetLength()+1];
	wcscpy((LPWSTR)wszClassName,T2W((LPWSTR)strImage.GetBuffer(NULL)));
	strImage.ReleaseBuffer();

	// 加载位图, 获取位图句柄
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL, wszClassName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 选择位图句柄到hBuf中, 并获取返回的原来位图句柄
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp);

	BITMAP bm;
	GetObject(hBmp, sizeof(BITMAP), &bm);

	// 透明色为蓝色 绘制
	::TransparentBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hBuf, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));
	// 还原位图对象
	::SelectObject(hBuf, hOldBmp);
	// 释放位图
	::DeleteObject(hBmp);
	// 释放兼容的内存设备上下文环境
	::DeleteDC(hBuf);
	// 释放设备上下文环境
	::ReleaseDC(hWnd, hDC);

	return TRUE;
}

BOOL PaintTransparentBmp(HWND hWnd,int nPosX,int nPosY)
{
	// 获取窗口的客户区域的显示设备上下文环境的句柄
	HDC hDC = ::GetDC(hWnd);
	// 创建一个与hDC兼容的内存设备上下文环境
	HDC hBuf = ::CreateCompatibleDC(hDC);
	// 加载位图, 获取位图句柄
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL, _T("image\\2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 选择位图句柄到hBuf中, 并获取返回的原来位图句柄
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp);

	BITMAP bm;
	GetObject(hBmp, sizeof(BITMAP), &bm);

	// 透明色为蓝色 绘制
	::TransparentBlt(hDC, nPosX, nPosY, bm.bmWidth, bm.bmHeight, hBuf, 0, 0,  bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));

	// 还原位图对象
	::SelectObject(hBuf, hOldBmp);
	// 释放位图
	::DeleteObject(hBmp);
	// 释放兼容的内存设备上下文环境
	::DeleteDC(hBuf);
	// 释放设备上下文环境
	::ReleaseDC(hWnd, hDC);

	return TRUE;
}


BOOL CTransparentPaint_TransparentBlt_Test02Dlg::PaintTransparentBmp(HWND hWnd,int nPosX,int nPosY)
{
	// 获取窗口的客户区域的显示设备上下文环境的句柄
	HDC hDC = ::GetDC(hWnd);
	// 创建一个与hDC兼容的内存设备上下文环境
	HDC hBuf = ::CreateCompatibleDC(hDC);
	// 加载位图, 获取位图句柄
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL, _T("image\\2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 选择位图句柄到hBuf中, 并获取返回的原来位图句柄
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp);

	BITMAP bm;
	GetObject(hBmp, sizeof(BITMAP), &bm);

	// 透明色为蓝色 绘制
	::TransparentBlt(hDC, nPosX, nPosY, bm.bmWidth, bm.bmHeight, hBuf, 0, 0,  bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));

	// 还原位图对象
	::SelectObject(hBuf, hOldBmp);
	// 释放位图
	::DeleteObject(hBmp);
	// 释放兼容的内存设备上下文环境
	::DeleteDC(hBuf);
	// 释放设备上下文环境
	::ReleaseDC(hWnd, hDC);

	return TRUE;
}

void CTransparentPaint_TransparentBlt_Test02Dlg::OnPaint()
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
		//PaintTransparentBmp(m_hWnd,"image\\2.bmp");
		//PaintTransparentBmp(m_hWnd,100,50);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTransparentPaint_TransparentBlt_Test02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

