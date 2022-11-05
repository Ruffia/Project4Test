#include "stdafx.h"
#include "ListenSocket.h"

CUDPSocket::CUDPSocket(HWND hWnd):m_hWnd(hWnd)
{

}


void CUDPSocket::OnReceive(int nErrorCode)
{
	//CString sziP;//用来存发来IP
	//UINT nPort;//端口
	//char* sz = new char[2048];//数据
	//memset(sz,0,2048);
	//int rLen = ReceiveFrom(sz,2048,sziP,nPort);//返回值，成功就返回接收长度
	//sz[rLen]=0;
	//::PostMessage(m_hWnd,WM_SOCKET_RECEIVE_MSG,(WPARAM)sz,0);

	CString sziP;//用来存发来IP
	UINT nPort;//端口
	byte* sz = new byte[64];//数据
	memset(sz,0,64);
	int rLen = ReceiveFrom(sz,64,sziP,nPort);//返回值，成功就返回接收长度
	if (rLen <= 0) return;

	CString sMsg = _T("");
	for (int i = 0; i < rLen;i++)
	{
		CString sByte = _T("");
		if (rLen -1 == i)
		{
			sByte.Format(_T("%02X"), sz[i]);
		}
		else
		{
			sByte.Format(_T("%02X "), sz[i]);
		}
		
		sMsg += sByte;
	}

	delete sz;
	sz = NULL;

	char* pMsg = new char[sMsg.GetLength() + 1];
	_tcscpy(pMsg, sMsg);

	::PostMessage(m_hWnd,WM_SOCKET_RECEIVE_MSG,(WPARAM)pMsg,0);
}