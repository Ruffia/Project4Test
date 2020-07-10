
// SetDIBitsToDeviceView.cpp : CSetDIBitsToDeviceView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SetDIBitsToDevice.h"
#endif

#include "SetDIBitsToDeviceDoc.h"
#include "SetDIBitsToDeviceView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int ReadInOneLine(TCHAR *path, TCHAR *Section, TCHAR *Entry, UINT uDataStyle, int nTotal, void* pData, TCHAR Separator=',')
{
	TCHAR szBuf1[255];
	TCHAR szBuf2[255];
	int* pint = (int*) pData;
	double* pdouble = (double*)pData;
	long* plong = (long*)pData;
	CString* pstr = (CString*)pData;
	int i = 0;
	if(GetPrivateProfileString(Section, Entry, _T(""), szBuf1, 255, path) != 0)
	{
		for(i=0; i<nTotal; i++)
		{
			_tcscpy(szBuf2, szBuf1);
			if(_tcschr(szBuf2, Separator) != NULL)
			{
				_tcscpy(szBuf1, _tcschr(szBuf2, Separator)+1);
				*_tcschr(szBuf2, Separator) = '\0';
				switch( uDataStyle )
				{
				case	INTSTYLE:
					pint[i] = _ttoi(szBuf2);
					break;
				case	DOUBLESTYLE:
					pdouble[i] = _ttof(szBuf2);
					break;
				case	LONGSTYLE:
					plong[i] = _ttol(szBuf2);
					break;
				case	STRSTYLE:
					pstr[i] = szBuf2;
					break;
				default:
					return 0;
				}
			}
			else
			{
				// This is the last data.
				switch( uDataStyle )
				{
				case	INTSTYLE:
					pint[i] = _ttoi(szBuf2);
					break;
				case	DOUBLESTYLE:
					pdouble[i] = _ttof(szBuf2);
					break;
				case	LONGSTYLE:
					plong[i] = _ttol(szBuf2);
					break;
				case	STRSTYLE:
					pstr[i] = szBuf2;
					break;
				default:
					return 0;
				}
				if(i == nTotal-1)
				{
					nTotal = i+1;
				}
				else
				{
					nTotal = i;
				}
				break;
			}
		}
	}
	return i+1;
}


void CSetDIBitsToDeviceView::ReadFooter_TimeFormat( TCHAR* buf )
{
	// buf = "Time=Y/m/d H/M"
	TCHAR szBuf[100], szBuf1[20], szPer, ch;
	_tcscpy( szBuf1, buf );
	_tcscpy(szBuf, _tcschr(szBuf1, '=')+1);	// szBuf中是日期格式字符串

	szPer = '%';
	_stprintf( szBuf1, _T("") );
	int len = _tcslen( szBuf );
	int index = 0;
	for( int i=0; i<len; i++ )
	{
		ch = szBuf[i];
		if(ch >='a' && ch<='z' ||  ch >='A' && ch<='Z')
		{
			szBuf1[index] = szPer;
			index++;
		}
		szBuf1[index] = ch;
		index++;
	}
	szBuf1[index] = '\0';
	m_footerOpt.opt[0].strDisp = szBuf1;
}

