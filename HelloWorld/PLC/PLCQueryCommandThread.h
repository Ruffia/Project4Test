#pragma once
#include "ThreadBase.h"
#include "CommSocket.h"
#include "QueryCommandBase.h"

class CPLCQueryCommandThread : public CThreadBase
{
public:
	CPLCQueryCommandThread(CCommSocket* pSocket,CQueryCommandBase* pCommand);
	virtual ~CPLCQueryCommandThread();

public:
	virtual DWORD DoJob();

protected:
	static UINT WorkThread(LPVOID lpData);

public:
	//任务是否完成
	bool m_bTaskDone;

private:
	CCommSocket*        m_pSocket;
	CQueryCommandBase*  m_pCommand;
};
