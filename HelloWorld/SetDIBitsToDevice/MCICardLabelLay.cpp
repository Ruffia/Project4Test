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

BOOL CMCICard::ShowLabel(BOOL boolShow)
{
	if ( m_boolShowLabel == boolShow )
		return m_boolShowLabel;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	CRect rcGrapic = CRect(0, m_szGraph.cy - m_szLabel.cy,
							m_szGraph.cx, m_szGraph.cy);
	CRect rcImage = LayWindowMapClip_Graph_to_Image( rcGrapic );

	if ( m_boolShowLabel == TRUE )
	{	
		m_UpdateRectsImage.Add( rcImage );
	}
	else
	{
		m_UpdateRectsLabel.Add( rcImage );
	}

	m_boolShowLabel = boolShow;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////

	return m_boolShowLabel;
}

BOOL CMCICard::ShowTime(BOOL boolShow)
{
	if ( m_boolShowTime == boolShow )
		return m_boolShowTime;
	m_boolShowTime = boolShow;
	if( m_boolShowLabel )
		RedrawLabelLay();
	return TRUE;
}

BOOL CMCICard::ShowNote(BOOL boolShow)
{
	if ( m_boolShowNote == boolShow )
		return m_boolShowNote;
	m_boolShowNote = boolShow;
	if( m_boolShowLabel )
		RedrawLabelLay();
	return TRUE;
}

BOOL CMCICard::InitLabelLay()
{
	if( m_sizeReso.cx < 128+1 )
		InitLabelLay_0128();
	else if( m_sizeReso.cx < 384+1 )
		InitLabelLay_0256();
	else if( m_sizeReso.cx < 480+1 )
		InitLabelLay_0480();
	else if( m_sizeReso.cx < 600+1 )
		InitLabelLay_0512();
	else if( m_sizeReso.cx < 640+1 )
		InitLabelLay_0640();
	else if( m_sizeReso.cx < 800+1 )
		InitLabelLay_0800();
	else if( m_sizeReso.cx < 1280+1 )
		InitLabelLay_1024();
	else if( m_sizeReso.cx < 1536+1 )
		InitLabelLay_1440();
	else if( m_sizeReso.cx < 2048+1 )
		InitLabelLay_2048();
	else
		InitLabelLay_4096();
	RedrawLabelLay();

	return TRUE;
}

void CMCICard::InitLabelLay_0128()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");			// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csWD				= _T("12.0 mm");
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 40;

	/////////////////////////////////////////////////
// 	m_ptHV				= CPoint(1,		10);		// 高压显示位置
// 	m_ptMag				= CPoint(24,	10);		// 放大倍数显示位置
// 	m_ptUScal			= CPoint(48,	10);		// 固定标尺显示位置
// 	m_ptLogo			= CPoint(64,	10);		// 产品标识显示位置
// 	m_ptPhotoSN			= CPoint(110,	10);		// 照相编号显示位置
	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        8, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        _T("Arial") );//m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        8, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        _T("Arial") );//m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelLogoText = CreateFont(
        8, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        _T("Arial") );//m_sysOpt.fName[SysOpt_nameEditText] );
	/////////////////////////////////////////////////
}

void CMCICard::InitLabelLay_0256()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");				// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csTime			= _T("2017.08.22 17:05");	// 日期时间显示
	m_csWD				= _T("12.0 mm");			// 工作距离显示
	m_csNote			= _T("KYKY Sample");		// 备注显示
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 80;

/*	/////////////////////////////////////////////////
	m_ptHV				= CPoint(0,		1);
	m_ptMag				= CPoint(56,	1);
	m_ptWD				= CPoint(0,		16);
	m_ptSG				= CPoint(56,	16);
	m_ptUScal			= CPoint(110,	1);
	m_ptLogo			= CPoint(110,	16);
	m_ptTime			= CPoint(220,	1);
	m_ptNote			= CPoint(220,	16);
*/	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        7, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        7, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );

    m_hfontLabelLogoText = CreateFont(
        7, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );
	/////////////////////////////////////////////////
}

