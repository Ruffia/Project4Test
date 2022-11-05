
// UDPServerSocketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDPServerSocket.h"
#include "UDPServerSocketDlg.h"
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


// CUDPServerSocketDlg �Ի���



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


// CUDPServerSocketDlg ��Ϣ�������

BOOL CUDPServerSocketDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUDPServerSocketDlg::OnPaint()
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
HCURSOR CUDPServerSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUDPServerSocketDlg::OnBnClickedButtonStartlisten()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pSocket->Close();
	delete m_pSocket;
	m_pSocket = NULL;

	m_lstContent.ResetContent();
	m_strText2Send = "";
	GetDlgItem(ID_BUTTON_STARTLISTEN)->EnableWindow(TRUE);	
}


void CUDPServerSocketDlg::OnBnClickedBtnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_pSocket->SendTo(m_strText2Send,m_strText2Send.GetLength(),6900,"127.0.0.1",0);
}
