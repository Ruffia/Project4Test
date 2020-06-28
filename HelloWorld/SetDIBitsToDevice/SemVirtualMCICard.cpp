// SemVirtualMCICard.cpp: implementation of the CSemVirtualMCICard class.
//
// Last Modify : 2009.06.01
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MCICard.h"
#include "SemVirtualMCICard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSemVirtualMCICard::CSemVirtualMCICard()
{
	m_pMCICard		= NULL;
	m_dblZoom		= 1.0;
	m_sizeReso		= CSize(512,512);
	m_nDetectorMode	= 0;
	m_nDet2nd		= 0;
	m_bDebugZ		= FALSE;
	m_bDebugOsc		= FALSE;
	m_bDebugOsc90	= FALSE;
	m_nusbFunction	= 1;
	m_bSplit		= FALSE;
	m_bLive			= FALSE;
	m_nChnIndex[0]	= 0;
	m_nChnIndex[1]	= 1;
	m_sizeMonitor.cx= 480;
	m_sizeMonitor.cy= 270;

	m_pMPComm		= NULL;

	m_csPhotoSN		= _T("SN:0000");			// 照相编号显示
	int i;
	for( i=0; i<SharedImageBuffCounts; i++ )
		m_pSharedImageBuff[i] = NULL;
}

CSemVirtualMCICard::~CSemVirtualMCICard()
{
	Close();
}


void CSemVirtualMCICard::SetScreenClientPos(const CPoint& pt)
{
	if(NULL == m_pMCICard) return;
	m_pMCICard->SetScreenClientPos(pt);
}

void CSemVirtualMCICard::SetScreenClientRect(const CRect& rc)
{
	if(NULL == m_pMCICard) return;
	m_pMCICard->SetScreenClientRect(rc);
}


HDIB CSemVirtualMCICard::GetDib()
{ 
	if ( !isReady() )
		return NULL;

	if ( m_pMCICard == NULL )
		return NULL;

	return m_pMCICard->CopyImageDib();
}

BOOL CSemVirtualMCICard::GetGraphBmp( CBitmap& bmpGraphLay )
{
	if ( !isReady() )
		return FALSE;

	if ( m_pMCICard == NULL )
		return FALSE;

	return m_pMCICard->CopyGraphBmp(bmpGraphLay);
}

BOOL CSemVirtualMCICard::CopyScreenBmp( CBitmap& bmpScreen )
{
	if ( !isReady() )
		return FALSE;

	if ( m_pMCICard == NULL )
		return FALSE;

	return m_pMCICard->CopyScreenBmp(bmpScreen);
}

BOOL CSemVirtualMCICard::Close( )
{
	if ( m_pMCICard != NULL )
	{
		m_pMCICard->Close();
		m_pMCICard->KillThread();
		m_pMCICard = NULL;
	}

	m_bReady = FALSE;

	return TRUE;
}