void CMCICard::InitLabelLay_0384()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");				// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csTime			= _T("2017.08.22 17:05");	// 日期时间显示
	m_csWD				= _T("12.0 mm");			// 工作距离显示
	m_csNote			= _T("KYKY Sample");		// 备注显示
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 80;

/*	/////////////////////////////////////////////////
	m_ptHV				= CPoint(4,		1);
	m_ptMag				= CPoint(90,	1);
	m_ptWD				= CPoint(4,		16);
	m_ptSG				= CPoint(90,	16);
	m_ptUScal			= CPoint(175,	1);
	m_ptLogo			= CPoint(175,	16);
	m_ptTime			= CPoint(350,	1);
	m_ptNote			= CPoint(350,	16);
*/	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        12, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        12, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );

    m_hfontLabelLogoText = CreateFont(
        12, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );
	/////////////////////////////////////////////////
}
void CMCICard::InitLabelLay_0480()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");				// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csTime			= _T("2017.08.22 17:05");	// 日期时间显示
	m_csWD				= _T("12.0 mm");			// 工作距离显示
	m_csNote			= _T("KYKY Sample");		// 备注显示
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 80;

/*	/////////////////////////////////////////////////
	m_ptHV				= CPoint(8,		1);
	m_ptMag				= CPoint(120,	1);
	m_ptWD				= CPoint(8,		16);
	m_ptSG				= CPoint(120,	16);
	m_ptUScal			= CPoint(220,	1);
	m_ptLogo			= CPoint(220,	16);
	m_ptTime			= CPoint(350,	1);
	m_ptNote			= CPoint(350,	16);
*/	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        12, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        12, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );

    m_hfontLabelLogoText = CreateFont(
        12, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );
	/////////////////////////////////////////////////
}

void CMCICard::InitLabelLay_0512()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");			// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csTime			= _T("2017.08.22 17:05");	// 日期时间显示
	m_csWD				= _T("12.0 mm");			// 工作距离显示
	m_csNote			= _T("KYKY Sample");		// 备注显示
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 100;

/*	/////////////////////////////////////////////////
	m_ptHV				= CPoint(8,		2);
	m_ptMag				= CPoint(120,	2);
	m_ptWD				= CPoint(8,		24);
	m_ptSG				= CPoint(120,	24);
	m_ptUScal			= CPoint(232,	2);
	m_ptLogo			= CPoint(232,	24);
	m_ptTime			= CPoint(350,	2);
	m_ptNote			= CPoint(350,	24);
*/	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        16, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        16, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );

    m_hfontLabelLogoText = CreateFont(
        16, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );
	/////////////////////////////////////////////////
}

void CMCICard::InitLabelLay_0640()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");			// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csTime			= _T("2017.08.22 17:05");	// 日期时间显示
	m_csWD				= _T("12.0 mm");			// 工作距离显示
	m_csNote			= _T("KYKY Sample");		// 备注显示
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 100;

/*	/////////////////////////////////////////////////
	m_ptHV				= CPoint(16,	2);
	m_ptMag				= CPoint(160,	2);
	m_ptWD				= CPoint(16,	22);
	m_ptSG				= CPoint(160,	22);
	m_ptUScal			= CPoint(300,	2);
	m_ptLogo			= CPoint(300,	22);
	m_ptTime			= CPoint(440,	2);
	m_ptNote			= CPoint(440,	22);
*/	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        16, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        20, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );

    m_hfontLabelLogoText = CreateFont(
        20, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );
	/////////////////////////////////////////////////
}

void CMCICard::InitLabelLay_0800()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");				// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csTime			= _T("2017.08.22 17:05");	// 日期时间显示
	m_csWD				= _T("12.0 mm");			// 工作距离显示
	m_csNote			= _T("KYKY Sample");		// 备注显示
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 100;

/*	/////////////////////////////////////////////////
	m_ptHV				= CPoint(16,	2);
	m_ptMag				= CPoint(200,	2);
	m_ptWD				= CPoint(16,	24);
	m_ptSG				= CPoint(200,	24);
	m_ptUScal			= CPoint(400,	2);
	m_ptLogo			= CPoint(400,	24);
	m_ptTime			= CPoint(580,	2);
	m_ptNote			= CPoint(580,	24);
*/	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        20, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        20, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );

    m_hfontLabelLogoText = CreateFont(
        20, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );
	/////////////////////////////////////////////////
}