int CSetDIBitsToDeviceView::ReadFooterSettings( TCHAR* path )
{
	int i=0;
	for( i=0; i<11; i++)
	{
		m_footerOpt.opt[i].bVisible	= FALSE;
	}

	TCHAR szBuf[20], szBuf1[255], szBuf2[255], szBuf3[50];
	int nLines = 0;
	if(GetPrivateProfileString( _T("FooterSettings"), _T("Lines"), _T(""), szBuf, 10, path) != 0 )
		nLines = _ttoi(szBuf);
	if( nLines < 1 )
		return -1;
	int nPos = 0;
	for( i=0; i<nLines; i++ )
	{
		_stprintf(szBuf, _T("MacroLine%d"), i+1);
		if(GetPrivateProfileString(_T("FooterSettings"), szBuf, _T(""), szBuf1, 255, path) != 0 )
		{
			_tcscpy(szBuf2, szBuf1);
			while(_tcschr(szBuf2, '}') != NULL)
			{
				_tcscpy(szBuf1, _tcschr(szBuf2, '}')+1);	// szBuf1中是该行剩余字符串
				*_tcschr(szBuf2, '}') = '\0';			// szBuf2中是字符串{HV;x=0
				_tcscpy(szBuf3, szBuf2+1);				// szBuf3中是当前字符串HV;x=0
				_tcscpy(szBuf2, _tcschr(szBuf3, '=')+1);	// szBuf2中是当前字符串的位置
				nPos = _ttoi(szBuf2);
				*_tcschr(szBuf3, ';') = '\0';			// szBuf3中是带标识的当前字符串的内容
				_tcscpy(szBuf2, szBuf3+1);				// szBuf2中是当前字符串的内容
				switch(szBuf3[0])
				{
				case	't':	// Time
					m_footerOpt.opt[0].bVisible	= TRUE;
					m_footerOpt.opt[0].ptPos.x	= nPos;
					m_footerOpt.opt[0].ptPos.y	= i+1;
					ReadFooter_TimeFormat(szBuf2);
					break;
				case	'h':	// HV
					m_footerOpt.opt[1].bVisible	= TRUE;
					m_footerOpt.opt[1].ptPos.x	= nPos;
					m_footerOpt.opt[1].ptPos.y	= i+1;
					m_footerOpt.opt[1].strDisp	= szBuf2;
					break;
				case	'w':	// WD
					m_footerOpt.opt[2].bVisible	= TRUE;
					m_footerOpt.opt[2].ptPos.x	= nPos;
					m_footerOpt.opt[2].ptPos.y	= i+1;
					m_footerOpt.opt[2].strDisp	= szBuf2;
					break;
				case	'm':	// Mag
					m_footerOpt.opt[3].bVisible	= TRUE;
					m_footerOpt.opt[3].ptPos.x	= nPos;
					m_footerOpt.opt[3].ptPos.y	= i+1;
					m_footerOpt.opt[3].strDisp	= szBuf2;
					break;
				case	'd':	// DET
					m_footerOpt.opt[4].bVisible	= TRUE;
					m_footerOpt.opt[4].ptPos.x	= nPos;
					m_footerOpt.opt[4].ptPos.y	= i+1;
					m_footerOpt.opt[4].strDisp	= szBuf2;
					break;
				case	'l':	// Logo
					m_footerOpt.opt[5].bVisible	= TRUE;
					m_footerOpt.opt[5].ptPos.x	= nPos;
					m_footerOpt.opt[5].ptPos.y	= i+1;
					m_footerOpt.opt[5].strDisp	= szBuf2;
					break;
				case	'u':	// uBar
					m_footerOpt.opt[6].bVisible	= TRUE;
					m_footerOpt.opt[6].ptPos.x	= nPos;
					m_footerOpt.opt[6].ptPos.y	= i+1;
					m_footerOpt.opt[6].strDisp	= szBuf2;
					break;
				case	'n':	// Note
					m_footerOpt.opt[7].bVisible	= TRUE;
					m_footerOpt.opt[7].ptPos.x	= nPos;
					m_footerOpt.opt[7].ptPos.y	= i+1;
					m_footerOpt.opt[7].strDisp	= szBuf2;
					break;
				case	'v':	// Vac
					m_footerOpt.opt[8].bVisible	= TRUE;
					m_footerOpt.opt[8].ptPos.x	= nPos;
					m_footerOpt.opt[8].ptPos.y	= i+1;
					m_footerOpt.opt[8].strDisp	= szBuf2;
					break;
				case	'e':	// EMI
					m_footerOpt.opt[9].bVisible	= TRUE;
					m_footerOpt.opt[9].ptPos.x	= nPos;
					m_footerOpt.opt[9].ptPos.y	= i+1;
					m_footerOpt.opt[9].strDisp	= szBuf2;
					break;
				case	's':	// Speed
					m_footerOpt.opt[10].bVisible	= TRUE;
					m_footerOpt.opt[10].ptPos.x	= nPos;
					m_footerOpt.opt[10].ptPos.y	= i+1;
					m_footerOpt.opt[10].strDisp	= szBuf2;
					break;
				}
				_tcscpy(szBuf2, szBuf1);
			}
		}
	}
	return 0;
}


