#include "stdafx.h"
#include "CommSocket.h"
#include "PLCDlg.h"

CCommSocket::CCommSocket()
{
	memset(m_szIP,64,0);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData );
	m_Socket = socket( AF_INET , SOCK_DGRAM , 0 ) ;

}

CCommSocket::~CCommSocket()
{
	closesocket(m_Socket) ;
	WSACleanup() ;
}

void CCommSocket::Init(const char* sIP,UINT nPort)
{	
	sprintf_s(m_szIP,"%s",sIP);
	m_szIP[strlen(sIP)] = 0;
	m_nPort = nPort;
}


int CCommSocket::Send(byte* bData)
{
	SOCKADDR_IN addrSrv ;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(m_szIP) ;
	addrSrv.sin_family = AF_INET ;
	addrSrv.sin_port = htons(m_nPort) ;
	int len = sizeof(SOCKADDR) ;
	int nDataLen = _msize(bData);
	int nSend = sendto(m_Socket, (char*)bData, nDataLen , 0 , (SOCKADDR*)&addrSrv, len) ; 
	return nSend;
}


int CCommSocket::Receive(byte* bData)
{
	SOCKADDR_IN addrSrv ;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(m_szIP) ;
	addrSrv.sin_family = AF_INET ;
	addrSrv.sin_port = htons(m_nPort) ;
	int len = sizeof(SOCKADDR) ;
	int nDataLen = _msize(bData);
	int nReceive = recvfrom( m_Socket , (char*)bData , nDataLen , 0 , (SOCKADDR*)&addrSrv , &len ) ;
	return nReceive;
}