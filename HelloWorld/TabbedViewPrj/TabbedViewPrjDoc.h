// TabbedViewPrjDoc.h : interface of the CTabbedViewPrjDoc class
//


#pragma once


class CTabbedViewPrjDoc : public CDocument
{
protected: // create from serialization only
	CTabbedViewPrjDoc();
	DECLARE_DYNCREATE(CTabbedViewPrjDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CTabbedViewPrjDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


