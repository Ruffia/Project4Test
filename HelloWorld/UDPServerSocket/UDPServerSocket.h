
// UDPServerSocket.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDPServerSocketApp:
// �йش����ʵ�֣������ UDPServerSocket.cpp
//

class CUDPServerSocketApp : public CWinApp
{
public:
	CUDPServerSocketApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUDPServerSocketApp theApp;