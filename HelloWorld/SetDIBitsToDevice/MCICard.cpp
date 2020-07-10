// MCICard.cpp : implementation file
//
// Last Modify : 2009.12.03

/////////////////////////////////////////////////////////////////////////////
// 09.11.24在SetZoom中加入同步语句
// 09.12.03修改Mainloop中同步语句的位置，将GetClientWindow也纳入同步
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ddutil.h"
#include "MCICard.h"
#include "CommFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TCHAR g_exeFullPath[255];
int g_index;

CCriticalSection CMCICard::m_mutexLayAll;
CCriticalSection CMCICard::m_mutexImageDib;
CCriticalSection CMCICard::m_mutexImageUSB;


void CaptureScreenRect( CBitmap& bmpScreen, CDC* pScreenDC, const CRect& rcCapture )
{
/*	CDC dcTemp;
	dcTemp.CreateCompatibleDC( pScreenDC );
	BOOL bRet = bmpScreen.CreateCompatibleBitmap( pScreenDC, rcCapture.Width(), rcCapture.Height() );
	if( !bRet )
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
		// Free the buffer.
		LocalFree( lpMsgBuf );
	}
	CBitmap* pOldBitmap = dcTemp.SelectObject( &bmpScreen );
	dcTemp.BitBlt( 0, 0, rcCapture.Width(), rcCapture.Height(),
		pScreenDC, rcCapture.left, rcCapture.top, SRCCOPY );
	dcTemp.SelectObject(pOldBitmap);
	dcTemp.DeleteDC();
*/
	/////////////////////////////////////////////
	HDC hcompDC = CreateCompatibleDC(pScreenDC->m_hDC);
	BITMAPINFO	bmi;
	BYTE		bits;
		
	// Setup BITMAPINFOHEAD.
	bmi.bmiHeader.biSize			= sizeof (BITMAPINFOHEADER) ;
	bmi.bmiHeader.biWidth			= rcCapture.Width();
	bmi.bmiHeader.biHeight			= rcCapture.Height();
	bmi.bmiHeader.biPlanes			= 1;
	bmi.bmiHeader.biBitCount		= 32;
	bmi.bmiHeader.biCompression		= BI_RGB;
	bmi.bmiHeader.biSizeImage		= 0;
	bmi.bmiHeader.biXPelsPerMeter	= 0;
	bmi.bmiHeader.biYPelsPerMeter	= 0;
	bmi.bmiHeader.biClrUsed			= 0;
	bmi.bmiHeader.biClrImportant	= 0;
	bmpScreen.m_hObject = CreateDIBSection (NULL, &bmi, 0, (void **)&bits, NULL, 0) ;
	/////////////////////////////////////////////
	if( bmpScreen.m_hObject == NULL)
		return;
	HBITMAP hbmp=(HBITMAP)SelectObject(hcompDC, bmpScreen.m_hObject);
	BitBlt(hcompDC, 0, 0, rcCapture.Width(), rcCapture.Height(), pScreenDC->m_hDC, rcCapture.left, rcCapture.top, SRCCOPY);
	SelectObject(hcompDC, hbmp);
	DeleteDC(hcompDC);
}


/////////////////////////////////////////////////////////////////////////////
// CMCICard

IMPLEMENT_DYNCREATE(CMCICard, CWinThread)

CMCICard::CMCICard()
{
	/////////////////////////////////////////////////////////////////
	m_bAutoDelete			= FALSE;

	// kill event starts out in the signaled state
	m_hEventKill = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hEventDead = CreateEvent(NULL, TRUE, FALSE, NULL);
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	m_boolReady				= FALSE;
	m_boolShouldReset		= FALSE;
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	m_lpDD					= NULL;		// DirectDraw object
	m_lpDDSPrimary			= NULL;		// DirectDraw primary surface
	m_lpDDPalette			= NULL;		// DirectDraw palette
	m_lpClipper				= NULL;		// clipper for primary

	m_lpDDSPrimaryBackLay	= NULL;		// Offscreen surface Primary Back Lay
	m_lpDDSGraphBackLay		= NULL;		// Offscreen surface Graph Back Lay

	m_lpDDSImageLay			= NULL;		// Offscreen surface Image Lay
	m_lpDDSGraphLay			= NULL;		// Offscreen surface Graph Lay
	m_lpDDSLabelLay			= NULL;		// Offscreen surface Label Lay
	m_lpDDSMobileUScaleLay	= NULL;		// Offscreen surface UScale Lay
	m_lpDDSOscillographLay	= NULL;		// Offscreen surface Oscillograph Lay
	m_lpDDSFrameRate		= NULL;		// Offscreen surface Info Lay

	m_sysOpt.color[SysOpt_clrTransparent] = g_clrUSB_Transparent;

#ifdef GRAPHIC_Transparent
	m_sysOpt.color[SysOpt_clrBack]		= g_clrUSB_Transparent;
#else
	m_sysOpt.color[SysOpt_clrBack]		= g_clrUSB_Background;
#endif

	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	m_hdibImage				= NULL;
	m_lpImageDibPlan		= NULL;
	/////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////
	m_pScreenWnd			= NULL;
	m_dblZoom				= 1.0;
//	SetResolution( USB_RESO_512_512 );

	m_lastTickCount			= 0;
	///////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// Label & uScale
	/////////////////////////////////////////////////////////////////
	m_boolRedrawLabel		= FALSE;
	m_boolRedrawUScal		= FALSE;

	m_boolShowLabel			= TRUE;
	m_boolShowTime			= FALSE;
	m_boolShowNote			= FALSE;
	m_boolShowMobileUScale	= FALSE;

    m_hfontEditText			= NULL;	// 2004-8-2_加强图形层显示
    m_hfontLabelText		= NULL;
    m_hfontLabelLogoText	= NULL;
	m_hfontMobileUScaleText	= NULL;
	///////////////////////////////////////////////////////////////////
	m_sysOpt.color[SysOpt_clrEditText]			= g_clrUSB_EditText;
	m_sysOpt.color[SysOpt_clrLabelText]			= g_clrUSB_LabelText;
	m_sysOpt.color[SysOpt_clrLabelLogoText]		= g_clrUSB_LabelLogoText;
	m_sysOpt.color[SysOpt_clrOscillographGrid]	= RGB(0,255,0);
	m_sysOpt.color[SysOpt_clrOscillographGraph]	= g_clrUSB_MobileUScale;
	///////////////////////////////////////////////////////////////////

	int i;
	/////////////////////////////////////////////////////////////////
	// Footer 19.02.18
	for( i=0; i<11; i++ )
		m_footerOpt.opt[i].bVisible = FALSE;
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// Statistical infomation
	/////////////////////////////////////////////////////////////////
    //m_boolShowFrameRate	= TRUE;
    m_boolShowFrameRate		= FALSE;

    m_hFontFrameRate		= NULL;
	m_sysOpt.color[SysOpt_clrFrameRate] = RGB(255,0,0);
    m_szFrameRate[0]		= '\0';
	_stprintf( m_szFPS, _T("%s"), _T("FPS %03d BPS %04dK IPS %03d") );

    m_dwFrameTime			= 0;

	m_dwFrameCount			= 0;
    m_dwFramesLast			= 0;
	m_dwFrames				= 0;
    m_iFrameRateX			= 0;

    m_dwAveFrameRate		= 0;
    m_dwAveFrameRateCount	= 0;

	m_dwByteCount			= 0;
    m_dwBytesLast			= 0;
	m_dwBytes				= 0;
	m_iBpsRateX				= 0;

	m_dwInputCount			= 0;
    m_dwInputsLast			= 0;
	m_dwInputs				= 0;
	m_iIPSRateX				= 0;
	/////////////////////////////////////////////////////////////////
	m_boolPreview			= FALSE;
	m_boolNewScanScreenMode	= TRUE;

	m_nDataStoreMode		= 1;					// XYZ存储方式
	m_nDetectorMode			= 0;					// 12.02.15 单探测器模式
	m_bDet2nd				= FALSE;				// 默认显示偶数通道图像
	m_bDebugZ				= FALSE;				// 13.04.03 非调试模式
	m_bDebugOsc				= FALSE;
	m_debugOSC.b90			= FALSE;
	m_debugOSC.nIndexY		= 1;					// 13.04.03 视频示波器Y向512像素代表+/-5
	m_debugOSC.dOffset		= 0.0;					// 13.08.05 示波器偏移量

	m_bDataNeedUpdated		= FALSE;
	m_bStopScan				= FALSE;
//	m_pBuffUSB				= NULL;
	m_pBuffUSB	= new unsigned short[LOOP_COUNTS*409600];
	m_dwExpectantDMABlockSize = 0;
	m_pPixX		= new WORD[ LOOP_COUNTS*409600/4 ];
	m_pPixY		= new WORD[ LOOP_COUNTS*409600/4 ];
	m_pPixZ		= new WORD[ LOOP_COUNTS*409600/4 ];
	m_pPixX2	= new WORD[ LOOP_COUNTS*409600/4 ];
	m_pPixY2	= new WORD[ LOOP_COUNTS*409600/4 ];
	m_pPixZ2	= new WORD[ LOOP_COUNTS*409600/4 ];
	m_pPixZmix	= new WORD[ LOOP_COUNTS*409600/4 ];

	m_hFileLog		= NULL;
	m_bNeedMon		= FALSE;
	m_hLineDataLog	= NULL;
	m_hOscillLog	= NULL;

//	GetMonitorSizeFromEDIDEx( m_dblPixelsPerMM_HORZ, m_dblPixelsPerMM_VERT );

	for( i=0; i<SharedImageBuffCounts; i++ )
		m_pSharedImageBuff[i] = NULL;
	m_nSharedImageBuffIndexRead		= 0;
	m_nSharedImageBuffIndexWrite	= 0;

	m_nCurrentY1	= 0;
	m_nCurrentY2	= 0;

	m_csSG1			= _T("SE");
	m_csSG2			= _T("SE/BSE");
}

CMCICard::~CMCICard()
{
	if ( m_pBuffUSB != NULL )
	{
		delete [] m_pBuffUSB;
		m_pBuffUSB	= NULL;
	}
	if ( m_pPixX != NULL )
	{
		delete [] m_pPixX;
		m_pPixX	= NULL;
	}
	if ( m_pPixY != NULL )
	{
		delete [] m_pPixY;
		m_pPixY	= NULL;
	}
	if ( m_pPixZ != NULL )
	{
		delete [] m_pPixZ;
		m_pPixZ	= NULL;
	}
	if ( m_pPixX2 != NULL )
	{
		delete [] m_pPixX2;
		m_pPixX2	= NULL;
	}
	if ( m_pPixY2 != NULL )
	{
		delete [] m_pPixY2;
		m_pPixY2	= NULL;
	}
	if ( m_pPixZ2 != NULL )
	{
		delete [] m_pPixZ2;
		m_pPixZ2	= NULL;
	}
	if ( m_pPixZmix != NULL )
	{
		delete [] m_pPixZmix;
		m_pPixZmix	= NULL;
	}

	Close();

	CloseHandle(m_hEventKill);
	CloseHandle(m_hEventDead);
}


BOOL CMCICard::InitInstance()
{
	// TODO:  perform and per-thread initialization here

	// loop but check for kill notification
	while (WaitForSingleObject(m_hEventKill, 0) == WAIT_TIMEOUT)
		MainLoop();

	// avoid entering standard message loop by returning FALSE
	return FALSE;  // TRUE;
}

int CMCICard::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMCICard, CWinThread)
	//{{AFX_DebugMessage_MAP(CMCICard)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DebugMessage_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMCICard message handlers
void CMCICard::Delete()
{
	// calling the base here won't do anything but it is a good habit
	CWinThread::Delete();

	// acknowledge receipt of kill notification
	VERIFY(SetEvent(m_hEventDead));
}

void CMCICard::KillThread()
{
	// Note: this function is called in the context of other threads,
	//  not the thread itself.

	// reset the m_hEventKill which signals the thread to shutdown
	VERIFY(SetEvent(m_hEventKill));

	// allow thread to run at higher priority during kill process
	//SetThreadPriority(THREAD_PRIORITY_NORMAL);
	//WaitForSingleObject(m_hEventDead, INFINITE);
	//WaitForSingleObject(m_hThread, INFINITE);

	// now delete CWinThread object since no longer necessary
	delete this;
}

BOOL CMCICard::Close()
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_boolReady		= FALSE;

	/////////////////////////////////////////////////////////////////
    if( m_lpDD != NULL )
    {
		if( m_lpDDSPrimary != NULL )
		{
			m_lpDDSPrimary->Release();
			m_lpDDSPrimary = NULL;
		}
		if( m_lpDDPalette != NULL )
		{
			m_lpDDPalette->Release();
			m_lpDDPalette = NULL;
		}
		if( m_lpClipper != NULL )
		{
			m_lpClipper->Release();
			m_lpClipper	= NULL;
		}

		if( m_lpDDSPrimaryBackLay != NULL )
		{
			m_lpDDSPrimaryBackLay->Release();
			m_lpDDSPrimaryBackLay = NULL;
		}

		if( m_lpDDSGraphBackLay != NULL )
		{
			m_lpDDSGraphBackLay->Release();
			m_lpDDSGraphBackLay = NULL;
		}
		
		if( m_lpDDSImageLay != NULL )
		{
			m_lpDDSImageLay->Release();
			m_lpDDSImageLay = NULL;
		}

		if( m_lpDDSGraphLay != NULL )
		{
			m_lpDDSGraphLay->Release();
			m_lpDDSGraphLay = NULL;
		}

		if( m_lpDDSLabelLay != NULL )
		{
			m_lpDDSLabelLay->Release();
			m_lpDDSLabelLay = NULL;
		}

		if( m_lpDDSMobileUScaleLay != NULL )
		{
			m_lpDDSMobileUScaleLay->Release();
			m_lpDDSMobileUScaleLay = NULL;
		}

		if( m_lpDDSOscillographLay != NULL )
		{
			m_lpDDSOscillographLay->Release();
			m_lpDDSOscillographLay = NULL;
		}

		if( m_lpDDSFrameRate != NULL )
		{
			m_lpDDSFrameRate->Release();
			m_lpDDSFrameRate = NULL;
		}

		m_lpDD->Release();
		m_lpDD = NULL;
    }
	
	if( m_hdibImage != NULL )
	{
		GlobalUnlock( (HGLOBAL)m_hdibImage );
		GlobalFree( (HGLOBAL)m_hdibImage );
		m_hdibImage = NULL;
	}
	m_lpImageDibPlan	= NULL;

	m_paletteImage.DeleteObject();
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    m_blSrcColorkey		= FALSE;
    m_blDestColorkey	= FALSE;
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    if (m_hFontFrameRate != NULL)
    {
        DeleteObject(m_hFontFrameRate);
		m_hFontFrameRate = NULL;
    }
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    if (m_hfontEditText != NULL)	// 2004-8-2_加强图形层显示
    {
        DeleteObject(m_hfontEditText);
		m_hfontEditText = NULL;
    }
    if (m_hfontLabelText != NULL)
    {
        DeleteObject(m_hfontLabelText);
		m_hfontLabelText = NULL;
    }
    if (m_hfontLabelLogoText != NULL)
    {
        DeleteObject(m_hfontLabelLogoText);
		m_hfontLabelLogoText = NULL;
    }
	/////////////////////////////////////////////////////////////////
    if (m_hfontMobileUScaleText != NULL)
    {
        DeleteObject(m_hfontMobileUScaleText);
		m_hfontMobileUScaleText = NULL;
    }
	/////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
	return TRUE;
}

