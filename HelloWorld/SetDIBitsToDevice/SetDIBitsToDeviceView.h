
// SetDIBitsToDeviceView.h : CSetDIBitsToDeviceView ��Ľӿ�
//

#pragma once
#include "USB_Functions.h"

class CSetDIBitsToDeviceView : public CScrollView
{
	enum {
		GraphHitTest_Normal	= 0,
		GraphHitTest_In		= 1,
		GraphHitTest_E		= 2,
		GraphHitTest_W		= 3,
		GraphHitTest_N		= 4,
		GraphHitTest_S		= 5,
		GraphHitTest_NE		= 6,
		GraphHitTest_SE		= 7,
		GraphHitTest_NW		= 8,
		GraphHitTest_SW		= 9,
		GraphHitTest_NS		= 10,
		// 09.11.18 ���ӵ�����������GraphHitTestNULL
		GraphHitTest_NULL	= 11,
	};

protected: // �������л�����
	CSetDIBitsToDeviceView();
	DECLARE_DYNCREATE(CSetDIBitsToDeviceView)

// ����
public:
	CSetDIBitsToDeviceDoc* GetDocument() const;

// ����
public:
	unsigned short	m_nAdjustorSort;
	unsigned short	m_nCondenserSort;
	unsigned short	m_nObjectiveSort;

	BOOL	m_bAbc;
	BOOL	m_bLabel;
	BOOL	m_bUScale;
	BOOL	m_bDate;
	BOOL	m_bNote;
	BOOL	m_bWobbler;
	BOOL	m_bLean;
	BOOL	m_bDynFocus;
	BOOL	m_bSacp;
	BOOL	m_bRobinson;
	BOOL	m_bOscillograph;
	BOOL	m_bFrameRate;

	BOOL	m_bCondRev;
	BOOL	m_bObjectiveRev;
	BOOL	m_bAuxStig;

	BOOL	m_bPreview;
	BOOL	m_bLive;
	BOOL	m_bSplit;
	BOOL	m_bSplitZoom;
	BOOL	m_bOnlyDet2;

	CRect	m_rcScan;
	BOOL	m_bZoomFit;

	///////////////////////////////////////////////////////////
	BOOL	m_boolScreenFull;

	long				m_nLineScanParam;
	CPoint				m_ptPointScanParam;
	CRect				m_rcAreaScanParam;
	CRect				m_rcStaticAreaScanParam;
	CRect				m_rcAutoBCAreaScanParam;
	CRect				m_rcAutoFocusAreaScanParam;
	CRect				m_rcAutoAstigmatAreaScanParam;
	CRect				m_rcDualMagParam;

	BOOL		m_bStopPhoto;	// 2004-5-12_�������Զ�����
	BOOL		m_bStopScan;	// 2005-1-17_0.0KV����

	///////////////////////////////////////////////////////
	// USB
	unsigned short	m_nusbScanResoIndex;
	CSize			m_sizeReso;
	unsigned short	m_nusbPixRateIndex;
	unsigned short	m_nusbPhotoPixRateIndex;
	unsigned short	m_nusbScanType;
	unsigned short	m_nusbScanTypeSaved;
	unsigned short	m_nusbScanStoreMode;
	unsigned short	m_nusbScanDetMode;		// 12.02.15 ̽����ģʽ
	PublicParam_Scan	m_scanParamLive;
	PublicParam_Scan	m_scanParamBak;

	UINT	m_nPixRateIndex[9];// = { 1, 2, 4, 8, 16, 32, 64, 128, 256 };//40, 80, 128 };
	int		m_nResos[RESO_COUNT];
	int		m_nResoX[8];
	int		m_nResoY[8];
	double	m_dResoRate;

	UINT	m_nCLgrade;
	// 	long	m_lCLgrade[3*9];	// 9���۹⾵���ٵ�λ��ÿ����λ�����۹⾵�����ȡ��Աȶȸ�һ��ֵ
	long	m_lCLfast[4];		// 4���۹⾵��������ֵ

	unsigned short			m_nusbPixRate;
	unsigned short			m_nusbPhotoPixRate;
	unsigned short			m_nusbPixRateSaved;

	//LMH//////////////////////////////////
protected:
	CPoint		m_ptPosSave;
	int			m_nGraphHitTestSave;
	BOOL		m_bCatch;

	CRect		m_rcDragRectLast;
	//CSize		m_szDragSizeLast;

	int			m_nMobileUScalePixelNum;
	CPoint		m_ptMobileUScale;
	CPoint		m_ptMobileUScale2;		// 07.07---07.08�������ⷽ����
	BOOL		m_bUScaleHitTest;

	// 16.06.12 ���ƶ����ʵ��
	int			m_nMobileUScalePixelNumArray[MobileUScaleCounts];
	CPoint		m_ptMobileUScaleArray[MobileUScaleCounts];
	CPoint		m_ptMobileUScaleArray2[MobileUScaleCounts];
	BOOL		m_bUScaleHitTestArray[MobileUScaleCounts];
	void		SetUScaleParamArray(int nIndex, CPoint point);

	int			m_nMobileUScaleCounts;	// �����ӵ��ƶ������Ŀ
	// 16.06.12 ���ƶ����ʵ��

	CPoint		m_ptOscillograph;
	BOOL		m_bOscillographHitTest;

	int			m_nMapMode;
	CSize		m_szTotalLog;			// total size in logical units (no rounding)
	CSize		m_szTotalDev;			// total size in device units

	BOOL		m_bCenter;             // Center output if larger than total size
	BOOL		m_bInsideUpdate;       // internal state for OnSize callback

	CBrush		m_brHatch;
	//LMH//////////////////////////////////
	CBitmap		m_bmpBackground;

	SYS_Options	m_sysOpt;
	Footer_Options	m_footerOpt;

	// 19.06.19 ɨ��������ʾ����
	int			m_nDispPixel;

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	int ReadFooterSettings(TCHAR* path);
	void SetFooterSettingsDefault();
	void ReadFooter_TimeFormat( TCHAR* buf );
// ʵ��
public:
	virtual ~CSetDIBitsToDeviceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SetDIBitsToDeviceView.cpp �еĵ��԰汾
inline CSetDIBitsToDeviceDoc* CSetDIBitsToDeviceView::GetDocument() const
   { return reinterpret_cast<CSetDIBitsToDeviceDoc*>(m_pDocument); }
#endif

