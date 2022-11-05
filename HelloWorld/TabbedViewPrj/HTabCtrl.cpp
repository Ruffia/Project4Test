// HTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TabbedViewPrj.h"
#include "HTabCtrl.h"
#include "IViewsAccessor.h"

#include "resource.h"

// HsTabCtrl

#define PG_WNDTAB_FONT                 0x00010000
// HsTabCtrl

IMPLEMENT_DYNAMIC(HsTabCtrl, HsWindow)

CString HsTabCtrl::m_stringWindowClass;

/************************************************
   *   Constructor/Destructor 
   *
 * * *
  ***
   *
*/
HsTabCtrl::HsTabCtrl() :
   m_dwFlag(0), m_uHeight(16), m_bTabModified(TRUE), m_pFont(NULL), m_iOffsetToLeft(20),
   m_uOffsetFontGap(3), m_uSelectedViewIndex(0)
{
	 
}

HsTabCtrl::~HsTabCtrl()
{
   if( m_dwFlag & PG_WNDTAB_FONT ) delete m_pFont;
}

/*-------------------------------------------------------------------------------------------------
Name:	   SetHeight()
Type:    Function
Purpose: Set height for tabs

Param:   uHeight = tab height
*/
void HsTabCtrl::SetHeight( UINT uHeight )
{ 
   m_uHeight      = uHeight;
   Invalidate();
}


/************************************************
   *   Virtual functions
   *
 * * *
  ***
   *
*/
/*-------------------------------------------------------------------------------------------------
Name:	   PreCreateWindow()
Type:    Virtual function
Purpose: Register a new window class
*/
BOOL HsTabCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	// LUC Check Immediate
	if(HsTabCtrl::m_stringWindowClass.GetLength() == 0)
	{
	  HsTabCtrl::m_stringWindowClass =
		 ::AfxRegisterWndClass( CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW,
								AfxGetApp()->LoadStandardCursor(IDC_ARROW),
								(HBRUSH)(COLOR_BTNFACE+1),
								NULL );
	}
	
    cs.lpszClass = HsTabCtrl::m_stringWindowClass;
	
	return CWnd::PreCreateWindow(cs);
}

/************************************************
   *   Functions 
   *
 * * *
  ***
   *
*/
/*-------------------------------------------------------------------------------------------------
Name:	   CreateFont()
Type:    Function
Purpose: Create font for text on tabs
*/
void HsTabCtrl::CreateFont()
{
   LOGFONT logfont;

   memset( &logfont, 0, sizeof( LOGFONT ) );
   
   logfont.lfHeight = m_uHeight - 2;
   // LUC CHECK PROB
   _tcscpy(logfont.lfFaceName, _T("MS Sans Serif")); 
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont); 

   m_dwFlag |= PG_WNDTAB_FONT;
}

