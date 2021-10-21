#include "stdafx.h"
#include "ListenSocket.h"

CListenSocket::CListenSocket(const int nPort,HWND hWnd):
	m_nPort(nPort),m_hWnd(hWnd)
{
	m_Sock2Client.clear();
}


void CListenSocket::OnAccept(int nErrorCode)
{
	if (0 != nErrorCode)
	{
		return;
	}

	//����һ������Socket
	CListenSocket* sock = new CListenSocket(0,m_hWnd);
	SOCKADDR addr;
	Accept(*sock,&addr);    //connectSocket���Ϳͻ�������
	m_Sock2Client[sock] = sock;
	char* sz = new char[1024];
	memset(sz,0,1024);

	sockaddr_in* pSin = (sockaddr_in*)&addr;
	char* sIP = inet_ntoa(pSin->sin_addr);
	sprintf_s(sz,1024,"%s connect in,port = %d",sIP,pSin->sin_port);
	::PostMessage(m_hWnd,WM_SOCKET_ACCEPT_CLIENT,(WPARAM)sz,(LPARAM)0);

	CSocket::OnAccept(nErrorCode);
}


void CListenSocket::OnReceive(int nErrorCode)
{
	//CString sziP;//�����淢��IP
	//UINT nPort;//�˿�
	//char* sz = new char[2048];//����
	//memset(sz,0,2048);
	//int rLen = ReceiveFrom(sz,2048,sziP,nPort);//����ֵ���ɹ��ͷ��ؽ��ճ���
	//sz[rLen]=0;
	//::PostMessage(m_hWnd,WM_SOCKET_RECEIVE_MSG,(WPARAM)sz,0);

	CString sziP;//�����淢��IP
	UINT nPort;//�˿�
	byte* sz = new byte[64];//����
	memset(sz,0,64);
	int rLen = ReceiveFrom(sz,64,sziP,nPort);//����ֵ���ɹ��ͷ��ؽ��ճ���
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