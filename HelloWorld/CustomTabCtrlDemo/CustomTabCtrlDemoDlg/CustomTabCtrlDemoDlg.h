// CustomTabCtrlDemoDlg.h : header file
//

#if !defined(AFX_CUSTOMTABCTRLDEMODLG_H__B07EA255_FBFF_47A2_BFBA_A8E170BD0FCC__INCLUDED_)
#define AFX_CUSTOMTABCTRLDEMODLG_H__B07EA255_FBFF_47A2_BFBA_A8E170BD0FCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\CustomTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoDlg dialog

class CCustomTabCtrlDemoDlg : public CDialog
{
// Construction
public:
	CCustomTabCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomTabCtrlDemoDlg)
	enum { IDD = IDD_CUSTOMTABCTRLDEMO_DIALOG };
	CButton	m_ctrlButtonsAfter;
	CButton	m_ctrlRTL;
	CButton	m_ctrlClose;
	CButton	m_ctrlDragmove;
	CButton	m_ctrlDragcopy;
	CButton	m_ctrl4Buttons;
	CButton	m_ctrlAutoHide;
	CButton	m_ctrlFixed;
	CButton	m_ctrlTooltips;
	CButton	m_ctrlMultihighlight;
	CButton	m_ctrlEditlabels;
	CStatic	m_ctrlColor;
	CCustomTabCtrl	m_ctrlTab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomTabCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCustomTabCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFixedck();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnFourbuttonsck();
	afx_msg void OnAutohidebuttonsck();
	afx_msg void OnMultihighlightck();
	afx_msg void OnTooltipsck();
	afx_msg void OnEditlabelsck();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDragmoveck();
	afx_msg void OnDragcopyck();
	afx_msg void OnClosebuttonsck();
	afx_msg void OnRtlyck();
	afx_msg void OnButtonsafterck();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	//}}AFX_MSG
	// Notify messages from CCustomTabCtrl
	afx_msg void OnLButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnRButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHighlightchangeTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnMoveitemTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnCopyitemTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnLabelupdateTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	DECLARE_MESSAGE_MAP()

private:
	void Size(int cx, int cy);
	LPCTSTR GetTooltipText(int nStyle);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTABCTRLDEMODLG_H__B07EA255_FBFF_47A2_BFBA_A8E170BD0FCC__INCLUDED_)
