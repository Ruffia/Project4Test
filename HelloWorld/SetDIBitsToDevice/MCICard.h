// Last Modify : 2009.11.24

/////////////////////////////////////////////////////////////////////////////
// 09.11.24��SetZoom�м���ͬ�����
/////////////////////////////////////////////////////////////////////////////

//#if !defined(AFX_MCICARD_H__3E643262_9D82_467B_91C1_DCF4B3D230DD__INCLUDED_)
//#define AFX_MCICARD_H__3E643262_9D82_467B_91C1_DCF4B3D230DD__INCLUDED_

//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
// MCICard.h : header file
//

#include "DIBAPI.H"
#include "RectManager.h"
#include "MCICardParam.h"
//#include "CriticalResource.h"
#include <afxmt.h>

#include "USB_Functions.h"

//_TB _TN _NB _NN

//#define GRAPHIC_Transparent
#define GRAPHIC_BLACK

// 07.10.31��ʾģʽ
#define	NEW_SCANSCREEN_MODE

//======2004-8-2_��ǿͼ�β���ʾ=======================
// �޸ı�ʾ��2004-8-2_��ǿͼ�β���ʾ
// �޸����ڣ�2004��8��2������һ
// �޸��ˣ�������
// �޸�ԭ�򣺺ӱ���ѧ���������û������ǿͼ�β���ʾ
//		�޸�ͼ�β��ַ���ɫ��ȫ����Ϊ��ɫ��
//	    �Ӵ�ױ������ֺ�
//      �Ӵֱ��
//======�޸����ڣ�2004��8��2������һ==================


#ifdef GRAPHIC_BLACK
	const int	c_fnWeight	= FW_BLACK;		// font weight
#else
	const int	c_fnWeight	= FW_NORMAL;	// font weight
#endif

const int		Edit_nFontSize			= 32;
const CString	Edit_csFontFacename		= _T("����");//_T("����");

const int		Label_nFontSize			= 40;	//32
const CString	Label_csFontFacename	= _T("����");//_T("����");

const int		Logo_nFontSize			= 40;	//32
const CString	Logo_csFontFacename		= _T("����");//_T("Times New Roman");

const int		UScale_nFontSize		= 32;
const CString	UScale_csFontFacename	= _T("����");//_T("����");

// 1 inch = 25.4 mm
const double mm_TO_inch				= (double)0.0393700787401574803149606299212598;
const double SEM_dfStandImageWidth	= (double)120;		// mm
const double SEM_dfStandImageHeight	= (double)90;		// mm

typedef struct tagDebug_OSC_MCI
{
	BOOL	b90;					// X/Y����
	int		nIndexY;				// ����ģʽ�£���Ƶʾ����Y��λ
	double	dOffset;				// ʾ����Y��ƫ����
}DebugOSCMCI;

/////////////////////////////////////////////////////////////////////////////
// CMCICard thread
class CMP;

class CMCICard : public CWinThread
{
	DECLARE_DYNCREATE(CMCICard)
protected:
	///////////////////////////////////////////////////////////////////
	BOOL				m_boolReady;
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	DWORD				m_lastTickCount;
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	HANDLE				m_hEventKill;
	HANDLE				m_hEventDead;
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	CWnd*				m_pScreenWnd;
	CRect				m_rcScreenClientRect;
	CPoint				m_ptScreenClientPos;
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	CSize				m_sizeReso;
	int					m_nusbFunction;
	BOOL				m_bSplit;
	BOOL				m_bLive;
	CRect				m_rcImageWindow;	// Graphic Frame map to ImageWindow
	CRect				m_rcDestFrame;
	double				m_dblZoom;			// The map of Image to screen

	double				m_dblScaleImageToGraph_W;
	double				m_dblScaleImageToGraph_H;

	int					m_nChnIndex[2];		// ˫ͨ����ʾ��ʽʱ���Ҹ���ʾ�ĸ�ͨ�������ݡ�
											// 0����ӦӲ��ͨ�����е�ż��ͨ��������Za��
											// 1����ӦӲ��ͨ�����е�����ͨ��������Zb��
											// 2����ͨ������ƽ��ֵ��Ϊ��ʾ����(Za+Zb)/2
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	BOOL				m_boolShouldReset;
	///////////////////////////////////////////////////////////////////

