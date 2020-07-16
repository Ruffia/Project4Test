#include "stdafx.h"
#include "DIB.h"

IMPLEMENT_DYNAMIC(CDIB, CGdiObject);

//////////////////////////////////////////////////////////////////////
//
// CDIB
//
// �豸�޹�λͼ��(�汾1.0)
//
// ��ɹ���:
//     �豸�޹�λͼ�Ĵ���,��ʾ,����,����,��׽λͼ
//
// �汾����: ����,��־
//
//////////////////////////////////////////////////////////////////////

//���캯��
CDIB::CDIB() : CGdiObject()
{
}

//��������
CDIB::~CDIB()
{
	DeleteObject();
}


//////////////////////////////////////////////////////////////////
// 
// CreateDIB(int cx, int cy, UINT ibitcount, const void* lpBits) 
// 
// ��ɹ���:
//     ����DIBλͼ
//
// �������:
//	   ͼ���� cx
//     ͼ��߶� cy
//     ͼ��λ�� ibitcount 
//     ͼ������ lpBits 
//
// ���ز���:
//	   �Ƿ�ɹ�
//
//////////////////////////////////////////////////////////////////

//����DIBλͼ
BOOL CDIB::CreateDIB(int cx, int cy, UINT ibitcount, const void* lpBits) 
{
	ASSERT((ibitcount == 1) || (ibitcount == 4) || 
			(ibitcount == 8) || (ibitcount == 16) 
			|| (ibitcount == 24) ||(ibitcount == 32))	;

	// Create a BITMAPINFOHEADER structure to describe the DIB
	//������Ϣͷ
    int iSize = sizeof(BITMAPINFOHEADER);// + 256*sizeof(RGBQUAD);
	BITMAPINFO* pBMI;
	BYTE *pByte;

	switch(ibitcount){
		case 8:
			iSize += 4*4;
			break;
		case 1:
		case 4:
		case 16:
		case 24:
		case 32:
			break;
		default:
			break;
	}

	pByte = new BYTE[iSize];
	pBMI = (BITMAPINFO*) pByte;
    memset(pBMI, 0, iSize);

	pBMI->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	pBMI->bmiHeader.biWidth       = cx;
	pBMI->bmiHeader.biHeight      = cy;
	pBMI->bmiHeader.biPlanes      = 1;
	pBMI->bmiHeader.biBitCount    = ibitcount;
	pBMI->bmiHeader.biCompression = BI_RGB; // to use this flag.

	BOOL bRet = CreateDIBIndirect(pBMI, lpBits);
	delete[] pByte;
	
	return(bRet);
}


//////////////////////////////////////////////////////////////////
// 
// CreateDIBIndirect(LPBITMAPINFO pBMI, const void* lpBits)
// 
// ��ɹ���:
//     ����DIBλͼ
//
// �������:
//	   λͼ��Ϣ�ṹָ�� pBMI
//     ͼ������ lpBits 
//
// ���ز���:
//	   �Ƿ�ɹ�
//
//////////////////////////////////////////////////////////////////

//����DIBλͼ
BOOL CDIB::CreateDIBIndirect(LPBITMAPINFO pBMI, const void* lpBits)
{
	//�ݻ�ԭ����
	if (m_hObject != NULL)
	{
		DeleteObject();
	}

	// Create the DIB section.
	//����
	CDC *pDC = new CDC;
	pDC->CreateCompatibleDC(NULL);
	LPVOID pBits;
	HBITMAP hDIB = ::CreateDIBSection(pDC->GetSafeHdc(),
							pBMI,
							DIB_RGB_COLORS,
                           	&pBits,
                           	NULL,
                           	0);
	delete pDC;

	ASSERT(hDIB);
	ASSERT(pBits);
	Attach(hDIB);

	//����ͼ������
	SetDIBBits(GetWidthBytes() * GetHeight(), lpBits);

	return TRUE;
}


//////////////////////////////////////////////////////////////////
// 
// SetDIBBits(DWORD dwCount,const void * lpBits)
// 
// ��ɹ���:
//     ����ͼ������,�� lpBits �����ݿ�����ͼ��
//
// �������:
//	   λͼ���ݴ�С dwCount
//     ͼ������ lpBits 
//
// ���ز���:
//	   ���������ݴ�С
//
//////////////////////////////////////////////////////////////////

