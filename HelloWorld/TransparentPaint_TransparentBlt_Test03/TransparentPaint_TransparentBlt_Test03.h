
// TransparentPaint_TransparentBlt_Test03.h : TransparentPaint_TransparentBlt_Test03 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CTransparentPaint_TransparentBlt_Test03App:
// 有关此类的实现，请参阅 TransparentPaint_TransparentBlt_Test03.cpp
//

class CTransparentPaint_TransparentBlt_Test03App : public CWinApp
{
public:
	CTransparentPaint_TransparentBlt_Test03App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
protected:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CTransparentPaint_TransparentBlt_Test03App theApp;