/*-------------------------------------------------------------------------------------------------
Name:	   DrawTab()
Type:    Function
Purpose: Draw all the tabs

Param:   pDC           = DC that the tabs should be drawn on.
*/
void HsTabCtrl::DrawTab( CDC* pDC )
{
   UINT  uTabIndex;          // tab that are drawn
   //POINT ppoint[4];          // points that will be used to draw tab                                                                   
   POINT ppoint[20];          // points that will be used to draw tab                                                                   
                             
   UINT  uTabHeight;         // the tab height 
   UINT  uDistanceToNextTab; // distance between tabs
   int   iOffsetToLeft;      // distance from left side of client edge                                                                 
                             
   CRect    rect;
   CPen     penBlack( PS_SOLID, 1, RGB(0,0,0) );
   CPen*    ppenOld;

   if( m_bTabModified ) UpdateTabWidth( pDC );             // update tab ?

   ppenOld = pDC->SelectObject( &penBlack );               // select a black pen

   pDC->SetBkMode( TRANSPARENT );                          // just text

   GetClientRect( &rect );                                 // get client rect
   //pDC->MoveTo( rect.left,  rect.top );                     // move to upper left
   //pDC->LineTo( rect.right, rect.top );                   // draw a line from left to right
   pDC->MoveTo( rect.left, rect.bottom - 1 );                     // move to upper left
   pDC->LineTo( rect.right, rect.bottom - 1 );                   // draw a line from left to right

   uTabHeight         = m_uHeight - 1;
   uDistanceToNextTab = uTabHeight / 2;
   iOffsetToLeft      = m_iOffsetToLeft;

   for( uTabIndex = 0; uTabIndex < (UINT)m_dwarrayTabWidth.GetSize(); uTabIndex++ )
   {
      // ***
      // set all points for tab, then we will be able to draw it
      // ***
	  int num_of_points = 6;
      
	  ppoint[0].x = iOffsetToLeft;                         // ""
      ppoint[0].y = 0;
	  int init_x = iOffsetToLeft;
	  int init_y = 0;
	  //ppoint[5].x = iOffsetToLeft;   // ""
	  //ppoint[5].y = 0;

	  
      //iOffsetToLeft -= uDistanceToNextTab;                 // "/" 
      ppoint[1].x   =  iOffsetToLeft - uDistanceToNextTab;
      ppoint[1].y   =  uTabHeight / 2;	  
	  
	  ppoint[2].x   =  iOffsetToLeft - uDistanceToNextTab;
      ppoint[2].y   =  uTabHeight;
	  /*if(uTabIndex == m_uSelectedViewIndex)
	  {
		  ppoint[2].x   =  iOffsetToLeft - 2 * uDistanceToNextTab;
	  }	*/  
      //draw tab-text 
      pDC->TextOut( ppoint[0].x + m_uOffsetFontGap,         
                    1,
                    m_sarrayViewName[uTabIndex] );

      iOffsetToLeft += m_dwarrayTabWidth[uTabIndex];       // "____"
      
	  ppoint[3].x   =  iOffsetToLeft + uDistanceToNextTab;
      ppoint[3].y   =  uTabHeight;

      if( uTabIndex == (UINT)(m_dwarrayTabWidth.GetSize() - 1) ) // "\____/"
      {
         iOffsetToLeft += uDistanceToNextTab;
         ppoint[4].x   =  iOffsetToLeft;
         ppoint[4].y   =  0;	
		 
		 ppoint[5].x   =  init_x;
         ppoint[5].y   =  init_y;	
		 num_of_points = 6;
      }
      else
	  {
         
		 ppoint[4].x   =  iOffsetToLeft;
         ppoint[4].y   =  uTabHeight;
		 ppoint[5].x   =  iOffsetToLeft;
         ppoint[5].y   =  uTabHeight / 2;
		 
		 iOffsetToLeft += (uDistanceToNextTab);
         
		 ppoint[6].x   =  iOffsetToLeft;
         ppoint[6].y   =  0;
		 
		 ppoint[7].x = init_x;
		 ppoint[7].y = init_y;		 
		 num_of_points = 8;
         //iOffsetToLeft -= (uDistanceToNextTab / 2);		 
		 //iOffsetToLeft += uDistanceToNextTab;		 
      }
	  
	  if(uTabIndex == m_uSelectedViewIndex)
	  {
		  CRgn   rgn;
		  CBrush brush;
		  brush.CreateSolidBrush( ::GetSysColor( COLOR_WINDOW ) );
		  rgn.CreatePolygonRgn( ppoint, num_of_points, ALTERNATE );	  	  
		  //pDC->SetBkColor(::GetSysColor( COLOR_WINDOW ));
		  pDC->FillRgn( &rgn, &brush );		  
		  pDC->TextOut( ppoint[0].x + m_uOffsetFontGap,         
                    1,
                    m_sarrayViewName[uTabIndex]);
	  }   
      pDC->Polyline( ppoint, num_of_points );
   }

   pDC->SelectObject( ppenOld );
}

