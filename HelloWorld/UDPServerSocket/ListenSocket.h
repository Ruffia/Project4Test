#pragma once
#include <afxsock.h>
#include <map>
using namespace std;

#define WM_SOCKET_ACCEPT_CLIENT WM_USER + 100
#define WM_SOCKET_RECEIVE_MSG   WM_USER + 101

class CUDPSocket : public CSocket
{
public:
	CUDPSocket(HWND hWnd=NULL);

protected:
	HWND m_hWnd; //事件处理窗口


protected:
	virtual void OnReceive(int nErrorCode);
};