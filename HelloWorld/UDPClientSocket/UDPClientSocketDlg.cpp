
// UDPClientSocketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDPClientSocket.h"
#include "UDPClientSocketDlg.h"
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


// CUDPClientSocketDlg �Ի���



CUDPClientSocketDlg::CUDPClientSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDPClientSocketDlg::IDD, pParent)
	, m_strServerIP(_T("127.0.0.1"))
	, m_nPort(5678)
	, m_strTxt2Send(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSocket = new CConnSocket(this);
}

void CUDPClientSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IP, m_strServerIP);
	DDV_MaxChars(pDX, m_strServerIP, 128);
	DDX_Text(pDX, IDC_Port, m_nPort);
	DDX_Text(pDX, IDC_Txt2Send, m_strTxt2Send);
	DDV_MaxChars(pDX, m_strTxt2Send, 2048);
	DDX_Control(pDX, IDC_LIST_RECV, m_lstRecv);
}

BEGIN_MESSAGE_MAP(CUDPClientSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnConnect, &CUDPClientSocketDlg::OnBnClickedBtnconnect)
	ON_BN_CLICKED(IDC_BtnReset, &CUDPClientSocketDlg::OnBnClickedBtnreset)
	ON_BN_CLICKED(IDC_BtnSend, &CUDPClientSocketDlg::OnBnClickedBtnsend)
	ON_BN_CLICKED(IDOK, &CUDPClientSocketDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUDPClientSocketDlg ��Ϣ�������

BOOL CUDPClientSocketDlg::OnInitDialog()
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
	WSADATA wsaData;
	int nRet  = WSAStartup(MAKEWORD(2,2),&wsaData);
	if(nRet != 0)
	{
		TRACE("WSAStartup failed");
		return FALSE;
	}

	UpdateData(FALSE);
	OnConnect(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CUDPClientSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUDPClientSocketDlg::OnPaint()
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
HCURSOR CUDPClientSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUDPClientSocketDlg::OnReceive(CString sText)
{
	m_lstRecv.AddString(sText);
	UpdateData(FALSE);
}

void CUDPClientSocketDlg::OnConnect(bool bConnect)
{
	//GetDlgItem(IDC_BtnConnect)->EnableWindow(!bConnect);
	//GetDlgItem(IDC_BtnReset)->EnableWindow(bConnect);
	//GetDlgItem(IDC_BtnSend)->EnableWindow(bConnect);
}

void CUDPClientSocketDlg::OnBnClickedBtnconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	DWORD dwErr = 0;
	//BOOL bCreate = m_pSocket->Create(m_nPort,SOCK_DGRAM,m_strServerIP);
	//if (!bCreate)
	//{
	//	char szMsg[1024] = {0};
	//	sprintf_s(szMsg, 1024,"create faild: %d", m_pSocket->GetLastError());
	//	CString sErr(szMsg);
	//	MessageBox(sErr);
	//	return;
	//}

	BOOL bCreate = m_pSocket->Create(AF_INET,SOCK_DGRAM,NULL);
	if (!bCreate)
	{
		char szMsg[1024] = {0};
		sprintf_s(szMsg, 1024,"create faild: %d", m_pSocket->GetLastError());
		CString sErr(szMsg);
		MessageBox(sErr);
		return;
	}

	m_pSocket->Init(m_strServerIP,m_nPort);
}


void CUDPClientSocketDlg::OnBnClickedBtnreset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_pSocket) return;
	m_pSocket->Close();
	m_strTxt2Send = "";
	UpdateData(FALSE);
}


void CUDPClientSocketDlg::OnBnClickedBtnsend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_pSocket) return;
	UpdateData(TRUE);

	char* src =(LPSTR)(LPCTSTR)m_strTxt2Send;
	char* sz = new char[1024];
	memcpy(sz,src,strlen(src)+ 1);
	int nRet = m_pSocket->SendTo(m_strTxt2Send.GetBuffer(0),m_strTxt2Send.GetLength(),m_nPort,m_strServerIP,0);
	if (-1 == nRet)
	{
		char szError[256] = {0};
		sprintf_s(szError, 256,"Send Faild: %d", GetLastError());
		MessageBox(szError);
		return;
	}
}


void CUDPClientSocketDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}