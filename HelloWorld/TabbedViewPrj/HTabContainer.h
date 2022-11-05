#pragma once


// HsTabContainer
#include "HsWindow.h"
#include "HTabCtrl.h"
class HsTabContainer : public HsWindow
{
	DECLARE_DYNAMIC(HsTabContainer)

public:
	HsTabContainer();
	virtual ~HsTabContainer();

protected:
	DECLARE_MESSAGE_MAP()

public:
	HsTabCtrl* GetTabCtrl()
	{
		return &m_tabCtrl;
	}
	int GetHeight()
	{
		const int offsetTabContainerHeight = 4;
		return GetTabCtrl()->GetHeight() + offsetTabContainerHeight;
	}
protected:
	HsTabCtrl m_tabCtrl;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	LRESULT OnSizeParent(WPARAM, LPARAM lParam);	
};


