// CustomTabCtrlDemoMDIDoc.h : interface of the CCustomTabCtrlDemoMDIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMTABCTRLDEMOMDIDOC_H__018A092D_B911_43B9_9F5D_DA0BB455FB0F__INCLUDED_)
#define AFX_CUSTOMTABCTRLDEMOMDIDOC_H__018A092D_B911_43B9_9F5D_DA0BB455FB0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCustomTabCtrlDemoMDIDoc : public CDocument
{
protected: // create from serialization only
	CCustomTabCtrlDemoMDIDoc();
	DECLARE_DYNCREATE(CCustomTabCtrlDemoMDIDoc)

// Attributes
public:
	CString m_sLabel;
	CString m_sTooltip;
	CString m_sUrl;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomTabCtrlDemoMDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomTabCtrlDemoMDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomTabCtrlDemoMDIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTABCTRLDEMOMDIDOC_H__018A092D_B911_43B9_9F5D_DA0BB455FB0F__INCLUDED_)