	BOOL				m_boolPreview;
	//06.11.22 3200��3900�ɼ�����ʾ����
	BOOL				m_boolNewScanScreenMode;

	double				m_dblPixelsPerMM_HORZ, m_dblPixelsPerMM_VERT;

	unsigned short*		m_pSharedImageBuff[SharedImageBuffCounts];

public:
	void SetScreenClientRect(const CRect& rc)
	{
		m_rcScreenClientRect = rc;
	}

	CRect& GetScreenClientRect()
	{ 
		return m_rcScreenClientRect;
	}

	void SetScreenClientPos(const CPoint& pt)
	{
		m_ptScreenClientPos = pt;
	}

	CPoint& GetScreenClientPos()
	{
		return m_ptScreenClientPos;
	}

public:
	CMCICard();   // protected constructor used by dynamic creation

	BOOL	IsReady(){ return m_boolReady; };
	BOOL	IsShouldReset(){ return m_boolShouldReset; };

	HDIB	GetDib(){return m_hdibImage;};

	HDIB	CopyImageDib();
	BOOL	CopyGraphBmp( CBitmap& bmpGraphLay );
	BOOL	CopyScreenBmp( CBitmap& bmpScreen );

	//05.02.06
	void	SetPhotoPreview( BOOL boolPreview ){
						m_boolPreview = boolPreview; };
	//06.11.22 3200��3900�ɼ�����ʾ����
	void	SetScanScreenMode( BOOL boolNewScanScreenMode = TRUE );
	void	SetProductLogo( CString csLogo );

// Attributes
public:
	CSize	GetResolution(){ return m_sizeReso; };
	void	SetResolution(CSize szReso);
	void	SetFunction( int nFunction );
	void	SetSplit( BOOL bSplit );
	void	SetLiveMode( BOOL bLive );

	double	GetZoom(){ return m_dblZoom; };
	void	SetZoom(double dblZoom);

	CSize	GetSizes( int nIndex );
	void	SetDestFrame( CRect rcDestFrame );

//	void	GetSizes( CSize &szImage, CSize &szGraph, CSize &szLabel, CSize &szUScale, CSize &szOscill );
	CSize	m_szImage, m_szGraph, m_szLabel, m_szUScale, m_szOscill;
	int		m_nCurrentY1, m_nCurrentY2;

	/////////////////////////////////////////////////////////////////
	// 15.07.23 ���õױꡢ��ǩ�����ߵȵı�ע��ɫ����ע���塢��ע�����С��
	void	SetColor( int nType, COLORREF color );
// 	COLORREF				m_colorTransparent;
// 	COLORREF				m_colorBack;
// 	COLORREF				m_colorEditText;
// 	COLORREF				m_colorLabelText;
// 	COLORREF				m_colorLabelLogoText;
// 	COLORREF				m_colorMobileUScaleText;
//	COLORREF				m_colorMobileUScaleLine;
// 	COLORREF				m_colorOscillographGrid;
// 	COLORREF				m_colorOscillographGraph;
// 	COLORREF				m_crFrameRateColor;
	void	SetFontName( int nType, CString strName );
	void	SetFontSize( int nType, int nSize );
	void	SetFontWeight( int nType, int nWeight );
	void	SetTransparent( int nTransparent );
	/////////////////////////////////////////////////////////////////

private:
	void	SetImageWindow(CRect rcImageWindow);

	//////////////////////////////////////////
    UINT					m_uBPP;
	BOOL					m_blColorFill;
    BOOL					m_blSrcColorkey;
    BOOL					m_blDestColorkey;
	//////////////////////////////////////////

protected:
	///////////////////////////////////////////////////////////////////
	LPDIRECTDRAW2			m_lpDD;					// DirectDraw object
	LPDIRECTDRAWSURFACE		m_lpDDSPrimary;			// DirectDraw primary surface
	LPDIRECTDRAWPALETTE		m_lpDDPalette;			// DirectDraw palette
	LPDIRECTDRAWCLIPPER 	m_lpClipper;			// clipper for primary

	LPDIRECTDRAWSURFACE		m_lpDDSPrimaryBackLay;	// Offscreen surface Primary Back Lay
	LPDIRECTDRAWSURFACE		m_lpDDSGraphBackLay;	// Offscreen surface Graph Back Lay

