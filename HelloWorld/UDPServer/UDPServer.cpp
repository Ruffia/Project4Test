#include <stdio.h>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	//≥ı ºªØsocketø‚
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		return 0;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) 
	{
		WSACleanup( );
		return 0; 
	}
	SOCKET sockSrv = socket( AF_INET , SOCK_DGRAM , 0 ) ;
	SOCKADDR_IN addrSrv ;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY) ;
	addrSrv.sin_family = AF_INET ;
	addrSrv.sin_port = htons(5678) ;
	bind( sockSrv , (SOCKADDR*)&addrSrv , sizeof(SOCKADDR) ) ;

	char sendBuf[100]  = {0};
	char recvBuf[100]  = {0};
	char tempBuf[200]  = {0};
	SOCKADDR_IN addrClient ;
	int len = sizeof(SOCKADDR) ;
	while (1)
	{
		recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR*)&addrClient,&len) ;
		recvBuf[strlen(recvBuf)] = 0;
		if ( 'q' == recvBuf[0] )
		{
			sendto(sockSrv,"q",strlen("q")+1,0,(SOCKADDR*)&addrClient,len) ;
			printf("chat end!\n") ;
			break ;
		}
		sprintf(tempBuf,"%s say : %s",inet_ntoa(addrClient.sin_addr),recvBuf) ;
		printf( "%s\n" , tempBuf ) ;
		printf( "Please input data:\n" ) ;
		gets( sendBuf ) ;
		sendto(sockSrv,sendBuf,strlen(sendBuf),0,(SOCKADDR*)&addrClient,len) ;
	}
	closesocket( sockSrv ) ;
	WSACleanup() ;

	return 0;
}
