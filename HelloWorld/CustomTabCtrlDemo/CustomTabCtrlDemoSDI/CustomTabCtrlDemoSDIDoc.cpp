// CustomTabCtrlDemoSDIDoc.cpp : implementation of the CCustomTabCtrlDemoSDIDoc class
//

#include "stdafx.h"
#include "CustomTabCtrlDemoSDI.h"

#include "CustomTabCtrlDemoSDIDoc.h"
#include "CustomTabCtrlDemoSDIView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIDoc

IMPLEMENT_DYNCREATE(CCustomTabCtrlDemoSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CCustomTabCtrlDemoSDIDoc, CDocument)
	//{{AFX_MSG_MAP(CCustomTabCtrlDemoSDIDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIDoc construction/destruction

CCustomTabCtrlDemoSDIDoc::CCustomTabCtrlDemoSDIDoc()
{
}

CCustomTabCtrlDemoSDIDoc::~CCustomTabCtrlDemoSDIDoc()
{
}

BOOL CCustomTabCtrlDemoSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	SetModifiedFlag();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIDoc serialization

void CCustomTabCtrlDemoSDIDoc::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		CStringArray a;
		CCustomTabCtrl& tab = ((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetTabCtrl();
		for(int i=0; i<tab.GetItemCount(); i++)
		{
			DWORD dwData;
			tab.GetItemData(i,dwData);
			CCustomTabCtrlDemoSDIView* pView = (CCustomTabCtrlDemoSDIView*)dwData;
			a.Add(pView->m_sLabel);
			a.Add(pView->m_sUrl);
			a.Add(pView->m_sTooltip);
		}
		a.Serialize(ar);
	}
	else
		m_aStrings.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIDoc diagnostics

#ifdef _DEBUG
void CCustomTabCtrlDemoSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCustomTabCtrlDemoSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDemoSDIDoc commands

void CCustomTabCtrlDemoSDIDoc::DeleteContents() 
{
	if(AfxGetApp()->m_pMainWnd)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->DeleteContents();
	CDocument::DeleteContents();
}

