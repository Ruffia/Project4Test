// Last Modify : 2009.11.24

/////////////////////////////////////////////////////////////////////////////
// 09.11.24在SetZoom中加入同步语句
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

// 07.10.31显示模式
#define	NEW_SCANSCREEN_MODE

//======2004-8-2_加强图形层显示=======================
// 修改标示：2004-8-2_加强图形层显示
// 修改日期：2004年8月2日星期一
// 修改人：罗鸣华
// 修改原因：河北大学（保定）用户建议加强图形层显示
//		修改图形层字符颜色，全部改为白色。
//	    加大底标字体字号
//      加粗标尺
//======修改日期：2004年8月2日星期一==================


#ifdef GRAPHIC_BLACK
	const int	c_fnWeight	= FW_BLACK;		// font weight
#else
	const int	c_fnWeight	= FW_NORMAL;	// font weight
#endif

const int		Edit_nFontSize			= 32;
const CString	Edit_csFontFacename		= _T("黑体");//_T("宋体");

const int		Label_nFontSize			= 40;	//32
const CString	Label_csFontFacename	= _T("黑体");//_T("宋体");

const int		Logo_nFontSize			= 40;	//32
const CString	Logo_csFontFacename		= _T("黑体");//_T("Times New Roman");

const int		UScale_nFontSize		= 32;
const CString	UScale_csFontFacename	= _T("黑体");//_T("宋体");

// 1 inch = 25.4 mm
const double mm_TO_inch				= (double)0.0393700787401574803149606299212598;
const double SEM_dfStandImageWidth	= (double)120;		// mm
const double SEM_dfStandImageHeight	= (double)90;		// mm

