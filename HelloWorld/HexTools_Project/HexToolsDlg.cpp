// HexToolsDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "HexTools.h"
#include "HexToolsDlg.h"

// for DDX_HexText
#include "HexText.h"
// for DDX_BitChecker
//#include "BitChecker.h"
#include "BitWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnStaticWww();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
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
   

//	int		m_nHexInt;
//	short		m_sHexShort;
//	DWORD		m_dwHexDWORD;
//	WORD		m_wHexWORD;
//	BYTE		m_bHexByte;
//	CString  m_strHexString;
//	int		m_nBitInt;
//	short		m_sBitShort;
//	DWORD		m_dwBitDWORD;
//	WORD		m_wBitWORD;
//	BYTE		m_bBitByte;
//	CString  m_strBracketString;
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_STATIC_WWW, OnStaticWww)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexToolsDlg Dialogfeld

CHexToolsDlg::CHexToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHexToolsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHexToolsDlg)
   m_nDecInt = -123;
   m_sDecShort = -123;
   m_dwDecDWORD = -123;
   m_wDecWORD = -123;
   m_bDecByte = -123;
   //m_strDecString = "OL\\?;
   m_nHexInt = 123;
   m_sHexShort = -123;
   m_dwHexDWORD = -123;
   m_wHexWORD = -123;
   m_bHexByte = -123;
   //m_strHexString = "OL\\?;
   //m_nBitInt = -123;
   m_sBitShort = -123;
   m_dwBitDWORD = -123;
   m_wBitWORD = -123;
   m_bBitByte = -123;
  // m_strBracketString = "OL?;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHexToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
//	DDX_Text(pDX, IDC_EDIT_INT_0, m_nDecIn);
	//{{AFX_DATA_MAP(CHexToolsDlg)
	DDX_Text(pDX,IDC_EDIT_INT_0,m_nDecInt);
	DDX_Text(pDX,IDC_EDIT_SHORT_0,m_sDecShort);
	DDX_Text(pDX,IDC_EDIT_DWORD_0,m_dwDecDWORD);
	DDX_Text(pDX,IDC_EDIT_WORD_0,(short&)m_wDecWORD);
	DDX_Text(pDX,IDC_EDIT_BYTE_0,m_bDecByte);
	DDX_Text(pDX,IDC_EDIT_STRING_0,m_strDecString);
	//}}AFX_DATA_MAP
   
   //HexValues
	DDX_HexText(pDX,IDC_EDIT_INT_1,m_nHexInt);
	DDX_HexText(pDX,IDC_EDIT_SHORT_1,m_sHexShort);
	DDX_HexText(pDX,IDC_EDIT_DWORD_1,m_dwHexDWORD);
	DDX_HexText(pDX,IDC_EDIT_WORD_1,m_wHexWORD);
	DDX_HexText(pDX,IDC_EDIT_BYTE_1,m_bHexByte);
	DDX_HexText(pDX,IDC_EDIT_STRING_1,m_strHexString);
   //BitValus
	DDX_BitWnd(pDX,IDC_STATIC_INT,m_nBitInt);
	DDX_BitWnd(pDX,IDC_STATIC_SHORT,m_sBitShort);

   CStringArray arStrings;
   arStrings.Add("First 14 entries");
   arStrings.Add("are set with");
   arStrings.Add("SetCaptions()");
   CString strTemp;
   for( char i=3 ; i<14 ; i++)
   {
      strTemp.Format("Nr.:%X",i);
      arStrings.Add( strTemp );
   }  

	DDX_BitWnd(pDX,IDC_STATIC_DWORD,m_dwBitDWORD,TRUE,16,&arStrings);
	DDX_BitWnd(pDX,IDC_STATIC_WORD,m_wBitWORD,FALSE,0,NULL,0,5);
	DDX_BitWnd(pDX,IDC_STATIC_BYTE,m_bBitByte,FALSE,0,NULL,0x06);
   //BracketString
	DDX_TextHexBracket(pDX,IDC_EDIT_STRING_2,m_strBracketString);
}

BEGIN_MESSAGE_MAP(CHexToolsDlg, CDialog)
	//{{AFX_MSG_MAP(CHexToolsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_APPLY_0, OnButtonApply0)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_1, OnButtonApply1)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_2, OnButtonApply2)
	//}}AFX_MSG_MAP
//   ON_CONTROL_RANGE( BN_CLICKED,IDC_STATIC_INT,IDC_STATIC_BYTE, OnButtonApply2 )
   ON_COMMAND_RANGE( IDC_STATIC_INT,IDC_STATIC_BYTE, OnBitWnds )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexToolsDlg Nachrichten-Handler

BOOL CHexToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmen?

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
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

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CHexToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CHexToolsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CHexToolsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHexToolsDlg::OnButtonApply0() 
{
   UpdateData();
	m_nHexInt      = m_nBitInt      = m_nDecInt;
	m_sHexShort    = m_sBitShort    = m_sDecShort;
	m_dwHexDWORD   = m_dwBitDWORD   = m_dwDecDWORD;
	m_wHexWORD     = m_wBitWORD     = m_wDecWORD;
	m_bHexByte     = m_bBitByte     = m_bDecByte;
	m_strHexString = m_strBracketString = m_strDecString;
   UpdateData(FALSE);
}

void CHexToolsDlg::OnButtonApply1() 
{
   UpdateData();
	m_nBitInt      = m_nDecInt      = m_nHexInt;
	m_sBitShort    = m_sDecShort    = m_sHexShort;
	m_dwBitDWORD   = m_dwDecDWORD   = m_dwHexDWORD;
	m_wBitWORD     = m_wDecWORD     = m_wHexWORD;
	m_bBitByte     = m_bDecByte     = m_bHexByte;
	m_strBracketString = m_strDecString = m_strHexString;
   UpdateData(FALSE);
}
void CHexToolsDlg::OnBitWnds(UINT nID)
{
   OnButtonApply2();
}

void CHexToolsDlg::OnButtonApply2() 
{
   UpdateData();
	m_nDecInt      = m_nHexInt      = m_nBitInt;
	m_sDecShort    = m_sHexShort    = m_sBitShort;
	m_dwDecDWORD   = m_dwHexDWORD   = m_dwBitDWORD;
	m_wDecWORD     = m_wHexWORD     = m_wBitWORD;
	m_bDecByte     = m_bHexByte     = m_bBitByte;
	m_strDecString = m_strHexString = m_strBracketString;
   UpdateData(FALSE);
}

void CAboutDlg::OnStaticWww() 
{
   ShellExecute(GetSafeHwnd(),"open","http://www.schikos.de",NULL,NULL,SW_SHOW)	;
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
   static CBrush brush(RGB(0,0,255));
   if( pWnd->m_hWnd == ::GetDlgItem(this->m_hWnd,IDC_STATIC_WWW))
   {
      pDC->SetTextColor(RGB(0,0,255));
   }
	return hbr;
}
