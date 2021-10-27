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
	SOCKET sockClient = socket( AF_INET , SOCK_DGRAM , 0 ) ;
	SOCKADDR_IN addrSrv ;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1") ;
	addrSrv.sin_family = AF_INET ;
	addrSrv.sin_port = htons(5678) ;
	char sendBuf[100] = {0} ;
	char recvBuf[100] = {0};
	char tempBuf[200] = {0};
	int len = sizeof(SOCKADDR) ;

	int n = 0;
	while (n < 10)
	{ 
		printf("Please input data:\n"); 
		gets( sendBuf ) ; 
		sendBuf[strlen(sendBuf)] = 0;
		sendto( sockClient , sendBuf , strlen(sendBuf) , 0 , (SOCKADDR*)&addrSrv , len ) ; 
		recvfrom( sockClient , recvBuf , 100 , 0 , (SOCKADDR*)&addrSrv , &len ) ;
		if ( 'q' == recvBuf[0] )
		{
			sendto(sockClient , "q" , strlen("q")+1 , 0 , (SOCKADDR*)&addrSrv , len) ;
			printf("chat end!") ;
			break ; 
		} 
		sprintf( tempBuf , "%s say: %s\n" , inet_ntoa(addrSrv.sin_addr) , recvBuf ) ;
		printf( tempBuf ) ;

		n++;
	}
	closesocket(sockClient) ;
	WSACleanup() ;

	return 0;
}