// CSetDIBitsToDeviceView

IMPLEMENT_DYNCREATE(CSetDIBitsToDeviceView, CView)

BEGIN_MESSAGE_MAP(CSetDIBitsToDeviceView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSetDIBitsToDeviceView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CSetDIBitsToDeviceView 构造/析构

CSetDIBitsToDeviceView::CSetDIBitsToDeviceView()
{
	// TODO: 在此处添加构造代码

	//	SetScrollSizes(MM_TEXT, CSize(0, 0));
	// 2005-1-17_液晶屏幕XY比例问题
	VERIFY(m_brHatch.CreateHatchBrush(HS_DIAGCROSS, RGB(191, 191, 191)));	// 09.12.02改回diagcross
	//	VERIFY(m_brHatch.CreateSolidBrush( gc_crScreenColor ));

	m_bCatch = FALSE;

	m_bUScaleHitTest		= FALSE;
	m_bOscillographHitTest	= FALSE;
	//LMH//////////////////////////////////

	m_nAdjustorSort			= SORT_OBJECTIVE_LENS;	//调节器类型为对比度调节
	m_nCondenserSort		= 0;					//聚光镜调节类型为粗调
	m_nObjectiveSort		= 0;					//物镜调节类型为粗调

	m_bAbc					= FALSE;	//不进行字符编辑
	m_bLabel				= TRUE;		//显示底标
	m_bUScale				= FALSE;	//隐藏活动标尺
	m_bDate					= FALSE;	//隐藏日期
	m_bNote					= FALSE;	//隐藏备注
	m_bWobbler				= FALSE;	//物镜摇摆关
	m_bLean					= FALSE;	//倾斜补偿关
	m_bDynFocus				= FALSE;	//动态聚焦关
	m_bSacp					= FALSE;	//通道花样关
	m_bRobinson				= FALSE;	//Robinson探头关
	m_bOscillograph			= FALSE;	//隐藏示波器
	m_bFrameRate			= FALSE;	//隐藏标准框

	m_bCondRev				= FALSE;	//聚光镜反转关
	m_bObjectiveRev			= FALSE;	//物镜反转关
	m_bAuxStig				= FALSE;	//辅助消像散关

	m_bPreview				= FALSE;	//非照相预览
	m_bZoomFit				= FALSE;
	m_bLive					= FALSE;	//快速扫描
	m_bSplit				= FALSE;	//非分割像
	m_bSplitZoom			= FALSE;	//分割像不放大显示
	m_bOnlyDet2				= FALSE;	//显示第一探测器图像

	m_boolScreenFull		= FALSE;

	m_bStopPhoto			= FALSE;	// 2004-5-12_照相编号自动增加
	m_bStopScan				= TRUE;		// 2005-1-17_0.0KV问题


	m_nusbScanResoIndex	= 4;
	m_nusbPixRate		= 2;					// 1us
	m_nusbPixRateIndex	= 1;					// 扫描速度为1档
	m_nusbPhotoPixRate	= 128;					// 64us
	m_nusbPhotoPixRateIndex	= 4;//11;			// pix clk = 20us, actual dwell time = 80us
	//	m_usbParam			= ;
	m_nusbScanStoreMode	= 1;					// XYZ存储方式
	m_nusbScanDetMode	= 0;					// 12.02.15 单探测器模式
	m_nCLgrade			= -1;
	///////////////////////////////////////////////////////////

	//	USB_GetResoSize( m_nusbScanResoIndex );
	m_dResoRate = 1.0;
	m_sizeReso = CSize(1024,768);

	///////////////////////////////////////////////////////////
	m_nLineScanParam = m_sizeReso.cy / 2;

	m_ptPointScanParam.x = m_sizeReso.cx / 2;
	m_ptPointScanParam.y = m_sizeReso.cy / 2;

	//	1024	512		256
	//	 768	384		192
	m_rcAreaScanParam.left		= 256;
	m_rcAreaScanParam.top		= 192;
	m_rcAreaScanParam.right		= 256 + 512;
	m_rcAreaScanParam.bottom	= 192 + 384;

	//	1024	512		256
	//	 768	384		192
	m_rcStaticAreaScanParam.left	= 256;
	m_rcStaticAreaScanParam.top		= 192;
	m_rcStaticAreaScanParam.right	= 256 + 512;
	m_rcStaticAreaScanParam.bottom	= 192 + 384;

	//	1024	512		256
	//	 768	384		192
	m_rcAutoBCAreaScanParam.left	= (1024 - 512) / 2;
	m_rcAutoBCAreaScanParam.top		= (768 - 384) / 2;
	m_rcAutoBCAreaScanParam.right	= 512 + m_rcAutoBCAreaScanParam.left;
	m_rcAutoBCAreaScanParam.bottom	= 384 + m_rcAutoBCAreaScanParam.top;

	//	1024	512		256
	//	 768	384		192
	m_rcAutoFocusAreaScanParam.left		= (1024 - 256) / 2;
	m_rcAutoFocusAreaScanParam.top		= (768 - 256) / 2;
	m_rcAutoFocusAreaScanParam.right	= 256 + m_rcAutoFocusAreaScanParam.left;
	m_rcAutoFocusAreaScanParam.bottom	= 256 + m_rcAutoFocusAreaScanParam.top;

	//	1024	512		256
	//	 768	384		192
	m_rcAutoAstigmatAreaScanParam.left		= (1024 - 256) / 2;
	m_rcAutoAstigmatAreaScanParam.top		= (768 - 256) / 2;
	m_rcAutoAstigmatAreaScanParam.right		= 256 + m_rcAutoAstigmatAreaScanParam.left;
	m_rcAutoAstigmatAreaScanParam.bottom	= 256 + m_rcAutoAstigmatAreaScanParam.top;

	//	1024	512		256
	//	 768	384		192
	m_rcDualMagParam.left	= 128;
	m_rcDualMagParam.top	= 192;
	m_rcDualMagParam.right	= 128 + 256;
	m_rcDualMagParam.bottom	= 192 + 384;
	///////////////////////////////////////////////////////////

	//--Auto Functions---------------------------------------//
	m_bImageBuff			= new BYTE[256*256];//bAutoBUFF;
	//--Auto Functions---------------------------------------//

	//	gpScanView = this;

	// 07.07---07.08加入任意方向标尺
	m_ptMobileUScale	= CPoint(100,400);
	m_ptMobileUScale2	= CPoint(400,400);

	// 16.06.12 多移动标尺实验
	for( int i=0; i<MobileUScaleCounts; i++ )
	{
		//		m_nMobileUScalePixelNumArray[i]	= ;
		m_ptMobileUScaleArray[i]		= CPoint( -1, -1 );
		m_ptMobileUScaleArray2[i]		= CPoint( -1, -1 );
		m_bUScaleHitTestArray[i]		= FALSE;
	}
	m_nMobileUScaleCounts	= 0;
}

CSetDIBitsToDeviceView::~CSetDIBitsToDeviceView()
{
}

BOOL CSetDIBitsToDeviceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSetDIBitsToDeviceView 绘制

void CSetDIBitsToDeviceView::OnDraw(CDC* /*pDC*/)
{
	CSetDIBitsToDeviceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CSetDIBitsToDeviceView 打印


void CSetDIBitsToDeviceView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSetDIBitsToDeviceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSetDIBitsToDeviceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSetDIBitsToDeviceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CSetDIBitsToDeviceView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSetDIBitsToDeviceView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSetDIBitsToDeviceView 诊断

#ifdef _DEBUG
void CSetDIBitsToDeviceView::AssertValid() const
{
	CView::AssertValid();
}

void CSetDIBitsToDeviceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSetDIBitsToDeviceDoc* CSetDIBitsToDeviceView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSetDIBitsToDeviceDoc)));
	return (CSetDIBitsToDeviceDoc*)m_pDocument;
}
#endif //_DEBUG


