
// GetDeviceCaps.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGetDeviceCapsApp:
// �йش����ʵ�֣������ GetDeviceCaps.cpp
//

class CGetDeviceCapsApp : public CWinApp
{
public:
	CGetDeviceCapsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGetDeviceCapsApp theApp;