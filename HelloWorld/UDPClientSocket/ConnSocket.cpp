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
	char sz[2048] = {0};//����
	int rLen = ReceiveFrom(sz,sizeof(sz),m_strServerIP,m_nPort);//����ֵ���ɹ��ͷ��ؽ��ճ���
	if(rLen <= 0) return;
	sz[rLen]=0;
	CUDPClientSocketDlg *pDlg= (CUDPClientSocketDlg*)AfxGetMainWnd();
	CString strReceive(sz);
	pDlg->OnReceive(strReceive);//�����Զ��庯������s����ȥ
}