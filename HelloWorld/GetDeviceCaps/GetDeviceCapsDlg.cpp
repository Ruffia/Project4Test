
// GetDeviceCapsDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CGetDeviceCapsDlg �Ի���



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


// CGetDeviceCapsDlg ��Ϣ�������

BOOL CGetDeviceCapsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGetDeviceCapsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGetDeviceCapsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGetDeviceCapsDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	HWND hd = ::GetDesktopWindow();	
	// ����һ	
	RECT rect;	
	// ֻ��ô��ڿͻ����Ĵ�С	
	::GetClientRect(hd, &rect);	
	int client_width = (rect.right - rect.left);	
	int client_height = (rect.bottom - rect.top);	
	// ��ȡ�����Ǵ�������Ļ�ϵ�λ��	
	::GetWindowRect(hd, &rect);	
	int window_width = (rect.right - rect.left);	
	int window_height = (rect.bottom - rect.top);	


	// ������	
	// �����˵����Ĵ�С	
	int no_menu_bar_width = GetSystemMetrics(SM_CXFULLSCREEN);	
	int no_menu_bar__height = GetSystemMetrics(SM_CYFULLSCREEN);

	// ���������Ͳ˵���	
	int have_menu_bar_width = GetSystemMetrics(SM_CXSCREEN);	
	int have_menu_bar_height = GetSystemMetrics(SM_CYSCREEN); 	

	//������	
	HDC hdc = ::GetDC(NULL);                           
	// �õ���ĻDC  	
	client_width = GetDeviceCaps(hdc, HORZRES);      
	// ��  	
	client_height = GetDeviceCaps(hdc, VERTRES);     
	// ��   	
	::ReleaseDC(NULL, hdc);   
	// �ͷ�DC	

	//������	
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, SPIF_SENDCHANGE);	
	client_width = (rect.right - rect.left);	
	client_height = (rect.bottom - rect.top);		

	//������	
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int nScreenWidth, nScreenHeight;  
	HDC hdcScreen = ::GetDC(NULL);   //��ȡ��Ļ��HDC  
	nScreenWidth = GetDeviceCaps(hdcScreen, HORZSIZE);  
	nScreenHeight = GetDeviceCaps(hdcScreen, VERTSIZE);  

	const double MILLIMETRE_TO_INCH = 0.03937;  
	double fDiagonalLen = sqrt((double(nScreenHeight * nScreenHeight + nScreenWidth * nScreenWidth)));
	float fInch = fDiagonalLen * MILLIMETRE_TO_INCH; 

	float f = sqrt(double((448 - 16)*(448 - 16) + (257 - 16)*(257 - 16)));
	float fInch2 = f * MILLIMETRE_TO_INCH;

}
