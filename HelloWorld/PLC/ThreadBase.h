#pragma once
#include <afxmt.h>

class CThreadBase
{
public:
	CThreadBase();
	virtual ~CThreadBase();

public:
	virtual BOOL Start();
	BOOL End();
	virtual void Release();
	void SetSleep(DWORD dwSleep){ m_dwSleep = dwSleep; }
	void Attach(HWND hWnd){m_hWnd = hWnd;}
	virtual DWORD DoJob() = 0;
	bool m_bExitWorkThread;

protected:
	DWORD  m_dwSleep;
	HANDLE m_hExitEvent;
	HWND   m_hWnd;
	CCriticalSection m_cs;
	CWinThread *m_pWorkThread;	
	static UINT WorkThread(LPVOID lpData);
};
