// CustomTabCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustomTabCtrlDemo.h"
#include "CustomTabCtrlDemoDlg.h"

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
// CCustomTabCtrlDemoDlg dialog

	
CCustomTabCtrlDemoDlg::CCustomTabCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomTabCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomTabCtrlDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomTabCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomTabCtrlDemoDlg)
	DDX_Control(pDX, IDC_BUTTONSAFTERCK, m_ctrlButtonsAfter);
	DDX_Control(pDX, IDC_RTLYCK, m_ctrlRTL);
	DDX_Control(pDX, IDC_CLOSEBUTTONSCK, m_ctrlClose);
	DDX_Control(pDX, IDC_DRAGMOVECK, m_ctrlDragmove);
	DDX_Control(pDX, IDC_DRAGCOPYCK, m_ctrlDragcopy);
	DDX_Control(pDX, IDC_FOURBUTTONSCK, m_ctrl4Buttons);
	DDX_Control(pDX, IDC_AUTOHIDEBUTTONSCK, m_ctrlAutoHide);
	DDX_Control(pDX, IDC_FIXEDCK, m_ctrlFixed);
	DDX_Control(pDX, IDC_TOOLTIPSCK, m_ctrlTooltips);
	DDX_Control(pDX, IDC_MULTIHIGHLIGHTCK, m_ctrlMultihighlight);
	DDX_Control(pDX, IDC_EDITLABELSCK, m_ctrlEditlabels);
	DDX_Control(pDX, IDC_COLOR, m_ctrlColor);
	DDX_Control(pDX, IDC_TAB, m_ctrlTab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCustomTabCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomTabCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_FIXEDCK, OnFixedck)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_FOURBUTTONSCK, OnFourbuttonsck)
	ON_BN_CLICKED(IDC_AUTOHIDEBUTTONSCK, OnAutohidebuttonsck)
	ON_BN_CLICKED(IDC_MULTIHIGHLIGHTCK, OnMultihighlightck)
	ON_BN_CLICKED(IDC_TOOLTIPSCK, OnTooltipsck)
	ON_BN_CLICKED(IDC_EDITLABELSCK, OnEditlabelsck)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_DRAGMOVECK, OnDragmoveck)
	ON_BN_CLICKED(IDC_DRAGCOPYCK, OnDragcopyck)
	ON_BN_CLICKED(IDC_CLOSEBUTTONSCK, OnClosebuttonsck)
	ON_BN_CLICKED(IDC_RTLYCK, OnRtlyck)
	ON_BN_CLICKED(IDC_BUTTONSAFTERCK, OnButtonsafterck)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	//}}AFX_MSG_MAP
	ON_NOTIFY(CTCN_CLICK, IDC_TAB, OnLButtonClickedTab)
	ON_NOTIFY(CTCN_RCLICK, IDC_TAB, OnRButtonClickedTab)
	ON_NOTIFY(CTCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_NOTIFY(CTCN_HIGHLIGHTCHANGE, IDC_TAB, OnHighlightchangeTab)
	ON_NOTIFY(CTCN_ITEMMOVE, IDC_TAB, OnMoveitemTab)
	ON_NOTIFY(CTCN_ITEMCOPY, IDC_TAB, OnCopyitemTab)
	ON_NOTIFY(CTCN_LABELUPDATE, IDC_TAB, OnLabelupdateTab)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoDlg message handlers

BOOL CCustomTabCtrlDemoDlg::OnInitDialog()
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
	
	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);
	CheckRadioButton(IDC_RADIO3,IDC_RADIO6,IDC_RADIO3);
	
	if(m_ctrlTab.GetStyle()&CTCS_FIXEDWIDTH)
		m_ctrlFixed.SetCheck(TRUE);	
	if(m_ctrlTab.GetStyle()&CTCS_FOURBUTTONS)
		m_ctrl4Buttons.SetCheck(TRUE);	
	if(m_ctrlTab.GetStyle()&CTCS_AUTOHIDEBUTTONS)
		m_ctrlAutoHide.SetCheck(TRUE);	
	if(m_ctrlTab.GetStyle()&CTCS_CLOSEBUTTON)
		m_ctrlClose.SetCheck(TRUE);		
	if(m_ctrlTab.GetStyle()&CTCS_MULTIHIGHLIGHT)
		m_ctrlMultihighlight.SetCheck(TRUE);	
	if(m_ctrlTab.GetStyle()&CTCS_EDITLABELS)
		m_ctrlEditlabels.SetCheck(TRUE);	
	if(m_ctrlTab.GetStyle()&CTCS_DRAGMOVE)
		m_ctrlDragmove.SetCheck(TRUE);
	if(m_ctrlTab.GetStyle()&CTCS_DRAGCOPY)
		m_ctrlDragcopy.SetCheck(TRUE);
	if(m_ctrlTab.GetExStyle()&WS_EX_LAYOUTRTL)
		m_ctrlRTL.SetCheck(TRUE);

	m_ctrlTab.SetDragCursors(AfxGetApp()->LoadCursor(IDC_CURSORMOVE),AfxGetApp()->LoadCursor(IDC_CURSORCOPY));
	m_ctrlTab.InsertItem(0,"SS_BLACKRECT");
	m_ctrlTab.SetItemData(0,SS_BLACKRECT);
	m_ctrlTab.InsertItem(1,"SS_GRAY");
	m_ctrlTab.SetItemData(1,SS_GRAYRECT);
	m_ctrlTab.InsertItem(2,"SS_WHITERECT");
	m_ctrlTab.SetItemData(2,SS_WHITERECT);
	m_ctrlTab.SetCurSel(0);
	
	if(m_ctrlTab.GetStyle()&CTCS_TOOLTIPS)
	{
		m_ctrlTooltips.SetCheck(TRUE);	

		if(m_ctrlTab.GetStyle()&CTCS_CLOSEBUTTON)
			m_ctrlTab.SetItemTooltipText(CTCID_CLOSEBUTTON,"Close");
		m_ctrlTab.SetItemTooltipText(CTCID_FIRSTBUTTON,"First");
		m_ctrlTab.SetItemTooltipText(CTCID_PREVBUTTON,"Prev");
		m_ctrlTab.SetItemTooltipText(CTCID_NEXTBUTTON,"Next");
		m_ctrlTab.SetItemTooltipText(CTCID_LASTBUTTON,"Last");
		m_ctrlTab.SetItemTooltipText(0,"Press to fill the static window background with the color used to draw window frames.");
		m_ctrlTab.SetItemTooltipText(1,"Press to fill the static window background with the color used to fill the screen background.");
		m_ctrlTab.SetItemTooltipText(2,"Press to fill the static window background with the color used to fill the the window background.");
	}

	CRect r;
	GetClientRect(r);
	Size(r.Width(),r.Height());
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCustomTabCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCustomTabCtrlDemoDlg::OnPaint() 
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
HCURSOR CCustomTabCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCustomTabCtrlDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	Size(cx,cy);
}

