// CustomTabCtrlDemoMDIDoc.cpp : implementation of the CCustomTabCtrlDemoMDIDoc class
//

#include "stdafx.h"
#include "CustomTabCtrlDemoMDI.h"
#include "CustomTabCtrlDemoMDIDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIDoc

IMPLEMENT_DYNCREATE(CCustomTabCtrlDemoMDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CCustomTabCtrlDemoMDIDoc, CDocument)
	//{{AFX_MSG_MAP(CCustomTabCtrlDemoMDIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIDoc construction/destruction

CCustomTabCtrlDemoMDIDoc::CCustomTabCtrlDemoMDIDoc()
{
	// TODO: add one-time construction code here
	m_sLabel = _T("Dbl click to edit");
}

CCustomTabCtrlDemoMDIDoc::~CCustomTabCtrlDemoMDIDoc()
{
}

BOOL CCustomTabCtrlDemoMDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIDoc serialization

void CCustomTabCtrlDemoMDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIDoc diagnostics

#ifdef _DEBUG
void CCustomTabCtrlDemoMDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCustomTabCtrlDemoMDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoMDIDoc commands