void CSetDIBitsToDeviceView::SetFooterSettingsDefault()
{
	// Time
	m_footerOpt.opt[0].bVisible	= TRUE;
	m_footerOpt.opt[0].ptPos.x	= 75;
	m_footerOpt.opt[0].ptPos.y	= 1;
	m_footerOpt.opt[0].strDisp	= _T("%Y.%m.%d %H:%M");
	// HV
    m_footerOpt.opt[1].bVisible	= TRUE;
	m_footerOpt.opt[1].ptPos.x	= 2;
	m_footerOpt.opt[1].ptPos.y	= 1;
	m_footerOpt.opt[1].strDisp	= _T("HV");
	// WD
	m_footerOpt.opt[2].bVisible	= TRUE;
	m_footerOpt.opt[2].ptPos.x	= 2;
	m_footerOpt.opt[2].ptPos.y	= 2;
	m_footerOpt.opt[2].strDisp	= _T("WD");
	// Mag
	m_footerOpt.opt[3].bVisible	= TRUE;
	m_footerOpt.opt[3].ptPos.x	= 25;
	m_footerOpt.opt[3].ptPos.y	= 1;
	m_footerOpt.opt[3].strDisp	= _T("MAG");
	// DET
	m_footerOpt.opt[4].bVisible	= TRUE;
	m_footerOpt.opt[4].ptPos.x	= 25;
	m_footerOpt.opt[4].ptPos.y	= 2;
	m_footerOpt.opt[4].strDisp	= _T("DET");
	// Logo
	m_footerOpt.opt[5].bVisible	= TRUE;
	m_footerOpt.opt[5].ptPos.x	= 50;
	m_footerOpt.opt[5].ptPos.y	= 2;
	m_footerOpt.opt[5].strDisp	= _T("Logo");
	// uBar
	m_footerOpt.opt[6].bVisible	= TRUE;
	m_footerOpt.opt[6].ptPos.x	= 50;
	m_footerOpt.opt[6].ptPos.y	= 1;
	m_footerOpt.opt[6].strDisp	= _T("uBar");
	// Note
	m_footerOpt.opt[7].bVisible	= TRUE;
	m_footerOpt.opt[7].ptPos.x	= 75;
	m_footerOpt.opt[7].ptPos.y	= 2;
	m_footerOpt.opt[7].strDisp	= _T("Note");
	// Vac
	m_footerOpt.opt[8].bVisible	= FALSE;
	m_footerOpt.opt[8].ptPos.x	= 0;
	m_footerOpt.opt[8].ptPos.y	= 0;
	m_footerOpt.opt[8].strDisp	= _T("Vac");
	// EMI
	m_footerOpt.opt[9].bVisible	= FALSE;
	m_footerOpt.opt[9].ptPos.x	= 0;
	m_footerOpt.opt[9].ptPos.y	= 0;
	m_footerOpt.opt[9].strDisp	= _T("EMI");
	// Speed
	m_footerOpt.opt[10].bVisible	= FALSE;
	m_footerOpt.opt[10].ptPos.x	= 0;
	m_footerOpt.opt[10].ptPos.y	= 0;
	m_footerOpt.opt[10].strDisp	= _T("Speed");
}

