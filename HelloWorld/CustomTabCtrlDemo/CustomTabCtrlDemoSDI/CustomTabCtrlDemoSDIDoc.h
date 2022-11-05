// CustomTabCtrlDemoSDIDoc.h : interface of the CCustomTabCtrlDemoSDIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMTABCTRLDEMOSDIDOC_H__C2A9364A_283E_4673_B848_BC659BE623A6__INCLUDED_)
#define AFX_CUSTOMTABCTRLDEMOSDIDOC_H__C2A9364A_283E_4673_B848_BC659BE623A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCustomTabCtrlDemoSDIDoc : public CDocument
{
protected: // create from serialization only
	CCustomTabCtrlDemoSDIDoc();
	DECLARE_DYNCREATE(CCustomTabCtrlDemoSDIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomTabCtrlDemoSDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomTabCtrlDemoSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomTabCtrlDemoSDIDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CStringArray m_aStrings;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTABCTRLDEMOSDIDOC_H__C2A9364A_283E_4673_B848_BC659BE623A6__INCLUDED_)
