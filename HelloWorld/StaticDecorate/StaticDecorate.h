
// StaticDecorate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CStaticDecorateApp:
// �йش����ʵ�֣������ StaticDecorate.cpp
//

class CStaticDecorateApp : public CWinApp
{
public:
	CStaticDecorateApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStaticDecorateApp theApp;