	LPDIRECTDRAWSURFACE		m_lpDDSImageLay;		// Offscreen surface Image Lay
	LPDIRECTDRAWSURFACE		m_lpDDSGraphLay;		// Offscreen surface Graph Lay
	LPDIRECTDRAWSURFACE		m_lpDDSLabelLay;		// Offscreen surface Label Lay
	LPDIRECTDRAWSURFACE		m_lpDDSMobileUScaleLay;	// Offscreen surface MobileUScale Lay
	LPDIRECTDRAWSURFACE		m_lpDDSOscillographLay;	// Offscreen surface Oscillograph Lay
	LPDIRECTDRAWSURFACE		m_lpDDSFrameRate;		// Offscreen surface Info Lay
	
	DWORD					m_dwVidMemTotal;
	DWORD					m_dwFrameMemSizeUsed;

// 	COLORREF				m_colorTransparent;
// 	COLORREF				m_colorBack;
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	HDIB					m_hdibImage;
	LPVOID					m_lpImageDibPlan;
	CPalette				m_paletteImage;
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
//	CriticalResource		m_mutexLayAll;
//	CriticalResource		m_mutexImageDib;
//	CriticalResource		m_mutexImageUSB;
	static	CCriticalSection		m_mutexLayAll;
	static	CCriticalSection		m_mutexImageDib;
	static	CCriticalSection		m_mutexImageUSB;
	///////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////
	// Oscillograph
	///////////////////////////////////////////////////////////////////
    BOOL					m_boolRedrawOscillograph;
    BOOL					m_boolShowOscillograph;

// 	COLORREF				m_colorOscillographGrid;
// 	COLORREF				m_colorOscillographGraph;
	
	CPoint					m_ptOscillograph;

	WORD					m_bOscillographBuff[8192];
	WORD					m_bOscillographData[8192];	// ʾ������ͼ����
	double					m_dblOscillographAmplifer;

	int						m_lOscillographState;
	long					m_lGrayHistogramBuff[256];
	///////////////////////////////////////////////////////////////////
	DWORD					m_dwFramGrayHistogramBuff[256];
	DWORD					m_dwFramGrayHistogramCountPixel;
	long					m_lFramGrayHistogramCountLine;
	long					m_lFramGrayHistogramCurrentLine;
	long					m_lFramGrayHistogramStartLine;
	BOOL					m_boolFramGrayHistogramBuffReady;
	BOOL					m_boolFramGrayHistogramBuffStart;
	///////////////////////////////////////////////////////////////////

	SYS_Options				m_sysOpt;
	Footer_Options			m_footerOpt;
	///////////////////////////////////////////////////////////////////
	// Label & uScale
	///////////////////////////////////////////////////////////////////
    BOOL					m_boolRedrawLabel;
    BOOL					m_boolRedrawUScal;

    BOOL					m_boolShowLabel;

    HFONT					m_hfontEditText;			// 2004-8-2_��ǿͼ�β���ʾ
// 	COLORREF				m_colorEditText;			// 2004-8-2_��ǿͼ�β���ʾ
// 	CString					m_fontEditTextName;
// 	int						m_fontEditTextSize;

    HFONT					m_hfontLabelText;
// 	COLORREF				m_colorLabelText;
// 	CString					m_fontLabelTextName;
// 	int						m_fontLabelTextSize;

    HFONT					m_hfontLabelLogoText;
// 	COLORREF				m_colorLabelLogoText;

	CString					m_csHV;						// ��ѹ��ʾ�ַ�
	CString					m_csMag;					// �Ŵ�����ʾ�ַ�
	CString					m_csUScal;					// �̶������ʾ�ַ�
	CString					m_csLogo;					// ��Ʒ��ʶ��ʾ�ַ�
	CString					m_csPhotoSN;				// ��������ʾ�ַ�
	CString					m_csTime;					// ����ʱ����ʾ�ַ�
	CString					m_csWD;						// ����������ʾ�ַ�
	CString					m_csSG1, m_csSG2;			// ̽����������ʾ�ַ�
	CString					m_csNote;					// ��ע��ʾ�ַ�
	CString					m_csVAC;					// ���ֵ�������ֵ����ʾ�ַ�

/*	CPoint					m_ptHV;						// ��ѹ�ַ���ʾλ��
	CPoint					m_ptMag;					// �Ŵ����ַ���ʾλ��
	CPoint					m_ptUScal;					// �̶�����ַ���ʾλ��
	CPoint					m_ptLogo;					// ��Ʒ��ʶ�ַ���ʾλ��
	CPoint					m_ptPhotoSN;				// �������ַ���ʾλ��
	CPoint					m_ptTime;					// ����ʱ���ַ���ʾλ��
	CPoint					m_ptWD;						// ���������ַ���ʾλ��
	CPoint					m_ptSG;						// ̽���������ַ���ʾλ��
	CPoint					m_ptNote;					// ��ע�ַ���ʾλ��
*/	///////////////////////////////////////////////////////////////////
	int						m_nUScalePixelNum;			// �̶������ʾ����
	///////////////////////////////////////////////////////////////////
    BOOL					m_boolShowMobileUScale;		// �ƶ������ʾ����
	BOOL					m_boolShowTime;				// ����ʱ����ʾ����
	BOOL					m_boolShowNote;				// ��ע��ʾ����

