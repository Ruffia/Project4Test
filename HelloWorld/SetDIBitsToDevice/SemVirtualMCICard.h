// SEMVIRTUALMCICARD.h: interface for the CSemVirtualMCICard class.
//
// Last Modify : 2009.06.01
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEMVIRTUALMCICARD_H__8B2499A8_98AF_4E41_BA44_A0AF88B434F0__INCLUDED_)
#define AFX_SEMVIRTUALMCICARD_H__8B2499A8_98AF_4E41_BA44_A0AF88B434F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MCICardParam.h"
#include "USB_Functions.h"

///////////////////////////////////////////////////////
#ifndef _INC_DIBAPI

// Handle to a DIB
DECLARE_HANDLE(HDIB);

#endif // _INC_DIBAPI
///////////////////////////////////////////////////////

class CMCICard;
class CMP;

class CSemVirtualMCICard  
{
	CMCICard*			m_pMCICard;
//	USB_Image_Resolution	m_Resolution;		// Resolution
	CSize				m_sizeReso;				// Resolution
	int					m_nusbFunction;			// Scan Type
	BOOL				m_bSplit;				// Split type
	BOOL				m_bLive;				// Live mode
	double				m_dblZoom;				// The map of Image to screen
	BOOL				m_bReady;
	int					m_nDetectorMode;		// 探测器模式
	int					m_nDet2nd;				// 0: 偶数通道，默认值；1：奇数通道
	BOOL				m_bDebugZ;				// 调试模式时，示波器意义不同
	BOOL				m_bDebugOsc;
	BOOL				m_bDebugOsc90;			// 示波器转90度
	int					m_nChnIndex[2];			// 双通道显示方式时左右各显示哪个通道的数据。
												// 0：对应硬件通道组中的偶数通道的数据Za；
												// 1：对应硬件通道组中的奇数通道的数据Zb；
												// 2：两通道数据平均值作为显示数据(Za+Zb)/2
	CSize				m_sizeMonitor;			// 屏幕实际尺寸

	CMP*				m_pMPComm;
	unsigned short*		m_pSharedImageBuff[SharedImageBuffCounts];

	CString				m_csPhotoSN;			// 照相编号显示字符

	SYS_Options			m_sysOpt;				// 系统颜色及字体设置
	Footer_Options		m_footerOpt;			// 底标设置

public:
	CSemVirtualMCICard();
	virtual ~CSemVirtualMCICard();

	BOOL	Close( );
	BOOL	Reset( CWnd* pWnd );
	BOOL	IsShouldReset();
	BOOL	isReady(){ return m_bReady; }

	HDIB	GetDib();
	BOOL	GetGraphBmp( CBitmap& bmpGraphLay );
	BOOL	CopyScreenBmp( CBitmap& bmpScreen );

	CSize	GetResolution();
	void	SetResolution(CSize szReso);
	void	SetFunction( int nFunction );
	void	SetSplit( BOOL bSplit );
	void	SetLiveMode( BOOL bLive );
	void	GetCurrentY( int &nY1, int &nY2 );

	double	GetZoom();
	void	SetZoom(double dblZoom);

	void	SetDestFrame( CRect rcDestFrame );
	CSize	GetSizes( int nIndex );

	void	SetColor( int nType, COLORREF color );
	void	SetFontName( int nType, CString strName );
	void	SetFontSize( int nType, int nSize );
	void	SetFontWeight( int nType, int nWeight );
	void	SetTransparent( int nTransparent );

	BOOL	Write( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow, int nDataStoreMode = 0 );
	BOOL	Read( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow );
	BOOL	PostData( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow );
	BOOL	InitData( DWORD dwExpectantDMABlockSize, int nXOffset = 0, int nYOffset = 0 );
	BOOL	ClearData();
	BOOL	MonitorError( int nModID, int nIndex );
	BOOL	IsSyncFinish();