BOOL CSemVirtualMCICard::Reset( CWnd* pWnd )
{
	//Close( );

	m_pMCICard = new CMCICard();

	ASSERT_VALID(m_pMCICard);
	if ( m_pMCICard != NULL )
	{
		int i;
		for( i=0; i<10; i++ )
			m_pMCICard->SetColor( i, m_sysOpt.color[i] );
		for( i=0; i<3; i++ )
			m_pMCICard->SetFontName( i, m_sysOpt.fName[i] );
		for( i=0; i<3; i++ )
			m_pMCICard->SetFontSize( i, m_sysOpt.fSize[i] );
		m_pMCICard->SetTransparent( m_sysOpt.nShowParams[SysOpt_showLabelTrans] );

		m_pMCICard->SetZoom( m_dblZoom );
		m_pMCICard->SetParams( SET_PARAMS_DetectorMode, m_nDetectorMode );
		m_pMCICard->SetParams( 4, m_nDet2nd );
		m_pMCICard->SetParams( 5, m_bDebugZ );
		m_pMCICard->SetParams( 6, m_bDebugOsc );
		m_pMCICard->SetParams( 8, m_bDebugOsc90 );
		m_pMCICard->SetParams( 10, m_sysOpt.nLineWidth );
		m_pMCICard->SetParams( 11, m_nChnIndex[0] );
		m_pMCICard->SetParams( 12, m_nChnIndex[1] );
		m_pMCICard->SetParams( 13, m_sizeMonitor.cx );
		m_pMCICard->SetParams( 14, m_sizeMonitor.cy );
		m_pMCICard->SetFunction( m_nusbFunction );
		m_pMCICard->SetSplit( m_bSplit );
		m_pMCICard->SetLiveMode( m_bLive );
		m_pMCICard->SetResolution( m_sizeReso );
		m_pMCICard->UpdatePhotoSN( m_csPhotoSN );
		for( i=0; i<11; i++ )
		{
			m_pMCICard->UpdateFooter( i, m_footerOpt.opt[i].bVisible, m_footerOpt.opt[i].ptPos );
			m_pMCICard->UpdateFooterText( i, m_footerOpt.opt[i].strDisp );
		}
		for( i=0; i<SharedImageBuffCounts; i++ )
			m_pMCICard->SetSharedImageBuff( i, m_pSharedImageBuff[i] );

		if ( m_pMCICard->Reset( pWnd ) )
		{
			m_pMCICard->m_pThreadParams = NULL;

			// Create Thread in a suspended state so we can set the Priority
			// before it starts getting away from us
			if (!m_pMCICard->CreateThread(CREATE_SUSPENDED))
			{
				delete m_pMCICard;
				m_pMCICard = NULL;
			}
			else
			{
				//VERIFY(m_pMCICard->SetThreadPriority(THREAD_PRIORITY_IDLE));
//				VERIFY(m_pMCICard->SetThreadPriority(THREAD_PRIORITY_NORMAL));
				//VERIFY(m_pMCICard->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL));
				VERIFY(m_pMCICard->SetThreadPriority(THREAD_PRIORITY_HIGHEST));

				// Now the thread can run wild
				m_pMCICard->ResumeThread();  // remark by LMH 2001-8-7 Test for 慢扫死机 T9

				m_bReady = TRUE;
			}
		}
		else
		{
			Close();
		}
	}

	return m_bReady;
}

BOOL CSemVirtualMCICard::IsShouldReset()
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->IsShouldReset();

	return FALSE;
}

BOOL CSemVirtualMCICard::InitData( DWORD dwExpectantDMABlockSize, int nXOffset, int nYOffset )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->InitData( dwExpectantDMABlockSize, nXOffset, nYOffset );

	return FALSE;
}

BOOL CSemVirtualMCICard::ClearData()
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->ClearData();

	return FALSE;
}

BOOL CSemVirtualMCICard::Write( LPVOID lpBuff, long lBuffSize, CRect& rcFrameWindow, int nDataStoreMode )
{
	if ( m_pMCICard == NULL )
		return FALSE;

	if ( !(m_pMCICard->IsReady()) )
		return FALSE;

	if( nDataStoreMode > 0 )
		m_pMCICard->ImageDibWriteNewXYZ( lpBuff, lBuffSize, rcFrameWindow );// 11.11.28
	else
//		m_pMCICard->ImageDibWriteNewZZZ( lpBuff, lBuffSize, rcFrameWindow );// 11.12.06
		m_pMCICard->ImageDibWrite( lpBuff, lBuffSize, rcFrameWindow );// 11.12.06

	return TRUE;
}

BOOL CSemVirtualMCICard::PostData( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	if ( m_pMCICard == NULL )
		return FALSE;

	if ( !(m_pMCICard->IsReady()) )
		return FALSE;

	m_pMCICard->PostData( lpBuff, lBuffSize, rcFrameDestWindow );

	return TRUE;
}

BOOL CSemVirtualMCICard::Read( LPVOID lpBuff, long lBuffSize, CRect& rcFrameWindow )
{
	if ( m_pMCICard == NULL )
		return FALSE;

	if ( !(m_pMCICard->IsReady()) )
		return FALSE;

	m_pMCICard->ImageDibRead( lpBuff, lBuffSize, rcFrameWindow );

	return TRUE;
}

