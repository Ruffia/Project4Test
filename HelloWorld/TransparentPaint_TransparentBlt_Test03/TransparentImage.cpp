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
	// 获取窗口的客户区域的显示设备上下文环境的句柄
	HDC hDC = ::GetDC(m_hWnd);
	// 创建一个与hDC兼容的内存设备上下文环境
	HDC hBuf = ::CreateCompatibleDC(hDC);
	// 加载位图, 获取位图句柄
	HBITMAP hBmp = GetBitmap();
	// 选择位图句柄到hBuf中, 并获取返回的原来位图句柄
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp);

	BITMAP bm;
	GetObject(hBmp, sizeof(BITMAP), &bm);

	// 透明色为蓝色 绘制
	::TransparentBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hBuf, 0, 0,  bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));

	// 还原位图对象
	::SelectObject(hBuf, hOldBmp);
	// 释放位图
	::DeleteObject(hBmp);
	// 释放兼容的内存设备上下文环境
	::DeleteDC(hBuf);
	// 释放设备上下文环境
	::ReleaseDC(m_hWnd, hDC);
}
