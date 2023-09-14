#include "stdafx.h"
#include "ConnSocket.h"
#include "ClientSocketAutoReconnectDlg.h"

CConnSocket::CConnSocket(CClientSocketAutoReconnectDlg* pDlg)
	:m_pDlg(pDlg)
{

}


CConnSocket::~CConnSocket()
{

}


void CConnSocket::Init(CString strIP,UINT nPort)
{
	m_strServerIP = strIP;
	m_nPort = nPort;
}

void CConnSocket::OnConnect(int nErrorCode)
{
	m_bConnect = true;
	CSocket::OnConnect(nErrorCode);
}

void CConnSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
}

void CConnSocket::OnReceive(int nErrorCode)
{
	CString sziP;//用来存发来IP
    UINT nPort;//端口
	char sz[2048] = {0};//数据
	int rLen = ReceiveFrom(sz,sizeof(sz),sziP,nPort);//返回值，成功就返回接收长度
	sz[rLen]=0;
	CClientSocketAutoReconnectDlg *pDlg= (CClientSocketAutoReconnectDlg*)AfxGetMainWnd();
	CString strReceive(sz);
	pDlg->OnReceive(strReceive);//调用自定义函数，把s传过去
}