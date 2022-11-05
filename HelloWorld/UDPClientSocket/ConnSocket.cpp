#include "stdafx.h"
#include "ConnSocket.h"
#include "UDPClientSocketDlg.h"

CConnSocket::CConnSocket(CUDPClientSocketDlg* pDlg)
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


void CConnSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
}

void CConnSocket::OnReceive(int nErrorCode)
{
	char sz[2048] = {0};//数据
	int rLen = ReceiveFrom(sz,sizeof(sz),m_strServerIP,m_nPort);//返回值，成功就返回接收长度
	if(rLen <= 0) return;
	sz[rLen]=0;
	CUDPClientSocketDlg *pDlg= (CUDPClientSocketDlg*)AfxGetMainWnd();
	CString strReceive(sz);
	pDlg->OnReceive(strReceive);//调用自定义函数，把s传过去
}