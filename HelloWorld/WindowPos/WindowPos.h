
// WindowPos.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWindowPosApp:
// �йش����ʵ�֣������ WindowPos.cpp
//

class CWindowPosApp : public CWinApp
{
public:
	CWindowPosApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWindowPosApp theApp;