BOOL CMCICard::Reset( CWnd* pWnd )
{
    DDSURFACEDESC			ddsd;
    HRESULT					ddrval;

	//Close();

	m_pScreenWnd = pWnd;

	/////////////////////////////////////////////////////////////////
	m_hdibImage = CreateImageBitmap();
	if ( m_hdibImage == NULL )
	{
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////
    // *
    // * create the main DirectDraw object
    // *
	/////////////////////////////////////////////////////////////////
	LPDIRECTDRAW lpDD;
	ddrval = DirectDrawCreate( NULL, &lpDD, NULL );
	if( ddrval != DD_OK )
		return FALSE;
	ddrval = lpDD->QueryInterface(IID_IDirectDraw2, (LPVOID *) &m_lpDD );
	if( ddrval != S_OK )
	{
		lpDD->Release();
		return FALSE;
	}
	lpDD->Release();
/*	ddrval = DirectDrawCreate( NULL, &m_lpDD, NULL );
    if( ddrval != DD_OK )
	{
        DebugMessage("DirectDrawCreate failed err=%d", ddrval);
		return FALSE;
	}
*/	ddrval = m_lpDD->SetCooperativeLevel( m_pScreenWnd->m_hWnd, DDSCL_NORMAL );
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    // *
    // * check capabilites
    // *
	/////////////////////////////////////////////////////////////////
    HDC			hdc;
    hdc = GetDC(NULL);
	int iPlanes		= GetDeviceCaps(hdc, PLANES);
	int iBitsPixel	= GetDeviceCaps(hdc, BITSPIXEL);
	m_uBPP			= iPlanes * iBitsPixel;
    ReleaseDC(NULL, hdc);

    DDCAPS		ddcaps;
    ddcaps.dwSize = sizeof( ddcaps );

    ddrval = m_lpDD->GetCaps( &ddcaps, NULL );
    if( ddrval != DD_OK )
    {
        DebugMessage(_T("GetCaps failed err=%d"), ddrval);
		return FALSE;
    }
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    if( ddcaps.dwCaps & DDCAPS_NOHARDWARE )
    {
        DebugMessage(_T("No hardware support at all"));
    }

    if( ddcaps.dwCaps & DDCAPS_BLTCOLORFILL )
    {
        m_blColorFill = TRUE;
        DebugMessage(_T("Device supports color fill" ));
    }
    else
    {
        m_blColorFill = FALSE;
        DebugMessage(_T("Device does not support color fill" ));
    }
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	BOOL boolUseSysMemPrimaryBackLay;
	BOOL boolUseSysMemGraphBackLay;
	BOOL boolUseSysMemImageLay;
	BOOL boolUseSysMemGraphLay;
	BOOL boolUseSysMemLabelLay;
	BOOL boolUseSysMemUScaleLay;

	DWORD dwFrameMemSizePrimaryBackLay = 
		GetSystemMetrics(SM_CXSCREEN) * GetSystemMetrics(SM_CYSCREEN) * ( m_uBPP / 8 );
	DWORD dwFrameMemSizeImageLay = m_szImage.cx * m_szImage.cy * ( m_uBPP / 8 );
	DWORD dwFrameMemSizeGraphLay = m_szGraph.cx * m_szGraph.cy * ( m_uBPP / 8 );
	DWORD dwFrameMemSizeLabelLay = m_szLabel.cx * m_szLabel.cy * ( m_uBPP / 8 );
	//07.10.31
	DWORD dwFrameMemSizeUScaleLay;
//	dwFrameMemSizeUScaleLay = m_szUScale.cx * m_szUScale.cy * ( m_uBPP / 8 );
#ifdef NEW_SCANSCREEN_MODE
	dwFrameMemSizeUScaleLay = m_szGraph.cx * m_szGraph.cy * ( m_uBPP / 8 );
#else
	dwFrameMemSizeUScaleLay = m_szUScale.cx * m_szUScale.cy * ( m_uBPP / 8 );
#endif
	//07.10.31
	DWORD dwFrameMemSizeGraphBackLay = dwFrameMemSizeGraphLay;
	/////////////////////////////////////////////////////////////////

	m_dwVidMemTotal = ddcaps.dwVidMemTotal;
	/////////////////////////////////////////////////////////////////
    if( ddcaps.dwVidMemTotal <= dwFrameMemSizePrimaryBackLay )
    {
		boolUseSysMemPrimaryBackLay	= TRUE;
		boolUseSysMemGraphBackLay	= TRUE;
		boolUseSysMemImageLay	= TRUE;
		boolUseSysMemGraphLay	= TRUE;
		boolUseSysMemLabelLay	= TRUE;
		boolUseSysMemUScaleLay	= TRUE;

		m_dwFrameMemSizeUsed	= 0;

        DebugMessage(_T("Using system memory at all (not enough memory)"));
    }
    else if( ddcaps.dwVidMemTotal <= dwFrameMemSizePrimaryBackLay + dwFrameMemSizeGraphBackLay )
    {
		boolUseSysMemPrimaryBackLay	= FALSE;
		boolUseSysMemGraphBackLay	= TRUE;
		boolUseSysMemImageLay	= TRUE;
		boolUseSysMemGraphLay	= TRUE;
		boolUseSysMemLabelLay	= TRUE;
		boolUseSysMemUScaleLay	= TRUE;

		m_dwFrameMemSizeUsed	= dwFrameMemSizePrimaryBackLay;

        DebugMessage(_T("Using system memory partly (not enough memory)"));
    }
    else if( ddcaps.dwVidMemTotal <= dwFrameMemSizePrimaryBackLay + dwFrameMemSizeGraphBackLay + dwFrameMemSizeImageLay )
    {
		boolUseSysMemPrimaryBackLay	= FALSE;
		boolUseSysMemGraphBackLay	= FALSE;
		boolUseSysMemImageLay	= TRUE;
		boolUseSysMemGraphLay	= TRUE;
		boolUseSysMemLabelLay	= TRUE;
		boolUseSysMemUScaleLay	= TRUE;

		m_dwFrameMemSizeUsed	= dwFrameMemSizePrimaryBackLay + dwFrameMemSizeGraphBackLay;

        DebugMessage(_T("Using system memory partly (not enough memory)"));
    }
    else if( ddcaps.dwVidMemTotal <= 
		dwFrameMemSizePrimaryBackLay + dwFrameMemSizeGraphBackLay + dwFrameMemSizeImageLay + dwFrameMemSizeGraphLay )
    {
		boolUseSysMemPrimaryBackLay	= FALSE;
		boolUseSysMemGraphBackLay	= FALSE;
		boolUseSysMemImageLay	= FALSE;
		boolUseSysMemGraphLay	= TRUE;
		boolUseSysMemLabelLay	= TRUE;
		boolUseSysMemUScaleLay	= TRUE;

		m_dwFrameMemSizeUsed	= dwFrameMemSizePrimaryBackLay + dwFrameMemSizeGraphBackLay + dwFrameMemSizeImageLay;

        DebugMessage(_T("Using system memory partly (not enough memory)"));
    }
    else if( ddcaps.dwVidMemTotal <= 
		dwFrameMemSizePrimaryBackLay + dwFrameMemSizeGraphBackLay + dwFrameMemSizeImageLay + dwFrameMemSizeGraphLay + dwFrameMemSizeLabelLay )
    {
		boolUseSysMemPrimaryBackLay	= FALSE;
		boolUseSysMemGraphBackLay	= FALSE;
		boolUseSysMemImageLay	= FALSE;
		boolUseSysMemGraphLay	= FALSE;
		boolUseSysMemLabelLay	= TRUE;
		boolUseSysMemUScaleLay	= TRUE;

		m_dwFrameMemSizeUsed	= dwFrameMemSizePrimaryBackLay + dwFrameMemSizeGraphBackLay + dwFrameMemSizeImageLay + dwFrameMemSizeGraphLay;

        DebugMessage(_T("Using system memory partly (not enough memory)"));
    }
    else if( ddcaps.dwVidMemTotal <= 
		dwFrameMemSizePrimaryBackLay + dwFrameMemSizeGraphBackLay + dwFrameMemSizeImageLay + dwFrameMemSizeGraphLay + dwFrameMemSizeLabelLay + dwFrameMemSizeUScaleLay )
    {
		boolUseSysMemPrimaryBackLay	= FALSE;
		boolUseSysMemGraphBackLay	= FALSE;
		boolUseSysMemImageLay	= FALSE;
		boolUseSysMemGraphLay	= FALSE;
		boolUseSysMemLabelLay	= FALSE;
		boolUseSysMemUScaleLay	= TRUE;

		m_dwFrameMemSizeUsed	=
			dwFrameMemSizePrimaryBackLay + dwFrameMemSizeGraphBackLay + dwFrameMemSizeImageLay + dwFrameMemSizeGraphLay + dwFrameMemSizeLabelLay;

        DebugMessage(_T("Using system memory partly (not enough memory)"));
    }
	else
	{
		boolUseSysMemPrimaryBackLay	= FALSE;
		boolUseSysMemGraphBackLay	= FALSE;
		boolUseSysMemImageLay	= FALSE;
		boolUseSysMemGraphLay	= FALSE;
		boolUseSysMemLabelLay	= FALSE;
		boolUseSysMemUScaleLay	= FALSE;

		m_dwFrameMemSizeUsed	=
			dwFrameMemSizePrimaryBackLay + dwFrameMemSizeGraphBackLay + dwFrameMemSizeImageLay + dwFrameMemSizeGraphLay + dwFrameMemSizeLabelLay + dwFrameMemSizeUScaleLay;

        DebugMessage(_T("Using video memory at all"));	
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    if( ddcaps.dwCaps & DDCAPS_COLORKEY )
    {
        if( ddcaps.dwCKeyCaps & DDCKEYCAPS_SRCBLT )
        {
            m_blSrcColorkey = TRUE;
			DebugMessage(_T("Can do Src colorkey in hardware"));
        }

        if( ddcaps.dwCKeyCaps & DDCKEYCAPS_DESTBLT )
        {
            m_blDestColorkey = TRUE;
            DebugMessage(_T("Can do Dest colorkey in hardware"));
        }
    }
    else
    {
        DebugMessage(_T("Can't do color key in hardware!" ));
    }
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    // Create the primary surface
	/////////////////////////////////////////////////////////////////
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    ddrval = m_lpDD->CreateSurface( &ddsd, &m_lpDDSPrimary, NULL );
    if( ddrval != DD_OK )
	{
        DebugMessage(_T("Create Primary Surface failed err=%d"), ddrval);
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    // create a clipper for the primary surface
	/////////////////////////////////////////////////////////////////
    ddrval = m_lpDD->CreateClipper( 0, &m_lpClipper, NULL );
    if( ddrval != DD_OK )
	{
        DebugMessage(_T("Create Clipper failed err=%d"), ddrval);
		return FALSE;
	}
    
    ddrval = m_lpClipper->SetHWnd( 0, m_pScreenWnd->m_hWnd );
    if( ddrval != DD_OK )
	{
        DebugMessage(_T("Clipper SetHWnd failed err=%d"), ddrval);
		return FALSE;
	}

    ddrval = m_lpDDSPrimary->SetClipper( m_lpClipper );
    if( ddrval != DD_OK )
	{
        DebugMessage(_T("SetClipper failed err=%d"), ddrval);
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
/*	if ( m_uBPP == 8 )
	{
	    // load our palette
	    m_lpDDPalette = DDLoadPalette(m_lpDD, m_hdibImage);

		// make sure to set the palette before loading bitmaps.
		if (m_lpDDPalette)
		{
			m_lpDDSPrimary->SetPalette(m_lpDDPalette);
		}
	}*/
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// create a DirectDrawSurface for Primary BackLay
	/////////////////////////////////////////////////////////////////
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize			= sizeof(ddsd);
    ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth		= GetSystemMetrics(SM_CXSCREEN);
    ddsd.dwHeight		= GetSystemMetrics(SM_CYSCREEN);
	if( boolUseSysMemPrimaryBackLay )
	{
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}
    ddrval = m_lpDD->CreateSurface( &ddsd, &m_lpDDSPrimaryBackLay, NULL );
    if ( ddrval != DD_OK )
	{
        DebugMessage(_T("Create BackLay Surface failed err=%d"), ddrval);
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// create a DirectDrawSurface for Graph BackLay
	/////////////////////////////////////////////////////////////////
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize			= sizeof(ddsd);
    ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth		= m_szGraph.cx;
    ddsd.dwHeight		= m_szGraph.cy;
	if( boolUseSysMemGraphBackLay )
	{
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}
    ddrval = m_lpDD->CreateSurface( &ddsd, &m_lpDDSGraphBackLay, NULL );
    if ( ddrval != DD_OK )
	{
        DebugMessage(_T("Create Graph BackLay Surface failed err=%d"), ddrval);
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// create a DirectDrawSurface for ImageLay
	/////////////////////////////////////////////////////////////////
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize			= sizeof(ddsd);
    ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth		= m_szImage.cx;
    ddsd.dwHeight		= m_szImage.cy;
	if( boolUseSysMemImageLay )
	{
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}
    ddrval = m_lpDD->CreateSurface( &ddsd, &m_lpDDSImageLay, NULL );
    if ( ddrval != DD_OK )
	{
        DebugMessage(_T("Create ImageLay Surface failed err=%d"), ddrval);
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    // create a DirectDrawSurface for GraphLay
	/////////////////////////////////////////////////////////////////
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize			= sizeof(ddsd);
    ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth		= m_szGraph.cx;
    ddsd.dwHeight		= m_szGraph.cy;
	if( boolUseSysMemGraphLay )
	{
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}
    ddrval = m_lpDD->CreateSurface( &ddsd, &m_lpDDSGraphLay, NULL );
    if ( ddrval != DD_OK )
	{
        DebugMessage(_T("Create GraphLay Surface failed err=%d"), ddrval);
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    // create a DirectDrawSurface for LabelLay
	/////////////////////////////////////////////////////////////////
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize			= sizeof(ddsd);
    ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth		= m_szLabel.cx;
    ddsd.dwHeight		= m_szLabel.cy;
	if( boolUseSysMemLabelLay )
	{
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}
    ddrval = m_lpDD->CreateSurface( &ddsd, &m_lpDDSLabelLay, NULL );
    if ( ddrval != DD_OK )
	{
        DebugMessage(_T("Create LabelLay Surface failed err=%d"), ddrval);
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    // create a DirectDrawSurface for UScaleLay
	/////////////////////////////////////////////////////////////////
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize			= sizeof(ddsd);
    ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN;
	//07.10.31
//	ddsd.dwWidth		= szUScale.cx;
//	ddsd.dwHeight		= szUScale.cy;
#ifdef NEW_SCANSCREEN_MODE
	ddsd.dwWidth		= m_szGraph.cx;
	ddsd.dwHeight		= m_szGraph.cy;
#else
	ddsd.dwWidth		= m_szUScale.cx;
	ddsd.dwHeight		= m_szUScale.cy;
#endif
	//07.10.31
	if( boolUseSysMemUScaleLay )
	{
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}
    ddrval = m_lpDD->CreateSurface( &ddsd, &m_lpDDSMobileUScaleLay, NULL );
    if ( ddrval != DD_OK )
	{
        DebugMessage(_T("Create UScaleLay Surface failed err=%d"), ddrval);
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    // *
    // * init the color key
    // *
	/////////////////////////////////////////////////////////////////
	DWORD	dwColorKey = 0;	
	
	dwColorKey = DDColorMatch(m_lpDDSGraphLay, m_sysOpt.color[SysOpt_clrTransparent]);
	
    if (m_blSrcColorkey)
    {
		DDCOLORKEY		ddck;
		ddck.dwColorSpaceLowValue	= dwColorKey;
		ddck.dwColorSpaceHighValue	= dwColorKey;
		m_lpDDSGraphBackLay->SetColorKey( DDCKEY_SRCBLT, &ddck );
		m_lpDDSGraphLay->SetColorKey( DDCKEY_SRCBLT, &ddck );
		m_lpDDSLabelLay->SetColorKey( DDCKEY_SRCBLT, &ddck );
		m_lpDDSMobileUScaleLay->SetColorKey( DDCKEY_SRCBLT, &ddck );
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// Init Lay
	/////////////////////////////////////////////////////////////////
	HBRUSH brBackBrush = CreateSolidBrush( m_sysOpt.color[SysOpt_clrTransparent] );

//	HPEN hPenOld;
	HPEN hPenR = CreatePen(PS_SOLID, 0, RGB(0xFF,0,0));
	HPEN hPenG = CreatePen(PS_SOLID, 0, RGB(0,0xFF,0));
	HPEN hPenB = CreatePen(PS_SOLID, 0, RGB(0,0,0xFF));

	CRect	rcFill;

	ddrval = m_lpDDSGraphBackLay->GetDC( &hdc );
	if( ddrval == DD_OK )
	{
		rcFill = CRect(0,0,m_szGraph.cx,m_szGraph.cy);
		FillRect( hdc, (LPRECT)rcFill, brBackBrush );
		m_lpDDSGraphBackLay->ReleaseDC(hdc);
	}

	ddrval = m_lpDDSGraphLay->GetDC( &hdc );
	if( ddrval == DD_OK )
	{
		rcFill = CRect(0,0,m_szGraph.cx,m_szGraph.cy);
		FillRect( hdc, (LPRECT)rcFill, brBackBrush );
		m_lpDDSGraphLay->ReleaseDC(hdc);
	}

	ddrval = m_lpDDSLabelLay->GetDC( &hdc );
	if( ddrval == DD_OK )
	{
		rcFill = CRect(0,0,m_szLabel.cx,m_szLabel.cy);
		FillRect( hdc, (LPRECT)rcFill, brBackBrush );
		m_lpDDSLabelLay->ReleaseDC(hdc);
	}

	ddrval = m_lpDDSMobileUScaleLay->GetDC( &hdc );
	if( ddrval == DD_OK )
	{
		rcFill = CRect(0,0,m_szUScale.cx,m_szUScale.cy);
		FillRect( hdc, (LPRECT)rcFill, brBackBrush );
		m_lpDDSMobileUScaleLay->ReleaseDC(hdc);
	}

	DeleteObject( hPenR );
	DeleteObject( hPenG );
	DeleteObject( hPenB );

	DeleteObject( brBackBrush );
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
    if ( !InitFrameRate() )
	{
        DebugMessage(_T("InitFrameRate failed err"));
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	if ( !InitLabelLay() )
	{
        DebugMessage(_T("InitLabelLay failed err"));
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	if ( !InitMobileUScaleLay() )
	{
        DebugMessage(_T("InitMobileUScale failed err"));
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////
	if ( !InitOscillographLay() )
	{
        DebugMessage(_T("InitOscillographLay failed err"));
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////
	m_UpdateRectsImage.Add( CRect(0, 0, m_szImage.cx, m_szImage.cy) );
	m_boolReady	= TRUE;
	/////////////////////////////////////////////////////////////////
	return TRUE;
}
/*
CRect RectMapDib( CRect rcDest )
{
	CRect rcSrc;

	rcSrc.left	= g_szUSB_FrameImage.cx - rcDest.right;
	rcSrc.right = g_szUSB_FrameImage.cx - rcDest.left;
	rcSrc.top = g_szUSB_FrameImage.cy - rcDest.bottom;
	rcSrc.bottom = g_szUSB_FrameImage.cy - rcDest.top;
	
	return rcSrc;
}
*/
DWORD CMCICard::ImageDibWrite( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	LPSTR		lpDIBHdr, lpDIBBits;
	LPSTR		lpBuffLine;
	LONG		lBuffLineOffset;
	LPSTR		lpImageWindowLine;
	LONG		lImageLineOffset;
	CRect		rcImage, rcFrame;
	DWORD		i, iMaxLine;

	////////////////////////////////////////////////////////////////////
	rcFrame.SetRect( 0,0,m_szImage.cx,m_szImage.cy );
	rcImage = rcFrameDestWindow & rcFrame;
	if ( rcImage != rcFrameDestWindow )
		return 0;
	////////////////////////////////////////////////////////////////////
	
	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}

	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

	if ( lBuffSize >= rcFrameDestWindow.Width() * rcFrameDestWindow.Height() )
	{
		iMaxLine = rcFrameDestWindow.Height();
	}
	else
	{
		iMaxLine = lBuffSize / rcFrameDestWindow.Width();
	}

	lBuffLineOffset	= rcFrameDestWindow.Width();
	lpBuffLine		= (LPSTR)lpBuff;

	lImageLineOffset	= m_szImage.cx;
	lpImageWindowLine	= &(lpDIBBits[ 
		  (m_szImage.cy - rcImage.top - 1) * lImageLineOffset
		+ rcImage.left ] );

	for ( i=0; i<iMaxLine; i++ )
	{
		memcpy( (void *)lpImageWindowLine, (const void *)lpBuffLine, lBuffLineOffset );
		lpBuffLine			+= lBuffLineOffset;
		lpImageWindowLine	-= lImageLineOffset;
	}
	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////

	m_UpdateRectsImage.Add( rcFrameDestWindow );

	m_mutexImageDib.Unlock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////
	i = iMaxLine * lBuffLineOffset;
	m_dwByteCount += i;
	m_dwInputCount ++;
	////////////////////////////////////////////////////////////////////

	return i;
}

// 10.08
DWORD CMCICard::ImageDibWriteImp( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	LPSTR		lpDIBHdr, lpDIBBits;
	LPSTR		lpBuffLine;
	LONG		lBuffLineOffset;
//	LPSTR		lpImageWindowLine;
	LONG		lImageLineOffset;
	CRect		rcImage, rcFrame;
	DWORD		i, iMaxLine;

	////////////////////////////////////////////////////////////////////
	rcFrame.SetRect( 0,0,m_szImage.cx,m_szImage.cy );
	rcImage = rcFrameDestWindow & rcFrame;
	if ( rcImage != rcFrameDestWindow )
		return 0;
	////////////////////////////////////////////////////////////////////
	
	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}

	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

/*	if ( lBuffSize >= rcFrameDestWindow.Width() * rcFrameDestWindow.Height() )
	{
		iMaxLine = rcFrameDestWindow.Height();
	}
	else
	{
		iMaxLine = lBuffSize / rcFrameDestWindow.Width();
	}

	lBuffLineOffset	= rcFrameDestWindow.Width();
	lpBuffLine		= (LPSTR)lpBuff;

	lImageLineOffset	= g_szFrameImage.cx;
	lpImageWindowLine	= &(lpDIBBits[ 
		  (g_szFrameImage.cy - rcImage.top - 1) * lImageLineOffset
		+ rcImage.left ] );

	for ( i=0; i<iMaxLine; i++ )
	{
		memcpy( (void *)lpImageWindowLine, (const void *)lpBuffLine, lBuffLineOffset );
		lpBuffLine			+= lBuffLineOffset;
		lpImageWindowLine	-= lImageLineOffset;
	}
*/	
	iMaxLine = lBuffSize /5;
	WORD wx, wy;

	lBuffLineOffset		= rcFrameDestWindow.Width();
	lpBuffLine			= (LPSTR)lpBuff;

	lImageLineOffset	= m_szImage.cx;

	BYTE bParam = 0x0;
	for (i=0; i<iMaxLine; i++)
	{
		bParam	= (BYTE)(((LPBYTE)lpBuffLine)[i*5]);							// low byte of x
		wx		= (WORD)bParam | ((WORD)(((LPBYTE)lpBuffLine)[i*5+1]) << 8);	// combine low & high of x
		bParam	= (BYTE)(((LPBYTE)lpBuffLine)[i*5+2]);							// low byte of y
		wy		= (WORD)bParam | ((WORD)(((LPBYTE)lpBuffLine)[i*5+3]) << 8);	// combine low & high of y
		// set z value to point(x,y)
		((LPBYTE)lpDIBBits)[ 
		  (m_szImage.cy - wy - 1) * lImageLineOffset + wx ]  = ((LPBYTE)lpBuffLine)[i*5+4];
	}
	
	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////

	m_UpdateRectsImage.Add( rcFrameDestWindow );

	m_mutexImageDib.Unlock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////
	i = iMaxLine * lBuffLineOffset;
	m_dwByteCount += i;
	m_dwInputCount ++;
	////////////////////////////////////////////////////////////////////

	return i;
}
// 10.08

BOOL CMCICard::InitData( DWORD dwExpectantDMABlockSize, int nXOffset, int nYOffset )
{
	m_dwExpectantDMABlockSize = dwExpectantDMABlockSize;

	ZeroMemory(m_pPixX, LOOP_COUNTS*102400/4 * sizeof(WORD));
	ZeroMemory(m_pPixY, LOOP_COUNTS*102400/4 * sizeof(WORD));
	ZeroMemory(m_pPixZ, LOOP_COUNTS*102400/4 * sizeof(WORD));
	ZeroMemory(m_pPixX2, LOOP_COUNTS*102400/4 * sizeof(WORD));
	ZeroMemory(m_pPixY2, LOOP_COUNTS*102400/4 * sizeof(WORD));
	ZeroMemory(m_pPixZ2, LOOP_COUNTS*102400/4 * sizeof(WORD));
	ZeroMemory(m_pPixZmix, LOOP_COUNTS*102400/4 * sizeof(WORD));

	m_dwX			= 0xFFFF;
	m_dwY			= 0xFFFF;
	m_dwZa			= 0xFFFF;
	m_nIndexX		= 0;		// 有效的数据的X序号
	m_nIndexY		= 0;		// 有效的数据的Y序号
	m_nX			= 0;
	m_nY			= 0;
	m_nXOffset		= nXOffset;
	m_nYOffset		= nYOffset;
	m_bPeakX		= FALSE;
	m_bPeakY		= FALSE;

	m_bDataNeedUpdated = FALSE;
	m_bStopScan		= FALSE;

	g_index			= 0;

	m_bUrgency		= FALSE;

	m_bSyncFinished	= FALSE;
	m_bFindFirstBOF	= FALSE;

	m_nSharedImageBuffIndexRead		= 0;
	m_nSharedImageBuffIndexWrite	= 0;

	m_nCurrentY1	= 0;
	m_nCurrentY2	= 0;
	////////////////////////////////////////////////////////////
	int i;
	for ( i=0; i<256; i++)
		m_lGrayHistogramBuff[i] = 0;
	
	for (i=0; i<8192; i++)
	{
		m_bOscillographBuff[i] = 0;
		m_bOscillographData[i] = 0;
	}
	////////////////////////////////////////////////////////////

	if( m_hFileLog != NULL )
	{
		CloseHandle(m_hFileLog);
		m_hFileLog = NULL;
	}
	if( m_hLineDataLog != NULL )
	{
		CloseHandle(m_hLineDataLog);
		m_hLineDataLog = NULL;
	}
	if( m_hOscillLog != NULL )
	{
		CloseHandle(m_hOscillLog);
		m_hOscillLog = NULL;
	}
	if( (m_nusbFunction == 3) && m_bNeedMon )
	{
		CString str, strTemp;
		CTime	timeCurrent = CTime::GetCurrentTime();
		strTemp = timeCurrent.Format(_T("%Y%m%d-%H%M%S"));
		str.Format(_T("%szLine%s-%05d.log"), g_exeFullPath, strTemp, g_index );
		m_hLineDataLog = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		str.Format(_T("%szOsc%s-%05d.log"), g_exeFullPath, strTemp, g_index );
		m_hOscillLog = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
	}
/*
	//////////////////////////////
	// 同步前图像区域清零
	if( m_nusbFunction != 6 )
		return TRUE;

	LPSTR		lpDIBHdr, lpDIBBits;
	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}
	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

	ZeroMemory( lpDIBBits, m_szImage.cx * m_szImage.cy * sizeof(BYTE) );
	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////

	CRect rcFrame = CRect( 0,0,m_szImage.cx,m_szImage.cy );
	m_UpdateRectsImage.Add( rcFrame );

	m_mutexImageDib.Unlock();
	//////////////////////////////
*/	return TRUE;
}

BOOL CMCICard::ClearData()
{
	m_bStopScan						= TRUE;
	// 15.10.08 与MainLoop中有同步问题？？？
	// 冻结后，MainLoop中Read还是不等于Write，就会进入do循环
	m_nSharedImageBuffIndexRead		= 0;
	m_nSharedImageBuffIndexWrite	= 0;

	if( (m_nusbFunction == 3) && m_bNeedMon )
	{
		if( m_hLineDataLog != NULL )
		{
			CloseHandle(m_hLineDataLog);
			m_hLineDataLog = NULL;
		}
		if( m_hOscillLog != NULL )
		{
			CloseHandle(m_hOscillLog);
			m_hOscillLog = NULL;
		}
	}

	if( m_nusbFunction == 6 )	// 同步照相
	{
		CRect rcIndication = CRect(0,m_rcDestFrame.top,8,m_rcDestFrame.bottom);
		PhotoIndication( rcIndication, RGB(0,0,0) );
	}
	return TRUE;
}

BOOL CMCICard::PostData( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	m_mutexImageUSB.Lock();
	memcpy( (void*)m_pBuffUSB, (const void*)lpBuff, lBuffSize * sizeof( unsigned short ) );
	m_mutexImageUSB.Unlock();
	m_bDataNeedUpdated = TRUE;

	return TRUE;
}

BOOL CMCICard::GetData( /*LPVOID lpBuff, long lBuffSize, */CRect& rcFrameDestWindow )
{
	m_mutexImageUSB.Lock();
	long lBuffSize = LOOP_COUNTS*(m_dwExpectantDMABlockSize +512);

	if( m_bSplit )	// 分割扫描
	{
		if( m_nDataStoreMode )	// XYZ
		{
			switch( m_nusbFunction )
			{
			case 3:
			case 4:
			case 5:
				ADxyzLine2( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
				break;
			case 6:
				ADxyzSync2( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
				break;
			default:
				ADxyz2( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
				break;
			}
		}
		else					// ZZZ
			ImageDibWriteNewZZZ2( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
	}
	else
	{
		// 其它扫描方式
		if( m_nDataStoreMode )	// XYZ
		{
			if( m_bDet2nd )	// 奇数通道
			{
				if( m_nChnIndex[1] > 1 )		// 奇数通道显示混合图像
				{
					switch( m_nusbFunction )
					{
					case 3:
					case 4:
					case 5:
						ADxyzLine2ndMix( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					case 6:
						ADxyzSync2ndMix( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					default:
						ADxyz2ndMix( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					}
				}
				else if( m_nChnIndex[1] > 0 )	// 奇数通道显示Zb
				{
					switch( m_nusbFunction )
					{
					case 3:
					case 4:
					case 5:
						ADxyzLine2nd( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					case 6:
						ADxyzSync2nd( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					default:
						ADxyz2nd( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					}
				}
				else							// 奇数通道显示Za
				{
					switch( m_nusbFunction )
					{
					case 3:
					case 4:
					case 5:
						ADxyzLine( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					case 6:
						ADxyzSync( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					default:
						ADxyz( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					}
				}
			}
			else			// 偶数通道
			{
				if( m_nChnIndex[0] > 1 )		// 偶数通道显示混合图像
				{
					switch( m_nusbFunction )
					{
					case 3:
					case 4:
					case 5:		// 线扫描、点扫描无需刷新图像数据
						ADxyzLine2ndMix( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					case 6:		// 同步扫描
						ADxyzSync2ndMix( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					default:
						ADxyz2ndMix( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					}
				}
				else if( m_nChnIndex[0] > 0 )	// 偶数通道显示Zb
				{
					switch( m_nusbFunction )
					{
					case 3:
					case 4:
					case 5:		// 线扫描、点扫描无需刷新图像数据
						ADxyzLine2nd( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					case 6:		// 同步扫描
						ADxyzSync2nd( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					default:
						ADxyz2nd( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					}
				}
				else							// 偶数通道显示Za
				{
					switch( m_nusbFunction )
					{
					case 3:
					case 4:
					case 5:		// 线扫描、点扫描无需刷新图像数据
						ADxyzLine( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					case 6:		// 同步扫描
						ADxyzSync( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					default:
						ADxyz( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
						break;
					}
				}
			}
		}
		else					// ZZZ
		{
			ImageDibWriteNewZZZ( (void*)(m_pSharedImageBuff[m_nSharedImageBuffIndexRead]), lBuffSize, rcFrameDestWindow );
		}
	}
	m_bDataNeedUpdated = FALSE;

	m_mutexImageUSB.Unlock();
	return TRUE;
}

// 11.11.28
DWORD CMCICard::ImageDibWriteNewXYZ( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	if( lpBuff == NULL )
		return 0;

	LPSTR		lpDIBHdr, lpDIBBits;
	LONG		lImageLineOffset;
	CRect		rcImage, rcFrame;
	DWORD		i;

	////////////////////////////////////////////////////////////////////
	rcFrame.SetRect( 0,0,m_szImage.cx,m_szImage.cy );
	rcImage = rcFrameDestWindow & rcFrame;
	if ( rcImage != rcFrameDestWindow )
		return 0;
	////////////////////////////////////////////////////////////////////
	
	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}

	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

	lImageLineOffset	= m_szImage.cx;

/*	DWORD* pPixX = new DWORD[ lBuffSize ];
	DWORD* pPixY = new DWORD[ lBuffSize ];
	DWORD* pPixZ = new DWORD[ lBuffSize ];
//	ZeroMemory(pPixX, lBuffSize * sizeof(DWORD));
//	ZeroMemory(pPixY, lBuffSize * sizeof(DWORD));
//	ZeroMemory(pPixZ, lBuffSize * sizeof(DWORD));
	for ( i = 0; i < lBuffSize; i++ )
	{
		pPixX[i] = 0xCCCC;
		pPixY[i] = 0xCCCC;
		pPixZ[i] = 0xCCCC;
	}

	DWORD dwCounts = PixConvertXYZ( (unsigned short*)lpBuff, lBuffSize*2, pPixX, pPixY, pPixZ );
	for( i=0; i<dwCounts; i++ )
	{
		// set z value to point(x,y)
		((LPBYTE)lpDIBBits)[ 
		  (m_szImage.cy - pPixY[i] - 1) * lImageLineOffset + pPixX[i] ]  = (BYTE)pPixZ[i];
	}

	// Use the delete operator as follows:
	delete [] pPixX;
	delete [] pPixY;
	delete [] pPixZ;
*/

	if( m_bNeedMon )
	{
		unsigned long cbRet;
		char Buf[32];
		CString str, strTemp;
		CTime	timeCurrent = CTime::GetCurrentTime();
		strTemp = timeCurrent.Format("%Y%m%d-%H%M");
		str.Format(_T("%sz%s-%05d-set.log"), g_exeFullPath, strTemp, g_index );
		m_hFileLog = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		sprintf(Buf, "/BEGIN set z value\\\r\n");
		WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
//		sprintf(Buf, "dwCounts = %ld\r\n", dwCounts );
//		WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	}

	DWORD dwOffset = 0;
	DWORD dwCounts = 0;
	DWORD dwIndexY1, dwIndexY2;
	unsigned long lSize = 0;
	for( int j=0; j<LOOP_COUNTS; j++ )
	{
		lSize = ((unsigned short*)lpBuff)[dwOffset];
//		lSize = lBuffSize;

//		TRACE("\r\nlSize_%d = %ld, %04X;   ", g_index, lSize, lSize );
//		TRACE("dwOffset_%d = %ld, %04X\r\n", g_index, dwOffset, dwOffset );
		
//		m_dwMinY		= m_szImage.cy;
//		m_dwMaxY		= 0;

/*		if( m_bDet2nd )	// 奇数通道数据分析显示
			dwCounts = PixConvertXYZ_2nd( &(((unsigned short*)lpBuff)[dwOffset]), lSize*2, m_pPixX, m_pPixY, m_pPixZ );
		else					// 默认偶数通道数据分析显示
			dwCounts = PixConvertXYZ( &(((unsigned short*)lpBuff)[dwOffset]), lSize*2, m_pPixX, m_pPixY, m_pPixZ );
*/		if( dwCounts > 0 )
			UpdateOscillographNew( dwCounts, m_pPixX, m_pPixY, (LPWORD)m_pPixZ, -1, 0, m_szOscill.cx );

		if( dwCounts > 0 )
		{
			dwIndexY1 = m_pPixY[0];
			dwIndexY2 = m_pPixY[dwCounts -1];
			for( i=0; i<dwCounts; i++ )
			{
				// set z value to point(x,y)
				((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)m_pPixZ[i];
			}

/*			unsigned long cbRet;
			char Buf[32];
			CString str, strTemp;
			CTime	timeCurrent = CTime::GetCurrentTime();
			strTemp = timeCurrent.Format("%Y%m%d-%H%M");
			str.Format( "%sz%s-%05d-set.log", g_exeFullPath, strTemp, g_index );
			HANDLE hFil = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
			sprintf(Buf, "/BEGIN set z value\\\r\n");
			WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
			sprintf(Buf, "dwCounts = %ld\r\n", dwCounts );
			WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
*/
			if( m_bNeedMon && m_hFileLog != NULL )
			{
				unsigned long cbRet;
				char Buf[32];
				for( i=0; i<dwCounts; i++ )
				{
					sprintf(Buf, "%04X, %04X, %04X\r\n", m_pPixX[i], m_pPixY[i], m_pPixZ[i] );
					WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
				}
			}
//			sprintf(Buf, "\\END set z value/\r\n\r\n");
//			WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
//			CloseHandle(hFil);
		}

		dwOffset = (j+1) *(m_dwExpectantDMABlockSize +512);
		g_index++;

		// Use the delete operator as follows:
		if( m_szImage.cy > 512 )
		{
			if( dwIndexY1 < dwIndexY2 )
			{
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, dwIndexY1, m_rcDestFrame.right, dwIndexY2+1) );
//				LowpassFilter( 0, 0, dwIndexY1, m_szImage.cx, dwIndexY2, lpDIBBits );
			}
			else
			{
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, dwIndexY1, m_rcDestFrame.right, m_szImage.cy) );
				m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, m_rcDestFrame.top, m_szImage.cx, dwIndexY2+1) );
//				LowpassFilter( 0, 0, dwIndexY1, m_szImage.cx, m_szImage.cy, lpDIBBits );
//				LowpassFilter( 0, 0, 0, m_szImage.cx, dwIndexY2, lpDIBBits );
			}
//			m_UpdateRectsImage.Add( CRect(m_rcDestFrame.left, m_dwMinY, m_rcDestFrame.right, m_dwMaxY) );
		}
		else
			m_UpdateRectsImage.Add( rcFrame );
	}
	if( m_bNeedMon )
	{
		if( m_hFileLog != NULL )
		{
			unsigned long cbRet;
			char Buf[32];
			sprintf(Buf, "\\END set z value/\r\n\r\n");
			WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
			CloseHandle(m_hFileLog);
			m_hFileLog = NULL;
		}
	}

	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////

	m_mutexImageDib.Unlock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	return i;
}

// 11.12.05
DWORD CMCICard::ImageDibWriteNewZZZ( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	if( lpBuff == NULL )
		return 0;
	
	LPSTR		lpDIBHdr, lpDIBBits;
	LONG		lBuffLineOffset;
	LONG		lImageLineOffset;
	CRect		rcImage, rcFrame;
	DWORD		i, nloops, iMaxLine;

	////////////////////////////////////////////////////////////////////
	rcFrame.SetRect( 0,0,m_szImage.cx,m_szImage.cy );
	rcImage = rcFrameDestWindow & rcFrame;
	if ( rcImage != rcFrameDestWindow )
		return 0;
	////////////////////////////////////////////////////////////////////
	
	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}

	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

	if ( lBuffSize >= rcFrameDestWindow.Width() * rcFrameDestWindow.Height() )
	{
		iMaxLine = rcFrameDestWindow.Height();
	}
	else
	{
		iMaxLine = lBuffSize / rcFrameDestWindow.Width();
	}

	lBuffLineOffset	= rcFrameDestWindow.Width();
//	lpBuffLine		= (LPSTR)lpBuff;

	lImageLineOffset	= m_szImage.cx;
	
	if( m_bNeedMon )
	{
		unsigned long cbRet;
		char Buf[32];
		CString str, strTemp;
		CTime	timeCurrent = CTime::GetCurrentTime();
		strTemp = timeCurrent.Format("%Y%m%d-%H%M");
		str.Format(_T("%sz%s-%05d-set.log"), g_exeFullPath, strTemp, g_index );
		m_hFileLog = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		sprintf(Buf, "/BEGIN set z value\\\r\n");
		WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
//		sprintf(Buf, "dwCounts = %ld\r\n", dwCounts );
//		WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	}
	
	CSize sz = m_szImage;
	DWORD dwOffset = 0;
	DWORD dwCounts = 0;
	WORD dwIndexY1, dwIndexY2;
	unsigned long lSize = 0;
	unsigned long cbRet;
	char Buf[32];
	for( nloops=0; nloops<LOOP_COUNTS; nloops++ )
	{
		lSize = ((unsigned short*)lpBuff)[dwOffset];

//		TRACE("\r\nlSize_%d = %ld, %04X;   ", g_index, lSize, lSize );
//		TRACE("dwOffset_%d = %ld, %04X\r\n", g_index, dwOffset, dwOffset );
//		m_lastTickCount = GetTickCount();
		dwCounts = PixConvertZZZ( &(((unsigned short*)lpBuff)[dwOffset]), lSize*2, m_pPixX, m_pPixY, m_pPixZ, dwIndexY1, dwIndexY2 );
		if( dwCounts > 0 )
		{
			UpdateOscillographNew( dwCounts, m_pPixX, m_pPixY, (LPWORD)m_pPixZ, -1, 0, m_szOscill.cx );
//			thisTickCount = GetTickCount();
//			TRACE( "\r\n PixConvertZZZ time = %ld\r\n", thisTickCount -m_lastTickCount );
			for( i=0; i<dwCounts; i++ )
			{
				// set z value to point(x,y)
				((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)m_pPixZ[i];
			}
			///////////////////////////////////////////////////////////////////
/*			unsigned long cbRet;
			char Buf[32];
			CString str, strTemp;
			CTime	timeCurrent = CTime::GetCurrentTime();
			strTemp = timeCurrent.Format("%Y%m%d-%H%M%S");
			str.Format( "%szzz%s-%05d-set.log", g_exeFullPath, strTemp, g_index );
			HANDLE hFil = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
			sprintf(Buf, "//BEGIN After PixConvertZZZ\\\r\n");
			WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
			sprintf(Buf, "\r\n\r\n" );
			WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
*/
			if( m_bNeedMon && m_hFileLog != NULL )
			{
				for( i=0; i<dwCounts; i++ )
				{
					sprintf(Buf, "%04X, %04X, %04X\r\n", m_pPixX[i], m_pPixY[i], m_pPixZ[i] );
					WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
				}
			}
//			sprintf(Buf, "\\END After PixConvertZZZ/\r\n\r\n");
//			WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
//			CloseHandle(hFil);
		}
		///////////////////////////////////////////////////////////////////

		dwOffset = (nloops+1) *(m_dwExpectantDMABlockSize +512);
		g_index++;

		if( m_szImage.cy > 512 )
		{
			if( dwIndexY1 < dwIndexY2 )
				m_UpdateRectsImage.Add( CRect(0, dwIndexY1, m_szImage.cx, dwIndexY2+1) );
			else
			{
				m_UpdateRectsImage.Add( CRect(0, dwIndexY1, m_szImage.cx, m_szImage.cy) );
				m_UpdateRectsImage.Add( CRect(0, 0, m_szImage.cx, dwIndexY2+1) );
			}
		}
		else
			m_UpdateRectsImage.Add( rcFrame );
	}
	if( m_bNeedMon )
	{
		if( m_hFileLog != NULL )
		{
			unsigned long cbRet;
			char Buf[32];
			sprintf(Buf, "\\END set z value/\r\n\r\n");
			WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
			CloseHandle(m_hFileLog);
			m_hFileLog = NULL;
		}
	}

	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////
/*
	if( dwIndexY1 < dwIndexY2 )
		m_UpdateRectsImage.Add( CRect(0, dwIndexY1, m_szImage.cx, dwIndexY2) );
	else
		m_UpdateRectsImage.Add( CRect(0, 0, m_szImage.cx, m_szImage.cy) );
*/
	m_mutexImageDib.Unlock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	return i;
}

///////////////////////////////////////////////////////////////////////////
// 像素数据转换：ZZZ模式
// 输入:	FrameData: 数据存储区
//			dwPixX: 用来存储X值的数组
//			dwPixY: 用来存储Y值的数组
//			dwPixZ: 用来存储Z值的数组
// 输出:	实际得到的有效数据的个数
DWORD CMCICard::PixConvertZZZ( unsigned short* pnFrameData, long lBytesTransferred,
								  WORD* pPixX, WORD* pPixY, WORD* pPixZ,
								  WORD& dwIndexY1, WORD& dwIndexY2 )
{
	// 因为每批数据的第一个数是总个数，所以nLoop要+1，且循环时从1开始
	long nLoop = lBytesTransferred/2 +1;
	long i;

/*	///////////////////////////////////////////////////////////////////////////
	unsigned long cbRet;
	char Buf[32];
	CString str, strTemp;
	CTime	timeCurrent = CTime::GetCurrentTime();
	strTemp = timeCurrent.Format("%Y%m%d-%H%M%S");
	str.Format( "%szzz%s-%05d-pc.log", g_exeFullPath, strTemp, g_index );
	HANDLE hFil = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
	sprintf(Buf, "/BEGIN CONVERT\\\r\n");
	WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	sprintf(Buf, "nLoop = %ld\r\n", nLoop -1);
	WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	for( i=1; i<nLoop; i++ )
	{
		sprintf(Buf, "%04X, ", pnFrameData[i] );
		WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	}
	sprintf(Buf, "\\END CONVERT/\r\n\r\n");
	WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
*/
	///////////////////////////////////////////////////////////////////////////
	BOOL bIsBOL, bIsBOF;
	unsigned short dwData	= 0;
	DWORD dwMaskBOL	= 0x1000;	// BOL 的掩码
	DWORD dwMaskBOF	= 0x3000;	// BOF 的掩码
	DWORD dwBitsOn;
//	CSize sz = m_szImage;
	DWORD dwDestWidth	= m_rcDestFrame.Width();
	DWORD dwDestHeight	= m_rcDestFrame.Height();
	int nLineCounts	= ValleyX +dwDestWidth +PeakX +FallX;
	int nFrameCounts= ValleyY +dwDestHeight +PeakY +FallY;
	bIsBOL		= FALSE;		// 当前数据是BOL
	bIsBOF		= FALSE;		// 当前数据是BOF
	dwIndexY1	= m_nIndexY;
	int nIndex	= 0;			// 有效的数据个数

	for( i=1; i<nLoop; i++ )
	{
		dwData = pnFrameData[i];			// 得到16进制的数据
		if( dwData == 0x3456 )
			continue;

		dwBitsOn = dwData & 0x3000;			// 得到所需的掩码位

		bIsBOL = (dwBitsOn == dwMaskBOL);
		if( bIsBOL )
		{
//			if( m_nY > ValleyY -1 && m_nY < ValleyY +sz.cy
//				&& m_nX > ValleyX -1 && m_nX < ValleyX +sz.cx )
			if( m_nY > 0 && m_nY < dwDestHeight +1
				&& m_nX > 0 && m_nX < dwDestWidth +1 )
			{
				m_nIndexX = 0;
				m_nIndexY++;
				if( m_nIndexY > dwDestHeight -1 )
					m_nY = 0;
			}
			m_nX = 0;
			m_nY++;
			if( m_nY > nFrameCounts -1 )
				m_nY = 0;
		}
		else
		{
			bIsBOF = (dwBitsOn == dwMaskBOF);
			if( bIsBOF )
			{
				m_nX		= 0;
				m_nY		= 0;
				m_nIndexX	= 0;
				m_nIndexY	= 0;
			}
			else
			{
				m_nX++;
/*				if( m_nX > nLineCounts -1 )
				{
					m_nX = 0;
					m_nY++;
				}
				if( m_nY > nFrameCounts -1 )
				{
					m_nX = 0;
					m_nY = 0;
				}
*/			}
		}

//		if( m_nY > ValleyY && m_nY < ValleyY +sz.cy +1
//			&& m_nX > ValleyX && m_nX < ValleyX +sz.cx +1 )
		if( m_nY > 0 && m_nY < dwDestHeight +1
			&& m_nX > 0 && m_nX < dwDestWidth +1 )
		{
			// 填充数组
			pPixX[nIndex] = m_nIndexX +m_rcDestFrame.left;
			pPixY[nIndex] = m_nIndexY +m_rcDestFrame.top;
//			pPixZ[nIndex] = ( dwData & 0x0FFF ) /16;
			pPixZ[nIndex] = ( dwData & 0x0FF0 ) >> 4;
			nIndex++;
			m_nIndexX++;
			if( m_nIndexX > dwDestWidth -1 )
			{
				m_nIndexX = 0;
				m_nIndexY++;
			}
			if( m_nIndexY > dwDestHeight -1 )
			{
				m_nIndexX = 0;
				m_nIndexY = 0;
			}
		}
//		bIsBOL	= FALSE;
//		bIsBOF	= FALSE;
	}
    ///////////////////////////////////////////////////////////////////////////
	dwIndexY2 = m_nIndexY;
	return nIndex;//(sz.cx * sz.cy);
}

DWORD CMCICard::ImageDibWriteNewZZZ2( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	LPSTR		lpDIBHdr, lpDIBBits;
//	LPSTR		lpBuffLine;
	LONG		lBuffLineOffset;
//	LPSTR		lpImageWindowLine;
	LONG		lImageLineOffset;
	CRect		rcImage, rcFrame;
	DWORD		i, nloops, iMaxLine;

	////////////////////////////////////////////////////////////////////
	rcFrame.SetRect( 0,0,m_szImage.cx,m_szImage.cy );
	rcImage = rcFrameDestWindow & rcFrame;
	if ( rcImage != rcFrameDestWindow )
		return 0;
	////////////////////////////////////////////////////////////////////
	
	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}

	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

	if ( lBuffSize >= rcFrameDestWindow.Width() * rcFrameDestWindow.Height() )
	{
		iMaxLine = rcFrameDestWindow.Height();
	}
	else
	{
		iMaxLine = lBuffSize / rcFrameDestWindow.Width();
	}

	lBuffLineOffset	= rcFrameDestWindow.Width();
//	lpBuffLine		= (LPSTR)lpBuff;

	lImageLineOffset	= m_szImage.cx;
	
	if( m_bNeedMon )
	{
		unsigned long cbRet;
		char Buf[32];
		CString str, strTemp;
		CTime	timeCurrent = CTime::GetCurrentTime();
		strTemp = timeCurrent.Format("%Y%m%d-%H%M");
		str.Format(_T("%sz%s-%05d-set.log"), g_exeFullPath, strTemp, g_index );
		m_hFileLog = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		sprintf(Buf, "/BEGIN set z value\\\r\n");
		WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
//		sprintf(Buf, "dwCounts = %ld\r\n", dwCounts );
//		WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	}
	
	CSize sz = m_szImage;
	DWORD dwOffset = 0;
	DWORD dwCounts = 0;
	WORD dwIndexY1, dwIndexY2;
	unsigned long lSize = 0;
	unsigned long cbRet;
	char Buf[32];
	for( nloops=0; nloops<LOOP_COUNTS; nloops++ )
	{
		lSize = ((unsigned short*)lpBuff)[dwOffset];

//		TRACE("\r\nlSize_%d = %ld, %04X;   ", g_index, lSize, lSize );
//		TRACE("dwOffset_%d = %ld, %04X\r\n", g_index, dwOffset, dwOffset );
//		m_lastTickCount = GetTickCount();
		dwCounts = PixConvertZZZ2( &(((unsigned short*)lpBuff)[dwOffset]), lSize*2, m_pPixX, m_pPixY, m_pPixZ, dwIndexY1, dwIndexY2 );
//		thisTickCount = GetTickCount();
//		TRACE( "\r\n PixConvertZZZ time = %ld\r\n", thisTickCount -m_lastTickCount );
		if( dwCounts > 0 )
		{
			for( i=0; i<dwCounts; i++ )
			{
				// set z value to point(x,y)
				((LPBYTE)lpDIBBits)[ (m_szImage.cy - m_pPixY[i] - 1) * lImageLineOffset + m_pPixX[i] ]  = (BYTE)m_pPixZ[i];
			}
			///////////////////////////////////////////////////////////////////
/*			unsigned long cbRet;
			char Buf[32];
			CString str, strTemp;
			CTime	timeCurrent = CTime::GetCurrentTime();
			strTemp = timeCurrent.Format("%Y%m%d-%H%M%S");
			str.Format( "%szzz%s-%05d-set.log", g_exeFullPath, strTemp, g_index );
			HANDLE hFil = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
			sprintf(Buf, "//BEGIN After PixConvertZZZ\\\r\n");
			WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
			sprintf(Buf, "Y1 = %d, Y2 = %d\r\n", dwIndexY1, dwIndexY2 );
			WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
			sprintf(Buf, "\r\n\r\n" );
			WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
*/
			if( m_bNeedMon && m_hFileLog != NULL )
			{
				for( i=0; i<dwCounts; i++ )
				{
					sprintf(Buf, "%04X\r\n", m_pPixZ[i] );
					WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
				}
			}
//			sprintf(Buf, "\\END After PixConvertZZZ/\r\n\r\n");
//			WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
//			CloseHandle(hFil);
		}
		///////////////////////////////////////////////////////////////////

		dwOffset = (nloops+1) *(m_dwExpectantDMABlockSize +512);
		g_index++;

		if( m_szImage.cy > 512 )
		{
			if( dwIndexY1 < dwIndexY2 )
				m_UpdateRectsImage.Add( CRect(0, dwIndexY1, m_szImage.cx, dwIndexY2+1) );
			else
			{
				m_UpdateRectsImage.Add( CRect(0, dwIndexY1, m_szImage.cx, m_szImage.cy) );
				m_UpdateRectsImage.Add( CRect(0, 0, m_szImage.cx, dwIndexY2+1) );
			}
		}
		else
			m_UpdateRectsImage.Add( rcFrame );
	}
	if( m_bNeedMon )
	{
		if( m_hFileLog != NULL )
		{
			unsigned long cbRet;
			char Buf[32];
			sprintf(Buf, "\\END set z value/\r\n\r\n");
			WriteFile(m_hFileLog, Buf, strlen(Buf), &cbRet, NULL);
			CloseHandle(m_hFileLog);
			m_hFileLog = NULL;
		}
	}

	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////
/*
	if( dwIndexY1 < dwIndexY2 )
		m_UpdateRectsImage.Add( CRect(0, dwIndexY1, m_szImage.cx, dwIndexY2) );
	else
		m_UpdateRectsImage.Add( CRect(0, 0, m_szImage.cx, m_szImage.cy) );
*/
	m_mutexImageDib.Unlock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	return i;
}
// 11.12.05

///////////////////////////////////////////////////////////////////////////
// 像素数据转换：ZZZ模式（专用于双探测器）
// 输入:	FrameData: 数据存储区
//			dwPixX: 用来存储X值的数组
//			dwPixY: 用来存储Y值的数组
//			dwPixZ: 用来存储Z值的数组
// 输出:	实际得到的有效数据的个数
DWORD CMCICard::PixConvertZZZ2( unsigned short* pnFrameData, long lBytesTransferred,
								  WORD* pPixX, WORD* pPixY, WORD* pPixZ,
								  WORD& dwIndexY1, WORD& dwIndexY2 )
{
	// 因为每批数据的第一个数是总个数，所以nLoop要+1，且循环时从1开始
	long nLoop = lBytesTransferred/2 +1;
	long i;

/*	///////////////////////////////////////////////////////////////////////////
	unsigned long cbRet;
	char Buf[32];
	CString str, strTemp;
	CTime	timeCurrent = CTime::GetCurrentTime();
	strTemp = timeCurrent.Format("%Y%m%d-%H%M%S");
	str.Format( "%szzz%s-%05d-pc.log", g_exeFullPath, strTemp, g_index );
	HANDLE hFil = CreateFile(str, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
	sprintf(Buf, "/BEGIN CONVERT\\\r\n");
	WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	sprintf(Buf, "nLoop = %ld\r\n", nLoop -1);
	WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	for( i=1; i<nLoop; i++ )
	{
		sprintf(Buf, "%04X, ", pnFrameData[i] );
		WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
	}
	sprintf(Buf, "\\END CONVERT/\r\n\r\n");
	WriteFile(hFil, Buf, strlen(Buf), &cbRet, NULL);
*/
	///////////////////////////////////////////////////////////////////////////
	BOOL bIsBOL, bIsBOF;
	unsigned short dwData	= 0;
	DWORD dwMaskBOL	= 0x1000;	// EOL 的掩码
	DWORD dwMaskBOF	= 0x3000;	// EOF 的掩码
	DWORD dwBitsOn;
	CSize sz = m_szImage;
	int nLineCounts	= ValleyX +sz.cx +PeakX +FallX;
	int nFrameCounts= ValleyY +sz.cy +PeakY +FallY;
	bIsBOL		= FALSE;		// 当前数据是EOL
	bIsBOF		= FALSE;		// 当前数据是EOF
	dwIndexY1	= m_nIndexY;
	int nIndex	= 0;			// 有效的数据个数

	for( i=1; i<nLoop; i++ )
	{
		dwData = pnFrameData[i];			// 得到16进制的数据
		if( dwData == 0x3456 )
			continue;

		dwBitsOn = dwData & 0x3000;			// 得到所需的掩码位

		bIsBOL = (dwBitsOn == dwMaskBOL);
		if( bIsBOL )
		{
			if( m_nY > ValleyY -1 && m_nY < ValleyY +sz.cy
				&& m_nX > ValleyX -1 && m_nX < ValleyX +sz.cx )
			{
				m_nIndexX = 0;
				m_nIndexY++;
//				CheckIndexs( sz.cx, sz.cy, m_nIndexX, m_nIndexY );
				if( m_nIndexY > sz.cy -1 )
					m_nY = 0;
			}
			m_nX = 0;
			m_nY++;
//			CheckIndexs( nLineCounts, nFrameCounts, m_nX, m_nY );
			if( m_nY > nFrameCounts -1 )
				m_nY = 0;
		}
		else
		{
			bIsBOF = (dwBitsOn == dwMaskBOF);
			if( bIsBOF )
			{
				m_nX		= 0;
				m_nY		= 0;
				m_nIndexX	= 0;
				m_nIndexY	= 0;
			}
			else
			{
				m_nX++;
//				CheckIndexs( nLineCounts, nFrameCounts, m_nX, m_nY );
				if( m_nX > nLineCounts -1 )
				{
					m_nX = 0;
					m_nY++;
				}
				if( m_nY > nFrameCounts -1 )
				{
					m_nX = 0;
					m_nY = 0;
				}
			}
		}

		if( m_nY > ValleyY && m_nY < ValleyY +sz.cy +1
			&& m_nX > ValleyX && m_nX < ValleyX +sz.cx +1 )
		{
			// 填充数组
/*			pPixX[m_nIndexY*sz.cx +m_nIndexX] = m_nIndexX;
			pPixY[m_nIndexY*sz.cx +m_nIndexX] = m_nIndexY;
			pbytePixZ[m_nIndexY*sz.cx +m_nIndexX] = (BYTE)(( dwData & 0xFFF ) /16);
*/
			pPixX[nIndex] = m_nIndexX;
			pPixY[nIndex] = m_nIndexY;
//			pPixZ[nIndex] = ( dwData & 0x0FFF ) /16;
			pPixZ[nIndex] = ( dwData & 0x0FF0 ) >> 4;
			nIndex++;
			m_nIndexX++;
//			CheckIndexs( sz.cx, sz.cy, m_nIndexX, m_nIndexY );
			if( m_nIndexX > sz.cx -1 )
			{
				m_nIndexX = 0;
				m_nIndexY++;
			}
			if( m_nIndexY > sz.cy -1 )
			{
				m_nIndexX = 0;
				m_nIndexY = 0;
			}
		}
//		bIsBOL	= FALSE;
//		bIsBOF	= FALSE;
	}
    ///////////////////////////////////////////////////////////////////////////
	dwIndexY2 = m_nIndexY;
	return nIndex;//(sz.cx * sz.cy);
}

void CMCICard::CheckIndexs( int nLineCounts, int nFrameCounts, int& nX, int& nY )
{
	if( nX > nLineCounts -1 )
	{
		nX = 0;
		nY++;
	}
	if( nY > nFrameCounts -1 )
	{
		nX = 0;
		nY = 0;
	}
}

DWORD CMCICard::ImageDibRead( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	LPSTR		lpDIBHdr, lpDIBBits;
	LPSTR		lpBuffLine;
	LONG		lBuffLineOffset;
	LPSTR		lpImageWindowLine;
	LONG		lImageLineOffset;
	CRect		rcImage, rcFrame;
	DWORD		i, iMaxLine;

	////////////////////////////////////////////////////////////////////
	rcFrame.SetRect( 0,0,m_szImage.cx,m_szImage.cy );
	rcImage = rcFrameDestWindow & rcFrame;
	if ( rcImage != rcFrameDestWindow )
		return 0;
	////////////////////////////////////////////////////////////////////
	
	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}

	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

	if ( lBuffSize >= rcFrameDestWindow.Width() * rcFrameDestWindow.Height() )
	{
		iMaxLine = rcFrameDestWindow.Height();
	}
	else
	{
		iMaxLine = lBuffSize / rcFrameDestWindow.Width();
	}

	lBuffLineOffset	= rcFrameDestWindow.Width();
	lpBuffLine		= (LPSTR)lpBuff;

	lImageLineOffset	= m_szImage.cx;
	lpImageWindowLine	= &(lpDIBBits[ 
		  (m_szImage.cy - rcImage.top - 1) * lImageLineOffset
		+ rcImage.left ] );

	for ( i=0; i<iMaxLine; i++ )
	{
		memcpy( (void *)lpBuffLine, (const void *)lpImageWindowLine, lBuffLineOffset );
		lpBuffLine			+= lBuffLineOffset;
		lpImageWindowLine	-= lImageLineOffset;
	}
	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////

	m_mutexImageDib.Unlock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////
	i = iMaxLine * lBuffLineOffset;
	////////////////////////////////////////////////////////////////////

	return i;
}

DWORD CMCICard::ImageDibCopy( LPVOID lpBuff, long lBuffSize, CRect& rcFrameDestWindow )
{
	LPSTR		lpDIBHdr, lpDIBBits;
	LPSTR		lpBuffLine;
	LONG		lBuffLineOffset;
	LPSTR		lpImageWindowLine;
	LONG		lImageLineOffset;
	CRect		rcImage, rcFrame;
	DWORD		i, iMaxLine;

	////////////////////////////////////////////////////////////////////
	rcFrame.SetRect( 0,0,m_szImage.cx,m_szImage.cy );
	rcImage = rcFrameDestWindow & rcFrame;
	if ( rcImage != rcFrameDestWindow )
		return 0;
	////////////////////////////////////////////////////////////////////
	
	m_mutexImageDib.Lock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) m_hdibImage);
	if ( lpDIBHdr == NULL )
	{
		m_mutexImageDib.Unlock();
		return 0;
	}

	lpDIBBits = ::FindDIBBits(lpDIBHdr);
	if ( lpDIBBits == NULL )
	{
		::GlobalUnlock((HGLOBAL) m_hdibImage);
		m_mutexImageDib.Unlock();
		return 0;
	}

	if ( lBuffSize >= rcFrameDestWindow.Width() * rcFrameDestWindow.Height() )
	{
		iMaxLine = rcFrameDestWindow.Height();
	}
	else
	{
		iMaxLine = lBuffSize / rcFrameDestWindow.Width();
	}

	lBuffLineOffset	= rcFrameDestWindow.Width();
	lpBuffLine		= (LPSTR)lpBuff + lBuffLineOffset * iMaxLine;

	lImageLineOffset	= m_szImage.cx;
	lpImageWindowLine	= &(lpDIBBits[ 
		  (m_szImage.cy - rcImage.top) * lImageLineOffset
		+ rcImage.left ] );

	for ( i=0; i<iMaxLine; i++ )
	{
		lpBuffLine			-= lBuffLineOffset;
		lpImageWindowLine	-= lImageLineOffset;
		memcpy( (void *)lpBuffLine, (const void *)lpImageWindowLine, lBuffLineOffset );
	}
	::GlobalUnlock((HGLOBAL) m_hdibImage);
	////////////////////////////////////////////////////////////////////

	m_mutexImageDib.Unlock();
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////
	i = iMaxLine * lBuffLineOffset;
	////////////////////////////////////////////////////////////////////

	return i;
}

HDIB CMCICard::CreateImageBitmap()
{
	DWORD			dwBitsSize;
	DWORD			dwOffBits;
	HDIB			hDIB;
	LPSTR			pDIB;
	LPBITMAPINFO 	pDibInfo;
	LPSTR	 		pDibBits;
	BYTE			bGrey;
	int				i;

	// Calculate the size of memory for hDIB.
	dwOffBits = sizeof(BITMAPINFO);											// BITMAPINFO
	dwOffBits += sizeof(RGBQUAD) * 255;										// Palette ( RGBQUAD area )
	dwBitsSize = WIDTHBYTES( m_szImage.cx * 8L ) * (DWORD)m_szImage.cy;		// Image bits

	// Allocate memory for DIB.
	hDIB = (HDIB) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize + dwOffBits);
	if (hDIB == 0)
	{
		return NULL;
	}
	DWORD dws	= GlobalSize( hDIB );
	pDIB		= (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
	pDibInfo	= (BITMAPINFO *)pDIB;	
	pDibBits	= &( pDIB[dwOffBits] );

	// Setup BITMAPINFOHEAD.
	pDibInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	pDibInfo->bmiHeader.biWidth			= WIDTHBYTES( m_szImage.cx * 8 ); 
	pDibInfo->bmiHeader.biHeight		= m_szImage.cy; 
	pDibInfo->bmiHeader.biPlanes		= 1;
	pDibInfo->bmiHeader.biBitCount		= 8;
	pDibInfo->bmiHeader.biCompression	= 0;
	pDibInfo->bmiHeader.biSizeImage		= dwBitsSize;
	pDibInfo->bmiHeader.biXPelsPerMeter	= 0;
	pDibInfo->bmiHeader.biYPelsPerMeter	= 0;
	pDibInfo->bmiHeader.biClrUsed		= 0;
	pDibInfo->bmiHeader.biClrImportant	= 0;

	// Image-lay pallete
	for (i=0; i<256; i++)
	{ 
		bGrey = (BYTE)i;
		pDibInfo->bmiColors[i].rgbRed		= bGrey;
		pDibInfo->bmiColors[i].rgbGreen		= bGrey;
		pDibInfo->bmiColors[i].rgbBlue		= bGrey;
		pDibInfo->bmiColors[i].rgbReserved	= (BYTE)0;
	}

	// Fill the bits.
//	FillMemory( (PVOID)pDibBits, dwBitsSize, 0xff );
	
/*	for (LONG dwLine=64; dwLine<m_szImage.cy; dwLine+=64)
	{
		FillMemory( (PVOID)&(pDibBits[dwLine*m_szImage.cx]),
			m_szImage.cx, 0xFF );
	}
*/
	::GlobalUnlock((HGLOBAL) hDIB);
	m_lpImageDibPlan = NULL;

	if ( hDIB != NULL ) 
		CreateDIBPalette(hDIB, &m_paletteImage);

	return hDIB;
}

long CMCICard::UpdateImageLay()
{
	CRect			rcTemp;
    HRESULT			ddrval = DD_OK;
    HDC             hdc;

	m_mutexImageDib.Lock();

	while ( !m_UpdateRectsImage.IsEmpty() )
	{
		rcTemp = m_UpdateRectsImage.Get();

		if ( !rcTemp.IsRectEmpty() )
		{
			m_UpdateRectsGraph.Add( rcTemp );

			if ( !IsReady() ) 
			{
				m_mutexImageDib.Unlock();
				return DD_OK;
			}

			if ((ddrval = m_lpDDSImageLay->GetDC(&hdc)) == DD_OK)
			{
				PaintDIB (hdc, (LPRECT)rcTemp, (HDIB)m_hdibImage, (LPRECT)rcTemp, &m_paletteImage);
//				DrawDIB (hdc, (LPRECT)rcTemp, (HDIB)m_hdibImage, (LPRECT)rcTemp);
				
				m_lpDDSImageLay->ReleaseDC(hdc);
			}
		}
	}

	m_mutexImageDib.Unlock();

	return ddrval;
}

long CMCICard::UpdateGraphLay()
{
	CRect			rcTemp;
    HRESULT			ddrval = DD_OK;

	while ( !m_UpdateRectsGraph.IsEmpty() )
	{
		rcTemp = m_UpdateRectsGraph.Get();

		if ( !rcTemp.IsRectEmpty() )
		{
			m_UpdateRectsLabel.Add( rcTemp );

			CRect rcDestImageLay	= rcTemp;
			CRect rcSrcGraphLay		= LayWindowMapClip_Image_to_Graph( rcDestImageLay );

			/*
			ddrval = m_lpDDSImageLay->Blt(
				(LPRECT)rcDestImageLay,			// dest rect
				m_lpDDSGraphLay,				// src surface
				(LPRECT)rcSrcGraphLay,			// src rect
				DDBLT_KEYSRC | DDBLT_WAIT,		//
				NULL);
			*/

			if ( !IsReady() ) return DD_OK;

			ddrval = m_lpDDSGraphBackLay->Blt(
				(LPRECT)rcSrcGraphLay,			// dest rect
				m_lpDDSGraphLay,				// src surface
				(LPRECT)rcSrcGraphLay,			// src rect
				DDBLT_WAIT,		// DDBLT_KEYSRC | 
				NULL);

			/*
			ddrval = m_lpDDSGraphBackLay->BltFast(
				0,
				0,
				m_lpDDSGraphLay,  
				(LPRECT)rcSrcGraphLay,
				DDBLTFAST_SRCCOLORKEY | DDBLT_WAIT );
			*/
		}
	}

	return ddrval;
}

long CMCICard::UpdateLabelLay()
{
	CRect			rcTemp;
    HRESULT			ddrval = DD_OK;

	while ( !m_UpdateRectsLabel.IsEmpty() )
	{
		rcTemp = m_UpdateRectsLabel.Get();

		if ( !rcTemp.IsRectEmpty() )
		{
			m_UpdateRectsMobileUScale.Add( rcTemp );

			if ( m_boolShowLabel )
			{
				CRect rcDestImageLay	= rcTemp;
				CRect rcSrcLabelLay		= LayWindowMapClip_Image_to_Label( rcDestImageLay );

				/*
				ddrval = m_lpDDSImageLay->Blt(
					(LPRECT)rcDestImageLay,			// dest rect
					m_lpDDSLabelLay,				// src surface
					(LPRECT)rcSrcLabelLay,			// src rect
					DDBLT_KEYSRC | DDBLT_WAIT,
					NULL);
				*/
				CRect rcDestGraphLay		= LayWindowMapClip_Image_to_Graph( rcDestImageLay );
				
				if ( !IsReady() ) return DD_OK;

				ddrval = m_lpDDSGraphBackLay->Blt(
					(LPRECT)rcDestGraphLay,			// dest rect
					m_lpDDSLabelLay,				// src surface
					(LPRECT)rcSrcLabelLay,			// src rect
					DDBLT_KEYSRC | DDBLT_WAIT,
					NULL);

/*				DDALPHABLTFX alphatx;
				alphatx.dwSize = sizeof(alphatx);
				
				alphatx.ddargbScaleFactors.alpha = 127;
				m_lpDDSGraphBackLay->AlphaBlt((LPRECT)rcDestGraphLay, m_lpDDSLabelLay, (LPRECT)rcDestGraphLay, DDBLT_WAITNOTBUSY, &alphatx);*/
			}
		}
	}

	return ddrval;
}

long CMCICard::UpdateUScaleMobileLay()
{
	CRect			rcTemp;
    HRESULT			ddrval = DD_OK;

	while ( !m_UpdateRectsMobileUScale.IsEmpty() )
	{
		rcTemp = m_UpdateRectsMobileUScale.Get();

		if ( !rcTemp.IsRectEmpty() )
		{
			//m_UpdateRectsGraphBack.Add( rcTemp );
			m_UpdateRectsOscillograph.Add( rcTemp );

			if ( m_boolShowMobileUScale )
			{
				CRect rcDestImageLay	= rcTemp;
				CRect rcSrcUScaleLay	= LayWindowMapClip_Image_to_MobileUScale( rcDestImageLay );

				/*
				ddrval = m_lpDDSImageLay->Blt(
					(LPRECT)rcDestImageLay,			// dest rect
					m_lpDDSMobileUScaleLay,				// src surface
					(LPRECT)rcSrcUScaleLay,			// src rect
					DDBLT_KEYSRC | DDBLT_WAIT,
					NULL);
				*/
				
				CRect rcDestGraphLay		= LayWindowMapClip_Image_to_Graph( rcDestImageLay );
				
				if ( !IsReady() ) return DD_OK;

				ddrval = m_lpDDSGraphBackLay->Blt(
					(LPRECT)rcDestGraphLay,			// dest rect
					m_lpDDSMobileUScaleLay,				// src surface
					(LPRECT)rcSrcUScaleLay,			// src rect
					DDBLT_KEYSRC | DDBLT_WAIT,
					NULL);
			}
		}
	}

	return ddrval;
}

void CMCICard::PhotoIndication( const CRect& rcDest, const COLORREF color, const BOOL boolFill )//09.06.01
{
	HDC				hdc;
    HRESULT			ddrval;

	if ( !IsReady() ) return;

	//////////////////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	//////////////////////////////////////////////////////////////////

	if( m_lpDDSGraphLay == NULL )
	{
		m_mutexLayAll.Unlock();
		return;
	}

	ddrval = m_lpDDSGraphLay->GetDC( &hdc );
	if( ddrval == DD_OK )
	{
		CRect	rcFill =
			rcDest & CRect(0,0,m_szGraph.cx,m_szGraph.cy);
		if( boolFill )	//填充
		{
			//////////////////////////////////////////
			HBRUSH brBrush = CreateSolidBrush( color );
			//////////////////////////////////////////

			FillRect( hdc, (LPRECT)rcFill, brBrush );
			//////////////////////////////////////////
			DeleteObject( brBrush );
			//////////////////////////////////////////
		}
		else			//仅画线
		{
			//////////////////////////////////////////
			HPEN hpen = CreatePen(PS_SOLID, 1, color );
			HPEN hpenOld = (HPEN)SelectObject(hdc, hpen);
			//////////////////////////////////////////

			MoveToEx (hdc, rcFill.left, rcFill.bottom -1, NULL);
			LineTo (hdc, rcFill.right, rcFill.bottom -1);

			//////////////////////////////////////////
			SelectObject(hdc, hpenOld);
			DeleteObject(hpen);
			//////////////////////////////////////////
		}
		m_lpDDSGraphLay->ReleaseDC(hdc);
	}

	CRect rcGrapic = rcDest;
	CRect rcImage = LayWindowMapClip_Graph_to_Image( rcGrapic );
	if ( color != m_sysOpt.color[SysOpt_clrTransparent] )
		m_UpdateRectsGraph.Add( rcImage );
	else
		m_UpdateRectsImage.Add( rcImage );

	//////////////////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	//////////////////////////////////////////////////////////////////
}

long CMCICard::UpdateGraphBackLay()
{
	CRect			rcTemp;
    HRESULT			ddrval = DD_OK;

	while ( !m_UpdateRectsGraphBack.IsEmpty() )
	{
		rcTemp = m_UpdateRectsGraphBack.Get();

		if ( !rcTemp.IsRectEmpty() )
		{
			CRect rcDestImageLay	= rcTemp;
			CRect rcSrcGraphLay		= LayWindowMapClip_Image_to_Graph( rcDestImageLay );

			if ( !IsReady() ) return DD_OK;

			ddrval = m_lpDDSImageLay->Blt(
				(LPRECT)rcDestImageLay,			// dest rect
				m_lpDDSGraphBackLay,			// src surface
				(LPRECT)rcSrcGraphLay,			// src rect
				DDBLT_KEYSRC | DDBLT_WAIT,		//
				NULL);
		}
	}

	return ddrval;
}

long CMCICard::UpdatePriamryLay()
{
    HRESULT			ddrval = DD_OK;

	CRect rcSrcImageLay	= m_rcImageWindow;
	CRect rcDestPriamryLay	= LayWindowMapClip_Image_to_Priamry( rcSrcImageLay );

	//======2007.05.14_扫描区域居中========================
	// 修改标示：2007.05.14_扫描区域居中
	// 修改日期：2007.05.14星期一
	// 修改人  ：J.Y.Ma
	// 修改原因：无论放大倍数多少，使图像扫描区域居中

	// 本次修改前代码副本
	/*----------------------------------------------------- 
	//---------------------------------------------------*/

	// 本次修改后代码
	//-----------------------------------------------------
	///////////////////////////////////////////////////////
/*	CPoint pt(0,0);
	// 非照相预览模式时，如果画图区大于图像，
	// 则计算将图像显示在中央所需偏移量，并进行偏移
	if( m_dblZoom != 0
		&& m_rcScreenClientRect.Width() >= rcSrcImageLay.Width()*m_dblZoom 
		&& m_rcScreenClientRect.Height() >= rcSrcImageLay.Height()*m_dblZoom )
		pt = CPoint( -( m_rcScreenClientRect.Width() - rcSrcImageLay.Width()*m_dblZoom ) / 2,
					-( m_rcScreenClientRect.Height() - rcSrcImageLay.Height()*m_dblZoom ) / 2 );
	rcDestPriamryLay.OffsetRect( -pt );
*/	///////////////////////////////////////////////////////


	if ( !IsReady() ) return DD_OK;

/*	ddrval = m_lpDDSPrimary->Blt(
		(LPRECT)rcDestPriamryLay,		// dest rect
		m_lpDDSImageLay,			// src surface
		(LPRECT)rcSrcImageLay,		// src rect
		DDBLT_WAIT,
		NULL);
*/

	ddrval = m_lpDDSPrimaryBackLay->Blt(
		(LPRECT)rcDestPriamryLay,		// dest rect
		m_lpDDSImageLay,				// src surface
		(LPRECT)rcSrcImageLay,			// src rect
		DDBLT_WAIT,
		NULL);
	if ( ddrval != DD_OK )
		return ddrval;

	if ( !IsReady() ) return DD_OK;

//	ddrval = m_lpDDSPrimary->Blt(NULL, m_lpDDSPrimaryBackLay, NULL, DDBLT_WAIT, NULL); 
	ddrval = m_lpDDSPrimary->Blt(
		(LPRECT)rcDestPriamryLay,		// dest rect
		m_lpDDSPrimaryBackLay,			// src surface
		(LPRECT)rcDestPriamryLay,		// src rect
		DDBLT_WAIT,
		NULL);
/*
	ddrval = m_lpDDSPrimary->BltFast(
		rcDestPriamryLay.left,
		rcDestPriamryLay.right,
		m_lpDDSPrimaryBackLay,  
		(LPRECT)rcDestPriamryLay,
		DDBLT_WAIT );
*/	
	return ddrval;
}

//======2006.11.22_3200与3900采集屏显示兼容============
// 修改标示：2006.11.22_3200与3900采集屏显示兼容
// 修改日期：2006.11.22
// 修改人  ：J.Y.Ma
// 修改原因：合并程序后，使各主程序均能调用同一动态链接库

// 本次修改前代码副本
/*----------------------------------------------------- 
-----------------------------------------------------*/

// 本次修改后代码
//-----------------------------------------------------
void CMCICard::SetProductLogo( CString csLogo )
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_csLogo = csLogo;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

void CMCICard::SetScanScreenMode( BOOL boolNewScanScreenMode )
{
	if( m_boolNewScanScreenMode == boolNewScanScreenMode )
		return;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_boolNewScanScreenMode = boolNewScanScreenMode;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}
//-----------------------------------------------------
//======2006.11.22_3200与3900采集屏显示兼容============

// 	COLORREF				m_colorTransparent;
// 	COLORREF				m_colorBack;
// 	COLORREF				m_colorOscillographGrid;
// 	COLORREF				m_colorOscillographGraph;
// 	COLORREF				m_colorEditText;
// 	COLORREF				m_colorLabelText;
// 	COLORREF				m_colorLabelLogoText;
// 	COLORREF				m_colorMobileUScaleText;
// 	COLORREF				m_crFrameRateColor;
void CMCICard::SetColor( int nType, COLORREF color )
{
	m_sysOpt.color[nType]	= color;
	switch( nType )
	{
	case	SysOpt_clrBack:
		RedrawLabelLay();
		break;
	case	SysOpt_clrLabelText:
	case	SysOpt_clrLabelLogoText:
		RedrawLabelLay();
		break;
	case	SysOpt_clrMobileUScaleText:
	case	SysOpt_clrMobileUScaleLine:
		RedrawMobileUScaleLay();
		break;
	case	SysOpt_clrOscillographGrid:
	case	SysOpt_clrOscillographGraph:
		RedrawOscillographLay();
		break;
	}
}

void CMCICard::SetFontName( int nType, CString strName )
{
	m_sysOpt.fName[nType]	= strName;
}

void CMCICard::SetFontSize( int nType, int nSize )
{
	m_sysOpt.fSize[nType]	= nSize;
}

void CMCICard::SetFontWeight( int nType, int nWeight )
{

}

void CMCICard::SetTransparent( int nTransparent )
{
	m_sysOpt.nShowParams[SysOpt_showLabelTrans]	= nTransparent;
// 	if( nTransparent > 0 )
// 		m_sysOpt.color[SysOpt_clrBack]		= g_clrUSB_Transparent;
// 	else
// 		m_sysOpt.color[SysOpt_clrBack]		= g_clrUSB_Background;
}

/*
const int SET_PARAMS_StoreMode			= 1;
const int SET_PARAMS_DetectorMode		= 2;
const int SET_PARAMS_NeedMon			= 3;
*/

void CMCICard::SetParams( int nType, int nParam )
{
	if( nType == SET_PARAMS_StoreMode )
		m_nDataStoreMode = nParam;
	else if( nType == SET_PARAMS_DetectorMode )
		m_nDetectorMode = nParam;
	else if( nType == SET_PARAMS_NeedMon )
		m_bNeedMon = (BOOL)nParam;
	else if( nType == 4 )
	{
		m_bDet2nd = (BOOL)nParam;
		RedrawLabelLay();
	}
	else if( nType == 5 )
		m_bDebugZ = (BOOL)nParam;
	else if( nType == 6 )
	{
		// 视频示波器分析及显示意义不同
		m_bDebugOsc		= (BOOL)nParam;
		switch( m_sizeReso.cx )
		{
		case 16:
		case 32:
		case 64:
		case 128:
		case 256:
			m_szOscill		= CSize( m_szOscill.cx, m_szImage.cy /2);
			break;
		default:
			if( m_bDebugOsc )
				m_szOscill		= CSize( m_szOscill.cx, m_szImage.cy/2 );
			else
				m_szOscill		= CSize( m_szOscill.cx, m_szImage.cy/4 );
			break;
		}
//		m_boolRedrawOscillograph = TRUE;
	}
	else if( nType == 7 )
	{
		// 示波器在调试模式下，Y向档位调节
		m_debugOSC.nIndexY		= nParam;
	}
	else if( nType == 8 )
	{
		m_debugOSC.b90 = (BOOL)nParam;
		ZeroMemory( &m_bOscillographBuff, sizeof(WORD)*8192);
//		m_boolRedrawOscillograph = TRUE;
	}
	else if( nType == 9 )
	{
		// 示波器在调试模式下，Y向偏移量
		m_debugOSC.dOffset			= nParam / 10000.0;
//		m_boolRedrawOscillograph	= TRUE;
	}
	else if( nType == 10 )
	{
		m_sysOpt.nLineWidth = nParam;
		RedrawMobileUScaleLay();
	}
	else if( nType == 11 )
	{
		m_nChnIndex[0] = nParam;
		UpdateSGname( m_nChnIndex[0], m_csSG1 );
		RedrawLabelLay();
	}
	else if( nType == 12 )
	{
		m_nChnIndex[1] = nParam;
		UpdateSGname( m_nChnIndex[1], m_csSG2 );
		RedrawLabelLay();
	}
	else if( nType == 13 )
		m_dblPixelsPerMM_HORZ = 1.0 * GetSystemMetrics(SM_CXSCREEN) / nParam;
	else if( nType == 14 )
		m_dblPixelsPerMM_VERT = 1.0 * GetSystemMetrics(SM_CYSCREEN) / nParam;
}

void CMCICard::UpdateSGname( int nIndex, CString& strName )
{
	switch( nIndex )
	{
	case	0:
		strName	= _T("SE");
		break;
	case	1:
		strName	= _T("BSE");
		break;
	case	2:
		strName	= _T("SE+BSE");
		break;
	}
}

void CMCICard::SetSharedImageBuff( int nIndex, unsigned short* pBuff )	// 设置并存储共享内存段首地址
{
	m_pSharedImageBuff[nIndex] = pBuff;
}

void CMCICard::SetSharedImageBuffIndex( int nIndex )
{
	m_nSharedImageBuffIndexWrite = nIndex;
}

// 09.11.24加入同步语句
// 改变放大倍数，由任意变为Fit时有时会出现图像被拉伸；或由大变小时，小区域到原来区域间有未被重画的区域
// 在调试过程中发现：GetClientWindow中会对m_rcScreenClient根据放大倍数做调整，
//					而LayWindowMapClip_Image_to_Priamry中如果Fit模式，会用到m_rcScreenClient，
//					这有可能造成使用的同步问题，故加入同步语句
void CMCICard::SetZoom( double dblZoom )
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_dblZoom = dblZoom;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

void CMCICard::SetDestFrame(CRect rcDestFrame)
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_rcDestFrame = rcDestFrame;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

CSize CMCICard::GetSizes( int nIndex )
{
	CSize sz(0,0);
	switch( nIndex )
	{
	case	0:
		sz.cx	= m_rcImageWindow.Width();
		sz.cy	= m_rcImageWindow.Height();
		break;
	case	1:
		sz		= m_szImage;
		break;
	case	2:
		sz		= m_szLabel;
		break;
	case	3:
		sz		= m_szUScale;
		break;
	case	4:
		sz		= m_szOscill;
		break;
	}
	return sz;
}

void CMCICard::GetClientWindow()
{
	///////////////////////////////////////////////////////////////////
	if( m_boolPreview )	//05.02.06 照相预览问题；
	{					//05.06.07修正，去掉Border和Caption部分，保证尺寸为12cm X 9cm
		CRect rcRect(0,0,0,0);
/*		CDC* pDC = m_pScreenWnd->GetDC();
		double dblPixelsPerMM_HORZ = 
			(double)pDC->GetDeviceCaps(HORZRES) / pDC->GetDeviceCaps(HORZSIZE);
		double dblPixelsPerMM_VERT = 
			(double)pDC->GetDeviceCaps(VERTRES) / pDC->GetDeviceCaps(VERTSIZE);
		m_pScreenWnd->ReleaseDC(pDC);

		rcRect.right	= (int)(SEM_dfStandImageWidth * dblPixelsPerMM_HORZ + 0.5);
		rcRect.bottom	= (int)(SEM_dfStandImageHeight * dblPixelsPerMM_VERT + 0.5);
*/
/*		CDC dc;
		dc.Attach( m_pScreenWnd->GetDC()->m_hDC );
		double dblPixelsPerInch_HORZ = dc.GetDeviceCaps( LOGPIXELSX );	// 屏幕横向每英寸像素数，例如：96
		double dblPixelsPerInch_VERT = dc.GetDeviceCaps( LOGPIXELSX );	// 屏幕纵向每英寸像素数，例如：96
		double dblPhysicalDisW = dc.GetDeviceCaps( HORZSIZE );	// 屏幕横向尺寸，单位毫米，例如410mm
		double dblPhysicalDisH = dc.GetDeviceCaps( VERTSIZE );	// 屏幕纵向尺寸，单位毫米，例如210mm
		double dblDisW = dc.GetDeviceCaps( HORZRES );	// 屏幕横向分辨率，单位像素，例如：1440
		double dblDisH = dc.GetDeviceCaps( VERTRES );	// 屏幕纵向分辨率，单位像素，例如：900
		dc.Detach();
*/
//		rcRect.right	= (int)(SEM_dfStandImageWidth * dblDisW / dblPhysicalDisW + 0.5 );
//		rcRect.bottom	= (int)(SEM_dfStandImageHeight * dblDisH / dblPhysicalDisH + 0.5 );
		double dRatio	= 1.0 *m_sizeReso.cy /m_sizeReso.cx;
		if( dRatio == 0.5 )
		{
			rcRect.right	= (int)(127 * m_dblPixelsPerMM_HORZ + 0.5 );
			rcRect.bottom	= (int)(63 * m_dblPixelsPerMM_VERT + 0.5 );
		}
		else if( dRatio == 1.0 )
		{
			rcRect.right	= (int)(127 * m_dblPixelsPerMM_HORZ + 0.5 );
			rcRect.bottom	= (int)(127 * m_dblPixelsPerMM_VERT + 0.5 );
		}
		else
		{
			rcRect.right	= (int)(127 * m_dblPixelsPerMM_HORZ + 0.5 );
			rcRect.bottom	= (int)(89 * m_dblPixelsPerMM_VERT + 0.5 );
		}
		//======2006.11.22_3200与3900采集屏显示兼容============
		// 修改标示：2006.11.22_3200与3900采集屏显示兼容
		// 修改日期：2006.11.22
		// 修改人  ：J.Y.Ma
		// 修改原因：合并程序后，使各主程序均能调用同一动态链接库

		// 本次修改前代码副本
		/*----------------------------------------------------- 
//			rcRect.right += GetSystemMetrics( SM_CXBORDER ) * 2;
//			rcRect.bottom += GetSystemMetrics( SM_CYBORDER ) * 2;
//			rcRect.bottom += GetSystemMetrics( SM_CYCAPTION );
		-----------------------------------------------------*/
		
		// 本次修改后代码
		//-----------------------------------------------------
		if( !m_boolNewScanScreenMode )	//06.11.22
		{
			rcRect.right += GetSystemMetrics( SM_CXBORDER ) * 2;
			rcRect.bottom += GetSystemMetrics( SM_CYBORDER ) * 2;
			rcRect.bottom += GetSystemMetrics( SM_CYCAPTION );
		}
		//-----------------------------------------------------
		//======2006.11.22_3200与3900采集屏显示兼容============

		m_rcScreenClientRect = rcRect;
	}
	else
	{
		m_pScreenWnd->GetClientRect( (LPRECT)m_rcScreenClientRect );
//------05.02.05 采集窗4:3问题 Start ----------------
		//======2006.11.22_3200与3900采集屏显示兼容============
		// 修改标示：2006.11.22_3200与3900采集屏显示兼容
		// 修改日期：2006.11.22
		// 修改人  ：J.Y.Ma
		// 修改原因：合并程序后，使各主程序均能调用同一动态链接库

		// 本次修改前代码副本
		/*----------------------------------------------------- 
		-----------------------------------------------------*/
		
		// 本次修改后代码
		//-----------------------------------------------------
		if( m_dblZoom == 0. && m_boolNewScanScreenMode )	//06.11.22
		{
/*			int w = m_rcScreenClientRect.Width();
			int h = m_rcScreenClientRect.Height();
			int w_scan, h_scan, base;
			if( w/4*3 < h )
			{
				base = (int)(1.*w/16 +0.5);
				w_scan = base*16;
				h_scan = base*12;
			}
			else
			{
				base = (int)(1.*h/12 +0.5);
				h_scan = base*12;
				w_scan = base*16;
			}

			m_rcScreenClientRect = CRect( m_rcScreenClientRect.left, m_rcScreenClientRect.top,
									m_rcScreenClientRect.left +w_scan, m_rcScreenClientRect.top +h_scan);
*/		}
		//-----------------------------------------------------
		//======2006.11.22_3200与3900采集屏显示兼容============
//------05.02.05 采集窗4:3问题 End ------------------
	}

	//m_ptScreenClientPos.x = m_pScreenWnd->GetScrollPos( SB_HORZ );
	//m_ptScreenClientPos.y = m_pScreenWnd->GetScrollPos( SB_VERT );
	/////////////////////////////////////////////////////////////////////

	//m_pScreenWnd->ClientToScreen( (LPRECT)m_rcScreenClientRect );
	PostMessage(m_pScreenWnd->m_hWnd, WM_USER_KYKYComm_Thread_MCICard_GetRect, (LPARAM)this,0L);
}

void CMCICard::PaintScreenWindow()
{
	static CPoint ptScreenPos_Old;
	
	CPoint ptScreenPos;

	ptScreenPos.x = m_rcScreenClientRect.left;
	ptScreenPos.y = m_rcScreenClientRect.top;

	if ( ptScreenPos_Old != ptScreenPos )
	{
		if ( ( ptScreenPos.x < ptScreenPos_Old.x )
			|| ( ptScreenPos.y < ptScreenPos_Old.y ) )
		{
			m_pScreenWnd->InvalidateRect(NULL);
		}

		ptScreenPos_Old = ptScreenPos;
	}
}

void CMCICard::MainLoop()
{
	DWORD	thisTickCount;
    
	///////////////////////////////////////////////////////
	if ( !m_boolReady )
    {
		Sleep( 1 );
		return;
    }
	///////////////////////////////////////////////////////
	if ( m_boolShouldReset )
    {
		m_lpDDSPrimary->Restore();
		m_boolShouldReset = FALSE;
		Sleep( 1 );
		return;
    }

//	if( m_bDataNeedUpdated )
	if( m_nSharedImageBuffIndexRead != m_nSharedImageBuffIndexWrite )
	{
		do
		{
			GetData( CRect(0,0,m_szImage.cx,m_szImage.cy) );
			m_nSharedImageBuffIndexRead++;
			if( m_nSharedImageBuffIndexRead >= SharedImageBuffCounts )
				m_nSharedImageBuffIndexRead = 0;
		}while( m_nSharedImageBuffIndexRead != m_nSharedImageBuffIndexWrite );
	}
	else
	{
		// 12.02.15 使用m_nDetectorMode临时作为判断是采集/冻结状态
		// -1表示冻结
		// 采集时如果没有数据更新就返回
		// 冻结时要继续执行之后的语句
/*		if( m_nDetectorMode > -1 )
		{
			Sleep( 1 );
			return;
		}*/
	///////////////////////////////////////////////////////
	thisTickCount = GetTickCount();
    if ((thisTickCount - m_lastTickCount) < g_dwUSB_UpdateDelay)
    {
		Sleep( 1 );
//		#ifdef _DEBUG
//			afxDump << "thisTickCount - m_lastTickCount = " << thisTickCount << " - " << m_lastTickCount << " = " << thisTickCount - m_lastTickCount << "\n";
//		#endif
		return;
    }
//		#ifdef _DEBUG
//			afxDump << "thisTickCount - m_lastTickCount = " << thisTickCount << " - " << m_lastTickCount << " = " << thisTickCount - m_lastTickCount << "\n";
//		#endif
	m_lastTickCount = thisTickCount;
	///////////////////////////////////////////////////////

	}

//	DWORD this1, this2;
//	this1 = GetTickCount();
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();	//09.12.03 (v 1.0.0.6 +)
	///////////////////////////////////////////////////////
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "01. Lock = " << this2 - this1 << "\n";
//	#endif

//	this1 = GetTickCount();
	GetClientWindow();

	///////////////////////////////////////////////////////////////////
	m_dblScaleImageToGraph_W = (double)m_szGraph.cx / m_rcImageWindow.Width();
	m_dblScaleImageToGraph_H = (double)m_szGraph.cy / m_rcImageWindow.Height();
	///////////////////////////////////////////////////////////////////
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "02. GetClientWindow = " << this2 - this1 << "\n";
//	#endif

	///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////
//	m_mutexLayAll.Lock();	//09.12.03 (v 1.0.0.5 src, v 1.0.0.6 -)
	///////////////////////////////////////////////////////

//	this1 = GetTickCount();
	if (m_boolRedrawLabel)
	{
		RedrawLabelLay();
		m_boolRedrawLabel = FALSE;
	}
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "03. RedrawLabelLay = " << this2 - this1 << "\n";
//	#endif

//	this1 = GetTickCount();
	if (m_boolRedrawUScal)
	{
		RedrawMobileUScaleLay();
		m_boolRedrawUScal = FALSE;
	}
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "04. RedrawMobileUScaleLay = " << this2 - this1 << "\n";
//	#endif

//	this1 = GetTickCount();
	if (m_boolRedrawOscillograph)
	{
		if (m_boolShowOscillograph)
			RedrawOscillographLay();

		m_boolRedrawOscillograph = FALSE;
	}
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "05. RedrawOscilLay = " << this2 - this1 << "\n";
//	#endif
	
//	this1 = GetTickCount();
	UpdateImageLay();
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "06. ImageLay = " << this2 - this1 << "\n";
//	#endif

//	this1 = GetTickCount();
	UpdateGraphLay();
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "07. GraphLay = " << this2 - this1 << "\n";
//	#endif

//	this1 = GetTickCount();
	UpdateLabelLay();
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "08. LabelLay = " << this2 - this1 << "\n";
//	#endif

//	this1 = GetTickCount();
	UpdateUScaleMobileLay();
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "09. UScaleMobileLay = " << this2 - this1 << "\n";
//	#endif

//	this1 = GetTickCount();
	UpdateOscillographLay();
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "10. OscillLay = " << this2 - this1 << "\n";
//	#endif


//	this1 = GetTickCount();
	UpdateGraphBackLay();
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "11. GraphBackLay = " << this2 - this1 << "\n";
//	#endif


//	this1 = GetTickCount();
	FormatFrameRate();
	UpdateFrameRateLay();
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "12. FrameRateLay = " << this2 - this1 << "\n";
//	#endif
	
//	this1 = GetTickCount();
	long ddrval = UpdatePriamryLay();
	////////////////////////////////////
	if ((ddrval == DDERR_SURFACELOST )
		||(ddrval == DDERR_GENERIC ))
	{
		m_boolShouldReset	= TRUE;
	}
	////////////////////////////////////
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "13. PriamryLay = " << this2 - this1 << "\n";
//	#endif

//	this1 = GetTickCount();
	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "14. Unlock = " << this2 - this1 << "\n";
//	#endif

//	this1 = GetTickCount();
	PaintScreenWindow();
	Sleep(0);
//	this2 = GetTickCount();
//	#ifdef _DEBUG
//		afxDump << "15. PaintScreenWindow = " << this2 - this1 << "\n";
//	#endif
}

void CMCICard::SetResolution(CSize szReso)
{
	///////////////////////////////////////////////////////
	m_mutexImageDib.Lock();
	m_mutexImageUSB.Lock();
	///////////////////////////////////////////////////////

	int nX;
	if( m_bSplit )
		nX = szReso.cx *2;
	else
		nX = szReso.cx;
	SetImageWindow( CRect(0,0,nX,szReso.cy) );
	if( szReso.cx < 16+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 2 );
		m_szUScale		= CSize( nX, 1 );
		m_szOscill		= CSize( nX, 8 );
	}
	else if( szReso.cx < 32+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 4 );
		m_szUScale		= CSize( nX, 2 );
		m_szOscill		= CSize( nX, 16 );
	}
	else if( szReso.cx < 64+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 8 );
		m_szUScale		= CSize( nX, 4 );
		m_szOscill		= CSize( nX, 32 );
	}
	else if( szReso.cx < 128+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 16 );
		m_szUScale		= CSize( nX, 8 );
		m_szOscill		= CSize( nX, 64 );
	}
	else if( szReso.cx < 256+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 24 );
		m_szUScale		= CSize( nX, 16 );
		m_szOscill		= CSize( nX, 128 );
	}
	else if( szReso.cx < 480+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 32 );
		m_szUScale		= CSize( nX, 16 );
		m_szOscill		= CSize( nX, 128 );
	}
	else if( szReso.cx < 600+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 40 );
		m_szUScale		= CSize( nX, 40 );
		m_szOscill		= CSize( nX, 128 );
	}
	else if( szReso.cx < 640+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 40 );
		m_szUScale		= CSize( nX, 40 );
		m_szOscill		= CSize( nX, 128 );
	}
	else if( szReso.cx < 800+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 48 );
		m_szUScale		= CSize( nX, 40 );
		m_szOscill		= CSize( nX, 256 );
	}
	else if( szReso.cx < 1280+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 64 );
		m_szUScale		= CSize( nX, 40 );
		m_szOscill		= CSize( nX, 256 );
	}
	else if( szReso.cx < 1536+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 96 );
		m_szUScale		= CSize( nX, 64 );
		m_szOscill		= CSize( nX, 512 );
	}
	else if( szReso.cx < 2048+1 )
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 128 );
		m_szUScale		= CSize( nX, 80 );
		m_szOscill		= CSize( nX, 512 );
	}
	else
	{
		m_szImage		= CSize( nX, szReso.cy );
		m_szGraph		= CSize( nX, szReso.cy );
		m_szLabel		= CSize( nX, 256 );
		m_szUScale		= CSize( nX, 160 );
		m_szOscill		= CSize( nX, 512 );
	}

	// 重新计算一下示波器大小
	switch( szReso.cx )
	{
	case 16:
	case 32:
	case 64:
	case 128:
	case 256:
		m_szOscill		= CSize( m_szOscill.cx, m_szImage.cy /2);
		break;
	default:
		if( m_bDebugOsc )
			m_szOscill		= CSize( m_szOscill.cx, m_szImage.cy/2 );
		else
			m_szOscill		= CSize( m_szOscill.cx, m_szImage.cy/4 );
		break;
	}

	m_sizeReso = szReso;

	///////////////////////////////////////////////////////
	m_mutexImageUSB.Unlock();
	m_mutexImageDib.Unlock();
	///////////////////////////////////////////////////////
}

void CMCICard::SetFunction( int nFunction )
{
	m_nusbFunction = nFunction;
}

void CMCICard::SetSplit( BOOL bSplit )
{
	m_bSplit = bSplit;
}

void CMCICard::SetLiveMode( BOOL bLive )
{
	m_bLive = bLive;
}

void CMCICard::SetImageWindow( CRect rcImageWindow )
{
	m_rcImageWindow = rcImageWindow;
}
/*
void CMCICard::GetSizes( CSize &szImage, CSize &szGraph, CSize &szLabel, CSize &szUScale, CSize &szOscill )
{
	USB_Image_Resolution reso = GetResolution();
	switch( reso )
	{
	case	USB_RESO_16_16:
		szImage		= g_sizeUSB_RESO_16_16;
		szGraph		= g_sizeUSB_RESO_16_16;
		szLabel		= CSize( g_sizeUSB_RESO_16_16.cx, 2 );
		szUScale	= CSize( g_sizeUSB_RESO_16_16.cx, 1 );
		szOscill	= CSize( g_sizeUSB_RESO_16_16.cx, 8 );
		break;
	case	USB_RESO_32_32:
		szImage		= g_sizeUSB_RESO_32_32;
		szGraph		= g_sizeUSB_RESO_32_32;
		szLabel		= CSize( g_sizeUSB_RESO_32_32.cx, 4 );
		szUScale	= CSize( g_sizeUSB_RESO_32_32.cx, 2 );
		szOscill	= CSize( g_sizeUSB_RESO_32_32.cx, 16 );
		break;
	case	USB_RESO_64_64:
		szImage		= g_sizeUSB_RESO_64_64;
		szGraph		= g_sizeUSB_RESO_64_64;
		szLabel		= CSize( g_sizeUSB_RESO_64_64.cx, 8 );
		szUScale	= CSize( g_sizeUSB_RESO_64_64.cx, 4 );
		szOscill	= CSize( g_sizeUSB_RESO_64_64.cx, 32 );
		break;
	case	USB_RESO_128_128:
		szImage		= g_sizeUSB_RESO_128_128;
		szGraph		= g_sizeUSB_RESO_128_128;
		szLabel		= CSize( g_sizeUSB_RESO_128_128.cx, 16 );
		szUScale	= CSize( g_sizeUSB_RESO_128_128.cx, 8 );
		szOscill	= CSize( g_sizeUSB_RESO_128_128.cx, 64 );
		break;
	case	USB_RESO_256_256:
		szImage		= g_sizeUSB_RESO_256_256;
		szGraph		= g_sizeUSB_RESO_256_256;
		szLabel		= CSize( g_sizeUSB_RESO_256_256.cx, 32 );
		szUScale	= CSize( g_sizeUSB_RESO_256_256.cx, 16 );
		szOscill	= CSize( g_sizeUSB_RESO_256_256.cx, 64 );
		break;
	case	USB_RESO_512_512:
		szImage		= g_sizeUSB_RESO_512_512;
		szGraph		= g_sizeUSB_RESO_512_512;
		szLabel		= CSize( g_sizeUSB_RESO_512_512.cx, 64 );
		szUScale	= CSize( g_sizeUSB_RESO_512_512.cx, 40 );
		szOscill	= CSize( g_sizeUSB_RESO_512_512.cx, 128 );
		break;
	case	USB_RESO_1024_1024:
		szImage		= g_sizeUSB_RESO_1024_1024;
		szGraph		= g_sizeUSB_RESO_1024_1024;
		szLabel		= CSize( g_sizeUSB_RESO_1024_1024.cx, 64 );
		szUScale	= CSize( g_sizeUSB_RESO_1024_1024.cx, 40 );
		szOscill	= CSize( g_sizeUSB_RESO_1024_1024.cx, 128 );
		break;
	case	USB_RESO_2048_2048:
		szImage		= g_sizeUSB_RESO_2048_2048;
		szGraph		= g_sizeUSB_RESO_2048_2048;
		szLabel		= CSize( g_sizeUSB_RESO_2048_2048.cx, 128 );
		szUScale	= CSize( g_sizeUSB_RESO_2048_2048.cx, 80 );
		szOscill	= CSize( g_sizeUSB_RESO_2048_2048.cx, 256 );
		break;
	case	USB_RESO_4096_4096:
		szImage		= g_sizeUSB_RESO_4096_4096;
		szGraph		= g_sizeUSB_RESO_4096_4096;
		szLabel		= CSize( g_sizeUSB_RESO_4096_4096.cx, 256 );
		szUScale	= CSize( g_sizeUSB_RESO_4096_4096.cx, 160 );
		szOscill	= CSize( g_sizeUSB_RESO_4096_4096.cx, 512 );
		break;
	case	USB_RESO_8192_8192:
		szImage		= g_sizeUSB_RESO_8192_8192;
		szGraph		= g_sizeUSB_RESO_8192_8192;
		szLabel		= CSize( g_sizeUSB_RESO_8192_8192.cx, 512 );
		szUScale	= CSize( g_sizeUSB_RESO_8192_8192.cx, 320 );
		szOscill	= CSize( g_sizeUSB_RESO_8192_8192.cx, 1024 );
		break;
	default:
		szImage		= g_sizeUSB_RESO_2048_2048;
		szGraph		= g_sizeUSB_RESO_2048_2048;
		szLabel		= CSize( g_sizeUSB_RESO_2048_2048.cx, 128 );
		szUScale	= CSize( g_sizeUSB_RESO_2048_2048.cx, 80 );
		szOscill	= CSize( g_sizeUSB_RESO_2048_2048.cx, 256 );
		break;
	}
}
*/
CRect CMCICard::LayWindowMapClip_Image_to_Graph( CRect& rcImage )
{
	CRect	rcGrapic;
	CPoint	ptOrigin(m_rcImageWindow.left, m_rcImageWindow.top);
	
	rcImage.OffsetRect( - ptOrigin );

	//////////////////////////////////////////////////////////////////////
	rcGrapic.left = (int)(rcImage.left * m_dblScaleImageToGraph_W + 0.5);
	rcGrapic.right = (int)(rcImage.right * m_dblScaleImageToGraph_W + 0.5);
	rcGrapic.top = (int)(rcImage.top * m_dblScaleImageToGraph_H + 0.5);
	rcGrapic.bottom = (int)(rcImage.bottom * m_dblScaleImageToGraph_H + 0.5);

	rcGrapic &= CRect(0, 0, m_szGraph.cx, m_szGraph.cy);
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	rcImage.left = (int)(rcGrapic.left / m_dblScaleImageToGraph_W + 0.5);
	rcImage.right = (int)(rcGrapic.right / m_dblScaleImageToGraph_W + 0.5);
	rcImage.top = (int)(rcGrapic.top / m_dblScaleImageToGraph_H + 0.5);
	rcImage.bottom = (int)(rcGrapic.bottom / m_dblScaleImageToGraph_H + 0.5);
	//////////////////////////////////////////////////////////////////////

	rcImage.OffsetRect( ptOrigin );

	return rcGrapic;
}

CRect CMCICard::LayWindowMapClip_Graph_to_Image( CRect& rcGrapic )
{
	CRect	rcImage;
	CPoint	ptOrigin(m_rcImageWindow.left, m_rcImageWindow.top);
	
	//////////////////////////////////////////////////////////////////////
	rcImage.left = (int)(rcGrapic.left / m_dblScaleImageToGraph_W + 0.5);
	rcImage.right = (int)(rcGrapic.right / m_dblScaleImageToGraph_W + 0.5);
	rcImage.top = (int)(rcGrapic.top / m_dblScaleImageToGraph_H + 0.5);
	rcImage.bottom = (int)(rcGrapic.bottom / m_dblScaleImageToGraph_H + 0.5);
	//////////////////////////////////////////////////////////////////////

	rcImage.OffsetRect( ptOrigin );
	rcImage &= m_rcImageWindow;

	return rcImage;
}

CRect CMCICard::LayWindowMapClip_Image_to_Label( CRect& rcImage )
{
	CRect	rcGrapic = LayWindowMapClip_Image_to_Graph( rcImage );
	CPoint	ptOrigin(0, m_szGraph.cy - m_szLabel.cy);
	
	CRect	rcLabel = rcGrapic;
	rcLabel.OffsetRect( - ptOrigin );
	rcLabel &= CRect(0, 0, m_szLabel.cx, m_szLabel.cy);

	if( !rcLabel.IsRectEmpty() )
	{
		rcGrapic = rcLabel;
		rcGrapic.OffsetRect( ptOrigin );
		rcImage = LayWindowMapClip_Graph_to_Image( rcGrapic );
	}

	return rcLabel;
}

CRect CMCICard::LayWindowMapClip_Image_to_Priamry( CRect& rcImage )
{
	//////////////////////////////////////////////////////////////////////
	double	dblScaleImageToPriamry_W;
	double	dblScaleImageToPriamry_H;

	//////////////////////////////////////////////////////////////////////
	if ( m_dblZoom <= 0 )
	{
		dblScaleImageToPriamry_W = (double)m_rcScreenClientRect.Width() / m_rcImageWindow.Width();
		dblScaleImageToPriamry_H = (double)m_rcScreenClientRect.Height() / m_rcImageWindow.Height();
		m_ptScreenClientPos = CPoint(0, 0);	
	}
	else
	{
		dblScaleImageToPriamry_W = m_dblZoom;
		dblScaleImageToPriamry_H = m_dblZoom;
	}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	CRect	rcPriamry;
	CRect	rcPriamryWindow;
	CPoint	ptOrigin(m_rcImageWindow.left, m_rcImageWindow.top);

	rcPriamryWindow.left = 0;
	rcPriamryWindow.top = 0;
	rcPriamryWindow.right = (int)(m_rcImageWindow.Width() * dblScaleImageToPriamry_W + 0.5);
	rcPriamryWindow.bottom = (int)(m_rcImageWindow.Height() * dblScaleImageToPriamry_H + 0.5);
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	// Image to Priamry (Logic)
	//////////////////////////////////////////////////////////////////////
	rcImage.OffsetRect( - ptOrigin );

	rcPriamry.left = (int)(rcImage.left * dblScaleImageToPriamry_W + 0.5);
	rcPriamry.right = (int)(rcImage.right * dblScaleImageToPriamry_W + 0.5);
	rcPriamry.top = (int)(rcImage.top * dblScaleImageToPriamry_H + 0.5);
	rcPriamry.bottom = (int)(rcImage.bottom * dblScaleImageToPriamry_H + 0.5);
	rcPriamry &= rcPriamryWindow;
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	// Priamry to Client (Logic)
	//////////////////////////////////////////////////////////////////////
	CRect	rcClient = rcPriamry;
	rcClient.OffsetRect( - m_ptScreenClientPos );
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	// Client to ScreenClient
	//////////////////////////////////////////////////////////////////////
	CRect	rcScreenClient;
	CPoint	ptOriginScreenClient(m_rcScreenClientRect.left, m_rcScreenClientRect.top);

	rcScreenClient = rcClient;
	rcScreenClient.OffsetRect( ptOriginScreenClient );
	rcScreenClient &= m_rcScreenClientRect;

	CRect rcSystemScreen(0,0,
		GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	rcScreenClient &= rcSystemScreen;
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	// ScreenClient to Client
	//////////////////////////////////////////////////////////////////////
	rcClient = rcScreenClient;
	rcClient.OffsetRect( - ptOriginScreenClient );
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	// Client to Priamry
	//////////////////////////////////////////////////////////////////////
	rcPriamry = rcClient;
	rcPriamry.OffsetRect( m_ptScreenClientPos );
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	// Priamry to Image
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	rcImage.left = (int)(rcPriamry.left / dblScaleImageToPriamry_W + 0.5);
	rcImage.right = (int)(rcPriamry.right / dblScaleImageToPriamry_W + 0.5);
	rcImage.top = (int)(rcPriamry.top / dblScaleImageToPriamry_H + 0.5);
	rcImage.bottom = (int)(rcPriamry.bottom / dblScaleImageToPriamry_H + 0.5);

	rcImage.OffsetRect( ptOrigin );
	//////////////////////////////////////////////////////////////////////

	return rcScreenClient;
}

BOOL CMCICard::CopyScreenBmp( CBitmap& bmpScreen )
{
	HDC				hdc;
    HRESULT			ddrval;

	ddrval = m_lpDDSImageLay->GetDC( &hdc );
	if( ddrval == DD_OK )
	{
		CDC	dcScreen;
		
		if ( dcScreen.Attach(hdc) )
		{
			CaptureScreenRect( bmpScreen, &dcScreen, m_rcImageWindow );

			dcScreen.Detach();
			m_lpDDSImageLay->ReleaseDC(hdc);
		}
		else 
		{
			m_lpDDSImageLay->ReleaseDC(hdc);
			return FALSE;
		}
	}
	else
	{
		switch( ddrval )
		{
		case	DDERR_DCALREADYCREATED:
			DebugMessage(_T("DDERR_DCALREADYCREATED"));	
			break;
		case	DDERR_GENERIC:
			DebugMessage(_T("DDERR_GENERIC"));	
			break;
		case	DDERR_INVALIDOBJECT:
			DebugMessage(_T("DDERR_INVALIDOBJECT"));	
			break;
		case	DDERR_INVALIDPARAMS:
			DebugMessage(_T("DDERR_INVALIDPARAMS"));	
			break;
		case	DDERR_INVALIDSURFACETYPE:
			DebugMessage(_T("DDERR_INVALIDSURFACETYPE"));	
			break;
		case	DDERR_SURFACELOST:
			DebugMessage(_T("DDERR_SURFACELOST"));	
			break;
		case	DDERR_UNSUPPORTED:
			DebugMessage(_T("DDERR_UNSUPPORTED"));	
			break;
		case	DDERR_WASSTILLDRAWING:
			DebugMessage(_T("DDERR_WASSTILLDRAWING"));	
			break;
		}
	}

	return (ddrval == DD_OK);
}

BOOL CMCICard::CopyGraphBmp( CBitmap& bmpGraphLay )
{
	HDC				hdc;
    HRESULT			ddrval;

	ddrval = m_lpDDSGraphBackLay->GetDC( &hdc );
	if( ddrval == DD_OK )
	{
		CDC	dcGraph;
		
		if ( dcGraph.Attach(hdc) )
		{
			CaptureScreenRect( bmpGraphLay, &dcGraph,
				CRect(0,0,m_szGraph.cx,m_szGraph.cy) );

			dcGraph.Detach();
			m_lpDDSGraphBackLay->ReleaseDC(hdc);
		}
		else 
		{
			m_lpDDSGraphBackLay->ReleaseDC(hdc);
			return FALSE;
		}
	}

	return (ddrval == DD_OK);
}

HDIB CMCICard::CopyImageDib()
{
	CRect rcImageWindow = m_rcImageWindow;	//GetImageWindow();
	const CSize szImageSize(rcImageWindow.Width(), rcImageWindow.Height());

	DWORD			dwBitsSize;
	DWORD			dwOffBits;
	HDIB			hDIB;
	LPSTR			pDIB;
	LPBITMAPINFO 	pDibInfo;
	LPSTR	 		pDibBits;
	BYTE			bGrey;
	int				i;

	// Calculate the size of memory for hDIB.
	dwOffBits = sizeof(BITMAPINFO);											// BITMAPINFO
	dwOffBits += sizeof(RGBQUAD) * 255;										// Palette ( RGBQUAD area )
	dwBitsSize = WIDTHBYTES( szImageSize.cx * 8L ) * (DWORD)szImageSize.cy;	// Image bits

	// Allocate memory for DIB.
	hDIB = (HDIB) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize + dwOffBits);
	if (hDIB == 0)
	{
		return NULL;
	}
	pDIB		= (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
	pDibInfo	= (BITMAPINFO *)pDIB;	
	pDibBits	= &( pDIB[dwOffBits] );

	// Setup BITMAPINFOHEAD.
	pDibInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	pDibInfo->bmiHeader.biWidth			= WIDTHBYTES( szImageSize.cx * 8 ); 
	pDibInfo->bmiHeader.biHeight		= szImageSize.cy; 
	pDibInfo->bmiHeader.biPlanes		= 1;
	pDibInfo->bmiHeader.biBitCount		= 8;
	pDibInfo->bmiHeader.biCompression	= 0;
	pDibInfo->bmiHeader.biSizeImage		= dwBitsSize;
	pDibInfo->bmiHeader.biXPelsPerMeter	= 0;
	pDibInfo->bmiHeader.biYPelsPerMeter	= 0;
	pDibInfo->bmiHeader.biClrUsed		= 0;
	pDibInfo->bmiHeader.biClrImportant	= 0;

	// Image-lay pallete
	for (i=0; i<256; i++)
	{ 
		bGrey = (BYTE)i;
		pDibInfo->bmiColors[i].rgbRed		= bGrey;
		pDibInfo->bmiColors[i].rgbGreen		= bGrey;
		pDibInfo->bmiColors[i].rgbBlue		= bGrey;
		pDibInfo->bmiColors[i].rgbReserved	= (BYTE)0;
	}

	// Fill the bits.
	ImageDibCopy( pDibBits, dwBitsSize, rcImageWindow );
	
	::GlobalUnlock((HGLOBAL) hDIB);

	return hDIB;
}

