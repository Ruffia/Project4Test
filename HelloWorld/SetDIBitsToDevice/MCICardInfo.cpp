// MCICard.cpp : implementation file
//

#include "stdafx.h"
#include "Ddutil.h"
#include "MCICard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMCICard

BOOL CMCICard::ShowFrameRate(BOOL boolShow)
{
	m_boolShowFrameRate = boolShow;

	return boolShow;
}

// InitNumSurface
//
long CMCICard::InitNumSurface()
{
    HDC				hdc;
    RECT			rc;
    int				len;
    HRESULT         ddrval = DD_OK;

    m_dwFramesLast = 0;

    len = _stprintf( m_szFrameRate, m_szFPS, 0, 0, 0 );

	if( m_lpDDSFrameRate != NULL )
	{
		ddrval = m_lpDDSFrameRate->GetDC( &hdc );
		if( ddrval == DD_OK )
		{
			SelectObject(hdc, m_hFontFrameRate);
			SetTextColor(hdc, m_sysOpt.color[SysOpt_clrFrameRate]);
			SetBkColor(hdc, m_sysOpt.color[SysOpt_clrTransparent]);
			SetBkMode(hdc, OPAQUE);
			SetRect(&rc, 0, 0, 10000, 10000);
			ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rc, m_szFrameRate, len, NULL);
			GetTextExtentPoint(hdc, m_szFrameRate, 4, &m_sizeFPS);
			m_iFrameRateX = m_sizeFPS.cx;
			GetTextExtentPoint(hdc, m_szFrameRate, 12, &m_sizeFPS);
			m_iBpsRateX = m_sizeFPS.cx;
			GetTextExtentPoint(hdc, m_szFrameRate, 22, &m_sizeFPS);
			m_iIPSRateX = m_sizeFPS.cx;
			GetTextExtentPoint(hdc, m_szFrameRate, len, &m_sizeFPS);

			m_lpDDSFrameRate->ReleaseDC(hdc);
		}
	}

	return ddrval;
} // InitNumSurface

//
// InitFrameRate
//
BOOL CMCICard::InitFrameRate()
{
	///////////////////////////////////////////
//	if (!m_boolShowFrameRate)
//		return TRUE;
	///////////////////////////////////////////

    HRESULT             ddrval;
    HDC             	hdc;

    if (m_hFontFrameRate != NULL)
    {
        DeleteObject(m_hFontFrameRate);
    }

    m_hFontFrameRate = CreateFont(
        24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        _T("Arial") );

    //
    // make a sample string so we can measure it with the current font.
    //
    if (m_hFontFrameRate != NULL)
    {
        InitNumSurface();

        hdc = GetDC(NULL);
        SelectObject(hdc, m_hFontFrameRate);
        GetTextExtentPoint(hdc, m_szFrameRate, lstrlen(m_szFrameRate), &m_sizeFPS);
        ReleaseDC(NULL, hdc);
    }
    
	//
    // Create a surface to copy our bits to.
    //
    DDSURFACEDESC			ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize			= sizeof(ddsd);
    ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth		= m_sizeFPS.cx;
    ddsd.dwHeight		= m_sizeFPS.cy;

	DWORD dwFrameMemSize = ddsd.dwWidth * ddsd.dwHeight;
	if ( (m_dwFrameMemSizeUsed + dwFrameMemSize) > m_dwVidMemTotal )
	{
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}
	else
	{
		m_dwFrameMemSizeUsed += dwFrameMemSize;
	}

    ddrval = m_lpDD->CreateSurface( &ddsd, &m_lpDDSFrameRate, NULL );
    if ( ddrval != DD_OK )
	{
 		m_lpDDSFrameRate = NULL;
		return FALSE;
	}

	/*
	DWORD dwColorKey = DDColorMatch(m_lpDDSFrameRate, m_colorTransparent);

    if (m_blSrcColorkey)
    {
		DDCOLORKEY		ddck;
        ddck.dwColorSpaceLowValue	= dwColorKey;
        ddck.dwColorSpaceHighValue	= dwColorKey;
        m_lpDDSFrameRate->SetColorKey( DDCKEY_SRCBLT, &ddck );
    }
	*/

    // now draw the text for real
    InitNumSurface();

    return TRUE;
}