// Set DIB's bits 
// ����ͼ������
DWORD CDIB::SetDIBBits(DWORD dwCount,const void * lpBits)
{
	if(lpBits != NULL){
		LPVOID pBits = GetBits();
		memcpy(pBits,lpBits,dwCount);
		return dwCount;
	}
	return 0;
}


//////////////////////////////////////////////////////////////////
// 
// GetDIBBits(DWORD dwCount, LPVOID lpBits)
// 
// ��ɹ���:
//     �õ�ͼ������.
//     ��� lpBits Ϊ��,�򷵻�ͼ������ָ��;
//	   ��� lpBits ��Ϊ��,
//             ��ͼ�����ݿ�������ָ��,
//             ������ͼ������ָ��;
//
// �������:
//	   ������λͼ���ݴ�С dwCount
//     ͼ������ lpBits 
//
// ���ز���:
//	   ͼ������ָ��
//
//////////////////////////////////////////////////////////////////

// Get DIB's bits
// �õ�ͼ������
LPVOID CDIB::GetDIBBits(DWORD dwCount, LPVOID lpBits)
{
	LPVOID pBits = GetBits();
	if(lpBits != NULL){
		memcpy(lpBits,pBits,dwCount);
		return pBits;
	}
	else{
		return pBits;
	}
}


//////////////////////////////////////////////////////////////////
// 
// operator = (CDIB& copy)
// 
// ��ɹ���:
//     ���ظ�ֵ��
//
// �������:
//	   Ҫ������λͼ copy
//
// ���ز���:
//	   ��ͼ������
//
//////////////////////////////////////////////////////////////////

//���ظ�ֵ��
CDIB& CDIB::operator = (CDIB& copy)
{
 	DIBSECTION DibSection;
	//�õ�ԭͼ����Ϣ
	copy.GetDibSection(&DibSection);
	int nSize = DibSection.dsBmih.biClrUsed*sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);

	//������ͼ����Ϣͷ�ڴ�
	BYTE *pByte = new BYTE[nSize];
	//������Ϣ
	memcpy(pByte, &(DibSection.dsBmih), sizeof(BITMAPINFOHEADER));

	CDC *pdc = copy.GetDC();
	//�õ���ɫ����Ϣ
	::GetDIBColorTable(pdc->GetSafeHdc(), 0, DibSection.dsBmih.biClrUsed,
						(RGBQUAD*)(pByte+sizeof(BITMAPINFOHEADER)));
	copy.ReleaseDC(pdc);

	//������λͼ
	BITMAPINFO *pBMI = (BITMAPINFO*)pByte;
	CreateDIBIndirect(pBMI);

	//����ͼ����Ϣ
	int nTotalSize = copy.GetWidthBytes() * copy.GetHeight();
	memcpy(GetBits(), copy.GetBits(), nTotalSize);

	delete[] pByte;
	return(*this);
}


//////////////////////////////////////////////////////////////////
// 
// SetPalette(UINT uStartIndex, UINT cEntries, CONST RGBQUAD *pColors)
// 
// ��ɹ���:
//     ���õ�ɫ��
//
// �������:
//	   ��ɫ�忪ʼ���� uStartIndex
//     ��ɫ����� cEntries
//     ��ɫ���� pColors
//
// ���ز���:
//	   ��
//
//////////////////////////////////////////////////////////////////

// Set the color table in the DIB section.
// ���õ�ɫ��
void CDIB::SetPalette(UINT uStartIndex, UINT cEntries, CONST RGBQUAD *pColors)
{
	HDC hdc = ::CreateCompatibleDC(NULL);
	HBITMAP hOld = (HBITMAP)::SelectObject(hdc, m_hObject);

	::SetDIBColorTable(hdc, uStartIndex, cEntries, pColors);
	
	::SelectObject(hdc, hOld);
	::DeleteObject(hdc);
}


