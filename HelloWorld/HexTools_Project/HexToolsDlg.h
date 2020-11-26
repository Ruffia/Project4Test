// HexToolsDlg.h : Header-Datei
//

#if !defined(AFX_HEXTOOLSDLG_H__8830449B_3992_47BE_8CBE_82DA1482BDAB__INCLUDED_)
#define AFX_HEXTOOLSDLG_H__8830449B_3992_47BE_8CBE_82DA1482BDAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHexToolsDlg Dialogfeld

class CHexToolsDlg : public CDialog
{
// Konstruktion
public:
	CHexToolsDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CHexToolsDlg)
	enum { IDD = IDD_HEXTOOLS_DIALOG };
	int		m_nDecInt;
	short		m_sDecShort;
	DWORD		m_dwDecDWORD;
	WORD		m_wDecWORD;
	BYTE		m_bDecByte;
	CString  m_strDecString;
	int		m_nHexInt;
	short		m_sHexShort;
	DWORD		m_dwHexDWORD;
	WORD		m_wHexWORD;
	BYTE		m_bHexByte;
	CString  m_strHexString;
	int		m_nBitInt;
	short		m_sBitShort;
	DWORD		m_dwBitDWORD;
	WORD		m_wBitWORD;
	BYTE		m_bBitByte;
	CString  m_strBracketString;


	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CHexToolsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CHexToolsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonApply0();
	afx_msg void OnButtonApply1();
	afx_msg void OnButtonApply2();
	//}}AFX_MSG
   afx_msg void OnBitWnds(UINT nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_HEXTOOLSDLG_H__8830449B_3992_47BE_8CBE_82DA1482BDAB__INCLUDED_)