	void	SetParams( int nType, int nParam );	// 设置数据存储模式，探测器模式
	void	SetSharedImageBuff( int nIndex,
					unsigned short* pBuff );	// 设置并存储共享内存段首地址
	void	SetSharedImageBuffIndex( int nIndex );

	void	PhotoIndication( const CRect& rcDest, const COLORREF color = RGB(0,0,0), const BOOL boolFill = TRUE );//09.06.01
	void	SetPhotoPreview( BOOL boolPreview );//05.02.06

	//06.11.22 3200与3900采集屏显示兼容
	void	SetScanScreenMode( BOOL boolNewScanScreenMode = TRUE );
	void	SetProductLogo( CString csLogo );

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

	BOOL	ShowLabel(BOOL boolShow = TRUE);
	BOOL	ShowTime(BOOL boolShow = TRUE);
	BOOL	ShowNote(BOOL boolShow = TRUE);
	BOOL	ShowMobileUScale(BOOL boolShow = TRUE);
	BOOL	ShowFrameRate(BOOL boolShow = TRUE);

	void SetScreenClientPos(const CPoint& pt);
	void SetScreenClientRect(const CRect& rc);

	//////////////////////////////////////////////////////////
	void	UpdateHV(CString	csHV);
	void	UpdateWD(CString	csWD);
	void	UpdatePhotoSN(CString	csPhotoSN);
	void	UpdateTime(CString	csTime);
	void	UpdateNote(CString	csNote);
	void	UpdateVac(CString csVac);

	void	UpdateMAG(
			CString	csMag,					// 放大倍数显示字符
			int		nUScalePixelNum,		// 固定标尺显示长度
			CString	csUScal,				// 固定标尺显示字符
			CString	csMobileUScaleText );	// 移动标尺显示字符

	void	UpdateUScale(
			int		nMobileUScalePixelNum,	// 移动标尺显示长度
			CString	csMobileUScaleText );	// 移动标尺显示字符

	void	GetMobileUScaleParam( int&	nMobileUScalePixelNum, CPoint& ptMobileUScale );
	void	SetMobileUScalePos( CPoint ptMobileUScale );

	// 07.08.20任意方向移动标尺试验
	void	GetMobileUScaleParamEx( int&	nMobileUScalePixelNum, CPoint& ptMobileUScale, CPoint& ptMobileUScale2 );
	void	SetMobileUScalePosEx( const CPoint ptMobileUScale, const CPoint ptMobileUScale2,
						const COLORREF color = RGB(0,0,0) );
	// 07.08.20任意方向移动标尺试验

	// 16.06.12 多移动标尺实验
	void	GetMobileUScaleParamArray( int nIndex, int&	nMobileUScalePixelNum, CPoint& ptMobileUScale, CPoint& ptMobileUScale2 );
	void	SetMobileUScalePosArray( int nIndex, CPoint ptMobileUScale, CPoint ptMobileUScale2,	COLORREF color = RGB(0,0,0) );
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
	//////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////
	BOOL	ShowOscillograph(BOOL boolShow = TRUE);
	void	SetOscillographPos( CPoint ptOscillograph );
	void	GetOscillographParam( CPoint& ptOscillograph );
	void	UpdateOscillograph( LPBYTE pOscillographBuff, long nScanLine,
						long nStart = 0, long nStop = g_szUSB_FrameOscillograph.cx );
	void	SetOscillographAmplifer(double dblAmplifer = 1.0);
	//////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////
	BOOL	IsReadyFramGrayHistogram();
	void	FramGrayHistogramStart();
	void	FramGrayHistogramStop();
	void	FramGrayHistogramReset();
	DWORD	CopyFramGrayHistogramBuff( DWORD* pFramGrayHistogramBuff );
	//////////////////////////////////////////////////////////
};

#endif // !defined(AFX_SEMVIRTUALMCICARD_H__8B2499A8_98AF_4E41_BA44_A0AF88B434F0__INCLUDED_)