void CCustomTabCtrlDemoDlg::Size(int cx, int cy)
{
	if(m_ctrlTab.m_hWnd)
	{
		int m = 10;
		int h = 20;
		CRect rBn;
		m_ctrlFixed.GetWindowRect(rBn);

		if(m_ctrlTab.IsVertical() && m_ctrlTab.GetStyle()&CTCS_TOP) // left
		{
			m_ctrlColor.MoveWindow(m+h,m,cx-3*m-rBn.Width()-h,cy-2*m);
			m_ctrlTab.MoveWindow(m,m,h,cy-2*m);
		}
		else if(m_ctrlTab.GetStyle()&CTCS_TOP) // top
		{
			m_ctrlColor.MoveWindow(m,h+m,cx-3*m-rBn.Width(),cy-h-2*m);
			m_ctrlTab.MoveWindow(m,m,cx-3*m-rBn.Width(),h);
		}
		else if(m_ctrlTab.IsVertical()) // right
		{
			m_ctrlColor.MoveWindow(m,m,cx-3*m-rBn.Width()-h,cy-2*m);
			m_ctrlTab.MoveWindow(m+cx-3*m-rBn.Width()-h,m,h,cy-2*m);
		}
		else // bottom
		{
			m_ctrlColor.MoveWindow(m,m,cx-3*m-rBn.Width(),cy-h-2*m);
			m_ctrlTab.MoveWindow(m,cy-h-m,cx-3*m-rBn.Width(),h);
		}

		m_ctrlFixed.MoveWindow(cx-m-rBn.Width(),m,rBn.Width(),rBn.Height());
		m_ctrl4Buttons.MoveWindow(cx-m-rBn.Width(),3*m,rBn.Width(),rBn.Height());
		m_ctrlAutoHide.MoveWindow(cx-m-rBn.Width(),5*m,rBn.Width(),rBn.Height());
		m_ctrlClose.MoveWindow(cx-m-rBn.Width(),7*m,rBn.Width(),rBn.Height());
		m_ctrlTooltips.MoveWindow(cx-m-rBn.Width(),9*m,rBn.Width(),rBn.Height());
		m_ctrlMultihighlight.MoveWindow(cx-m-rBn.Width(),11*m,rBn.Width(),rBn.Height());
		m_ctrlEditlabels.MoveWindow(cx-m-rBn.Width(),13*m,rBn.Width(),rBn.Height());
		m_ctrlDragmove.MoveWindow(cx-m-rBn.Width(),15*m,rBn.Width(),rBn.Height());
		m_ctrlDragcopy.MoveWindow(cx-m-rBn.Width(),17*m,rBn.Width(),rBn.Height());
		m_ctrlRTL.MoveWindow(cx-m-rBn.Width(),19*m,rBn.Width(),rBn.Height());
		m_ctrlButtonsAfter.MoveWindow(cx-m-rBn.Width(),21*m,rBn.Width(),rBn.Height());
		GetDlgItem(IDC_RADIO3)->MoveWindow(cx-m-rBn.Width(),23*m,rBn.Width(),rBn.Height());
		GetDlgItem(IDC_RADIO4)->MoveWindow(cx-m-rBn.Width(),25*m,rBn.Width(),rBn.Height());
		GetDlgItem(IDC_RADIO5)->MoveWindow(cx-m-rBn.Width(),27*m,rBn.Width(),rBn.Height());
		GetDlgItem(IDC_RADIO6)->MoveWindow(cx-m-rBn.Width(),29*m,rBn.Width(),rBn.Height());
		GetDlgItem(IDC_RADIO1)->MoveWindow(cx-m-rBn.Width(),31*m,rBn.Width(),rBn.Height());
		GetDlgItem(IDC_RADIO2)->MoveWindow(cx-m-rBn.Width(),33*m,rBn.Width(),rBn.Height());
		RedrawWindow(NULL,NULL,RDW_ALLCHILDREN|RDW_ERASE|RDW_INVALIDATE);
	}
}

void CCustomTabCtrlDemoDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_SELCHANGE): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
				((CTC_NMHDR*)pNMHDR)->nItem,
				((CTC_NMHDR*)pNMHDR)->pszText,
				((CTC_NMHDR*)pNMHDR)->lParam,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
				((CTC_NMHDR*)pNMHDR)->rItem.left,
				((CTC_NMHDR*)pNMHDR)->rItem.top,
				((CTC_NMHDR*)pNMHDR)->rItem.right,
				((CTC_NMHDR*)pNMHDR)->rItem.bottom,
				((CTC_NMHDR*)pNMHDR)->fSelected,
				((CTC_NMHDR*)pNMHDR)->fHighlighted);
	m_ctrlColor.ModifyStyle(SS_BLACKRECT|SS_GRAYRECT|SS_WHITERECT,((CTC_NMHDR*)pNMHDR)->lParam);
	m_ctrlColor.Invalidate();
	*pResult = 0;
}

void CCustomTabCtrlDemoDlg::OnHighlightchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_HIGHLIGHTCHANGE): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
				((CTC_NMHDR*)pNMHDR)->nItem,
				((CTC_NMHDR*)pNMHDR)->pszText,
				((CTC_NMHDR*)pNMHDR)->lParam,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
				((CTC_NMHDR*)pNMHDR)->rItem.left,
				((CTC_NMHDR*)pNMHDR)->rItem.top,
				((CTC_NMHDR*)pNMHDR)->rItem.right,
				((CTC_NMHDR*)pNMHDR)->rItem.bottom,
				((CTC_NMHDR*)pNMHDR)->fSelected,
				((CTC_NMHDR*)pNMHDR)->fHighlighted);
	

	*pResult = 0;
}

