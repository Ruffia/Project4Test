
// TransparentPaint_TransparentBlt_Test03.h : TransparentPaint_TransparentBlt_Test03 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTransparentPaint_TransparentBlt_Test03App:
// �йش����ʵ�֣������ TransparentPaint_TransparentBlt_Test03.cpp
//

class CTransparentPaint_TransparentBlt_Test03App : public CWinApp
{
public:
	CTransparentPaint_TransparentBlt_Test03App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
protected:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CTransparentPaint_TransparentBlt_Test03App theApp;
