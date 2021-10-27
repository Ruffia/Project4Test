#include "StdAfx.h"
#include "PLCQueryCommandThread.h"

CPLCQueryCommandThread::CPLCQueryCommandThread(CCommSocket* pSocket,CQueryCommandBase* pCommand)
	:m_pSocket(pSocket),m_pCommand(pCommand)
{
	m_bTaskDone = false;
	m_dwSleep = 100;
}

CPLCQueryCommandThread::~CPLCQueryCommandThread()
{

}


UINT CPLCQueryCommandThread::WorkThread(LPVOID lpData)
{
	CPLCQueryCommandThread *pThread = (CPLCQueryCommandThread *)lpData;
	ASSERT(pThread);
	while(!pThread->m_bTaskDone)
	{
		if( WaitForSingleObject(pThread->m_hExitEvent, pThread->m_dwSleep) == WAIT_OBJECT_0 )
			break;
		pThread->DoJob();
		Sleep(10);
	}

	return 0;
}


DWORD CPLCQueryCommandThread::DoJob()
{
	if(!m_pSocket) return -1;

	m_pCommand->BuildCommand();
	byte* pData = m_pCommand->m_pCommand;
	int nLen = _msize(pData);
    PostMessage(m_hWnd,WM_PLC_THREAD_DATA,(WPARAM)pData,(LPARAM)nLen);

	int nRet = m_pSocket->Send(m_pCommand->m_pCommand);
	if (-1 == nRet)
	{
		char szError[256] = {0};
		sprintf_s(szError, 256,"Send Faild: %d", GetLastError());
		return nRet;
	}

	return nRet;
}