// CSetDIBitsToDeviceView 消息处理程序
int CSetDIBitsToDeviceView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CMainFrame* frame = (CMainFrame *)theApp.GetMainWnd();



	SetScrollSizes( MM_TEXT, m_sizeReso );
	m_szTotalLog = m_sizeReso;

	///////////////////////////////////////////////////////
	// 读取各参数
	// 获取工作路径
	TCHAR path[256];
	::GetModuleFileName(0, path, 255);
	TCHAR *exd = _tcschr(path, (int)'\\');
	if(exd != NULL)
		*exd = '\0';
	_tcscat(path, _T("\\KYKYcfg.ini"));

	///////////////////////////////////////////////////////
	// 读颜色值
	int i;
	long* pnColor = new long[10];
	if(ReadInOneLine(path, _T("Options"), _T("Colors"), LONGSTYLE, 10, pnColor) == 10 )
	{
		for( i=0; i<10; i++ )
		{
			m_sysOpt.color[i]	= pnColor[i];
			theApp.m_ImageCard.SetColor( i, pnColor[i] );
		}
	}
	delete [] pnColor;
	TCHAR szBuf[20];
	m_sysOpt.nLineWidth = 3;
	if(GetPrivateProfileString(_T("Options"), _T("LineWidth"), _T("3"), szBuf, 10, path) != 0 )
		m_sysOpt.nLineWidth = _ttoi( szBuf );
	theApp.m_ImageCard.SetParams( 10, m_sysOpt.nLineWidth );
	///////////////////////////////////////////////////////
	// 读字体参数
	CString* pstrName = new CString[3];
	if(ReadInOneLine(path, _T("Options"), _T("FontNames"), STRSTYLE, 3, pstrName) == 3 )
	{
		for( i=0; i<3; i++ )
		{
			m_sysOpt.fName[i]	= pstrName[i];
			theApp.m_ImageCard.SetFontName( i, pstrName[i] );
		}
	}
	delete [] pstrName;
	int* pnSize = new int[3];
	if( ReadInOneLine(path, _T("Options"), _T("FontSizes"), INTSTYLE, 3, pnSize) == 3 )
	{
		for( i=0; i<3; i++ )
		{
			m_sysOpt.fSize[i]	= pnSize[i];
			theApp.m_ImageCard.SetFontSize( i, pnSize[i] );
		}
	}
	delete [] pnSize;
	///////////////////////////////////////////////////////
	// 显示参数
	m_sysOpt.nShowParams[SysOpt_showLabelTrans]	= 1;
	m_sysOpt.nShowParams[SysOpt_showScrMag]		= 1;
	m_sysOpt.nShowParams[SysOpt_showDate]		= 0;
	m_sysOpt.nShowParams[SysOpt_showNote]		= 0;
	m_sysOpt.nShowParams[SysOpt_showCCD]			= 1;
	int* pnShow = new int[5];
	if(ReadInOneLine(path, _T("Options"), _T("ShowParams"), INTSTYLE, 5, pnShow) == 5 )
	{
		for( i=0; i<5; i++ )
			m_sysOpt.nShowParams[i]	= pnShow[i];
	}
	delete [] pnShow;
	theApp.m_ImageCard.SetTransparent( m_sysOpt.nShowParams[SysOpt_showLabelTrans] );
	m_bDate = m_sysOpt.nShowParams[SysOpt_showDate];
	m_bNote = m_sysOpt.nShowParams[SysOpt_showNote];
	///////////////////////////////////////////////////////
	// 其它系统参数
	CString strLo1, strLo2, strLo3, strLo4;
	if(GetPrivateProfileString(_T("Options2"), _T("Lo1"), _T("EM"), szBuf, 10, path) != 0 )
		strLo1 = szBuf;
	if(GetPrivateProfileString(_T("Options2"),_T("Lo2"), _T("62"), szBuf, 10, path) != 0 )
		strLo2 = szBuf;
	if(GetPrivateProfileString(_T("Options2"), _T("Lo3"), _T("00"), szBuf, 10, path) != 0 )
		strLo3 = szBuf;
	if(GetPrivateProfileString(_T("Options2"), _T("Lo4"), _T(""), szBuf, 10, path) != 0 )
		strLo4 = szBuf;
	///////////////////////////////////////////////////////
	// 底标参数
	if( ReadFooterSettings( path ) < 0 )
		SetFooterSettingsDefault();
	for( i=0; i<11; i++ )
	{
		theApp.m_ImageCard.UpdateFooter( i, m_footerOpt.opt[i].bVisible, m_footerOpt.opt[i].ptPos );
		theApp.m_ImageCard.UpdateFooterText( i,m_footerOpt.opt[i].strDisp );
	}
	// 19.06.19 扫描区域显示像素
	m_nDispPixel = 1024;
	if(GetPrivateProfileString( _T("Hardware"), _T("DispP"), _T("1024"), szBuf, 10, path) != 0 )
		m_nDispPixel = _ttoi(szBuf);

	m_scanParamLive.nScan_Type		= 1;
	m_scanParamLive.nScan_Speed		= 1;	// 500ns
	m_scanParamLive.nSync_Speed		= m_nusbPhotoPixRate;
	m_scanParamLive.nScan_ResoX		= 512;	// 512*384
	m_scanParamLive.nScan_ResoY		= 384;
	m_scanParamLive.nScan_left		= 0;
	m_scanParamLive.nScan_top		= 0;
	m_scanParamLive.nScan_right		= 512;
	m_scanParamLive.nScan_bottom	= 384;
	m_scanParamLive.nSplit			= 0;
	m_scanParamLive.nDet2			= 0;
	m_scanParamLive.nStoreMode		= 1;

	theApp.m_ImageCard.SetZoom( 1.0 );