void CMCICard::InitLabelLay_1024()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");			// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csTime			= _T("2017.08.22 17:05");	// 日期时间显示
	m_csWD				= _T("12.0 mm");			// 工作距离显示
	m_csNote			= _T("KYKY Sample");		// 备注显示
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 100;

/*	/////////////////////////////////////////////////
	m_ptHV				= CPoint(16,	2);
	m_ptMag				= CPoint(240,	2);
	m_ptWD				= CPoint(16,	34);
	m_ptSG				= CPoint(240,	34);
	m_ptUScal			= CPoint(480,	2);
	m_ptLogo			= CPoint(480,	34);
	m_ptTime			= CPoint(736,	2);
	m_ptNote			= CPoint(736,	34);
*/	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        m_sysOpt.fSize[SysOpt_nameEditText], 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        m_sysOpt.fSize[SysOpt_nameLabelText]/*Label_nFontSize*/, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );

    m_hfontLabelLogoText = CreateFont(
        m_sysOpt.fSize[SysOpt_nameLabelText]/*Logo_nFontSize*/, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );
	/////////////////////////////////////////////////
}

void CMCICard::InitLabelLay_1440()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");			// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csTime			= _T("2017.08.22 17:05");	// 日期时间显示
	m_csWD				= _T("12.0 mm");			// 工作距离显示
	m_csNote			= _T("KYKY Sample");		// 备注显示
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 200;

/*	/////////////////////////////////////////////////
	m_ptHV				= CPoint(24,	2);
	m_ptMag				= CPoint(340,	2);
	m_ptWD				= CPoint(24,	48);
	m_ptSG				= CPoint(340,	48);
	m_ptUScal			= CPoint(680,	2);
	m_ptLogo			= CPoint(680,	48);
	m_ptTime			= CPoint(940,	2);
	m_ptNote			= CPoint(940,	48);
*/	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        40, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        48, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );

    m_hfontLabelLogoText = CreateFont(
        48, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );
	/////////////////////////////////////////////////
}

void CMCICard::InitLabelLay_2048()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");			// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csTime			= _T("2017.08.22 17:05");	// 日期时间显示
	m_csWD				= _T("12.0 mm");			// 工作距离显示
	m_csNote			= _T("KYKY Sample");		// 备注显示
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 200;

/*	/////////////////////////////////////////////////
	m_ptHV				= CPoint(48,	5);
	m_ptMag				= CPoint(500,	5);
	m_ptWD				= CPoint(48,	64);
	m_ptSG				= CPoint(500,	64);
	m_ptUScal			= CPoint(1000,	5);
	m_ptLogo			= CPoint(1000,	64);
	m_ptTime			= CPoint(1500,	5);
	m_ptNote			= CPoint(1500,	64);
*/	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        60, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        64, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );

    m_hfontLabelLogoText = CreateFont(
        64, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );
	/////////////////////////////////////////////////
}

void CMCICard::InitLabelLay_4096()
{
	/////////////////////////////////////////////////
	m_csHV				= _T("0.0 KV");				// 高压显示
	m_csMag				= _T("250 X");				// 放大倍数显示
	m_csUScal			= _T("100 μm");				// 固定标尺显示
	m_csLogo			= _T("KYKY-EM6200");		// 产品标识显示
	m_csPhotoSN			= _T("SN:0000");			// 照相编号显示
	m_csTime			= _T("2017.08.22 17:05");	// 日期时间显示
	m_csWD				= _T("12.0 mm");			// 工作距离显示
	m_csNote			= _T("KYKY Sample");		// 备注显示
	/////////////////////////////////////////////////

	m_nUScalePixelNum	= 400;

/*	/////////////////////////////////////////////////
	m_ptHV				= CPoint(40,	5);
	m_ptMag				= CPoint(1000,	5);
	m_ptWD				= CPoint(40,	120);
	m_ptSG				= CPoint(1000,	120);
	m_ptUScal			= CPoint(2000,	5);
	m_ptLogo			= CPoint(2000,	120);
	m_ptTime			= CPoint(3000,	5);
	m_ptNote			= CPoint(3000,	120);
*/	/////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Create Font
	/////////////////////////////////////////////////
    if (m_hfontEditText != NULL)
        DeleteObject(m_hfontEditText);

    if (m_hfontLabelText != NULL)
        DeleteObject(m_hfontLabelText);

    if (m_hfontLabelLogoText != NULL)
        DeleteObject(m_hfontLabelLogoText);

    m_hfontEditText = CreateFont(
        100, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameEditText] );

    m_hfontLabelText = CreateFont(
        120, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );

    m_hfontLabelLogoText = CreateFont(
        120, 0, 0, 0, c_fnWeight, FALSE, FALSE, FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,	// NONANTIALIASED_QUALITY,
        VARIABLE_PITCH,
        m_sysOpt.fName[SysOpt_nameLabelText] );
	/////////////////////////////////////////////////
}

