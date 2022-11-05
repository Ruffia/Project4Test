#pragma once


// HsMDIClient
#include "HMDIContainer.h"

class IViewsAccessor;
class HsMDIClient : public CWnd
{
	DECLARE_DYNAMIC(HsMDIClient)

public:
	HsMDIClient();
	virtual ~HsMDIClient();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	virtual void PreSubclassWindow();

public:
	HsMDIContainer* GetDefaultMDIContainer()
	{
		return &m_mdiDefaultContainer;
	}

	HsTabContainer* GetTabBar()
	{
		return &m_tabBar;
	}


	void AddView(CView* pView);
	void RemoveView(CView* pView);
	void ArrangeWindows();
	void GetViewsArray(IViewsAccessor* pViewsAccessor);
	
protected:
	// actually there should be a list of them
	HsMDIContainer m_mdiDefaultContainer;
	
	HsTabContainer m_tabBar;

	int m_cx, m_cy;

public:
	CArray<CView*, CView*&>	m_arrayViews;
	CArray<CView*, CView*&>	m_arrayTiledViews;
	CArray<CView*, CView*&>	m_arrayUnTiledViews;

protected:
	LRESULT OnMDISetMenu(WPARAM wParam, LPARAM lParam);	
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void UpdateTileInfo(bool bHideUntiledWindow);

	CWnd* m_lastFocussedWnd;
	bool m_bTiling;
};