//////////////////////////////////////////////////////////////////
// 
// SetPalette(CPalette* pPal)
// 
// ��ɹ���:
//     ���õ�ɫ��
//
// �������:
//	   ��ɫ��ṹָ�� pPal
//
// ���ز���:
//	   ��
//
//////////////////////////////////////////////////////////////////

// ���õ�ɫ��
void CDIB::SetPalette(CPalette* pPal)
{
    ASSERT(pPal);

    // get the colors from the palette
    int iColors = 0;
    pPal->GetObject(sizeof(iColors), &iColors);
    ASSERT(iColors > 0);
    PALETTEENTRY* pPE = new PALETTEENTRY[iColors];
    pPal->GetPaletteEntries(0, iColors, pPE);

    // Build a table of RGBQUADS
    RGBQUAD* pRGB = new RGBQUAD[iColors];
    ASSERT(pRGB);
    for (int i = 0; i < iColors; i++) {
        pRGB[i].rgbRed = pPE[i].peRed;
        pRGB[i].rgbGreen = pPE[i].peGreen;
        pRGB[i].rgbBlue = pPE[i].peBlue;
        pRGB[i].rgbReserved = 0;
    }

	SetPalette(0, iColors, pRGB);

    delete [] pRGB;
    delete [] pPE;
}


//////////////////////////////////////////////////////////////////
// 
// GetDC(void)
// 
// ��ɹ���:
//     �õ���λͼ��ص��豸
//
// �������:
//	   ��
//
// ���ز���:
//	   ��λͼ��ص��豸ָ��
//
//////////////////////////////////////////////////////////////////

//�õ���λͼ��ص��豸
CDC* CDIB::GetDC(void)
{
	CDibDC* pdc = new CDibDC;
	if(pdc == NULL)
		return(NULL);
	pdc->CreateCompatibleDC(NULL);
	pdc->m_hOld = (HBITMAP)::SelectObject(pdc->GetSafeHdc(), GetSafeHandle());

	return(pdc);
}


//////////////////////////////////////////////////////////////////
// 
// ReleaseDC(CDC *pdc)
// 
// ��ɹ���:
//     �õ���λͼ��ص��豸
//
// �������:
//	   ��λͼ��ص��豸
//
// ���ز���:
//	   �Ƿ�ɹ�
//
//////////////////////////////////////////////////////////////////

//�ͷŵõ�����λͼ��ص��豸
BOOL CDIB::ReleaseDC(CDC *pdc)
{
	ASSERT(pdc != NULL);
	if(pdc->IsKindOf(RUNTIME_CLASS(CDibDC))){
		delete pdc;
		return(TRUE);
	}
	return(FALSE);
}

#ifdef _DEBUG
void CDIB::Dump(CDumpContext& dc) const
{
	CGdiObject::Dump(dc);

	if (m_hObject == NULL)
		return;

	BITMAP bm;
	VERIFY(GetObject(sizeof(bm), &bm));
	dc << "bm.bmType = " << bm.bmType;
	dc << "\nbm.bmHeight = " << bm.bmHeight;
	dc << "\nbm.bmWidth = " << bm.bmWidth;
	dc << "\nbm.bmWidthBytes = " << bm.bmWidthBytes;
	dc << "\nbm.bmPlanes = " << bm.bmPlanes;
	dc << "\nbm.bmBitsPixel = " << bm.bmBitsPixel;

	dc << "\n";
}
#endif


//////////////////////////////////////////////////////////////////
// 
// LoadBmp(LPCSTR filename)
// 
// ��ɹ���:
//     ����ͼ���ļ�
//
// �������:
//	   λͼ�ļ��� filename
//
// ���ز���:
//	   �Ƿ�ɹ�(-1Ϊ���ɹ�)
//
//////////////////////////////////////////////////////////////////