void CSemVirtualMCICard::SetColor( int nType, COLORREF color )
{
	m_sysOpt.color[nType]	= color;

	if ( m_pMCICard != NULL )
		m_pMCICard->SetColor( nType, color );
}

void CSemVirtualMCICard::SetFontName( int nType, CString strName )
{
	m_sysOpt.fName[nType]	= strName;

	if ( m_pMCICard != NULL )
		m_pMCICard->SetFontName( nType, strName );
}

void CSemVirtualMCICard::SetFontSize( int nType, int nSize )
{
	m_sysOpt.fSize[nType]	= nSize;

	if ( m_pMCICard != NULL )
		m_pMCICard->SetFontSize( nType, nSize );
}

void CSemVirtualMCICard::SetFontWeight( int nType, int nWeight )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->SetFontWeight( nType, nWeight );
}

void CSemVirtualMCICard::SetTransparent( int nTransparent )
{
	m_sysOpt.nShowParams[SysOpt_showLabelTrans] = nTransparent;

	if ( m_pMCICard != NULL )
		m_pMCICard->SetTransparent( nTransparent );
}

void CSemVirtualMCICard::SetParams( int nType, int nParam )
{
	switch( nType )
	{
	case	SET_PARAMS_DetectorMode:
		m_nDetectorMode = nParam;
		break;
	case	4:	// 显示奇数/偶数通道图像数据
		m_nDet2nd = nParam;	// 0: 偶数通道，默认值；1：奇数通道
		break;
	case	5:	// 调试模式吗？
		m_bDebugZ = (BOOL)nParam;
		break;
	case	6:
		m_bDebugOsc = (BOOL)nParam;
		break;
	case	8:
		m_bDebugOsc90 = (BOOL)nParam;
		break;
	case	10:
		m_sysOpt.nLineWidth = nParam;
		break;
	case	11:
		m_nChnIndex[0] = nParam;
		break;
	case	12:
		m_nChnIndex[1] = nParam;
		break;
	case	13:
		m_sizeMonitor.cx = nParam;
		break;
	case	14:
		m_sizeMonitor.cy = nParam;
		break;
	default:
		break;
	}

	if ( m_pMCICard == NULL )
		return;

	if ( !(m_pMCICard->IsReady()) )
		return;

	m_pMCICard->SetParams( nType, nParam );
}

void CSemVirtualMCICard::SetSharedImageBuff( int nIndex, unsigned short* pBuff )	// 设置并存储共享内存段首地址
{
	m_pSharedImageBuff[nIndex] = pBuff;

	if( m_pMCICard != NULL )
		m_pMCICard->SetSharedImageBuff( nIndex, pBuff );
}

void CSemVirtualMCICard::SetSharedImageBuffIndex( int nIndex )
{
	if( m_pMCICard != NULL )
		m_pMCICard->SetSharedImageBuffIndex( nIndex );
}
void CSemVirtualMCICard::GetCurrentY( int &nY1, int &nY2 )
{
	if( m_pMCICard != NULL )
	{
		nY1	= m_pMCICard->m_nCurrentY1;
		nY2	= m_pMCICard->m_nCurrentY2;
	}
	else
	{
		nY1 = 0;
		nY2	= 0;
	}
}

CSize CSemVirtualMCICard::GetResolution()
{ 
	if (m_pMCICard != NULL)
		return m_pMCICard->GetResolution();

	return m_sizeReso;
}

void CSemVirtualMCICard::SetResolution(CSize szReso)
{
	m_sizeReso = szReso;

	if (m_pMCICard != NULL)
		m_pMCICard->SetResolution( m_sizeReso );
}

void CSemVirtualMCICard::SetFunction( int nFunction )
{
	m_nusbFunction = nFunction;

	if (m_pMCICard != NULL)
		m_pMCICard->SetFunction( nFunction );
}

void CSemVirtualMCICard::SetSplit( BOOL bSplit )
{
	m_bSplit = bSplit;

	if (m_pMCICard != NULL)
		m_pMCICard->SetSplit( bSplit );
}

