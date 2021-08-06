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
	// ��ȡ���ڵĿͻ��������ʾ�豸�����Ļ����ľ��
	HDC hDC = ::GetDC(m_hWnd);
	// ����һ����hDC���ݵ��ڴ��豸�����Ļ���
	HDC hBuf = ::CreateCompatibleDC(hDC);
	// ����λͼ, ��ȡλͼ���
	HBITMAP hBmp = GetBitmap();
	// ѡ��λͼ�����hBuf��, ����ȡ���ص�ԭ��λͼ���
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hBuf, hBmp);

	BITMAP bm;
	GetObject(hBmp, sizeof(BITMAP), &bm);

	// ͸��ɫΪ��ɫ ����
	::TransparentBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hBuf, 0, 0,  bm.bmWidth, bm.bmHeight, RGB(255, 0, 255));

	// ��ԭλͼ����
	::SelectObject(hBuf, hOldBmp);
	// �ͷ�λͼ
	::DeleteObject(hBmp);
	// �ͷż��ݵ��ڴ��豸�����Ļ���
	::DeleteDC(hBuf);
	// �ͷ��豸�����Ļ���
	::ReleaseDC(m_hWnd, hDC);
}