//	theApp.m_ImageCard.SetResolution(RESO_1024_768);
	theApp.m_ImageCard.SetResolution(m_sizeReso);
	theApp.m_ImageCard.Reset( this );
	theApp.m_ImageCard.ShowLabel( m_bLabel );
	theApp.m_ImageCard.SetParams( 4, 0 );	// 默认显示偶数通道图像数据

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
	theApp.m_ImageCard.SetScanScreenMode( TRUE );
	theApp.m_ImageCard.SetProductLogo( _T("Draw Device"));
	//-----------------------------------------------------
	//======2006.11.22_3200与3900采集屏显示兼容============

	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	// 分配多个内存段，并通知SemScan和VirtualMCICard
	for( i=0; i<SharedImageBuffCounts; i++ )
	{
		theApp.m_pSharedImageBuff[i] = new unsigned short[LOOP_COUNTS * 40960];
		//theApp.m_SemCtrl.m_SemScan.USB_SetSharedImageBuff( i, theApp.m_pSharedImageBuff[i] );
		theApp.m_ImageCard.SetSharedImageBuff( i, theApp.m_pSharedImageBuff[i] );
	}
	// 按最快100ms一个数据计算，1秒10个，1分钟600个，1小时36000个，10小时360000个
	for( i=0; i<GraphDataBuffGroups; i++ )
	{
		theApp.m_pGraphDataBuff[i] = new double[GraphDataBuffCounts];
		ZeroMemory( theApp.m_pGraphDataBuff[i], sizeof(double)*GraphDataBuffCounts );
	}
	for( i=0; i<GraphDataBuffGroups; i++ )
	{
		theApp.m_pDiffGraphDataBuff[i] = new double[GraphDataBuffCounts];
		ZeroMemory( theApp.m_pDiffGraphDataBuff[i], sizeof(double)*GraphDataBuffCounts );
	}
	///////////////////////////////////////////////////////

	return 0;
}
