
// UDPClientSocket.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDPClientSocketApp:
// �йش����ʵ�֣������ UDPClientSocket.cpp
//

class CUDPClientSocketApp : public CWinApp
{
public:
	CUDPClientSocketApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUDPClientSocketApp theApp;