//
// FormatFrameRate
//
long CMCICard::FormatFrameRate()
{
	///////////////////////////////////////////
	if (!m_boolShowFrameRate)
		return DD_OK;
	///////////////////////////////////////////

    DWORD               time2;
    TCHAR                buff[256];
    TCHAR                buff_bps[256];
    TCHAR                buff_ips[256];
    HDC                 hdc;
    HRESULT             ddrval;
    CRect               rcFrameRate;
	BOOL				blUpdate = FALSE;
    DWORD               dwKBPS;

    m_dwFrameCount++;
    time2 = timeGetTime() - m_dwFrameTime;
    if( time2 > 1000 )
    {
        m_dwFrames = (m_dwFrameCount*1000)/time2;
        m_dwFrameTime = timeGetTime();
        m_dwFrameCount = 0;

        m_dwAveFrameRate += m_dwFrames;
        m_dwAveFrameRateCount++;

		m_dwBytes		= (m_dwByteCount*1000)/time2;
		m_dwByteCount	= 0;

		m_dwInputs		= (m_dwInputCount*1000)/time2;
		m_dwInputCount	= 0;
    }

    if( m_dwFrames != 0 )
    {
		if( m_dwBytes != m_dwBytesLast )
		{
			m_dwBytesLast = m_dwBytes;
			blUpdate = TRUE;
		}
		if( m_dwFrames != m_dwFramesLast )
		{
			m_dwFramesLast = m_dwFrames;
			blUpdate = TRUE;
		}
		if( m_dwInputs != m_dwInputsLast )
		{
			m_dwInputsLast = m_dwInputs;
			blUpdate = TRUE;
		}
	}

	if ( blUpdate )
	{
		ddrval = m_lpDDSFrameRate->GetDC( &hdc );
		if( ddrval == DD_OK )
        {
			if( m_dwFrames > 999 )
			{
				buff[0] = (char)('9');
				buff[1] = (char)('9');
				buff[2] = (char)('9');
			}
			else if( m_dwFrames > 99 )
			{
				buff[0] = (char)((m_dwFrames / 100)     + '0');
				buff[1] = (char)((m_dwFrames / 10) % 10 + '0');
				buff[2] = (char)((m_dwFrames % 10)      + '0');
			}
			else if( m_dwFrames > 9 )
			{
				buff[0] = (char)('0');
				buff[1] = (char)((m_dwFrames / 10) + '0');
				buff[2] = (char)((m_dwFrames % 10) + '0');
			}
			else
			{
				buff[0] = (char)('0');
				buff[1] = (char)('0');
				buff[2] = (char)((m_dwFrames % 10) + '0');
			}
			//sprintf( buff, "%3d", dwFrames );

			if( m_dwInputs > 999 )
			{
				buff_ips[0] = (char)('9');
				buff_ips[1] = (char)('9');
				buff_ips[2] = (char)('9');
			}
			else if( m_dwInputs > 99 )
			{
				buff_ips[0] = (char)((m_dwInputs / 100)     + '0');
				buff_ips[1] = (char)((m_dwInputs / 10) % 10 + '0');
				buff_ips[2] = (char)((m_dwInputs % 10)      + '0');
			}
			else if( m_dwInputs > 9 )
			{
				buff_ips[0] = (char)('0');
				buff_ips[1] = (char)((m_dwInputs / 10) + '0');
				buff_ips[2] = (char)((m_dwInputs % 10) + '0');
			}
			else
			{
				buff_ips[0] = (char)('0');
				buff_ips[1] = (char)('0');
				buff_ips[2] = (char)((m_dwInputs % 10) + '0');
			}

			dwKBPS = m_dwBytesLast / 1024;
			if( dwKBPS > 9999 )
			{
				buff_bps[0] = (char)('9');
				buff_bps[1] = (char)('9');
				buff_bps[2] = (char)('9');
				buff_bps[3] = (char)('9');
			}
			else if( dwKBPS > 999 )
			{
				buff_bps[0] = (char)((dwKBPS / 1000)		+ '0');
				buff_bps[1] = (char)((dwKBPS / 100) % 10	+ '0');
				buff_bps[2] = (char)((dwKBPS / 10) % 10		+ '0');
				buff_bps[3] = (char)((dwKBPS % 10)			+ '0');
			}
			else if( dwKBPS > 99 )
			{
				buff_bps[0] = (char)('0');
				buff_bps[1] = (char)((dwKBPS / 100)			+ '0');
				buff_bps[2] = (char)((dwKBPS / 10) % 10		+ '0');
				buff_bps[3] = (char)((dwKBPS % 10)			+ '0');
			}
			else if( dwKBPS > 9 )
			{
				buff_bps[0] = (char)('0');
				buff_bps[1] = (char)('0');
				buff_bps[2] = (char)((dwKBPS / 10)			+ '0');
				buff_bps[3] = (char)((dwKBPS % 10)			+ '0');
			}
			else
			{
				buff_bps[0] = (char)('0');
				buff_bps[1] = (char)('0');
				buff_bps[2] = (char)('0');
				buff_bps[3] = (char)((dwKBPS % 10)			+ '0');
			}

					
            if(m_hFontFrameRate != NULL)
            {
                SelectObject(hdc, m_hFontFrameRate);
                SetTextColor(hdc, m_sysOpt.color[SysOpt_clrFrameRate]);
                SetBkColor(hdc, m_sysOpt.color[SysOpt_clrTransparent]);
                TextOut(hdc, m_iFrameRateX, 0, buff, 3);
                TextOut(hdc, m_iBpsRateX, 0, buff_bps, 4);
                TextOut(hdc, m_iIPSRateX, 0, buff_ips, 3);
            }
            m_lpDDSFrameRate->ReleaseDC(hdc);
        }		
		return ddrval;
	}

    return DD_OK;
} // FormatFrameRate

long CMCICard::UpdateFrameRateLay()
{
	///////////////////////////////////////////
	if (!m_boolShowFrameRate)
		return DD_OK;
	///////////////////////////////////////////

    HRESULT             ddrval = DD_OK;
	/////////////////////////////////////////////////////////////////////////
	CPoint pos;
	pos.x = (m_szGraph.cx - m_sizeFPS.cx) / 2;
	pos.y = 20;

	CRect rcSrcGrapic	= CRect(0, 0, m_sizeFPS.cx, m_sizeFPS.cy) + pos;
	CRect rcDestImage	= LayWindowMapClip_Graph_to_Image( rcSrcGrapic );

	CRect rcSrcFrameRate = rcSrcGrapic;
	rcSrcFrameRate.OffsetRect( - pos );
	rcSrcFrameRate &= CRect(0, 0, m_sizeFPS.cx, m_sizeFPS.cy);

	if ( !rcDestImage.IsRectEmpty() )
	{
		if ( !IsReady() )
			return DD_OK;

		ddrval = m_lpDDSImageLay->Blt(
			(LPRECT)rcDestImage,	// dest rect
			m_lpDDSFrameRate,		// src surface
			(LPRECT)rcSrcFrameRate,	// src rect
			DDBLT_WAIT,
			NULL);

	}
	/////////////////////////////////////////////////////////////////////////

	return ddrval;
}

