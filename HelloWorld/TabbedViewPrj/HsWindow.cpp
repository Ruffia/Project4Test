// HsWindow.cpp : implementation file
//

#include "stdafx.h"
#include "TabbedViewPrj.h"
#include "HsWindow.h"


// HsWindow

IMPLEMENT_DYNAMIC(HsWindow, CWnd)

typedef UINT (CALLBACK* MSIMG32callBack)(HDC,CONST PTRIVERTEX,DWORD,CONST PVOID,DWORD,DWORD);

HsWindow::HsWindow()
{

}

HsWindow::~HsWindow()
{
}

void HsWindow::ResizeWindow(int cx, int cy, BOOL bRedraw/*=FALSE*/)
{
	CRect rc;
	this->GetClientRect(rc);
	this->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW);	
	this->Invalidate();
	if(!bRedraw)
	{
		this->ValidateRect(rc);
	}
	this->UpdateWindow();	
}

void HsWindow::DrawGradientRect(CDC *pDC, CRect r, COLORREF cLeft, COLORREF cRight, BOOL bVertical)
{
	/*MSIMG32callBack  m_dllGradientFillFunc;
	HINSTANCE m_hMsimg32 = LoadLibrary (_T("msimg32.dll"));
      if (m_hMsimg32 != NULL) {
          m_dllGradientFillFunc =
            ((MSIMG32callBack) GetProcAddress (m_hMsimg32, "GradientFill"));
          ASSERT (m_dllGradientFillFunc != NULL);
      }
  // Use GradientFill function from MSIMG32.dll if possible
  if (m_dllGradientFillFunc != NULL) {

		  TRIVERTEX rcVertex[2];
		  rcVertex[0].x = r.left;
		  rcVertex[0].y = r.top;
		  rcVertex[0].Red = (unsigned short) (GetRValue (cLeft) << 8);
		  rcVertex[0].Green = (unsigned short) (GetGValue (cLeft) << 8);
		  rcVertex[0].Blue = (unsigned short) (GetBValue (cLeft) << 8);
		  rcVertex[0].Alpha = 0;

		  rcVertex[1].x = r.right;
		  rcVertex[1].y = r.bottom;
		  rcVertex[1].Red = (unsigned short) (GetRValue (cRight) << 8);
		  rcVertex[1].Green = (unsigned short) (GetGValue (cRight) << 8);
		  rcVertex[1].Blue = (unsigned short) (GetBValue (cRight) << 8);
		  rcVertex[1].Alpha = 0;
		  
		  GRADIENT_RECT gRect;
		  gRect.UpperLeft = 0;
		  gRect.LowerRight = 1;
		  
		  // fill the area 
		  m_dllGradientFillFunc
        (*pDC, rcVertex, 2, &gRect, 1,
         bVertical ? GRADIENT_FILL_RECT_V : GRADIENT_FILL_RECT_H);

		 if(m_hMsimg32 != NULL)
		 {
			 ::FreeLibrary(m_hMsimg32);
		 }

      return;
  }*/

  // Otherwise, do a manual gradient fill
	CRect stepR;					// rectangle for color's band
	COLORREF color;				// color for the bands
	float fStep;
	
	if(bVertical)
		fStep = ((float)r.Height())/255.0f;	
	else
		fStep = ((float)r.Width())/255.0f;	// width of color's band
	
	for (int iOnBand = 0; iOnBand < 255; iOnBand++) 
	{
		// set current band
		if(bVertical)
		{
			SetRect(&stepR,
				r.left, 
				r.top+(int)(iOnBand * fStep),
				r.right, 
				r.top+(int)((iOnBand+1)* fStep));	
		}
		else
		{
			SetRect(&stepR,
				r.left+(int)(iOnBand * fStep), 
				r.top,
				r.left+(int)((iOnBand+1)* fStep), 
				r.bottom);	
		}

		// set current color
		color = RGB((GetRValue(cRight)-GetRValue(cLeft))*((float)iOnBand)/255.0f+GetRValue(cLeft),
			(GetGValue(cRight)-GetGValue(cLeft))*((float)iOnBand)/255.0f+GetGValue(cLeft),
			(GetBValue(cRight)-GetBValue(cLeft))*((float)iOnBand)/255.0f+GetBValue(cLeft));
		// fill current band
		pDC->FillSolidRect(stepR,color);
	}
}


BEGIN_MESSAGE_MAP(HsWindow, CWnd)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// HsWindow message handlers



BOOL HsWindow::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CRect rc;
	GetClientRect(rc);
	DrawGradientRect(pDC, rc, RGB(160, 190, 230), RGB(250, 250, 250), TRUE);
	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}
