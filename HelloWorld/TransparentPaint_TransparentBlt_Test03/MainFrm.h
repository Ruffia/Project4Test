
// MainFrm.h : CMainFrame ��Ľӿ�
//
#include "TransparentBltTestDlg.h"
#include "TransparentBltTestDlg02.h"

#pragma once

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:
	CTransparentBltTestDlg    m_dlgTransparentBltTest;
	CTransparentBltTestDlg02  m_dlgTransparentBltTest02;
// ����
public:
   void	AdjustPanelPos();
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