    HFONT					m_hfontMobileUScaleText;
// 	COLORREF				m_colorMobileUScaleText;
// 	COLORREF				m_colorMobileUScaleLine;
// 	CString					m_fontMobileUScaleName;
// 	int						m_fontMobileUScaleSize;

	int						m_nMobileUScalePixelNum;	// �ƶ������ʾ����
	CString					m_csMobileUScaleText;		// �ƶ������ʾ�ַ�
	CPoint					m_ptMobileUScaleText;		// �ƶ�����ַ���ʾλ��
	CPoint					m_ptMobileUScale;			// �ƶ����λ��

	// 07.08.20���ⷽ���ƶ��������
	CPoint					m_ptMobileUScale2;			// �ƶ����λ��
	CPoint					m_ptMobileUScaleSaved;
	CPoint					m_ptMobileUScale2Saved;
	// 07.08.20���ⷽ���ƶ��������

	// 16.06.12 ���ƶ����ʵ��
	CPoint					m_ptMobileUScaleArray[MobileUScaleCounts];
	CPoint					m_ptMobileUScaleArray2[MobileUScaleCounts];
	int						m_nMobileUScalePixelNumArray[MobileUScaleCounts];
	CString					m_csMobileUScaleTextArray[MobileUScaleCounts];
	// 16.06.12 ���ƶ����ʵ��
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	// Statistical infomation
	///////////////////////////////////////////////////////////////////
    BOOL					m_boolShowFrameRate;

    DWORD					m_dwFrameTime;

	DWORD					m_dwFrameCount;
    DWORD					m_dwFramesLast;
	DWORD					m_dwFrames;

	DWORD					m_dwByteCount;
    DWORD					m_dwBytesLast;
	DWORD					m_dwBytes;

    DWORD					m_dwAveFrameRate;
    DWORD					m_dwAveFrameRateCount;

    SIZE					m_sizeFPS;
    int						m_iFrameRateX;
	int						m_iBpsRateX;
	int						m_iIPSRateX;

	DWORD					m_dwInputCount;
    DWORD					m_dwInputsLast;
	DWORD					m_dwInputs;

    TCHAR					m_szFrameRate[64];
	TCHAR					m_szFPS[64];

    HFONT					m_hFontFrameRate;
// 	COLORREF				m_crFrameRateColor;
	///////////////////////////////////////////////////////////////////

// Operations
public:
	void	KillThread();

	BOOL	Reset( CWnd* pWnd );
	BOOL	Close();

	///////////////////////////////////////////////////////////////////
	BOOL	IsSupportColorFill() {  return m_blColorFill; };
	///////////////////////////////////////////////////////////////////

	DWORD	ImageDibWrite( LPVOID lpBuff, long lBuffSize, CRect& rcDest );
	DWORD	ImageDibWriteImp( LPVOID lpBuff, long lBuffSize, CRect& rcDest );			// 10.08
	DWORD	ImageDibWriteNewXYZ( LPVOID lpBuff, long lBuffSize, CRect& rcDest );		// 11.11.28
	DWORD	ImageDibWriteNewZZZ( LPVOID lpBuff, long lBuffSize, CRect& rcDest );		// 11.12.05
	DWORD	ImageDibWriteNewZZZ2( LPVOID lpBuff, long lBuffSize, CRect& rcDest );		// 11.12.05

