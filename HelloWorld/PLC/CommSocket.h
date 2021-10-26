#pragma once
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

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