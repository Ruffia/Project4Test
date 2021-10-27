#pragma once
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define  WM_PLC_THREAD_DATA    WM_USER + 3001
#define  WM_QUERY_THREAD_DATA  WM_USER + 3002
#define  Socket_RecvSize 64

//与PLC通信的Socket
class CCommSocket
{
public:
	CCommSocket();
	virtual ~CCommSocket();

	void Init(const char* sIP,UINT nPort);
	int  Send( byte* bData);
	int  Receive(byte* bData);

private:
	SOCKET m_Socket;
	char m_szIP[64];
	UINT m_nPort;
	bool m_bConnect;
};