long CMCICard::RedrawLabelLay()
{
	HDC				hdc;
    HRESULT			ddrval;

	/////////////////////////////////////////////////////////////////
	if ( m_lpDDSLabelLay == NULL ) return DD_OK;
	ddrval = m_lpDDSLabelLay->GetDC( &hdc );
	if( ddrval != DD_OK )
		return ddrval;
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	COLORREF clrBack;
	if( m_sysOpt.nShowParams[SysOpt_showLabelTrans] )
		clrBack = g_clrUSB_Transparent;
	else
		clrBack	= m_sysOpt.color[SysOpt_clrBack];
	HBRUSH brBackBrush = CreateSolidBrush( clrBack );
	CRect rcFill = CRect(0,0,m_szLabel.cx,m_szLabel.cy);
	FillRect( hdc, (LPRECT)rcFill, brBackBrush );
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	int nOffsetX;
	if( m_bSplit )
		nOffsetX	= m_szGraph.cx /2;
	else
		nOffsetX	= 0;
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	int nLineWidth;
	switch( m_sizeReso.cx )
	{
	case	256:
	case	384:
	case	480:
	case	512:
		nLineWidth	= 1;
		break;
	case	600:
	case	640:
	case	768:
	case	800:
		nLineWidth	= 1;
		break;
	case	1024:
		nLineWidth	= 1;
		break;
	case	1280:
	case	1440:
	case	1536:
		nLineWidth	= 2;
		break;
	case	2048:
		nLineWidth	= 5;
		break;
	case	4096:
		nLineWidth	= 10;
		break;
	default:
		nLineWidth	= 1;
		break;
	}
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, nLineWidth, m_sysOpt.color[SysOpt_clrLabelText]);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	if( m_footerOpt.opt[Footer_UBAR].bVisible )
	{
		CPoint ptPos0(1,12);
		CPoint ptPos1(1,12);
		switch( m_sizeReso.cx )
		{
		case	128:
			ptPos0.y = 5;
			ptPos1.y = 5;
			break;
		case	256:
			ptPos0.y = 10;
			ptPos1.y = 10;
			break;
		case	512:
		case	1024:
			ptPos0.y = 16;
			ptPos1.y = 16;
			break;
		case	2048:
			ptPos0.y = 24;
			ptPos1.y = 24;
			break;
		case	4096:
			ptPos0.y = 48;
			ptPos1.y = 48;
			break;
		default:
			ptPos0.y = 10;
			ptPos1.y = 10;
			break;
		}
		ptPos0.x = m_footerOpt.opt[Footer_UBAR].ptPos.x;;
		ptPos1.x = ptPos0.x + m_nUScalePixelNum;

	#ifdef GRAPHIC_BLACK
//		MoveToEx ( hdc, ptPos0.x, ptPos0.y-2, NULL );
//		LineTo ( hdc, ptPos1.x, ptPos1.y-2 );
		MoveToEx ( hdc, ptPos0.x, ptPos0.y-1, NULL );
		LineTo ( hdc, ptPos1.x, ptPos1.y-1 );
		MoveToEx ( hdc, ptPos0.x, ptPos0.y, NULL );
		LineTo ( hdc, ptPos1.x, ptPos1.y );
		MoveToEx ( hdc, ptPos0.x, ptPos0.y+1, NULL );
		LineTo ( hdc, ptPos1.x, ptPos1.y+1 );
//		MoveToEx ( hdc, ptPos0.x, ptPos0.y+2, NULL );
//		LineTo ( hdc, ptPos1.x, ptPos1.y+2 );

		MoveToEx ( hdc, ptPos0.x-1, ptPos0.y-6, NULL );
		LineTo ( hdc, ptPos0.x-1, ptPos0.y+7 );
		MoveToEx ( hdc, ptPos0.x, ptPos0.y-6, NULL );
		LineTo ( hdc, ptPos0.x, ptPos0.y+7 );
//		MoveToEx ( hdc, ptPos0.x+1, ptPos0.y-6, NULL );
//		LineTo ( hdc, ptPos0.x+1, ptPos0.y+7 );

//		MoveToEx ( hdc, ptPos1.x-1, ptPos1.y-6, NULL );
//		LineTo ( hdc, ptPos1.x-1, ptPos1.y+7 );
		MoveToEx ( hdc, ptPos1.x, ptPos1.y-6, NULL );
		LineTo ( hdc, ptPos1.x, ptPos1.y+7 );
		MoveToEx ( hdc, ptPos1.x+1, ptPos1.y-6, NULL );
		LineTo ( hdc, ptPos1.x+1, ptPos1.y+7 );

		if( m_bSplit )
		{
			ptPos0.x += nOffsetX;
			ptPos1.x += nOffsetX;

//			MoveToEx ( hdc, ptPos0.x, ptPos0.y-2, NULL );
//			LineTo ( hdc, ptPos1.x, ptPos1.y-2 );
			MoveToEx ( hdc, ptPos0.x, ptPos0.y-1, NULL );
			LineTo ( hdc, ptPos1.x, ptPos1.y-1 );
			MoveToEx ( hdc, ptPos0.x, ptPos0.y, NULL );
			LineTo ( hdc, ptPos1.x, ptPos1.y );
			MoveToEx ( hdc, ptPos0.x, ptPos0.y+1, NULL );
			LineTo ( hdc, ptPos1.x, ptPos1.y+1 );
//			MoveToEx ( hdc, ptPos0.x, ptPos0.y+2, NULL );
//			LineTo ( hdc, ptPos1.x, ptPos1.y+2 );

			MoveToEx ( hdc, ptPos0.x-1, ptPos0.y-6, NULL );
			LineTo ( hdc, ptPos0.x-1, ptPos0.y+7 );
			MoveToEx ( hdc, ptPos0.x, ptPos0.y-6, NULL );
			LineTo ( hdc, ptPos0.x, ptPos0.y+7 );
//			MoveToEx ( hdc, ptPos0.x+1, ptPos0.y-6, NULL );
//			LineTo ( hdc, ptPos0.x+1, ptPos0.y+7 );

//			MoveToEx ( hdc, ptPos1.x-1, ptPos1.y-6, NULL );
//			LineTo ( hdc, ptPos1.x-1, ptPos1.y+7 );
			MoveToEx ( hdc, ptPos1.x, ptPos1.y-6, NULL );
			LineTo ( hdc, ptPos1.x, ptPos1.y+7 );
			MoveToEx ( hdc, ptPos1.x+1, ptPos1.y-6, NULL );
			LineTo ( hdc, ptPos1.x+1, ptPos1.y+7 );
		}

	#else
		MoveToEx ( hdc, ptPos0.x, ptPos0.y-1, NULL );
		LineTo ( hdc, ptPos1.x, ptPos1.y-1 );
		MoveToEx ( hdc, ptPos0.x, ptPos0.y, NULL );
		LineTo ( hdc, ptPos1.x, ptPos1.y );
		MoveToEx ( hdc, ptPos0.x, ptPos0.y+1, NULL );
		LineTo ( hdc, ptPos1.x, ptPos1.y+1 );

		MoveToEx ( hdc, ptPos0.x, ptPos0.y-3, NULL );
		LineTo ( hdc, ptPos0.x, ptPos0.y+4 );
		MoveToEx ( hdc, ptPos0.x+1, ptPos0.y-3, NULL );
		LineTo ( hdc, ptPos0.x+1, ptPos0.y+4 );

		MoveToEx ( hdc, ptPos1.x, ptPos1.y-3, NULL );
		LineTo ( hdc, ptPos1.x, ptPos1.y+4 );
		MoveToEx ( hdc, ptPos1.x+1, ptPos1.y-3, NULL );
		LineTo ( hdc, ptPos1.x+1, ptPos1.y+4 );

		if( m_bSplit )
		{
			ptPos0.x += nOffsetX;
			ptPos1.x += nOffsetX;

			MoveToEx ( hdc, ptPos0.x, ptPos0.y-1, NULL );
			LineTo ( hdc, ptPos1.x, ptPos1.y-1 );
			MoveToEx ( hdc, ptPos0.x, ptPos0.y, NULL );
			LineTo ( hdc, ptPos1.x, ptPos1.y );
			MoveToEx ( hdc, ptPos0.x, ptPos0.y+1, NULL );
			LineTo ( hdc, ptPos1.x, ptPos1.y+1 );

			MoveToEx ( hdc, ptPos0.x, ptPos0.y-3, NULL );
			LineTo ( hdc, ptPos0.x, ptPos0.y+4 );
			MoveToEx ( hdc, ptPos0.x+1, ptPos0.y-3, NULL );
			LineTo ( hdc, ptPos0.x+1, ptPos0.y+4 );

			MoveToEx ( hdc, ptPos1.x, ptPos1.y-3, NULL );
			LineTo ( hdc, ptPos1.x, ptPos1.y+4 );
			MoveToEx ( hdc, ptPos1.x+1, ptPos1.y-3, NULL );
			LineTo ( hdc, ptPos1.x+1, ptPos1.y+4 );
		}
	#endif
		SelectObject(hdc, hPenOld);
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	SetTextAlign(hdc, TA_TOP | TA_LEFT);
	SIZE szText;
	CString str;
	if(m_hfontLabelText != NULL)
	{
		SelectObject(hdc, m_hfontLabelText);
		SetTextColor(hdc, m_sysOpt.color[SysOpt_clrLabelText]);
		SetBkColor(hdc, clrBack);

		if( m_footerOpt.opt[Footer_HV].bVisible )
		{
			str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_HV].strDisp, m_csHV );
			TextOut(hdc, m_footerOpt.opt[Footer_HV].ptPos.x, m_footerOpt.opt[Footer_HV].ptPos.y, (LPCTSTR)str, str.GetLength());
		}
		if( m_footerOpt.opt[Footer_MAG].bVisible )
		{
			str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_MAG].strDisp, m_csMag );
			TextOut(hdc, m_footerOpt.opt[Footer_MAG].ptPos.x, m_footerOpt.opt[Footer_MAG].ptPos.y, (LPCTSTR)str, str.GetLength());
		}
		if( m_footerOpt.opt[Footer_WD].bVisible )
		{
			str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_WD].strDisp, m_csWD );
			TextOut(hdc, m_footerOpt.opt[Footer_WD].ptPos.x, m_footerOpt.opt[Footer_WD].ptPos.y, (LPCTSTR)str, str.GetLength());
		}
		if( m_footerOpt.opt[Footer_VAC].bVisible )
		{
			str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_VAC].strDisp, m_csVAC );
			TextOut(hdc, m_footerOpt.opt[Footer_VAC].ptPos.x, m_footerOpt.opt[Footer_VAC].ptPos.y, (LPCTSTR)str, str.GetLength());
		}
		if( m_footerOpt.opt[Footer_DET].bVisible )
		{
			if( m_bDet2nd )	// 只看第二通道时
			{
				str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_DET].strDisp, m_csSG2 );
				TextOut(hdc, m_footerOpt.opt[Footer_DET].ptPos.x, m_footerOpt.opt[Footer_DET].ptPos.y, (LPCTSTR)str, str.GetLength());
			}
			else
			{
				str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_DET].strDisp, m_csSG1 );
				TextOut(hdc, m_footerOpt.opt[Footer_DET].ptPos.x, m_footerOpt.opt[Footer_DET].ptPos.y, (LPCTSTR)str, str.GetLength());
			}
		}
		if( m_footerOpt.opt[Footer_UBAR].bVisible )
		{
			GetTextExtentPoint( hdc, (LPCTSTR)m_csUScal, m_csUScal.GetLength(), &szText );
			TextOut(hdc, m_footerOpt.opt[Footer_UBAR].ptPos.x +(m_nUScalePixelNum -szText.cx)/2, m_footerOpt.opt[Footer_UBAR].ptPos.y, (LPCTSTR)m_csUScal, m_csUScal.GetLength());
		}
		if( m_boolShowTime && m_footerOpt.opt[Footer_TIME].bVisible )
			TextOut(hdc, m_footerOpt.opt[Footer_TIME].ptPos.x, m_footerOpt.opt[Footer_TIME].ptPos.y, (LPCTSTR)m_csTime, m_csTime.GetLength());
		if( m_boolShowNote && m_footerOpt.opt[Footer_NOTE].bVisible )
			TextOut(hdc, m_footerOpt.opt[Footer_NOTE].ptPos.x, m_footerOpt.opt[Footer_NOTE].ptPos.y, (LPCTSTR)m_csNote, m_csNote.GetLength());

		if( m_bSplit )
		{
			if( m_footerOpt.opt[Footer_HV].bVisible )
			{
				str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_HV].strDisp, m_csHV );
				TextOut(hdc, m_footerOpt.opt[Footer_HV].ptPos.x +nOffsetX, m_footerOpt.opt[Footer_HV].ptPos.y, (LPCTSTR)str, str.GetLength());
			}
			if( m_footerOpt.opt[Footer_MAG].bVisible )
			{
				str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_MAG].strDisp, m_csMag );
				TextOut(hdc, m_footerOpt.opt[Footer_MAG].ptPos.x +nOffsetX, m_footerOpt.opt[Footer_MAG].ptPos.y, (LPCTSTR)str, str.GetLength());
			}
			if( m_footerOpt.opt[Footer_WD].bVisible )
			{
				str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_WD].strDisp, m_csWD );
				TextOut(hdc, m_footerOpt.opt[Footer_WD].ptPos.x +nOffsetX, m_footerOpt.opt[Footer_WD].ptPos.y, (LPCTSTR)str, str.GetLength());
			}
			if( m_footerOpt.opt[Footer_VAC].bVisible )
			{
				str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_VAC].strDisp, m_csVAC );
				TextOut(hdc, m_footerOpt.opt[Footer_VAC].ptPos.x +nOffsetX, m_footerOpt.opt[Footer_VAC].ptPos.y, (LPCTSTR)str, str.GetLength());
			}
			if( m_footerOpt.opt[Footer_DET].bVisible )
			{
				str.Format(_T("%s:%s"), m_footerOpt.opt[Footer_DET].strDisp, m_csSG2 );
				TextOut(hdc, m_footerOpt.opt[Footer_DET].ptPos.x +nOffsetX, m_footerOpt.opt[Footer_DET].ptPos.y, (LPCTSTR)str, str.GetLength());
			}

			if( m_footerOpt.opt[Footer_UBAR].bVisible )
			{
				GetTextExtentPoint( hdc, (LPCTSTR)m_csUScal, m_csUScal.GetLength(), &szText );
				TextOut(hdc, m_footerOpt.opt[Footer_UBAR].ptPos.x +nOffsetX +(m_nUScalePixelNum -szText.cx)/2, m_footerOpt.opt[Footer_UBAR].ptPos.y-4, (LPCTSTR)m_csUScal, m_csUScal.GetLength());
			}
			if( m_boolShowTime && m_footerOpt.opt[Footer_TIME].bVisible )
				TextOut(hdc, m_footerOpt.opt[Footer_TIME].ptPos.x +nOffsetX, m_footerOpt.opt[Footer_TIME].ptPos.y, (LPCTSTR)m_csTime, m_csTime.GetLength());
			if( m_boolShowNote && m_footerOpt.opt[Footer_NOTE].bVisible )
				TextOut(hdc, m_footerOpt.opt[Footer_NOTE].ptPos.x +nOffsetX, m_footerOpt.opt[Footer_NOTE].ptPos.y, (LPCTSTR)m_csNote, m_csNote.GetLength());
		}
	}
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	if(m_hfontLabelLogoText != NULL && m_footerOpt.opt[Footer_LOGO].bVisible)
	{
		SelectObject(hdc, m_hfontLabelLogoText);
		SetTextColor(hdc, m_sysOpt.color[SysOpt_clrLabelLogoText]);
		SetBkColor(hdc, clrBack);

		TextOut(hdc, m_footerOpt.opt[Footer_LOGO].ptPos.x, m_footerOpt.opt[Footer_LOGO].ptPos.y, (LPCTSTR)m_csLogo, m_csLogo.GetLength());
		if( m_bSplit )
			TextOut(hdc, m_footerOpt.opt[Footer_LOGO].ptPos.x +nOffsetX, m_footerOpt.opt[Footer_LOGO].ptPos.y, (LPCTSTR)m_csLogo, m_csLogo.GetLength());
	}
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	DeleteObject( hPen );
	DeleteObject( brBackBrush );
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	if ( m_lpDDSLabelLay == NULL ) return DD_OK;
	m_lpDDSLabelLay->ReleaseDC(hdc);
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	if ( m_boolShowLabel )
	{
		CRect rcGrapic = CRect(0, m_szGraph.cy - m_szLabel.cy,
			m_szGraph.cx, m_szGraph.cy);
		CRect rcImage = LayWindowMapClip_Graph_to_Image( rcGrapic );

		m_UpdateRectsImage.Add( rcImage );
	}
	/////////////////////////////////////////////////////////////////

	return DD_OK;
}

