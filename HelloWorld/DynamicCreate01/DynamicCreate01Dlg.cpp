
// DynamicCreate01Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DynamicCreate01.h"
#include "DynamicCreate01Dlg.h"
#include "afxdialogex.h"

#define ButtonID_Base 10000
#define ButtonID_Min  10100
#define ButtonID_Max  10244
#define Button_RowCount 12

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


// CDynamicCreate01Dlg 对话框



CDynamicCreate01Dlg::CDynamicCreate01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDynamicCreate01Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDynamicCreate01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDynamicCreate01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(ButtonID_Min,ButtonID_Max,OnButtonClick)
END_MESSAGE_MAP()


// CDynamicCreate01Dlg 消息处理程序

BOOL CDynamicCreate01Dlg::OnInitDialog()
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
	_CreateButton();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDynamicCreate01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDynamicCreate01Dlg::OnPaint()
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
		_DrawCircle();


		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDynamicCreate01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDynamicCreate01Dlg::OnButtonClick(UINT uID)
{
	MessageBox(_T("button Clicked"));
}

void CDynamicCreate01Dlg::_CreateButton()
{
	const int nLeftMost = 87;  //最左侧点
	const int nTopMost = 86;   //最上面点
	const int nButtonWidth = 30;
	for (int i = ButtonID_Min; i < ButtonID_Max;i++ )
	{
		int nRow = (i - ButtonID_Min)/Button_RowCount;
		int nColumn = i - ButtonID_Min - nRow * Button_RowCount;

		CButton* btn = new CButton();
		CString strCaption = _T("");
		strCaption.Format(_T("%d"),i - ButtonID_Min);
		btn->Create(strCaption, WS_CHILD | WS_VISIBLE, CRect(nButtonWidth* nColumn + nLeftMost,nButtonWidth * nRow + nTopMost,nButtonWidth* nColumn + nLeftMost + nButtonWidth,nButtonWidth * nRow + nTopMost + nButtonWidth), this, i);
	}
}

void CDynamicCreate01Dlg::_DrawCircle()
{
	CRect rect;
	GetClientRect(&rect);
	int nWidth = min(rect.Width(),rect.Height()) - 20;
	CClientDC dcClient(this);
	dcClient.SelectStockObject(NULL_BRUSH);
	dcClient.Ellipse(10,10,nWidth,nWidth);
	dcClient.MoveTo(98,rect.Height() - 100);
	dcClient.LineTo(98 + 335,rect.Height() - 100);

	CRect rectErase(98,461,435,531),fillrect;
	CBrush brush;
	brush.CreateSolidBrush(RGB(240,240,240));
	dcClient.FillRect(&rectErase,&brush); //用FillRect成员函数利用笔刷填充指定区域
	brush.DeleteObject();
}