void CCustomTabCtrlDemoDlg::OnLButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	switch(((CTC_NMHDR*)pNMHDR)->nItem)
	{
	case CTCHT_ONCLOSEBUTTON:
		TRACE("OnLButtonClicked: Close\n");
		if(m_ctrlTab.DeleteItem(m_ctrlTab.GetCurSel())!=CTCERR_NOERROR)
			AfxMessageBox("DeleteItem(...) failed.\nPossible errors:\n1. Item index out of range.");
		break;
	case CTCHT_ONFIRSTBUTTON:
		TRACE("OnLButtonClicked: First\n");
		break;
	case CTCHT_ONPREVBUTTON:
		TRACE("OnLButtonClicked: Prev\n");
		break;
	case CTCHT_ONNEXTBUTTON:
		TRACE("OnLButtonClicked: Next\n");
		break;
	case CTCHT_ONLASTBUTTON:
		TRACE("OnLButtonClicked: Last\n");
		break;
	case CTCHT_NOWHERE:
		TRACE("OnLButtonClicked: Nowhere\n");
		break;
	default:
		{
			TRACE("Notify(CTCN_CLICK): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
				((CTC_NMHDR*)pNMHDR)->nItem,
				((CTC_NMHDR*)pNMHDR)->pszText,
				((CTC_NMHDR*)pNMHDR)->lParam,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
				((CTC_NMHDR*)pNMHDR)->rItem.left,
				((CTC_NMHDR*)pNMHDR)->rItem.top,
				((CTC_NMHDR*)pNMHDR)->rItem.right,
				((CTC_NMHDR*)pNMHDR)->rItem.bottom,
				((CTC_NMHDR*)pNMHDR)->fSelected,
				((CTC_NMHDR*)pNMHDR)->fHighlighted);
		}
		break;
	}
	*pResult = 0;
}

