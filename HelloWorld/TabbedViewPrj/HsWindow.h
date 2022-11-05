#pragma once


// HsWindow

class HsWindow : public CWnd
{
	DECLARE_DYNAMIC(HsWindow)

public:
	HsWindow();
	virtual ~HsWindow();
	void ResizeWindow(int cx, int cy, BOOL bRedraw = FALSE);
	void DrawGradientRect(CDC *pDC, CRect r, COLORREF cLeft, COLORREF cRight, BOOL bVertical);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