	DWORD	ADxyz( LPVOID lpBuff, long lBuffSize, CRect& rcDest );
	DWORD	ADxyzLine( LPVOID lpBuff, long lBuffSize, CRect& rcDest );
	DWORD	ADxyzSync( LPVOID lpBuff, long lBuffSize, CRect& rcDest );

	DWORD	ADxyz2nd( LPVOID lpBuff, long lBuffSize, CRect& rcDest );
	DWORD	ADxyzLine2nd( LPVOID lpBuff, long lBuffSize, CRect& rcDest );
	DWORD	ADxyzSync2nd( LPVOID lpBuff, long lBuffSize, CRect& rcDest );

	DWORD	ADxyz2ndMix( LPVOID lpBuff, long lBuffSize, CRect& rcDest );
	DWORD	ADxyzLine2ndMix( LPVOID lpBuff, long lBuffSize, CRect& rcDest );
	DWORD	ADxyzSync2ndMix( LPVOID lpBuff, long lBuffSize, CRect& rcDest );

	DWORD	ADxyz2( LPVOID lpBuff, long lBuffSize, CRect& rcDest );
	DWORD	ADxyzLine2( LPVOID lpBuff, long lBuffSize, CRect& rcDest );
	DWORD	ADxyzSync2( LPVOID lpBuff, long lBuffSize, CRect& rcDest );

	BOOL	PostData( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow );
	BOOL	GetData( /*LPVOID lpBuff, long lBuffSize, */CRect& rcFrameDestWindow );

	DWORD	ImageDibRead( LPVOID lpBuff, long lBuffSize, CRect& rcDest );
	DWORD	ImageDibCopy( LPVOID lpBuff, long lBuffSize, CRect& rcDest );

	DWORD	PixConvertZZZ( unsigned short* pnFrameData, long lBytesTransferred, WORD* pPixX, WORD* pPixY, WORD* pPixZ, WORD& dwIndexY1, WORD& dwIndexY2 );
	DWORD	PixConvertZZZ2( unsigned short* pnFrameData, long lBytesTransferred, WORD* pPixX, WORD* pPixY, WORD* pPixZ, WORD& dwIndexY1, WORD& dwIndexY2 );
	void	CheckIndexs( int nLineCounts, int nFrameCounts, int& nX, int& nY );
	WORD	m_dwX, m_dwY, m_dwZa;
	int		m_nX, m_nY, m_nIndexX, m_nIndexY, m_nXOffset, m_nYOffset;
	BOOL	m_bPeakX, m_bPeakY;
	BOOL	m_bUrgency;
	WORD	*m_pPixX, *m_pPixX2;
	WORD	*m_pPixY, *m_pPixY2;
	WORD	*m_pPixZ, *m_pPixZ2, *m_pPixZmix;
	WORD	m_dwMinY, m_dwMaxY;

	BOOL	Convolution( double *Kernel, CSize KernelSize, int nX1, int nY1, int nX2, int nY2, LPSTR lpDIBBits );
	BOOL	LowpassFilter( DWORD *dwFact, int nX1, int nY1, int nX2, int nY2, LPSTR lpDIBBits );
	BOOL	Gauss(UINT uSize, int nX1, int nY1, int nX2, int nY2, LPSTR lpDIBBits);

	BOOL	InitData( DWORD dwExpectantDMABlockSize, int nXOffset = 0, int nYOffset = 0 );
	BOOL	ClearData();
	BOOL	m_bDataNeedUpdated;
	BOOL	m_bStopScan;
	unsigned short*		m_pBuffUSB;
	DWORD				m_dwExpectantDMABlockSize;
	BOOL	m_bSyncFinished;
	BOOL	m_bFindFirstBOF;
	HANDLE	m_hFileLog;
	BOOL	m_bNeedMon;
	HANDLE	m_hLineDataLog;
	HANDLE	m_hOscillLog;

	void	SetSharedImageBuff( int nIndex,
					unsigned short* pBuff );	// ���ò��洢�����ڴ���׵�ַ
	void	SetSharedImageBuffIndex( int nIndex );
	int		m_nSharedImageBuffIndexRead, m_nSharedImageBuffIndexWrite;

	void	SetParams( int nType, int nParam );	// �������ݴ洢ģʽ��̽����ģʽ
	int		m_nDataStoreMode;					// ���ݴ洢ģʽ
	int		m_nDetectorMode;					// ̽����ģʽ
	BOOL	m_bDet2nd;
	BOOL	m_bDebugZ;							// ����ģʽ�£�ʾ�����������岻ͬ
	BOOL	m_bDebugOsc;
	DebugOSCMCI	m_debugOSC;