/*-------------------------------------------------------------------------------------------------
Name:	   DrawSelectedTab
Type:    Function
Purpose: Draw the tab for selected view

Param:   pDC           = DC that the tabs should be drawn on.
*/
void HsTabCtrl::DrawSelectedTab( CDC* pDC )
{	
   CRgn   rgn;               // filling region
   CBrush brush;             // brush that the selected tab will be filled with

   UINT  uTabHeight;         // the tab height
   UINT  uDistanceToNextTab; // distance between tabs
   int   iOffsetToLeft;      // distance from left side of client edge

   POINT  ppoint[4];         // points that will be used to draw tab

   uTabHeight         = m_uHeight - 1;                     // set tab height
   uDistanceToNextTab = uTabHeight / 2;                    // distance to next tab
   iOffsetToLeft      = m_iOffsetToLeft;                   // distance to left side

   // *** loop to selected tab ***
   UINT uCounter = 0;
   for( uCounter = 0; uCounter < m_uSelectedViewIndex; uCounter++ )
   {
      iOffsetToLeft += m_dwarrayTabWidth[uCounter];
      iOffsetToLeft += uDistanceToNextTab;
   }

   // ***
   // set all points for selected tab, then we will be able to draw it
   // ***
   ppoint[0].x = iOffsetToLeft;                            // ""
   ppoint[0].y = 0;

   iOffsetToLeft += uDistanceToNextTab;                    // "\"
   ppoint[1].x   =  iOffsetToLeft;
   ppoint[1].y   =  uTabHeight;

   iOffsetToLeft += m_dwarrayTabWidth[uCounter];           // "\____"
   ppoint[2].x   =  iOffsetToLeft;
   ppoint[2].y   =  uTabHeight;

   iOffsetToLeft += uDistanceToNextTab;                    // "\____/"
   ppoint[3].x   =  iOffsetToLeft;
   ppoint[3].y   =  0;

   brush.CreateSolidBrush( ::GetSysColor( COLOR_WINDOW ) );
   rgn.CreatePolygonRgn( ppoint, 4, ALTERNATE );

   pDC->FillRgn( &rgn, &brush );
   pDC->Polyline( ppoint, 4 );
   pDC->TextOut( ppoint[1].x + m_uOffsetFontGap, 1, m_sarrayViewName[uCounter] );
}

/*-------------------------------------------------------------------------------------------------
Name:	   UpdateTabWidth()
Type:    Function
Purpose: Update widenes for all tabs

Param:   pDC = DC that the tabs should be drawn on.
*/
void HsTabCtrl::UpdateTabWidth( CDC* pDC )
{
   CSize size;

   m_dwarrayTabWidth.RemoveAll();

   for( int iCounter = 0; iCounter < m_sarrayViewName.GetSize(); iCounter++ )
   {
      // get text size
      size = pDC->GetTextExtent( m_sarrayViewName[iCounter] );
      // add the width for text plus gap to array
      m_dwarrayTabWidth.Add( size.cx + (m_uOffsetFontGap << 1) );
   }

   m_bTabModified = FALSE;                                 // tabs updated
}


BEGIN_MESSAGE_MAP(HsTabCtrl, HsWindow)
	//{{AFX_MSG_MAP(HsTabCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SIZEPARENT, OnSizeParent)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP		
	ON_WM_CREATE()
END_MESSAGE_MAP()

/************************************************
   *   Messages
   *
 * * *
  ***
   *
*/

/*-------------------------------------------------------------------------------------------------
Name:	   OnPaint()
Type:    Message
Purpose: Draw all the information in the tab window
*/
void HsTabCtrl::OnPaint() 
{
   CFont*   pfontOld;   // pointer to old font

   CPaintDC dc(this);                                      // device context for painting

   if( m_pFont == NULL ) CreateFont();                     // if no tab font, create one

   pfontOld = dc.SelectObject( m_pFont );                  // select tab font

   if((m_pArrayViews != NULL) && (m_pArrayViews->GetSize() > 0))
   {
		DrawTab( &dc );                                         // draw the tabs
		//DrawSelectedTab( &dc );                                 // draw th selected tab
   }
   dc.SelectObject( pfontOld );                            // select old font
}