//����ͼ���ļ�
int CDIB::LoadBmp(LPCSTR filename)
{
	//���ļ�
	CFile file(filename,CFile::modeRead|CFile::shareDenyNone);

	WORD	bfType;
	DWORD   bfSize; 
	
	//�����ļ�ͷ
	file.Read(&bfType,sizeof(WORD));
	file.Read(&bfSize,sizeof(DWORD));
	if(bfSize <= 0)
	{
		file.Close();
		return -1;
	}
	
	//�Ƿ�Bmp�ļ�
	if (bfType != (((WORD)'M'<<8) + 'B'))
	{
		file.Close();
		return -1;
	}

	DWORD   bfOffBits; 
	//�ҵ�λͼ������ʼƫ�Ʋ�����
	file.Seek(2*sizeof(WORD),CFile::current);
	file.Read(&bfOffBits,sizeof(DWORD));

	LPVOID DibBuf;
	
	DibBuf = (LPVOID)new char[bfSize];

	if(DibBuf == NULL)
	{
		file.Close();
		return -1;
	}

	//����λͼ����
	file.ReadHuge(DibBuf,bfSize);
	file.Close();
	
	LPBITMAPINFO pBMI;
	
	int size = bfOffBits - 14;
	pBMI = (LPBITMAPINFO)new char[sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)];

	//������Ϣͷ
	memcpy(pBMI,DibBuf,size);
	LPVOID lpBits = (LPVOID)((LPSTR)DibBuf + size);

	//����λͼ
	CreateDIBIndirect(pBMI, lpBits);

	delete pBMI;
	delete DibBuf;
	return 1;
}


//////////////////////////////////////////////////////////////////
// 
// GetColorUsed()
// 
// ��ɹ���:
//     �õ�ʹ�õ���ɫ��
//
// �������:
//	   ��
//
// ���ز���:
//	   ��ɫ��
//
//////////////////////////////////////////////////////////////////

//�õ�ʹ�õ���ɫ��
int CDIB::GetColorUsed()
{
	LPBITMAPINFOHEADER pBMIH;
	DIBSECTION DibSection;
	GetDibSection(&DibSection);
	pBMIH = &DibSection.dsBmih;
	return pBMIH->biClrUsed;
}

//////////////////////////////////////////////////////////////////
// 
// GetPalette()
// 
// ��ɹ���:
//     �õ�ʹ�õĵ�ɫ��
//
// �������:
//	   ��
//
// ���ز���:
//	   ��ɫ��ָ��,����Ӧ�ͷ�
//
//////////////////////////////////////////////////////////////////

//�õ�ʹ�õĵ�ɫ��
CPalette * CDibDC::GetPalette()
{
	LOGPALETTE * pLogPal = (LOGPALETTE *)new char[sizeof(LOGPALETTE) +
		 256 * sizeof(PALETTEENTRY)];

	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = 256;

	HDC hdc = GetSafeHdc();
	RGBQUAD pRGB[256];
	::GetDIBColorTable(hdc, 0, 256,pRGB);
	
	for(int i = 0 ; i < 256 ; i ++)
	{
		pLogPal->palPalEntry[i].peRed = pRGB[i].rgbRed;
		pLogPal->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
		pLogPal->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
		pLogPal->palPalEntry[i].peFlags = 0;
	}
	
	CPalette * pPal = NULL;
	pPal = new CPalette;	
	pPal->CreatePalette(pLogPal);

	delete pLogPal;
	return pPal;
}

//////////////////////////////////////////////////////////////////
// 
// GetBitmapInfo(void)
// 
// ��ɹ���:
//     �õ�λͼ��Ϣ
//
// �������:
//	   ��
//
// ���ز���:
//	   λͼ��Ϣָ��,����Ӧ�ͷ�
//
//////////////////////////////////////////////////////////////////

//�õ�λͼ��Ϣ
LPBITMAPINFO CDIB::GetBitmapInfo(void)
{
	DIBSECTION DibSection;
	GetDibSection(&DibSection);
	int nSize = DibSection.dsBmih.biClrUsed*sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	
	BYTE *pByte = new BYTE[nSize];
	memcpy(pByte, &(DibSection.dsBmih), sizeof(BITMAPINFOHEADER));
	CDC *pdc = GetDC();
	::GetDIBColorTable(pdc->GetSafeHdc(), 0, DibSection.dsBmih.biClrUsed,
						(RGBQUAD*)(pByte+sizeof(BITMAPINFOHEADER)));
	ReleaseDC(pdc);
	BITMAPINFO *pBMI = (BITMAPINFO*)pByte;
	return(pBMI);
}


