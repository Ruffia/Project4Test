#pragma once
#include <afxsock.h>
class CClientSocketAutoReconnectDlg;
class CConnSocket : public CSocket
{
public:
	CConnSocket(CClientSocketAutoReconnectDlg* dlg = NULL);
	virtual ~CConnSocket();

	void Init(CString strIP,UINT nPort);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
private:
	CString m_strServerIP;
	UINT m_nPort;
	CClientSocketAutoReconnectDlg* m_pDlg;
	bool m_bConnect;
public:
	virtual void OnReceive(int nErrorCode);
};