	void	PhotoIndication( const CRect& rcDest, const COLORREF color = RGB(0,0,0), const BOOL boolFill = TRUE );//09.06.01

	BOOL	GraphDrawLine( const CPoint ptPos0, const CPoint ptPos1,
						const COLORREF color = RGB(0,0,0) );
	BOOL	GraphDrawLineEx( const int nLength );	// ��λ��mm
	BOOL	GraphDrawRect( const CRect rcDest, const COLORREF color = RGB(0,0,0) );
	BOOL	GraphDrawRectEx( const BOOL bDrawCircle, const CRect rcDest, const COLORREF color = RGB(0,0,0) );
	BOOL	GraphDrawCircle( const CPoint ptCenter, const CPoint ptEnd, BOOL bDrawArrow = TRUE, 
						const int nRadius = nSTAGE_TRACE_POINT_RADIUS, const COLORREF color = RGB(0,0,0) );	// 12.10.11
	BOOL	GraphClear(	const CRect rcDest = CRect(0, 0, g_szUSB_FrameGraph.cx, g_szUSB_FrameGraph.cy),
						const COLORREF color = RGB(0,0,0) );
	CSize	GraphTextOut( const CPoint ptPos, const CString csText );
	CSize	GetOutputTextExtent( const CString csText );

	BOOL	ShowLabel( BOOL boolShow = TRUE );
	BOOL	ShowTime( BOOL boolShow = TRUE );
	BOOL	ShowNote( BOOL boolShow = TRUE );
	BOOL	ShowMobileUScale( BOOL boolShow = TRUE );
	BOOL	ShowFrameRate( BOOL boolShow = TRUE );

	void	UpdateHV( CString csHV );
	void	UpdateWD( CString csWD);
	void	UpdatePhotoSN( CString csPhotoSN );
	void	UpdateTime( CString csTime );
	void	UpdateNote( CString csNote );
	void	UpdateVac( CString csVac );

	void	UpdateMAG(
			CString	csMag,					// �Ŵ�����ʾ�ַ�
			int		nUScalePixelNum,		// �̶������ʾ����
			CString	csUScal,				// �̶������ʾ�ַ�
			CString	csMobileUScaleText );	// �ƶ������ʾ�ַ�

	void	UpdateUScale(
			int		nMobileUScalePixelNum,	// �ƶ������ʾ����
			CString	csMobileUScaleText );	// �ƶ������ʾ�ַ�

	void	UpdateSGname( int nIndex, CString& strName );

	void	GetMobileUScaleParam( int&	nMobileUScalePixelNum, CPoint& ptMobileUScale );
	void	SetMobileUScalePos( CPoint ptMobileUScale );

	//07.08.20���ⷽ���ƶ��������
	void	GetMobileUScaleParamEx( int&	nMobileUScalePixelNum, CPoint& ptMobileUScale, CPoint& ptMobileUScale2 );
	void	SetMobileUScalePosEx( const CPoint ptMobileUScale, const CPoint ptMobileUScale2,
						const COLORREF color = RGB(0,0,0) );
	//07.08.20���ⷽ���ƶ��������

	// 16.06.12 ���ƶ����ʵ��
	void	GetMobileUScaleParamArray( int nIndex, int&	nMobileUScalePixelNum, CPoint& ptMobileUScale, CPoint& ptMobileUScale2 );
	void	SetMobileUScalePosArray( int nIndex, const CPoint ptMobileUScale, const CPoint ptMobileUScale2,
						const COLORREF color = RGB(0,0,0) );
	void	UpdateUScaleArray(	int			nIndex,
								int			nMobileUScalePixelNum,	// �ƶ������ʾ����
								CString		csMobileUScaleText );	// �ƶ������ʾ�ַ�
	void	UpdateMAGArray(	int nIndex,
			CString	csMobileUScaleText );	// �ƶ������ʾ�ַ�
	// 16.06.12 ���ƶ����ʵ��

	// 19.02.18 �ױ��Զ���
	void	UpdateFooter( int nIndex, BOOL bVisible, CPoint ptPos );
	void	UpdateFooterText( int nIndex, CString csText );
	// 19.02.18 �ױ��Զ���

