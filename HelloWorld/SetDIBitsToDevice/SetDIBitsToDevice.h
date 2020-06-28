
// SetDIBitsToDevice.h : SetDIBitsToDevice Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "SemVirtualMCICard.h"

#define	SORT_BEAM_ALIGNMENT		0	//�����
#define	SORT_SCAN_SHIFT			1	//��λ��
#define	SORT_BEAM_ROTATE		2	//����ת
#define	SORT_CONDENSER_LENS		3	//�۹⾵
#define	SORT_OBJECTIVE_LENS		4	//�ﾵ
#define	SORT_BRIGHT				5	//����
#define	SORT_CONTRAST			6	//�Աȶ�
#define	SORT_STIGMATOR			7	//����ɢ

#define RESO_COUNT				18
#define UPDATEVIEW_CHANGEADJUSTOR	1


// CSetDIBitsToDeviceApp:
// �йش����ʵ�֣������ SetDIBitsToDevice.cpp
//

class CSetDIBitsToDeviceApp : public CWinAppEx
{
public:
	CSetDIBitsToDeviceApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
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
