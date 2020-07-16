
// MinidumpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Minidump.h"
#include "MinidumpDlg.h"
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


// CMinidumpDlg �Ի���



CMinidumpDlg::CMinidumpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMinidumpDlg::IDD, pParent)
	, m_fNum1(0)
	, m_fNum2(0)
	, m_fResult(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMinidumpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Number1, m_fNum1);
	DDX_Control(pDX, IDC_COMBO1, m_cmbOperator);
	DDX_Text(pDX, IDC_EDIT_Number2, m_fNum2);
	DDX_Text(pDX, IDC_EDIT_Result, m_fResult);
}

BEGIN_MESSAGE_MAP(CMinidumpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_Button_Calc, &CMinidumpDlg::OnBnClickedButtonCalc)
	ON_BN_CLICKED(IDC_BUTTON_Clear, &CMinidumpDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CMinidumpDlg ��Ϣ�������

BOOL CMinidumpDlg::OnInitDialog()
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
	m_cmbOperator.AddString("+");
	m_cmbOperator.AddString("-");
	m_cmbOperator.AddString("*");
	m_cmbOperator.AddString("/");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMinidumpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMinidumpDlg::OnPaint()
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
HCURSOR CMinidumpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMinidumpDlg::OnBnClickedButtonCalc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString strOperator = "";
	m_cmbOperator.GetWindowTextA(strOperator);

	if ("+" == strOperator)
	{
		m_fResult = m_fNum1 + m_fNum2;
	}
	else if ("-" == strOperator)
	{
		m_fResult = m_fNum1 - m_fNum2;
	}
	else if ("*" == strOperator)
	{
		m_fResult = m_fNum1 * m_fNum2;
	}
	else if ("/" == strOperator)
	{
		m_fResult = m_fNum1 / m_fNum2;
	}
	UpdateData(FALSE);
}


void CMinidumpDlg::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_fNum1 = 0.f;
	m_fNum2 = 0.f;
	m_cmbOperator.SetCurSel(0);
	m_fResult = 0.f;
	int n = 0;
	int r = 1/n;
	UpdateData(FALSE);
}