//////////////////////////////////////////////////////////////////
// 
// SaveBmp(LPCSTR filename)
// 
// ��ɹ���:
//     ����λͼ�ļ�
//
// �������:
//	   �ļ��� filename
//
// ���ز���:
//	   �Ƿ�ɹ�
//
//////////////////////////////////////////////////////////////////

//�����ļ�
int CDIB::SaveBmp(LPCSTR filename)
{
	BITMAPFILEHEADER hdr;

	//���ļ�
	CFile file(filename,CFile::modeWrite|CFile::modeCreate);

	//�ļ�ͷ
	hdr.bfType = ((WORD)'M'<<8) + 'B';
	LPBITMAPINFO pbi = GetBitmapInfo(); 
	PBITMAPINFOHEADER pbih = (PBITMAPINFOHEADER) pbi; 

	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + pbih->biSizeImage); 

    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 

    // Compute the offset to the array of color indices. 
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof (RGBQUAD); 
	
    //д���ļ�ͷ
	file.Write((LPVOID) &hdr, sizeof(BITMAPFILEHEADER));

	//д����Ϣͷ
    file.Write((LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
                  + pbih->biClrUsed * sizeof (RGBQUAD)); 

    // Copy the array of color indices into the .BMP file. 
	//д������
    int nTotal = pbih->biSizeImage; 
	
    LPVOID lpBits = GetBits(); 
    file.WriteHuge(lpBits, nTotal);

	//�ر��ļ�
	file.Close();	
	
	delete pbi;

	return 1;
}
void CDIB::Show(CWnd *pWnd)
{
HDC hdc=::GetDC(pWnd->m_hWnd);
HBITMAP bmp=HBITMAP(m_hObject);
HDC hdcmem=::CreateCompatibleDC(hdc);
::SelectObject(hdcmem,bmp);
::BitBlt(hdc,0,0,GetWidth(),GetHeight(),hdcmem,0,0,SRCCOPY);
::DeleteObject(bmp);
}

//////////////////////////////////////////////////////////////////
// 
// CaptureDIB(CWnd * pWnd, const CRect& capRect)
// 
// ��ɹ���:
//     ��׽����ͼ��
//
// �������:
//	   ����ָ�� pWnd
//     ��׽�Ĵ�С capRect
//
// ���ز���:
//	   �Ƿ�ɹ�
//
//////////////////////////////////////////////////////////////////

//��׽����ͼ��
BOOL CDIB::CaptureDIB(CWnd * pWnd, const CRect& capRect)
{
	BOOL ret = false;

	if(pWnd == NULL)
		return false;

	CDC * pPlayDc = pWnd->GetDC();

	if(pPlayDc == NULL)
		return false;

	CRect Rect;
	if(capRect.IsRectEmpty())
		pWnd->GetClientRect(Rect);
	else
		Rect = capRect;

	//�õ�ͼ����ɫ��
	UINT nBitCount = pPlayDc->GetDeviceCaps(BITSPIXEL);

	//����λͼ
	if(CreateDIB(Rect.Width(), Rect.Height(), nBitCount))
	{
		CDC * pCopyDc = GetDC();
		
		if(pCopyDc == NULL)
		{
			pWnd->ReleaseDC(pPlayDc);		
			return false;
		}

		pWnd->ShowWindow(SW_SHOW);
		//��׽
		if(pCopyDc->BitBlt(0, 0, Rect.Width(), Rect.Height(), pPlayDc, 0, 0, SRCCOPY))
			ret = true;
		
		ReleaseDC(pCopyDc);
	}

	pWnd->ReleaseDC(pPlayDc);		
	return ret;
}


////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// CDibDC
//
// �豸�޹�λͼ�豸��(�汾1.0)
//
// ��ɹ���:
//     ���豸�޹�λͼ�������
//
// �汾����: ����,��־
//
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CDibDC, CDC);

CDibDC::CDibDC()
{
	m_hOld = NULL;
}

CDibDC::~CDibDC()
{
	if(m_hOld != NULL){
		::SelectObject(GetSafeHdc(), m_hOld);
	}
}

