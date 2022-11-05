#pragma once
#include "afxwin.h"

#include "HsButton.h"
// HsListTiledWindows dialog

class HsListTiledWindows : public CDialog
{
	DECLARE_DYNAMIC(HsListTiledWindows)

public:
	HsListTiledWindows(CWnd* pParent = NULL);   // standard constructor
	virtual ~HsListTiledWindows();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CCheckListBox m_listTiledWnds;
public:
	afx_msg void OnBnClickedOk();
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnCheckchangeListTiledWindows();

public:
	HsButton m_btnOk;
};
