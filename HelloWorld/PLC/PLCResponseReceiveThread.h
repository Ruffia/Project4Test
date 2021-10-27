#pragma once
#include "ThreadBase.h"
#include "CommSocket.h"

class CPLCResponseReceiveThread : public CThreadBase
{
public:
	CPLCResponseReceiveThread(CCommSocket* pSocket);
	virtual ~CPLCResponseReceiveThread();

public:
	virtual DWORD DoJob();

private:
	CCommSocket* m_pSocket;
};
