
// SetDIBitsToDevice.h : SetDIBitsToDevice 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "SemVirtualMCICard.h"

#define	SORT_BEAM_ALIGNMENT		0	//电对中
#define	SORT_SCAN_SHIFT			1	//电位移
#define	SORT_BEAM_ROTATE		2	//电旋转
#define	SORT_CONDENSER_LENS		3	//聚光镜
#define	SORT_OBJECTIVE_LENS		4	//物镜
#define	SORT_BRIGHT				5	//亮度
#define	SORT_CONTRAST			6	//对比度
#define	SORT_STIGMATOR			7	//消像散

#define RESO_COUNT				18
#define UPDATEVIEW_CHANGEADJUSTOR	1


// CSetDIBitsToDeviceApp:
// 有关此类的实现，请参阅 SetDIBitsToDevice.cpp
//

class CSetDIBitsToDeviceApp : public CWinAppEx
{
public:
	CSetDIBitsToDeviceApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	CSemVirtualMCICard		m_ImageCard;

	unsigned short*	m_pSharedImageBuff[SharedImageBuffCounts];
	double*	m_pGraphDataBuff[GraphDataBuffGroups];
	double* m_pDiffGraphDataBuff[GraphDataBuffGroups];

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSetDIBitsToDeviceApp theApp;
