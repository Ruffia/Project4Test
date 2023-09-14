#pragma once
#include <string>
using namespace std;
#include <winsock2.h>  
#include "StatusDetector.h"

class  CSocketConnector : public CStatusDetector
{
protected:
	CSocketConnector();
	~CSocketConnector();

public:
	static CSocketConnector& Instance();
	void Init( HWND hWnd,string strIP,int nPort);
	virtual DWORD DoJob();

public:
	SOCKET m_Sock;
	string m_strIP;
	HWND   m_hWnd;
	int    m_nPort;
};