
// TransparentPaint_StretchBlt_Test02Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TransparentPaint_StretchBlt_Test02.h"
#include "TransparentPaint_StretchBlt_Test02Dlg.h"
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


// CTransparentPaint_StretchBlt_Test02Dlg �Ի���
BOOL PaintTransparentBmp(HWND hWnd)
{
	// ��ȡ���ڵĿͻ��������ʾ�豸�����Ļ����ľ��
	HDC hDC = ::GetDC(hWnd);
	// ����һ����hDC���ݵ��ڴ��豸�����Ļ���
	HDC hBuf = ::CreateCompatibleDC(hDC);
	// ����λͼ, ��ȡλͼ���
	HBITMAP hBmp1 = (HBITMAP)::LoadImage(NULL, _T("image\\1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBITMAP hBmp2 = (HBITMAP)::LoadImage(NULL, _T("image\\2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// ѡ��λͼ�����hBuf��, ����ȡ���ص�ԭ��λͼ���
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp1);
	// "��"��������
	::StretchBlt(hDC, 260, 170, 200, 200, hBuf, 0, 0, 101, 121, SRCAND);

	// ѡ��λͼ�����hBuf��
	::SelectObject(hBuf, hBmp2);
	// "��"��������
	::StretchBlt(hDC, 260, 170, 200, 200, hBuf, 0, 0, 101, 121, SRCPAINT);

	// ��ԭλͼ����
	::SelectObject(hBuf, hOldBmp);
	// �ͷ�λͼ
	::DeleteObject(hBmp1);
	::DeleteObject(hBmp2);
	// �ͷż��ݵ��ڴ��豸�����Ļ���
	::DeleteDC(hBuf);
	// �ͷ��豸�����Ļ���
	::ReleaseDC(hWnd, hDC);

	return TRUE;
}


CTransparentPaint_StretchBlt_Test02Dlg::CTransparentPaint_StretchBlt_Test02Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTransparentPaint_StretchBlt_Test02Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransparentPaint_StretchBlt_Test02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTransparentPaint_StretchBlt_Test02Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTransparentPaint_StretchBlt_Test02Dlg ��Ϣ�������

BOOL CTransparentPaint_StretchBlt_Test02Dlg::OnInitDialog()
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

void CTransparentPaint_StretchBlt_Test02Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTransparentPaint_StretchBlt_Test02Dlg::OnPaint()
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
		PaintTransparentBmp("image\\1.bmp");
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTransparentPaint_StretchBlt_Test02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// CTransparentPaint_StretchBlt_Test02Dlg �Ի���
BOOL CTransparentPaint_StretchBlt_Test02Dlg::PaintTransparentBmp(char* sImage)
{
	// ��ȡ���ڵĿͻ��������ʾ�豸�����Ļ����ľ��
	CPaintDC dcPaint(this);
	CRect rcClient;
	GetClientRect( &rcClient );

	HDC hDC = ::GetDC(m_hWnd);
	// ����һ����hDC���ݵ��ڴ��豸�����Ļ���
	HDC hBuf = ::CreateCompatibleDC(dcPaint);

	CDC dcBuf;
	dcBuf.CreateCompatibleDC(&dcPaint);

	CString strImage = CString(sImage);
	USES_CONVERSION;
	LPCWSTR wszClassName = new WCHAR[strImage.GetLength()+1];
	wcscpy((LPWSTR)wszClassName,T2W((LPWSTR)strImage.GetBuffer(NULL)));
	strImage.ReleaseBuffer();

	// ����λͼ, ��ȡλͼ���
	HBITMAP hBmp1 = (HBITMAP)::LoadImage(NULL, strImage, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);




	HBITMAP hBmp2 = (HBITMAP)::LoadImage(NULL, _T("image\\2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	CBitmap MaskBitmap;
	MaskBitmap.CreateBitmap( rcClient.Width(), rcClient.Height(), 1, 1, NULL );

	// ѡ��λͼ�����hBuf��, ����ȡ���ص�ԭ��λͼ���
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp1);
	// "��"��������
	::StretchBlt(hDC, 260, 170, 200, 200, hBuf, 0, 0, 101, 121, SRCAND);

	// ѡ��λͼ�����hBuf��
	::SelectObject(hBuf, hBmp2);
	// "��"��������
	::StretchBlt(hDC, 260, 170, 200, 200, hBuf, 0, 0, 101, 121, SRCPAINT);

	// ��ԭλͼ����
	::SelectObject(hBuf, hOldBmp);
	// �ͷ�λͼ
	::DeleteObject(hBmp1);
	::DeleteObject(hBmp2);
	// �ͷż��ݵ��ڴ��豸�����Ļ���
	::DeleteDC(hBuf);
	// �ͷ��豸�����Ļ���
	::ReleaseDC(m_hWnd, hDC);

	return TRUE;
}