	BOOL	ShowOscillograph(BOOL boolShow = TRUE);
	void	SetOscillographPos( CPoint ptOscillograph );
	void	GetOscillographParam( CPoint& ptOscillograph );
	void	UpdateOscillograph( LPBYTE pOscillographBuff, long nScanLine, long nStart = 0, long nStop = g_szUSB_FrameOscillograph.cx );
	void	UpdateOscillographNew(	DWORD dwCounts, LPWORD pPixX, LPWORD pPixY, LPWORD pPixZ,
//									LPBYTE		pOscillographBuff,	// ʾ������ʾ����
									long		nScanLine,			// ��ǰɨ����
									long nStart = 0, long nStop = g_szUSB_FrameOscillograph.cx );
	void	SetOscillographAmplifer(double dblAmplifer = 1.0);

	BOOL	IsReadyFramGrayHistogram(){ return m_boolFramGrayHistogramBuffReady; };
	void	FramGrayHistogramStart();
	void	FramGrayHistogramStop();
	void	FramGrayHistogramReset();
	DWORD	CopyFramGrayHistogramBuff( DWORD* pFramGrayHistogramBuff );

private:
	HDIB	CreateImageBitmap();

	void	MainLoop();

	void	GetClientWindow();
	void	PaintScreenWindow();

	long	UpdateImageLay();
	long	UpdateGraphLay();
	long	UpdateLabelLay();
	long	UpdateUScaleMobileLay();

	long	UpdateGraphBackLay();
	long	UpdatePriamryLay();

	long	RedrawLabelLay();
	long	RedrawMobileUScaleLay();

	///////////////////////////////////////////////////////////////////
	CRectManager	m_UpdateRectsImage;
	CRectManager	m_UpdateRectsGraph;
	CRectManager	m_UpdateRectsLabel;
	CRectManager	m_UpdateRectsMobileUScale;
	CRectManager	m_UpdateRectsOscillograph;
	CRectManager	m_UpdateRectsGraphBack;

	CRect	LayWindowMapClip_Graph_to_Image( CRect& rcGrapic );
	CRect	LayWindowMapClip_Image_to_Graph( CRect& rcImage );
	CRect	LayWindowMapClip_Image_to_Label( CRect& rcImage );
	CRect	LayWindowMapClip_Image_to_MobileUScale( CRect& rcImage );
	CRect	LayWindowMapClip_Image_to_Oscillograph( CRect& rcImage );
	CRect	LayWindowMapClip_Image_to_Priamry( CRect& rcImage );
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	// Oscillograph
	///////////////////////////////////////////////////////////////////
	BOOL	InitOscillographLay();
	long	RedrawOscillographLay();
	long	UpdateOscillographLay();
	void	UpdateGrayHistogram(LPBYTE	pVideoDataBuff, long nBuffLength);
	void	UpdateFramGrayHistogram(LPBYTE	pVideoDataBuff, long nBuffLength, long lCurrentLine);
	void	UpdateGrayHistogramNew(LPWORD	pVideoDataBuff, long nBuffLength);
	void	UpdateFramGrayHistogramNew(
				DWORD dwCounts, LPWORD pPixX, LPWORD pPixY, LPWORD pPixZ );

	///////////////////////////////////////////////////////////////////
	// Label & uScale
	///////////////////////////////////////////////////////////////////
	BOOL	InitLabelLay();
	void	InitLabelLay_0128();
	void	InitLabelLay_0256();
	void	InitLabelLay_0384();
	void	InitLabelLay_0480();
	void	InitLabelLay_0512();
	void	InitLabelLay_0640();
	void	InitLabelLay_0800();
	void	InitLabelLay_1024();
	void	InitLabelLay_1440();
	void	InitLabelLay_2048();
	void	InitLabelLay_4096();
	BOOL	InitMobileUScaleLay();
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	// Statistical infomation
	///////////////////////////////////////////////////////////////////
	long	UpdateFrameRateLay();
	long	FormatFrameRate();
	BOOL	InitFrameRate();
	long	InitNumSurface();
	///////////////////////////////////////////////////////////////////

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMCICard)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
public:
	virtual ~CMCICard();
	virtual void Delete();

	// Generated message map functions
	//{{AFX_MSG(CMCICard)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_MCICARD_H__3E643262_9D82_467B_91C1_DCF4B3D230DD__INCLUDED_)