void CCustomTabCtrlDemoDlg::OnRButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	switch(((CTC_NMHDR*)pNMHDR)->nItem)
	{
	case CTCHT_ONCLOSEBUTTON:
		TRACE("OnLButtonClicked: Close\n");
		break;
	case CTCHT_ONFIRSTBUTTON:
		TRACE("OnLButtonClicked: First\n");
		break;
	case CTCHT_ONPREVBUTTON:
		TRACE("OnLButtonClicked: Prev\n");
		break;
	case CTCHT_ONNEXTBUTTON:
		TRACE("OnLButtonClicked: Next\n");
		break;
	case CTCHT_ONLASTBUTTON:
		TRACE("OnLButtonClicked: Last\n");
		break;
	default:
		{
			int nInsNdx;
			CMenu menu;
			menu.CreatePopupMenu();
			if(((CTC_NMHDR*)pNMHDR)->nItem==CTCHT_NOWHERE)
			{
				TRACE("OnLButtonClicked: Nowhere\n");
				nInsNdx = m_ctrlTab.GetItemCount();
				menu.AppendMenu(MF_STRING,1,_T("Insert Item"));
				menu.AppendMenu(MF_STRING|MF_GRAYED,2,_T("Delete Item"));
				menu.AppendMenu(MF_STRING|MF_GRAYED,3,_T("Rename"));
			}
			else
			{
				TRACE("Notify(CTCN_RCLICK): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
						((CTC_NMHDR*)pNMHDR)->nItem,
						((CTC_NMHDR*)pNMHDR)->pszText,
						((CTC_NMHDR*)pNMHDR)->lParam,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
						((CTC_NMHDR*)pNMHDR)->rItem.left,
						((CTC_NMHDR*)pNMHDR)->rItem.top,
						((CTC_NMHDR*)pNMHDR)->rItem.right,
						((CTC_NMHDR*)pNMHDR)->rItem.bottom,
						((CTC_NMHDR*)pNMHDR)->fSelected,
						((CTC_NMHDR*)pNMHDR)->fHighlighted);
				m_ctrlTab.SetCurSel(((CTC_NMHDR*)pNMHDR)->nItem);
				nInsNdx = ((CTC_NMHDR*)pNMHDR)->nItem;
				menu.AppendMenu(MF_STRING,1,_T("Insert Item"));
				menu.AppendMenu(MF_STRING,2,_T("Delete Item"));
				menu.AppendMenu(MF_STRING,3,_T("Rename"));
			}
	
			CPoint pt(((CTC_NMHDR*)pNMHDR)->ptHitTest);
			m_ctrlTab.ClientToScreen(&pt);

			int nRet = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, 
								pt.x, pt.y, this);
			switch(nRet)
			{
			case 1:
				{
					if(m_ctrlTab.InsertItem(nInsNdx,_T("New SS_WHITERECT Item"),SS_WHITERECT)<0)
						AfxMessageBox("InsertItem(...) failed.\nPossible errors:\n1. Item index out of range.");
				}
				break;
			case 2:
				{
					if(m_ctrlTab.DeleteItem(((CTC_NMHDR*)pNMHDR)->nItem)!=CTCERR_NOERROR)
						AfxMessageBox("DeleteItem(...) failed.\nPossible errors:\n1. Item index out of range.");
				}
				break;
			case 3:
				{
					if(m_ctrlTab.EditLabel(((CTC_NMHDR*)pNMHDR)->nItem)!=CTCERR_NOERROR)
						AfxMessageBox("EditLabel(...) failed.\nPossible errors:\n1. Item index out of range.\n2. Item not selected.\n3. CTCS_EDITLABELS style not specified.");
				}
				break;
			}
		}
		break;
	}
	*pResult = 0;
}

void CCustomTabCtrlDemoDlg::OnMoveitemTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_ITEMMOVE): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
						((CTC_NMHDR*)pNMHDR)->nItem,
						((CTC_NMHDR*)pNMHDR)->pszText,
						((CTC_NMHDR*)pNMHDR)->lParam,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
						((CTC_NMHDR*)pNMHDR)->rItem.left,
						((CTC_NMHDR*)pNMHDR)->rItem.top,
						((CTC_NMHDR*)pNMHDR)->rItem.right,
						((CTC_NMHDR*)pNMHDR)->rItem.bottom,
						((CTC_NMHDR*)pNMHDR)->fSelected,
						((CTC_NMHDR*)pNMHDR)->fHighlighted);
	*pResult = 0;
}

void CCustomTabCtrlDemoDlg::OnCopyitemTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_ITEMCOPY): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
						((CTC_NMHDR*)pNMHDR)->nItem,
						((CTC_NMHDR*)pNMHDR)->pszText,
						((CTC_NMHDR*)pNMHDR)->lParam,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
						((CTC_NMHDR*)pNMHDR)->rItem.left,
						((CTC_NMHDR*)pNMHDR)->rItem.top,
						((CTC_NMHDR*)pNMHDR)->rItem.right,
						((CTC_NMHDR*)pNMHDR)->rItem.bottom,
						((CTC_NMHDR*)pNMHDR)->fSelected,
						((CTC_NMHDR*)pNMHDR)->fHighlighted);
	*pResult = 0;
}

