// TransparentImage.cpp : implementation file
//

#include "stdafx.h"
#include "TransparentImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentImage

CTransparentImage::CTransparentImage()
{
}

CTransparentImage::~CTransparentImage()
{
}


BEGIN_MESSAGE_MAP(CTransparentImage, CStatic)
	//{{AFX_MSG_MAP(CTransparentImage)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentImage message handlers

void CTransparentImage::OnPaint() 
{
	HBITMAP hBitmap = GetBitmap();

	BITMAP bm;
	GetObject(hBitmap, sizeof(BITMAP), &bm);

	CBitmap maskBmp;
	maskBmp.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1,NULL); 

	CDC maskDC;                                               //��������DC
	maskDC.CreateCompatibleDC(NULL);                          //��ʼ���豸DC
	CBitmap *oldMaskBmp = maskDC.SelectObject(&maskBmp);

	CBitmap* bmpSquare;                                        //����һ��CBitmap����洢��Ҫ���Ƶ�ͼ(IDΪIDC_SQUARE)
	bmpSquare = CBitmap::FromHandle(hBitmap);                            //����λͼ
                        
	CDC memDC;                                                //�����ڴ�DC
	memDC.CreateCompatibleDC(NULL);                           //��ʼ��DC
	CBitmap *oldMemBmp = memDC.SelectObject(bmpSquare);      //��λͼ�����ڴ�DC��,�����ؾɵ�λͼ
	memDC.SetBkColor(RGB(255,0,255));        

	maskDC.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memDC, 0,0, SRCCOPY);

	CPaintDC dc(this);            //����DC
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memDC, 0, 0,SRCINVERT);

	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &maskDC, 0, 0,SRCAND);

	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memDC, 0, 0,SRCINVERT);

	maskDC.SelectObject(oldMaskBmp);
	memDC.SelectObject(oldMemBmp);
	memDC.DeleteDC();
}