void CMCICard::UpdateHV(CString	csHV)
{	
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_csHV = csHV;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

void CMCICard::UpdateWD(CString	csWD)
{	
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_csWD = csWD;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

void CMCICard::UpdatePhotoSN(CString	csPhotoSN)
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_csPhotoSN = csPhotoSN;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

void CMCICard::UpdateTime(CString	csTime)
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_csTime = csTime;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

void CMCICard::UpdateVac(CString	csVac)
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_csVAC = csVac;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

void CMCICard::UpdateNote(CString	csNote)
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_csNote = csNote;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

void CMCICard::UpdateMAG(
	CString		csMag,					// 放大倍数显示字符
	int			nUScalePixelNum,		// 固定标尺显示长度
	CString		csUScal,				// 固定标尺显示字符
	CString		csMobileUScaleText )	// 移动标尺显示字符
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_csMag					= csMag;
	m_nUScalePixelNum		= nUScalePixelNum;
	m_csUScal				= csUScal;
	m_csMobileUScaleText	= csMobileUScaleText;
	m_boolRedrawUScal = TRUE;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

// 16.06.12 多移动标尺实验
void CMCICard::UpdateMAGArray( int nIndex,
	CString		csMobileUScaleText )	// 移动标尺显示字符
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_csMobileUScaleTextArray[nIndex]	= csMobileUScaleText;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}
// 16.06.12 多移动标尺实验

// 19.02.18 底标自定义
void CMCICard::UpdateFooter( int nIndex, BOOL bVisible, CPoint ptPos )
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_footerOpt.opt[nIndex].bVisible	= bVisible;
	m_footerOpt.opt[nIndex].ptPos.x		= (int)(m_sizeReso.cx *ptPos.x /100.0);
	if( ptPos.y < 2 )
		m_footerOpt.opt[nIndex].ptPos.y = 5;
	else
		m_footerOpt.opt[nIndex].ptPos.y = m_szLabel.cy /2 +5;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}

void CMCICard::UpdateFooterText( int nIndex, CString csText )
{
	///////////////////////////////////////////////////////
	m_mutexLayAll.Lock();
	///////////////////////////////////////////////////////

	m_footerOpt.opt[nIndex].strDisp	= csText;
	m_boolRedrawLabel = TRUE;

	///////////////////////////////////////////////////////
	m_mutexLayAll.Unlock();
	///////////////////////////////////////////////////////
}
// 19.02.18 底标自定义

