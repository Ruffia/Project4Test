#include "stdafx.h"
#include "ListenSocket.h"

CUDPSocket::CUDPSocket(HWND hWnd):m_hWnd(hWnd)
{

}


void CUDPSocket::OnReceive(int nErrorCode)
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