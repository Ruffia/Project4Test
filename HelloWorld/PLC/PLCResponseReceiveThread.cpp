#include "StdAfx.h"
#include "PLCResponseReceiveThread.h"

CPLCResponseReceiveThread::CPLCResponseReceiveThread(CCommSocket* pSocket)
	:m_pSocket(pSocket)
{
	m_dwSleep = 100;
}

CPLCResponseReceiveThread::~CPLCResponseReceiveThread()
{

}


DWORD CPLCResponseReceiveThread::DoJob()
{
	if(!m_pSocket) return -1;

	byte* pData = new byte[64];
	memset(pData,0,64);
	int nRecv = m_pSocket->Receive(pData);
	if(nRecv <= 0) return -1;

	PostMessage(m_hWnd,WM_PLC_THREAD_DATA,(WPARAM)pData,(LPARAM)nRecv);
	return 0;
}