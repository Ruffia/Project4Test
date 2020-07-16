#ifndef __DIB_H
#define __DIB_H
//
// CDIB -
// CDibDC -
//
// Implements a simple encapsulation of a DIB section and a DC.
//
//

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


class CDIB;
class CDibDC;

class CDIB : public CGdiObject
{
	DECLARE_DYNAMIC(CDIB)

public:
	//�ɾ������λͼ
	static CDIB* PASCAL FromHandle(HBITMAP hBitmap);

// Constructors
	CDIB();

	//����λͼ
	BOOL CreateDIB(int nWidth, int nHeight, UINT nBitcount, const void* lpBits=NULL);

	//����λͼ
	BOOL CreateDIBIndirect(LPBITMAPINFO lpBitmap, const void* lpBits=NULL);

	//��׽����ͼ��
	BOOL CaptureDIB(CWnd * pWnd, const CRect& capRect = CRect(0,0,0,0));

// Attributes
	//�õ�λͼ
	operator HBITMAP() const;

	//����λͼ
	CDIB& operator = (CDIB& copy);

// Operations
	//����ͼ������
	DWORD SetDIBBits(DWORD dwCount, const void* lpBits);
	//�õ�ͼ������
	LPVOID GetDIBBits(DWORD dwCount = 0, LPVOID lpBits = NULL);

// Implementation
public:
	virtual ~CDIB();
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif

// Newly added functions
public:
	//�õ�ʹ�õ���ɫ��
	int GetColorUsed();

	//����λͼ
	int LoadBmp(LPCSTR filename);
	//����λͼ
	int SaveBmp(LPCSTR filename);

	//���õ�ɫ��
	void SetPalette(UINT uStartIndex, UINT cEntries, CONST RGBQUAD *pColors);
	//���õ�ɫ��
	void SetPalette(CPalette* pPal);
    void Show(CWnd *pWnd);	
	//�õ��豸
	CDC* GetDC(void);
	//�ͷ��豸
	static BOOL ReleaseDC(CDC *pdc);

	//�õ�λͼ
	int GetBitmap(BITMAP* pBitMap);
	//�õ�DibSection
	int GetDibSection(DIBSECTION* pDibSection);
	
	//�õ����
	int GetWidth();
	//�õ��߶�
	int GetHeight();
	//�õ��ߴ�
	SIZE GetSize();
	//�õ�ÿ��ͼ���ֽ���
	int GetWidthBytes();
	//�õ�ͼ��λ��
	int GetBitCount();
	//�õ�ͼ������
	LPVOID GetBits();
	//�õ�ͼ����Ϣͷ
	LPBITMAPINFO GetBitmapInfo(void);
};

////////////////////////////////////////////////////////////////////
// inline functions

//////////////////////////////////////////////////////////////////
// 
// GetBitmap(BITMAP* pBitMap)
// 
// ��ɹ���:
//     �õ�λͼ
//
// �������:
//	   λͼָ�� pBitMap
//
// ���ز���:
//	   �Ƿ�ɹ�
//
//////////////////////////////////////////////////////////////////

//�õ�λͼ
inline int CDIB::GetBitmap(BITMAP* pBitMap)
{
	return(::GetObject(m_hObject, sizeof(BITMAP), pBitMap));
}


//////////////////////////////////////////////////////////////////
// 
// GetDibSection(DIBSECTION *pDibSection)
// 
// ��ɹ���:
//     �õ�DibSection
//
// �������:
//	   DibSectionָ�� pDibSection
//
// ���ز���:
//	   �Ƿ�ɹ�
//
//////////////////////////////////////////////////////////////////

//�õ�DibSection
inline int CDIB::GetDibSection(DIBSECTION *pDibSection)
{
	return(::GetObject(m_hObject, sizeof(DIBSECTION), pDibSection));
}


//////////////////////////////////////////////////////////////////
// 
// HBITMAP()
// 
// ��ɹ���:
//     �õ�λͼ���
//
// �������:
//	   ��
//
// ���ز���:
//	   λͼ���
//
//////////////////////////////////////////////////////////////////

//�õ�λͼ���
inline CDIB::operator HBITMAP() const
{
	return (HBITMAP)(this == NULL ? NULL : m_hObject);
}


//////////////////////////////////////////////////////////////////
// 
// FromHandle(HBITMAP hDib)
// 
// ��ɹ���:
//     ��λͼ����õ�λͼ��
//
// �������:
//	   λͼ��� hDib
//
// ���ز���:
//	   λͼ��
//
//////////////////////////////////////////////////////////////////

//��λͼ����õ�λͼ��
inline CDIB* PASCAL CDIB::FromHandle(HBITMAP hDib)
{
	return((CDIB*)CGdiObject::FromHandle(hDib));
}


//////////////////////////////////////////////////////////////////
// 
// GetWidth(void)
// 
// ��ɹ���:
//     �õ����
//
// �������:
//	   ��
//
// ���ز���:
//	   ���
//
//////////////////////////////////////////////////////////////////

//�õ����
inline int CDIB::GetWidth(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmWidth);
}


//////////////////////////////////////////////////////////////////
// 
// GetHeight(void)
// 
// ��ɹ���:
//     �õ��߶�
//
// �������:
//	   ��
//
// ���ز���:
//	   �߶�
//
//////////////////////////////////////////////////////////////////

//�õ��߶�
inline int CDIB::GetHeight(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmHeight);
}


//////////////////////////////////////////////////////////////////
// 
// GetSize(void)
// 
// ��ɹ���:
//     �õ��ߴ�
//
// �������:
//	   ��
//
// ���ز���:
//	   �ߴ�
//
//////////////////////////////////////////////////////////////////

//�õ��ߴ�
inline SIZE CDIB::GetSize(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	CSize size(bmp.bmWidth, bmp.bmHeight);
	return(size);
}


//////////////////////////////////////////////////////////////////
// 
// GetWidthBytes(void)
// 
// ��ɹ���:
//     �õ�ÿ���ֽ���
//
// �������:
//	   ��
//
// ���ز���:
//	   ÿ���ֽ���
//
//////////////////////////////////////////////////////////////////

//�õ�ÿ���ֽ���
inline int CDIB::GetWidthBytes(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmWidthBytes);
}


//////////////////////////////////////////////////////////////////
// 
// GetBitCount(void)
// 
// ��ɹ���:
//     �õ�ͼ��λ��
//
// �������:
//	   ��
//
// ���ز���:
//	   ͼ��λ��
//
//////////////////////////////////////////////////////////////////

//�õ�ͼ��λ��
inline int CDIB::GetBitCount(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmBitsPixel);
}

//////////////////////////////////////////////////////////////////
// 
// GetBits(void)
// 
// ��ɹ���:
//     �õ�ͼ������
//
// �������:
//	   ��
//
// ���ز���:
//	   ͼ������
//
//////////////////////////////////////////////////////////////////

//�õ�ͼ������
inline LPVOID CDIB::GetBits(void)
{
	BITMAP bmp;
	GetBitmap(&bmp);
	return(bmp.bmBits);
}

//////////////////////////////////////////////////////////////////////

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


class CDibDC : public CDC
{
	DECLARE_DYNAMIC(CDibDC)

// Constructors
public:
	CDibDC();

// Attributes
protected:
	HBITMAP m_hOld;

// Implementation
public:
	CPalette * GetPalette();
	virtual ~CDibDC();
	
	friend class CDIB;
};

#endif //__DIB_H