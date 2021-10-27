#include "StdAfx.h"
#include "ThreadBase.h"

const UINT TIMEOUT_RETRYTIMES_MAX = 3;
const UINT TIMEOUT_MAX = 1*60*1000;

CThreadBase::CThreadBase()
{
	m_hExitEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);  
	m_dwSleep = 100;
	m_pWorkThread = NULL;
	m_bExitWorkThread = false;
}

CThreadBase::~CThreadBase()
{
	if(m_hExitEvent != NULL)
	{
		::CloseHandle(m_hExitEvent);
	}
}


UINT CThreadBase::WorkThread(LPVOID lpData)
{
	CThreadBase *pThreadBase = (CThreadBase *)lpData;
	ASSERT(pThreadBase);
	while(TRUE)
	{
		if( WaitForSingleObject(pThreadBase->m_hExitEvent, pThreadBase->m_dwSleep) == WAIT_OBJECT_0 )
			break;
		pThreadBase->DoJob();
		Sleep(10);
	}

	return 0;
}


BOOL CThreadBase::Start()
{
	if( m_pWorkThread == NULL )
	{
		m_pWorkThread = AfxBeginThread(WorkThread, this,0,0,CREATE_SUSPENDED,0);
		m_pWorkThread->m_bAutoDelete = FALSE;
		m_pWorkThread->ResumeThread();
		m_bExitWorkThread = false;
	}

	return TRUE;
}


BOOL CThreadBase::End()
{
	m_bExitWorkThread = true;
	if(m_pWorkThread != NULL)
	{
		if(m_hExitEvent != NULL)
			SetEvent(m_hExitEvent);
		WaitForSingleObject(m_pWorkThread->m_hThread, INFINITE);

		delete m_pWorkThread;
		m_pWorkThread = NULL;
	}

	return TRUE;
}


void CThreadBase::Release() 
{
	End();
	ResetEvent(m_hExitEvent);
}