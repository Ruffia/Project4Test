// FastProcessingDlg.h : header file
//

#include "afxwin.h"
#if !defined(AFX_FASTPROCESSINGDLG_H__BBCE1750_5560_4863_BB2F_FF61437B2131__INCLUDED_)
#define AFX_FASTPROCESSINGDLG_H__BBCE1750_5560_4863_BB2F_FF61437B2131__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFastProcessingDlg dialog

class CFastProcessingDlg : public CDialog
{
// Construction
public:
	CFastProcessingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFastProcessingDlg)
	enum { IDD = IDD_FASTPROCESSING_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFastProcessingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFastProcessingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnColor;
	afx_msg void OnBnClickedButtonSettext();
	afx_msg void OnBnClickedButton3();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASTPROCESSINGDLG_H__BBCE1750_5560_4863_BB2F_FF61437B2131__INCLUDED_)
