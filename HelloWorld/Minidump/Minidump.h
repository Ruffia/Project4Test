
// Minidump.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMinidumpApp:
// �йش����ʵ�֣������ Minidump.cpp
//

class CMinidumpApp : public CWinApp
{
public:
	CMinidumpApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMinidumpApp theApp;