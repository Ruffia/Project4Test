
// DynamicCreate01.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDynamicCreate01App:
// �йش����ʵ�֣������ DynamicCreate01.cpp
//

class CDynamicCreate01App : public CWinApp
{
public:
	CDynamicCreate01App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDynamicCreate01App theApp;