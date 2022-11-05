// TabbedViewPrjDoc.cpp : implementation of the CTabbedViewPrjDoc class
//

#include "stdafx.h"
#include "TabbedViewPrj.h"

#include "TabbedViewPrjDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTabbedViewPrjDoc

IMPLEMENT_DYNCREATE(CTabbedViewPrjDoc, CDocument)

BEGIN_MESSAGE_MAP(CTabbedViewPrjDoc, CDocument)
END_MESSAGE_MAP()


// CTabbedViewPrjDoc construction/destruction

CTabbedViewPrjDoc::CTabbedViewPrjDoc()
{
	// TODO: add one-time construction code here

}

CTabbedViewPrjDoc::~CTabbedViewPrjDoc()
{
}

BOOL CTabbedViewPrjDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CTabbedViewPrjDoc serialization

void CTabbedViewPrjDoc::Serialize(CArchive& ar)
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


// CTabbedViewPrjDoc diagnostics

#ifdef _DEBUG
void CTabbedViewPrjDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTabbedViewPrjDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTabbedViewPrjDoc commands