/*-------------------------------------------------------------------------------------------------
Name:	   OnLButtonDown()
Type:    Message
Purpose: Check if klicked on a tab, and if so switch view
*/
void HsTabCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
   int  iOffsetToLeft;
   UINT uDistanceToNextTab;

   uDistanceToNextTab = (m_uHeight - 1) / 2;
   
   iOffsetToLeft = m_iOffsetToLeft;

   // *** check if clicked on a tab ***
   for( UINT uCounter = 0; uCounter < (UINT)m_dwarrayTabWidth.GetSize(); uCounter++ )
   {
      iOffsetToLeft += uDistanceToNextTab;

      if( ( point.x >= (iOffsetToLeft - 1) ) && 
          ( point.x <= (int)(iOffsetToLeft + m_dwarrayTabWidth[uCounter] + 1) ) )
      {		 
         SelectView( uCounter );
         break;
      }

      iOffsetToLeft += m_dwarrayTabWidth[uCounter];
   }

	CWnd::OnLButtonDown(nFlags, point);
}

//void HsTabCtrl::AddView(CView* pView)
void HsTabCtrl::NotifyNewViewAdded(CView* pNewView)
{
	//m_arrayViews.Add(pView);	
	m_sarrayViewName.Add(pNewView->GetDocument()->GetTitle());
	SetModified();
	Invalidate();	
	
}

void HsTabCtrl::NotifyViewDeleted(UINT uIndex)
{
	//m_arrayViews.Add(pView);	
	m_sarrayViewName.RemoveAt(uIndex);
	SetModified();
	Invalidate();	
	
}


void HsTabCtrl::SelectView(UINT uIndex)
{
	
	m_uSelectedViewIndex = uIndex;
	CArray<CView*, CView*&>& arrayViews = *m_pArrayViews;
	CView* pView = (CView*) arrayViews[uIndex];	
	
	pView->GetParentFrame()->ShowWindow(SW_SHOW);
	pView->GetParentFrame()->ActivateFrame();		
	
	Invalidate();		

}

void HsTabCtrl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	m_btnListTiledWnds.MoveWindow(cx-26, 1, 20, cy - 2);
}

LRESULT HsTabCtrl::OnSizeParent(WPARAM, LPARAM lParam)
{
	AFX_SIZEPARENTPARAMS* layout = (AFX_SIZEPARENTPARAMS*)lParam;	
	
    return 0;
}

void HsTabCtrl::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);		
	// TODO: Add your message handler code here
}

void HsTabCtrl::NotifyActiveViewChanged(CView* pActiveView, bool bRepaint/*=TRUE*/)
{
	CArray<CView*, CView*&>& arrayViews = *m_pArrayViews;
	
	for(int i = 0; i < arrayViews.GetSize(); i++)
	{
		CView* pView = (CView*)arrayViews[i];
		if(pView==pActiveView)
		{
			m_uSelectedViewIndex = i;
			break;
		}
	}

	if(bRepaint)
	{
		Invalidate();
		RedrawWindow();
	}
}

void HsTabCtrl::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	
	CWnd::PreSubclassWindow();
}

int HsTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_btnListTiledWnds.Create(_T(""), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, 1);
	m_btnListTiledWnds.AttachEventHandler(this);
	m_btnListTiledWnds.setType(HsButton::hotPushButton);
	m_btnListTiledWnds.setBitmapId(IDB_BITMAP_DOWNARROW, RGB(255, 0, 0));
	m_btnListTiledWnds.setGradient (true);	

	
	
	return 0;
}

int HsTabCtrl::OnLHsButtonDown (HsButton* sender, UINT nFlags, CPoint point)
{	
	if(m_wndListTiledWnds.GetSafeHwnd() == NULL)
	{
		CWnd* pWnd = AfxGetMainWnd();
		m_wndListTiledWnds.Create(IDD_DIALOG1, pWnd);
	}

	CRect wr;
	GetWindowRect(wr);

	CRect rc;
	m_wndListTiledWnds.GetClientRect(rc);	
	m_wndListTiledWnds.SetWindowPos(&CWnd::wndTop, wr.right - rc.Width() - 6, wr.bottom + 1, 0, 0, SWP_NOSIZE | SWP_NOZORDER);	
	m_wndListTiledWnds.ShowWindow(SW_SHOW);
	

	return 0;
}	

int HsTabCtrl::OnLHsButtonUp (HsButton* sender, UINT nFlags, CPoint point)
{
	return 0;
}