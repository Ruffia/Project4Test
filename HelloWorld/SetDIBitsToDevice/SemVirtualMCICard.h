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
	int					m_nDetectorMode;		// ̽����ģʽ
	int					m_nDet2nd;				// 0: ż��ͨ����Ĭ��ֵ��1������ͨ��
	BOOL				m_bDebugZ;				// ����ģʽʱ��ʾ�������岻ͬ
	BOOL				m_bDebugOsc;
	BOOL				m_bDebugOsc90;			// ʾ����ת90��
	int					m_nChnIndex[2];			// ˫ͨ����ʾ��ʽʱ���Ҹ���ʾ�ĸ�ͨ�������ݡ�
												// 0����ӦӲ��ͨ�����е�ż��ͨ��������Za��
												// 1����ӦӲ��ͨ�����е�����ͨ��������Zb��
												// 2����ͨ������ƽ��ֵ��Ϊ��ʾ����(Za+Zb)/2
	CSize				m_sizeMonitor;			// ��Ļʵ�ʳߴ�

	CMP*				m_pMPComm;
	unsigned short*		m_pSharedImageBuff[SharedImageBuffCounts];

	CString				m_csPhotoSN;			// ��������ʾ�ַ�

	SYS_Options			m_sysOpt;				// ϵͳ��ɫ����������
	Footer_Options		m_footerOpt;			// �ױ�����

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

	void	SetParams( int nType, int nParam );	// �������ݴ洢ģʽ��̽����ģʽ
	void	SetSharedImageBuff( int nIndex,
					unsigned short* pBuff );	// ���ò��洢�����ڴ���׵�ַ
	void	SetSharedImageBuffIndex( int nIndex );

	void	PhotoIndication( const CRect& rcDest, const COLORREF color = RGB(0,0,0), const BOOL boolFill = TRUE );//09.06.01
	void	SetPhotoPreview( BOOL boolPreview );//05.02.06

	//06.11.22 3200��3900�ɼ�����ʾ����
	void	SetScanScreenMode( BOOL boolNewScanScreenMode = TRUE );
	void	SetProductLogo( CString csLogo );

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
			CString	csMag,					// �Ŵ�����ʾ�ַ�
			int		nUScalePixelNum,		// �̶������ʾ����
			CString	csUScal,				// �̶������ʾ�ַ�
			CString	csMobileUScaleText );	// �ƶ������ʾ�ַ�

	void	UpdateUScale(
			int		nMobileUScalePixelNum,	// �ƶ������ʾ����
			CString	csMobileUScaleText );	// �ƶ������ʾ�ַ�

	void	GetMobileUScaleParam( int&	nMobileUScalePixelNum, CPoint& ptMobileUScale );
	void	SetMobileUScalePos( CPoint ptMobileUScale );

	// 07.08.20���ⷽ���ƶ��������
	void	GetMobileUScaleParamEx( int&	nMobileUScalePixelNum, CPoint& ptMobileUScale, CPoint& ptMobileUScale2 );
	void	SetMobileUScalePosEx( const CPoint ptMobileUScale, const CPoint ptMobileUScale2,
						const COLORREF color = RGB(0,0,0) );
	// 07.08.20���ⷽ���ƶ��������

	// 16.06.12 ���ƶ����ʵ��
	void	GetMobileUScaleParamArray( int nIndex, int&	nMobileUScalePixelNum, CPoint& ptMobileUScale, CPoint& ptMobileUScale2 );
	void	SetMobileUScalePosArray( int nIndex, CPoint ptMobileUScale, CPoint ptMobileUScale2,	COLORREF color = RGB(0,0,0) );
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
