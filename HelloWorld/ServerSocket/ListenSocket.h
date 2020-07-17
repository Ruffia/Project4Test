#pragma once
#include <afxsock.h>
#include <map>
using namespace std;

#define WM_SOCKET_ACCEPT_CLIENT WM_USER + 100
#define WM_SOCKET_RECEIVE_MSG   WM_USER + 101

class CListenSocket : public CSocket
{
public:
	CListenSocket(const int nPort = 0,HWND hWnd=NULL);

	map<CSocket*,CSocket*>& GetClient()
	{
		return m_Sock2Client;
	}

protected:
	HWND m_hWnd; //事件处理窗口
	int m_nPort;
	map<CSocket*,CSocket*> m_Sock2Client;

protected:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};