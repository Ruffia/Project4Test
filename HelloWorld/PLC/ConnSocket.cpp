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
	//CString sziP;//用来存发来IP
 //   UINT nPort;//端口
	//byte sz[2048] = {0};//数据
	//int rLen = ReceiveFrom(sz,sizeof(sz),sziP,nPort);//返回值，成功就返回接收长度
	//sz[rLen]=0;
	//CPLCDlg *pDlg= (CPLCDlg*)AfxGetMainWnd();
	//CString strReceive(sz);
	//pDlg->OnReceive(strReceive);//调用自定义函数，把s传过去

	CString sziP;//用来存发来IP
	UINT nPort;//端口
	byte* sz = new byte[64];//数据
	memset(sz,0,64);
	int rLen = ReceiveFrom(sz,64,sziP,nPort);//返回值，成功就返回接收长度
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
	pDlg->OnReceive(strReceive);//调用自定义函数，把s传过去
}