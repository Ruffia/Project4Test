#pragma once
#include <afxsock.h>
class CPLCDlg;
class CConnSocket : public CSocket
{
public:
	CConnSocket(CPLCDlg* dlg = NULL);
	virtual ~CConnSocket();

	void Init(CString strIP,UINT nPort);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
private:
	CString m_strServerIP;
	UINT m_nPort;
	CPLCDlg* m_pDlg;
	bool m_bConnect;
public:
	virtual void OnReceive(int nErrorCode);
};