void CCustomTabCtrlDemoDlg::OnLabelupdateTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_LABELUPDATE): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
						((CTC_NMHDR*)pNMHDR)->nItem,
						((CTC_NMHDR*)pNMHDR)->pszText,
						((CTC_NMHDR*)pNMHDR)->lParam,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
						((CTC_NMHDR*)pNMHDR)->rItem.left,
						((CTC_NMHDR*)pNMHDR)->rItem.top,
						((CTC_NMHDR*)pNMHDR)->rItem.right,
						((CTC_NMHDR*)pNMHDR)->rItem.bottom,
						((CTC_NMHDR*)pNMHDR)->fSelected,
						((CTC_NMHDR*)pNMHDR)->fHighlighted);
	if(CString(((CTC_NMHDR*)pNMHDR)->pszText).IsEmpty())
	{
		*pResult = 1; // Invalid label name
		AfxMessageBox("Invalid label name");
	}
	else
		*pResult = 0; // Label name OK
}

void CCustomTabCtrlDemoDlg::OnFixedck() 
{
	if(m_ctrlFixed.GetCheck())
		m_ctrlTab.ModifyStyle(0,CTCS_FIXEDWIDTH,0);
	else
		m_ctrlTab.ModifyStyle(CTCS_FIXEDWIDTH,0,0);
}

void CCustomTabCtrlDemoDlg::OnFourbuttonsck() 
{
	if(m_ctrl4Buttons.GetCheck())
		m_ctrlTab.ModifyStyle(0,CTCS_FOURBUTTONS,0);
	else
		m_ctrlTab.ModifyStyle(CTCS_FOURBUTTONS,0,0);
}

void CCustomTabCtrlDemoDlg::OnAutohidebuttonsck()
{
	if(m_ctrlAutoHide.GetCheck())
		m_ctrlTab.ModifyStyle(0,CTCS_AUTOHIDEBUTTONS,0);
	else
		m_ctrlTab.ModifyStyle(CTCS_AUTOHIDEBUTTONS,0,0);
}

void CCustomTabCtrlDemoDlg::OnMultihighlightck() 
{
	if(m_ctrlMultihighlight.GetCheck())
		m_ctrlTab.ModifyStyle(0,CTCS_MULTIHIGHLIGHT,0);
	else
		m_ctrlTab.ModifyStyle(CTCS_MULTIHIGHLIGHT,0,0);	
}

void CCustomTabCtrlDemoDlg::OnTooltipsck()
{
	if(m_ctrlTooltips.GetCheck())
	{
		m_ctrlTab.ModifyStyle(0,CTCS_TOOLTIPS,0);
		m_ctrlTab.SetItemTooltipText(CTCID_CLOSEBUTTON,"Close");
		m_ctrlTab.SetItemTooltipText(CTCID_FIRSTBUTTON,"First");
		m_ctrlTab.SetItemTooltipText(CTCID_PREVBUTTON,"Prev");
		m_ctrlTab.SetItemTooltipText(CTCID_NEXTBUTTON,"Next");
		m_ctrlTab.SetItemTooltipText(CTCID_LASTBUTTON,"Last");
		LPCTSTR p;
		for(int i=0;i<m_ctrlTab.GetItemCount();i++)
		{
			DWORD dwData;
			m_ctrlTab.GetItemData(i,dwData);
			p = GetTooltipText(dwData);
			if(p)
				m_ctrlTab.SetItemTooltipText(i,p);
		}
	}
	else
		m_ctrlTab.ModifyStyle(CTCS_TOOLTIPS,0,0);
}

void CCustomTabCtrlDemoDlg::OnEditlabelsck() 
{
	if(m_ctrlEditlabels.GetCheck())
		m_ctrlTab.ModifyStyle(0,CTCS_EDITLABELS,0);
	else
		m_ctrlTab.ModifyStyle(CTCS_EDITLABELS,0,0);	
}

