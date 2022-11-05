
// DynamicCreate01Dlg.cpp : ʵ���ļ�
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


// CDynamicCreate01Dlg �Ի���



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


// CDynamicCreate01Dlg ��Ϣ�������

BOOL CDynamicCreate01Dlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	_CreateButton();


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDynamicCreate01Dlg::OnPaint()
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
		_DrawCircle();


		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	const int nLeftMost = 87;  //������
	const int nTopMost = 86;   //�������
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
	dcClient.FillRect(&rectErase,&brush); //��FillRect��Ա�������ñ�ˢ���ָ������
	brush.DeleteObject();
}
