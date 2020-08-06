// FastProcessingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FastProcessing.h"
#include "FastProcessingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFastProcessingDlg dialog

CFastProcessingDlg::CFastProcessingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFastProcessingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFastProcessingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFastProcessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFastProcessingDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFastProcessingDlg, CDialog)
	//{{AFX_MSG_MAP(CFastProcessingDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFastProcessingDlg message handlers

BOOL CFastProcessingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFastProcessingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFastProcessingDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFastProcessingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
UINT p[403200];
//UINT *ptr;
//UINT pi[403200];
//int *p;
int r=0;
int shift=10;
int x=100;
int y=200;
int m_iWidth=100;
int	m_iHeight=100;
UINT imgArr[500][500];

void *imageData;
BITMAPINFO BitmapInfo;
CDC dc1;
CBitmap cbp1;
BITMAP bp1;

CDC dc3;
CBitmap cbp3;
BITMAP bp3;
void CFastProcessingDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDC *dc=GetDC();
	cbp1.DeleteObject();
	cbp3.DeleteObject();

	dc1.DeleteDC();
	dc3.DeleteDC();

	cbp1.LoadBitmap(IDB_BITMAP1);
	dc1.CreateCompatibleDC(dc);
	cbp1.GetBitmap(&bp1);
	dc1.SelectObject(cbp1);
	
	
	dc3.CreateCompatibleDC(dc);
	cbp3.CreateCompatibleBitmap(dc,1000,1000);
	dc3.SelectObject(cbp3);
	dc3.BitBlt(0,0,1000,1000,dc,0,0,SRCCOPY);

	dc3.BitBlt(0,0,bp1.bmWidth,bp1.bmHeight,&dc1,0,0,SRCCOPY);


	HBITMAP hbm=NULL;
	
	HDC DeskHdc=::GetDC(NULL);
	HDC hdc=::CreateCompatibleDC(DeskHdc);
	
	BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BitmapInfo.bmiHeader.biWidth = bp1.bmWidth;
	BitmapInfo.bmiHeader.biHeight = bp1.bmHeight;
	BitmapInfo.bmiHeader.biSizeImage = (((bp1.bmWidth * 32 + 31) & ~31) >> 3) * bp1.bmHeight;
	BitmapInfo.bmiHeader.biCompression = BI_RGB ;
	BitmapInfo.bmiHeader.biXPelsPerMeter = 0;
	BitmapInfo.bmiHeader.biYPelsPerMeter = 0; 
	BitmapInfo.bmiHeader.biClrImportant = 0;
	BitmapInfo.bmiHeader.biClrUsed = 0; // we are not using palette
	BitmapInfo.bmiHeader.biPlanes = 1; // has to be 1
	BitmapInfo.bmiHeader.biBitCount = 32; // as we want true-color

	
	hbm=::CreateDIBSection(GetDesktopWindow()->GetWindowDC()->m_hDC, &BitmapInfo, DIB_RGB_COLORS, (void**)&imageData, NULL, 0);
	HBITMAP m_hbmOld;
	
	if (hbm)
	{
		m_hbmOld = (HBITMAP)::SelectObject(hdc,hbm);
	} 

	::BitBlt(hdc,0,0,bp1.bmWidth,bp1.bmHeight,dc3.m_hDC,0,0,SRCCOPY); 
	SetTimer(0,10,0);
	//while (true)
	//{
	//	OnTimer(1);
	//}
	
}
double m=20;
void CFastProcessingDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(r==0)
	{
		memcpy(p,imageData,BitmapInfo.bmiHeader.biSizeImage);
		for(int j=0;j<=bp1.bmHeight;j++)
		for(int k=0;k<=bp1.bmWidth;k++)
		{
			imgArr[j][k]=p[j*bp1.bmWidth+k];
		}
		r=1;

	}

	//KillTimer(0);
	

	//for(int k=0;k<=bp1.bmHeight;k++)
	//for(int f=0;f<=bp1.bmWidth;f++)
	//{
	//	int R,G,B;
	//	int Rx,Gx;

	//	//Rx=rand()%(int)m+k;
	//	//Gx=rand()%(int)m+f;

	//	Rx=rand()%(int)3+k;
	//	Gx=rand()%(int)3+f;

	//	p[k*bp1.bmWidth+f]=imgArr[Rx][Gx];
	//	
	//}
	
	//r++;
	m-=.5;
	if(m<1)
		m=20;
	if(r>bp1.bmWidth)
		r=0;
	HDC dc = ::GetDC(m_hWnd);
	SetDIBitsToDevice(/*::GetDC(NULL)*/dc,
				  10,
				  10,
				  bp1.bmWidth,
				  bp1.bmHeight,
				  0,
				  0,
				  0,
				  bp1.bmHeight,
				  p,
				  //imageData,
				  &BitmapInfo,
				  DIB_RGB_COLORS);
	
	//SetTimer(0,30,0);
	CDialog::OnTimer(nIDEvent);
}