void CSemVirtualMCICard::SetLiveMode( BOOL bLive )
{
	m_bLive = bLive;
	
	if (m_pMCICard != NULL)
		m_pMCICard->SetLiveMode( bLive );
}

double CSemVirtualMCICard::GetZoom()
{
	if (m_pMCICard != NULL)
		return m_pMCICard->GetZoom();

	return m_dblZoom;
}

void CSemVirtualMCICard::SetZoom(double dblZoom)
{
	m_dblZoom = dblZoom;

	if (m_pMCICard != NULL)
		m_pMCICard->SetZoom( m_dblZoom );
}

void CSemVirtualMCICard::SetDestFrame(CRect rcDestFrame)
{
	if (m_pMCICard != NULL)
		m_pMCICard->SetDestFrame( rcDestFrame );
}

CSize CSemVirtualMCICard::GetSizes( int nIndex )
{
	if( m_pMCICard != NULL )
		return m_pMCICard->GetSizes( nIndex );

	return CSize(0,0);
}

void CSemVirtualMCICard::PhotoIndication( const CRect& rcDest, const COLORREF color, const BOOL boolFill )//09.06.01
{
	if ( m_pMCICard != NULL )
		m_pMCICard->PhotoIndication( rcDest, color, boolFill );
}

void CSemVirtualMCICard::SetPhotoPreview( BOOL boolPreview )//05.02.06
{
	if( m_pMCICard != NULL )
		m_pMCICard->SetPhotoPreview( boolPreview );
}

//06.11.22 3200与3900采集屏显示兼容
void CSemVirtualMCICard::SetScanScreenMode( BOOL boolNewScanScreenMode )
{
	if( m_pMCICard != NULL )
		m_pMCICard->SetScanScreenMode( boolNewScanScreenMode );
}

void CSemVirtualMCICard::SetProductLogo( CString csLogo )
{
	if( m_pMCICard != NULL )
		m_pMCICard->SetProductLogo( csLogo );
}

BOOL CSemVirtualMCICard::ShowLabel( BOOL boolShow )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->ShowLabel( boolShow );

	return FALSE;
}

BOOL CSemVirtualMCICard::ShowTime( BOOL boolShow )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->ShowTime( boolShow );
	
	return FALSE;
}

BOOL CSemVirtualMCICard::ShowNote( BOOL boolShow )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->ShowNote( boolShow );
	
	return FALSE;
}

BOOL CSemVirtualMCICard::ShowMobileUScale( BOOL boolShow )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->ShowMobileUScale( boolShow );

	return FALSE;
}

BOOL CSemVirtualMCICard::ShowFrameRate( BOOL boolShow )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->ShowFrameRate( boolShow );

	return FALSE;
}

void CSemVirtualMCICard::UpdateHV( CString csHV )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->UpdateHV( csHV );
}

void CSemVirtualMCICard::UpdateWD( CString csWD )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->UpdateWD( csWD );
}

void CSemVirtualMCICard::UpdatePhotoSN( CString csPhotoSN )
{
	m_csPhotoSN = csPhotoSN;
	if ( m_pMCICard != NULL )
		m_pMCICard->UpdatePhotoSN( csPhotoSN );
}

void CSemVirtualMCICard::UpdateTime( CString csTime )
{
	if (m_pMCICard != NULL )
		m_pMCICard->UpdateTime( csTime );
}

void CSemVirtualMCICard::UpdateNote( CString csNote )
{
	if (m_pMCICard != NULL )
		m_pMCICard->UpdateNote( csNote );
}

void CSemVirtualMCICard::UpdateVac( CString csVac )
{
	if (m_pMCICard != NULL )
		m_pMCICard->UpdateVac( csVac );
}

void CSemVirtualMCICard::UpdateMAG(
	CString		csMag,					// 放大倍数显示字符
	int			nUScalePixelNum,		// 固定标尺显示长度
	CString		csUScal,				// 固定标尺显示字符
	CString		csMobileUScaleText )	// 移动标尺显示字符
{	
	if ( m_pMCICard != NULL )
		m_pMCICard->UpdateMAG(csMag, nUScalePixelNum, csUScal, csMobileUScaleText);
}

