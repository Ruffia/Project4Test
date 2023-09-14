#include "stdafx.h"
#include "ReconnectThread.h"
#include "ClientSocketAutoReconnectDlg.h"
#pragma comment(lib,"ws2_32.lib")     //链接库文件

CSocketConnector::CSocketConnector():m_hWnd(NULL),m_nPort(-1)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD( 2, 2 );
	int err = WSAStartup( wVersionRequested, &wsaData );
	m_strIP = "127.0.0.1";
}

CSocketConnector::~CSocketConnector()
{
	WSACleanup(); 
}


CSocketConnector& CSocketConnector::Instance()
{
	static CSocketConnector Inst;
	return Inst;
}


void CSocketConnector::Init(HWND hWnd,string strIP,int nPort)
{
	m_hWnd = hWnd;
	m_strIP = strIP;
	m_nPort = nPort;
}


DWORD CSocketConnector::DoJob()
{
	SOCKADDR_IN addrSrv ;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(m_strIP.c_str()) ;
	addrSrv.sin_family = AF_INET ;
	addrSrv.sin_port = htons(m_nPort) ;
	int len = sizeof(SOCKADDR) ;

	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	int nRet = connect(m_Sock ,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	if ( SOCKET_ERROR == nRet)
	{
		DWORD dwErr = GetLastError();
		closesocket(m_Sock);
		m_Sock = INVALID_SOCKET;
		Sleep(3000);
		return -1;
	}


	while(true)
	{
		char sz[256] = "ADDGDSGDAS";
		memset(sz,256,0);
		nRet = send(m_Sock, sz, 256, 0);
		if (SOCKET_ERROR == nRet)
		{
			//异常，关闭socket
			closesocket(m_Sock);
			m_Sock = INVALID_SOCKET;
			break;
		}


		//接收数据处理
		//PostMessage(m_hWnd,MSG_XX,WPARAM(sz),0);

		Sleep(3000);
	}

	return 0L;
}