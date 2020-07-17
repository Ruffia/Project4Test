#include "stdafx.h"
#include "ConnSocket.h"
#include "ClientSocketDlg.h"

CConnSocket::CConnSocket(CClientSocketDlg* pDlg)
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
	CString sziP;//�����淢��IP
    UINT nPort;//�˿�
	char sz[2048] = {0};//����
	int rLen = ReceiveFrom(sz,sizeof(sz),sziP,nPort);//����ֵ���ɹ��ͷ��ؽ��ճ���
	sz[rLen]=0;
	CClientSocketDlg *pDlg= (CClientSocketDlg*)AfxGetMainWnd();
	CString strReceive(sz);
	pDlg->OnReceive(strReceive);//�����Զ��庯������s����ȥ
}