// BitWnd.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "BitWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitWnd
IMPLEMENT_DYNAMIC(CBitWnd,CWnd);

CBitWnd::CBitWnd(BOOL bAutoDelete/* = FALSE*/)
{
   m_bAutoDelete = bAutoDelete;
   m_arCheckBoxes = NULL;
	m_nCountOfBits = 0;
   m_nSpaceExtra = 2;
   m_bAutoDelete = bAutoDelete;
   m_hDlgWnd     = NULL;
}

CBitWnd::~CBitWnd()
{
   delete[] m_arCheckBoxes;
}


BEGIN_MESSAGE_MAP(CBitWnd, CWnd)
	//{{AFX_MSG_MAP(CBitWnd)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
   ON_COMMAND_RANGE(100,227,OnCheckBoxes)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CBitWnd 
int CBitWnd::CreateChecks()
{
   CFont* pFont = GetParent()->GetFont();
   CRect rect(0,0,1,1);//correct size will be set in OnSize
   int nIDCheck = 100;
	for(int i=0; i < m_nCountOfBits; i++)
	{
		CString strCaption;
		strCaption.Format("%d",i);
      DWORD dwStyle = WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX ;
      if( i==0 )
         dwStyle |= WS_GROUP; 
		if(! m_arCheckBoxes[i].Create(
				strCaption,// caption
				dwStyle,//style
				rect,//rect
				this,// parent
            nIDCheck++))
			return FALSE;
      m_arCheckBoxes[i].SetFont(pFont);
	}
   return TRUE;
}
void CBitWnd::EnableChecks(DWORD dwDisableMask /*= 0x00000000*/)
{
   m_dwDisableMask = dwDisableMask;
	for(int i=0; i<m_nCountOfBits; ++i)
   {
      if( ! IsWindowEnabled() )
         m_arCheckBoxes[i].EnableWindow(FALSE);
      else
         // enables all bits > 32
         m_arCheckBoxes[i].EnableWindow( ! ((1<<i) & dwDisableMask) );
   }
}
void CBitWnd::SetCaptions(CStringArray* pArray/*=NULL*/)
{
   for(int i=0 ; i<m_nCountOfBits; i++)
   {
      if(pArray && i<pArray->GetSize())
      {
            CString strTemp;
            strTemp.Format(pArray->ElementAt(i),i);
            m_arCheckBoxes[i].SetWindowText(strTemp);
      }
   }
}
BOOL CBitWnd::GetValue(LPVOID pValue,BOOL bGet /*=TRUE*/)
{
	if(!IsWindow(m_hWnd))
		return FALSE;
   EnableChecks(m_dwDisableMask);

	if(bGet)
	{
      BYTE* pByte = (BYTE*)pValue;
      int   nBitsLeft = m_nCountOfBits;
		do
      {
		   for(int i=0; i<8 && nBitsLeft; i++,nBitsLeft--)
		   {
            *pByte &= ~(1 << i);
			   if(m_arCheckBoxes[m_nCountOfBits-nBitsLeft].GetCheck())
				   *pByte |= (1 << i);
		   }
         pByte++;
      }while(nBitsLeft);
	}
	else
	{
      BYTE* pByte = (BYTE*)pValue;
      int   nBitsLeft = m_nCountOfBits;
		do
      {
		   for(int i=0; i<8 && nBitsLeft; i++,nBitsLeft--)
		   {
				if( *pByte & (1 << i))
			      m_arCheckBoxes[m_nCountOfBits-nBitsLeft].SetCheck(TRUE);
            else
			      m_arCheckBoxes[m_nCountOfBits-nBitsLeft].SetCheck(FALSE);
		   }
         pByte++;
      }while(nBitsLeft);
	}
   return TRUE;
}

void CBitWnd::PreSubclassWindow() 
{
   ASSERT(m_arCheckBoxes == NULL);
	m_arCheckBoxes = new CButton[m_nCountOfBits];
	
	CWnd::PreSubclassWindow();
}

void CBitWnd::PostNcDestroy() 
{
	CWnd::PostNcDestroy();
   if(m_bAutoDelete)
      delete this;
}
void CBitWnd::OnCheckBoxes(UINT nID)
{
   MessageBeep(0); ::PostMessage(m_hDlgWnd,WM_COMMAND,m_ID,0/*(LPARAM)GetSafeHwnd()*/);
}

void CBitWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
   EnableChecks(m_dwDisableMask);
   // resize checkbox-subwindows
	CRect rect;
	GetClientRect(rect);

	int width = rect.Width();
	int height = rect.Height();
   int nSpaces = m_nCountOfBits / 4 -1;//
//C4244: Konvertierung von 'double' in 'long', moeglicher Datenverlust
#pragma warning(push)
#pragma warning(disable: 4244)
	if(m_bVertical)
	{
      //Lowest Bits at the top
		CRect rectButton=rect;
      double fBoxHeight = double(height -(nSpaces*m_nSpaceExtra))/(m_nCountOfBits);
		for(int i=0; i<m_nCountOfBits; ++i)
		{
			CButton* button= &m_arCheckBoxes[i];
			if(IsWindow(*button))
			{
				rectButton.top=		i	*(fBoxHeight)  + (i/4 *m_nSpaceExtra);
				rectButton.bottom=(i+1)	*(fBoxHeight)  + (i/4 *m_nSpaceExtra);
				button->MoveWindow(rectButton,TRUE);
			}
		}
	}
	else
	{
     //Lowest Bits right
		CRect rectButton=rect;
      double fBoxHeight = double(width -(nSpaces*m_nSpaceExtra))/(m_nCountOfBits);
		for(int i=0; i<m_nCountOfBits; ++i)
		{
			CButton* button= &m_arCheckBoxes[m_nCountOfBits -i -1];
			if(IsWindow(*button))
			{
				rectButton.left=	i	   *(fBoxHeight)  + (i/4 *m_nSpaceExtra);
				rectButton.right=(i+1)	*(fBoxHeight)  + (i/4 *m_nSpaceExtra);
				button->MoveWindow(rectButton,TRUE);
			}
		}
	}
#pragma warning(pop)
}