void CSemVirtualMCICard::UpdateUScale(
	int			nMobileUScalePixelNum,	// 移动标尺显示长度
	CString		csMobileUScaleText )	// 移动标尺显示字符
{
	if ( m_pMCICard != NULL )
		m_pMCICard->UpdateUScale(nMobileUScalePixelNum, csMobileUScaleText);
}

void CSemVirtualMCICard::GetMobileUScaleParam( int& nMobileUScalePixelNum, CPoint& ptMobileUScale )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->GetMobileUScaleParam(nMobileUScalePixelNum, ptMobileUScale);
}

void CSemVirtualMCICard::SetMobileUScalePos( CPoint ptMobileUScale )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->SetMobileUScalePos(ptMobileUScale);
}

//======2007.08.20_任意方向移动标尺========================
// 修改标示：2007.08.20_任意方向移动标尺
// 修改日期：2007.08.20星期一
// 修改人  ：J.Y.Ma
// 修改原因：移动标尺由单一水平方向变为任意方向

// 本次修改前代码副本
/*----------------------------------------------------- 
//---------------------------------------------------*/

// 本次修改后代码
//-----------------------------------------------------
///////////////////////////////////////////////////////
void CSemVirtualMCICard::GetMobileUScaleParamEx( int& nMobileUScalePixelNum, CPoint& ptMobileUScale, CPoint& ptMobileUScale2 )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->GetMobileUScaleParamEx(nMobileUScalePixelNum, ptMobileUScale, ptMobileUScale2);
}

void CSemVirtualMCICard::SetMobileUScalePosEx(
		const CPoint ptMobileUScale, const CPoint ptMobileUScale2, const COLORREF color )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->SetMobileUScalePosEx(ptMobileUScale, ptMobileUScale2, color);
}
//-----------------------------------------------------
//======2007.08.20_任意方向移动标尺========================

// 16.06.12 多移动标尺实验
void CSemVirtualMCICard::GetMobileUScaleParamArray( int nIndex, int&	nMobileUScalePixelNum, CPoint& ptMobileUScale, CPoint& ptMobileUScale2 )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->GetMobileUScaleParamArray(nIndex, nMobileUScalePixelNum, ptMobileUScale, ptMobileUScale2);
}

void CSemVirtualMCICard::SetMobileUScalePosArray( int nIndex, CPoint ptMobileUScale, CPoint ptMobileUScale2, COLORREF color )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->SetMobileUScalePosArray(nIndex, ptMobileUScale, ptMobileUScale2, color);
}

void CSemVirtualMCICard::UpdateUScaleArray(	int			nIndex,
						  int			nMobileUScalePixelNum,	// 移动标尺显示长度
						  CString		csMobileUScaleText )	// 移动标尺显示字符
{
	if ( m_pMCICard != NULL )
		m_pMCICard->UpdateUScaleArray( nIndex, nMobileUScalePixelNum, csMobileUScaleText );
}

void CSemVirtualMCICard::UpdateMAGArray(	int nIndex,
					   CString	csMobileUScaleText )	// 移动标尺显示字符
{
	if ( m_pMCICard != NULL )
		m_pMCICard->UpdateMAGArray( nIndex, csMobileUScaleText );
}
// 16.06.12 多移动标尺实验

// 19.02.18 底标自定义
void CSemVirtualMCICard::UpdateFooter( int nIndex, BOOL bVisible, CPoint ptPos )
{
	m_footerOpt.opt[nIndex].bVisible = bVisible;
	m_footerOpt.opt[nIndex].ptPos = ptPos;
	if ( m_pMCICard != NULL )
		m_pMCICard->UpdateFooter( nIndex, bVisible, ptPos );
}

void CSemVirtualMCICard::UpdateFooterText( int nIndex, CString csText )
{
	m_footerOpt.opt[nIndex].strDisp = csText;
	if ( m_pMCICard != NULL )
		m_pMCICard->UpdateFooterText( nIndex, csText );
}
// 19.02.18 底标自定义

