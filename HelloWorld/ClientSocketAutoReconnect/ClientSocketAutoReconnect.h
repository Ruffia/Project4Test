
// ClientSocketAutoReconnect.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CClientSocketAutoReconnectApp:
// �йش����ʵ�֣������ ClientSocketAutoReconnect.cpp
//

class CClientSocketAutoReconnectApp : public CWinApp
{
public:
	CClientSocketAutoReconnectApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CClientSocketAutoReconnectApp theApp;