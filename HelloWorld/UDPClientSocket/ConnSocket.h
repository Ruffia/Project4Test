#pragma once
#include <afxsock.h>
class CUDPClientSocketDlg;
class CConnSocket : public CSocket
{
public:
	CConnSocket(CUDPClientSocketDlg* dlg = NULL);
	virtual ~CConnSocket();

	void Init(CString strIP,UINT nPort);
	virtual void OnClose(int nErrorCode);
private:
	CString m_strServerIP;
	UINT m_nPort;
	CUDPClientSocketDlg* m_pDlg;
public:
	virtual void OnReceive(int nErrorCode);
};