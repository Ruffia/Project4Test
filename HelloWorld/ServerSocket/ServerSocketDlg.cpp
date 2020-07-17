
// ServerSocketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServerSocket.h"
#include "ServerSocketDlg.h"
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


// CServerSocketDlg �Ի���



CServerSocketDlg::CServerSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerSocketDlg::IDD, pParent)
	, m_nPort(5678)
	, m_strBroadcast(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_LIST_Content, m_lstContent);
	DDX_Text(pDX, IDC_EDIT_Broadcast, m_strBroadcast);
}

BEGIN_MESSAGE_MAP(CServerSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_STARTLISTEN, &CServerSocketDlg::OnBnClickedButtonStartlisten)
	ON_MESSAGE(WM_SOCKET_ACCEPT_CLIENT,&CServerSocketDlg::OnClientConnectIn)
	ON_MESSAGE(WM_SOCKET_RECEIVE_MSG,&CServerSocketDlg::OnReveiveClientMessage)
	ON_BN_CLICKED(ID_BTN_RESET, &CServerSocketDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(ID_BTN_Broadcast, &CServerSocketDlg::OnBnClickedBtnBroadcast)
END_MESSAGE_MAP()


// CServerSocketDlg ��Ϣ�������

BOOL CServerSocketDlg::OnInitDialog()
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

void CServerSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerSocketDlg::OnPaint()
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
HCURSOR CServerSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerSocketDlg::OnBnClickedButtonStartlisten()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_pSocket = new CListenSocket(m_nPort,this->m_hWnd);
	BOOL bRet = m_pSocket->Create(m_nPort);
	if (!bRet)
	{
		char szError[256] = {0};
		sprintf(szError, "Create Faild: %d", GetLastError());
		MessageBox(szError);
		return;
	}

	bRet = m_pSocket->Listen(10);
	if (!bRet)
	{
		char szError[256] = {0};
		sprintf(szError, "Listen Faild: %d", GetLastError());
		MessageBox(szError);
		return;
	}

	GetDlgItem(ID_BUTTON_STARTLISTEN)->EnableWindow(FALSE);	
}


HRESULT CServerSocketDlg::OnClientConnectIn(WPARAM w, LPARAM l)
{
	char* s = (char*)w;
	m_lstContent.AddString(s);
	UpdateData(FALSE);
	return 0L;
}


HRESULT CServerSocketDlg::OnReveiveClientMessage(WPARAM w, LPARAM l)
{
	char* s = (char*)w;
	m_lstContent.AddString(s);
	UpdateData(FALSE);
	return 0L;
}


void CServerSocketDlg::OnBnClickedBtnReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pSocket->Close();
	delete m_pSocket;
	m_pSocket = NULL;

	m_lstContent.ResetContent();
	m_strBroadcast = "";
	GetDlgItem(ID_BUTTON_STARTLISTEN)->EnableWindow(TRUE);	
}


void CServerSocketDlg::OnBnClickedBtnBroadcast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
   map<CSocket*,CSocket*>& mapClient = m_pSocket->GetClient();
   for (map<CSocket*,CSocket*>::iterator it = mapClient.begin();it != mapClient.end();it++ )
   {
	   CSocket* pSock = it->first;
	   int nRet = pSock->Send(m_strBroadcast.GetBuffer(0),m_strBroadcast.GetLength());  
	   if (-1 == nRet)
	   {
		   char szError[256] = {0};
		   sprintf(szError, "Send Faild: %d", GetLastError());
		   MessageBox(szError);
		   return;
	   }
   }
}