void CCustomTabCtrlDemoDlg::OnDragmoveck() 
{
	if(m_ctrlDragmove.GetCheck())
		m_ctrlTab.ModifyStyle(0,CTCS_DRAGMOVE,0);
	else
		m_ctrlTab.ModifyStyle(CTCS_DRAGMOVE,0,0);		
}

void CCustomTabCtrlDemoDlg::OnDragcopyck() 
{
	if(m_ctrlDragcopy.GetCheck())
		m_ctrlTab.ModifyStyle(0,CTCS_DRAGCOPY,0);
	else
		m_ctrlTab.ModifyStyle(CTCS_DRAGCOPY,0,0);		
}

void CCustomTabCtrlDemoDlg::OnRadio1() 
{
	// Default font
	m_ctrlTab.SetControlFont(m_ctrlTab.GetDefaultFont(), TRUE);
}

void CCustomTabCtrlDemoDlg::OnRadio2() 
{	
	LOGFONT lf = {15, 0, 0, 0, FW_NORMAL, 0, 0, 0,
			DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier"};

	m_ctrlTab.SetControlFont(lf, TRUE);
}

void CCustomTabCtrlDemoDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/) 
{
}

LPCTSTR CCustomTabCtrlDemoDlg::GetTooltipText(int nStyle)
{
	static LPCTSTR s[] = {"Sets the static window style to SS_BLACKRECT",
						"Sets the static window style to SS_GRAYRECT",
						"Sets the static window style to SS_WHITERECT"};
	switch(nStyle)
	{
	case SS_BLACKRECT:
		return s[0];
	case SS_GRAYRECT:
		return s[1];
	case SS_WHITERECT:
		return s[2];
	}
	return NULL;
}

void CCustomTabCtrlDemoDlg::OnClosebuttonsck() 
{
	if(m_ctrlClose.GetCheck())
		m_ctrlTab.ModifyStyle(0,CTCS_CLOSEBUTTON,0);
	else
		m_ctrlTab.ModifyStyle(CTCS_CLOSEBUTTON,0,0);	
}

void CCustomTabCtrlDemoDlg::OnRtlyck() 
{
	if(m_ctrlRTL.GetCheck())
	{
		ModifyStyleEx(0,WS_EX_LAYOUTRTL);
		m_ctrlTab.ModifyStyleEx(0,WS_EX_LAYOUTRTL);
	}
	else
	{
		ModifyStyleEx(WS_EX_LAYOUTRTL,0);
		m_ctrlTab.ModifyStyleEx(WS_EX_LAYOUTRTL,0);
	}
	CRect r;
	GetClientRect(r);
	Size(r.Width(),r.Height());
	m_ctrlFixed.Invalidate();
}

void CCustomTabCtrlDemoDlg::OnButtonsafterck() 
{
	if(m_ctrlButtonsAfter.GetCheck())
		m_ctrlTab.ModifyStyle(0,CTCS_BUTTONSAFTER);
	else
		m_ctrlTab.ModifyStyle(CTCS_BUTTONSAFTER,0);	
}

void CCustomTabCtrlDemoDlg::OnRadio3() 
{
	m_ctrlTab.ModifyStyle(CTCS_LEFT,0,0);
	CRect r;
	GetClientRect(r);
	Size(r.Width(),r.Height());	
}

void CCustomTabCtrlDemoDlg::OnRadio4() 
{
	m_ctrlTab.ModifyStyle(CTCS_RIGHT,CTCS_TOP,0);
	CRect r;
	GetClientRect(r);
	Size(r.Width(),r.Height());		
}

void CCustomTabCtrlDemoDlg::OnRadio5() 
{
	m_ctrlTab.ModifyStyle(0,CTCS_LEFT,0);
	CRect r;
	GetClientRect(r);
	Size(r.Width(),r.Height());			
}

void CCustomTabCtrlDemoDlg::OnRadio6() 
{
	m_ctrlTab.ModifyStyle(CTCS_TOP,CTCS_RIGHT,0);
	CRect r;
	GetClientRect(r);
	Size(r.Width(),r.Height());		
}
