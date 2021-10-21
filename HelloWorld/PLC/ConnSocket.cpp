#include "stdafx.h"
#include "ConnSocket.h"
#include "PLCDlg.h"

CConnSocket::CConnSocket(CPLCDlg* pDlg)
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
	//CString sziP;//�����淢��IP
 //   UINT nPort;//�˿�
	//byte sz[2048] = {0};//����
	//int rLen = ReceiveFrom(sz,sizeof(sz),sziP,nPort);//����ֵ���ɹ��ͷ��ؽ��ճ���
	//sz[rLen]=0;
	//CPLCDlg *pDlg= (CPLCDlg*)AfxGetMainWnd();
	//CString strReceive(sz);
	//pDlg->OnReceive(strReceive);//�����Զ��庯������s����ȥ

	CString sziP;//�����淢��IP
	UINT nPort;//�˿�
	byte* sz = new byte[64];//����
	memset(sz,0,64);
	int rLen = ReceiveFrom(sz,64,sziP,nPort);//����ֵ���ɹ��ͷ��ؽ��ճ���
	if (rLen <= 0) return;

	CString sMsg = _T("");
	for (int i = 0; i < rLen;i++)
	{
		CString sByte = _T("");
		sByte.Format(_T("%X "), sz[i]);
		sMsg += sByte;
	}

	delete sz;
	sz = NULL;

	CPLCDlg *pDlg= (CPLCDlg*)AfxGetMainWnd();
	CString strReceive(sMsg);
	pDlg->OnReceive(strReceive);//�����Զ��庯������s����ȥ
}