BOOL CSemVirtualMCICard::GraphDrawLine(
		const CPoint ptPos0, const CPoint ptPos1, const COLORREF color )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->GraphDrawLine(	ptPos0, ptPos1, color );

	return FALSE;
}

BOOL CSemVirtualMCICard::GraphDrawLineEx( const int nLength )	// 单位：mm
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->GraphDrawLineEx(	nLength );

	return FALSE;
}

BOOL CSemVirtualMCICard::GraphDrawRect( const CRect rcDest, const COLORREF color )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->GraphDrawRect( rcDest, color );

	return FALSE;
}

BOOL CSemVirtualMCICard::GraphDrawRectEx( const BOOL bDrawCircle, const CRect rcDest, const COLORREF color )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->GraphDrawRectEx( bDrawCircle, rcDest, color );

	return FALSE;
}

BOOL CSemVirtualMCICard::GraphDrawCircle( const CPoint ptCenter, const CPoint ptEnd, BOOL bDrawArrow, const int nRadius, const COLORREF color )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->GraphDrawCircle( ptCenter, ptEnd, bDrawArrow, nRadius, color );

	return FALSE;
}

BOOL CSemVirtualMCICard::GraphClear( const CRect rcDest, const COLORREF color )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->GraphClear( rcDest, color );

	return FALSE;
}

CSize CSemVirtualMCICard::GraphTextOut( const CPoint ptPos, const CString csText )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->GraphTextOut( ptPos, csText );

	return CSize(0,0);
}

CSize CSemVirtualMCICard::GetOutputTextExtent( const CString csText )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->GetOutputTextExtent( csText );

	return CSize(0,0);
}

BOOL CSemVirtualMCICard::ShowOscillograph( BOOL boolShow )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->ShowOscillograph( boolShow );

	return FALSE;
}

void CSemVirtualMCICard::GetOscillographParam( CPoint& ptPos )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->GetOscillographParam(ptPos);
}

void CSemVirtualMCICard::SetOscillographPos( CPoint ptPos )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->SetOscillographPos(ptPos);
}

void CSemVirtualMCICard::UpdateOscillograph( LPBYTE pBuff, long nScanLine, long nStart, long nStop )
{
	if ( m_pMCICard != NULL )
		m_pMCICard->UpdateOscillograph( pBuff, nScanLine, nStart, nStop );
}

void CSemVirtualMCICard::SetOscillographAmplifer(double dblAmplifer)
{
	if ( m_pMCICard != NULL )
		m_pMCICard->SetOscillographAmplifer( dblAmplifer );
}


BOOL CSemVirtualMCICard::IsReadyFramGrayHistogram()
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->IsReadyFramGrayHistogram();

	return FALSE;
}

void CSemVirtualMCICard::FramGrayHistogramStart()
{
	if ( m_pMCICard != NULL )
		m_pMCICard->FramGrayHistogramStart();
}

void CSemVirtualMCICard::FramGrayHistogramStop()
{
	if ( m_pMCICard != NULL )
		m_pMCICard->FramGrayHistogramStop();
}

void CSemVirtualMCICard::FramGrayHistogramReset()
{
	if ( m_pMCICard != NULL )
		m_pMCICard->FramGrayHistogramReset();
}

DWORD CSemVirtualMCICard::CopyFramGrayHistogramBuff( DWORD* pFramGrayHistogramBuff )
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->CopyFramGrayHistogramBuff( pFramGrayHistogramBuff );

	return 0;
}

BOOL CSemVirtualMCICard::MonitorError( int nModID, int nIndex )
{
	if( m_pMPComm == NULL )
		return FALSE;

	USB_SEM_ControlMessage	mciMSG;
	mciMSG.bType			= 0x1;
	mciMSG.bCtlMSGLength	= 3;
	mciMSG.bMessageID		= USB_TTTT_Mon_Err;
	mciMSG.bData[1]			= nModID;
	mciMSG.bData[2]			= nIndex;

	return TRUE;
}

BOOL CSemVirtualMCICard::IsSyncFinish()
{
	if ( m_pMCICard != NULL )
		return m_pMCICard->m_bSyncFinished;
	return FALSE;
}
