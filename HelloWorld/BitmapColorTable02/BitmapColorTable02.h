
// BitmapColorTable02.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBitmapColorTable02App:
// �йش����ʵ�֣������ BitmapColorTable02.cpp
//

class CBitmapColorTable02App : public CWinApp
{
public:
	CBitmapColorTable02App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBitmapColorTable02App theApp;