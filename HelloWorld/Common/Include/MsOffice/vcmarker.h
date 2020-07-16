#if !defined(AFX_VCMARKER_H__89164835_4328_11D6_9373_B2FE5AB4317A__INCLUDED_)
#define AFX_VCMARKER_H__89164835_4328_11D6_9373_B2FE5AB4317A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CVcPen;
class CVcColor;

/////////////////////////////////////////////////////////////////////////////
// CVcMarker wrapper class

class CVcMarker : public COleDispatchDriver
{
public:
	CVcMarker() {}		// Calls COleDispatchDriver default constructor
	CVcMarker(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcMarker(const CVcMarker& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetStyle();
	void SetStyle(long nNewValue);
	CVcPen GetPen();
	float GetSize();
	void SetSize(float newValue);
	CVcColor GetFillColor();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCMARKER_H__89164835_4328_11D6_9373_B2FE5AB4317A__INCLUDED_)