typedef struct tagDebug_OSC_MCI
{
	BOOL	b90;					// X/Y互换
	int		nIndexY;				// 调试模式下，视频示波器Y向档位
	double	dOffset;				// 示波器Y向偏移量
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

	int					m_nChnIndex[2];		// 双通道显示方式时左右各显示哪个通道的数据。
											// 0：对应硬件通道组中的偶数通道的数据Za；
											// 1：对应硬件通道组中的奇数通道的数据Zb；
											// 2：两通道数据平均值作为显示数据(Za+Zb)/2
	///////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	BOOL				m_boolShouldReset;
	///////////////////////////////////////////////////////////////////

	BOOL				m_boolPreview;
	//06.11.22 3200与3900采集屏显示兼容
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
	//06.11.22 3200与3900采集屏显示兼容
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
	// 15.07.23 设置底标、标签、活动标尺等的标注颜色、标注字体、标注字体大小等
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
	WORD					m_bOscillographData[8192];	// 示波器画图数据
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

    HFONT					m_hfontEditText;			// 2004-8-2_加强图形层显示
// 	COLORREF				m_colorEditText;			// 2004-8-2_加强图形层显示
// 	CString					m_fontEditTextName;
// 	int						m_fontEditTextSize;

    HFONT					m_hfontLabelText;
// 	COLORREF				m_colorLabelText;
// 	CString					m_fontLabelTextName;
// 	int						m_fontLabelTextSize;

    HFONT					m_hfontLabelLogoText;
// 	COLORREF				m_colorLabelLogoText;

	CString					m_csHV;						// 高压显示字符
	CString					m_csMag;					// 放大倍数显示字符
	CString					m_csUScal;					// 固定标尺显示字符
	CString					m_csLogo;					// 产品标识显示字符
	CString					m_csPhotoSN;				// 照相编号显示字符
	CString					m_csTime;					// 日期时间显示字符
	CString					m_csWD;						// 工作距离显示字符
	CString					m_csSG1, m_csSG2;			// 探测器类型显示字符
	CString					m_csNote;					// 备注显示字符
	CString					m_csVAC;					// 真空值（低真空值）显示字符

/*	CPoint					m_ptHV;						// 高压字符显示位置
	CPoint					m_ptMag;					// 放大倍数字符显示位置
	CPoint					m_ptUScal;					// 固定标尺字符显示位置
	CPoint					m_ptLogo;					// 产品标识字符显示位置
	CPoint					m_ptPhotoSN;				// 照相编号字符显示位置
	CPoint					m_ptTime;					// 日期时间字符显示位置
	CPoint					m_ptWD;						// 工作距离字符显示位置
	CPoint					m_ptSG;						// 探测器类型字符显示位置
	CPoint					m_ptNote;					// 备注字符显示位置
*/	///////////////////////////////////////////////////////////////////
	int						m_nUScalePixelNum;			// 固定标尺显示长度
	///////////////////////////////////////////////////////////////////
    BOOL					m_boolShowMobileUScale;		// 移动标尺显示开关
	BOOL					m_boolShowTime;				// 日期时间显示开关
	BOOL					m_boolShowNote;				// 备注显示开关

    HFONT					m_hfontMobileUScaleText;
// 	COLORREF				m_colorMobileUScaleText;
// 	COLORREF				m_colorMobileUScaleLine;
// 	CString					m_fontMobileUScaleName;
// 	int						m_fontMobileUScaleSize;

	int						m_nMobileUScalePixelNum;	// 移动标尺显示长度
	CString					m_csMobileUScaleText;		// 移动标尺显示字符
	CPoint					m_ptMobileUScaleText;		// 移动标尺字符显示位置
	CPoint					m_ptMobileUScale;			// 移动标尺位置

	// 07.08.20任意方向移动标尺试验
	CPoint					m_ptMobileUScale2;			// 移动标尺位置
	CPoint					m_ptMobileUScaleSaved;
	CPoint					m_ptMobileUScale2Saved;
	// 07.08.20任意方向移动标尺试验

	// 16.06.12 多移动标尺实验
	CPoint					m_ptMobileUScaleArray[MobileUScaleCounts];
	CPoint					m_ptMobileUScaleArray2[MobileUScaleCounts];
	int						m_nMobileUScalePixelNumArray[MobileUScaleCounts];
	CString					m_csMobileUScaleTextArray[MobileUScaleCounts];
	// 16.06.12 多移动标尺实验
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
					unsigned short* pBuff );	// 设置并存储共享内存段首地址
	void	SetSharedImageBuffIndex( int nIndex );
	int		m_nSharedImageBuffIndexRead, m_nSharedImageBuffIndexWrite;

	void	SetParams( int nType, int nParam );	// 设置数据存储模式，探测器模式
	int		m_nDataStoreMode;					// 数据存储模式
	int		m_nDetectorMode;					// 探测器模式
	BOOL	m_bDet2nd;
	BOOL	m_bDebugZ;							// 调试模式下，示波器数据意义不同
	BOOL	m_bDebugOsc;
	DebugOSCMCI	m_debugOSC;

	void	PhotoIndication( const CRect& rcDest, const COLORREF color = RGB(0,0,0), const BOOL boolFill = TRUE );//09.06.01

	BOOL	GraphDrawLine( const CPoint ptPos0, const CPoint ptPos1,
						const COLORREF color = RGB(0,0,0) );
	BOOL	GraphDrawLineEx( const int nLength );	// 单位：mm
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
			CString	csMag,					// 放大倍数显示字符
			int		nUScalePixelNum,		// 固定标尺显示长度
			CString	csUScal,				// 固定标尺显示字符
			CString	csMobileUScaleText );	// 移动标尺显示字符

	void	UpdateUScale(
			int		nMobileUScalePixelNum,	// 移动标尺显示长度
			CString	csMobileUScaleText );	// 移动标尺显示字符

	void	UpdateSGname( int nIndex, CString& strName );

	void	GetMobileUScaleParam( int&	nMobileUScalePixelNum, CPoint& ptMobileUScale );
	void	SetMobileUScalePos( CPoint ptMobileUScale );

	//07.08.20任意方向移动标尺试验
	void	GetMobileUScaleParamEx( int&	nMobileUScalePixelNum, CPoint& ptMobileUScale, CPoint& ptMobileUScale2 );
	void	SetMobileUScalePosEx( const CPoint ptMobileUScale, const CPoint ptMobileUScale2,
						const COLORREF color = RGB(0,0,0) );
	//07.08.20任意方向移动标尺试验

	// 16.06.12 多移动标尺实验
	void	GetMobileUScaleParamArray( int nIndex, int&	nMobileUScalePixelNum, CPoint& ptMobileUScale, CPoint& ptMobileUScale2 );
	void	SetMobileUScalePosArray( int nIndex, const CPoint ptMobileUScale, const CPoint ptMobileUScale2,
						const COLORREF color = RGB(0,0,0) );
	void	UpdateUScaleArray(	int			nIndex,
								int			nMobileUScalePixelNum,	// 移动标尺显示长度
								CString		csMobileUScaleText );	// 移动标尺显示字符
	void	UpdateMAGArray(	int nIndex,
			CString	csMobileUScaleText );	// 移动标尺显示字符
	// 16.06.12 多移动标尺实验

	// 19.02.18 底标自定义
	void	UpdateFooter( int nIndex, BOOL bVisible, CPoint ptPos );
	void	UpdateFooterText( int nIndex, CString csText );
	// 19.02.18 底标自定义

	BOOL	ShowOscillograph(BOOL boolShow = TRUE);
	void	SetOscillographPos( CPoint ptOscillograph );
	void	GetOscillographParam( CPoint& ptOscillograph );
	void	UpdateOscillograph( LPBYTE pOscillographBuff, long nScanLine, long nStart = 0, long nStop = g_szUSB_FrameOscillograph.cx );
	void	UpdateOscillographNew(	DWORD dwCounts, LPWORD pPixX, LPWORD pPixY, LPWORD pPixZ,
//									LPBYTE		pOscillographBuff,	// 示波器显示数据
									long		nScanLine,			// 当前扫描线
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
