#pragma once


// HsMDIContainer
#include "HsWindow.h"
#include "HTabContainer.h"
class HsMDIContainer : public HsWindow
{
	DECLARE_DYNAMIC(HsMDIContainer)

public:
	HsMDIContainer();
	virtual ~HsMDIContainer();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	HsTabContainer* GetTabContainer()
	{
		return &m_tabContainer;
	}
protected:
	HsTabContainer m_tabContainer;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:

public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


