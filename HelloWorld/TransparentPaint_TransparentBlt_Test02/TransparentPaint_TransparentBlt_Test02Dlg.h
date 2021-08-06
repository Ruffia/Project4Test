
// TransparentPaint_TransparentBlt_Test02Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "TransparentImage.h"


// CTransparentPaint_TransparentBlt_Test02Dlg 对话框
class CTransparentPaint_TransparentBlt_Test02Dlg : public CDialogEx
{
// 构造
public:
	CTransparentPaint_TransparentBlt_Test02Dlg(CWnd* pParent = NULL);	// 标准构造函数
	BOOL PaintTransparentBmp(HWND hWnd,int nPosX,int nPosY);

// 对话框数据
	enum { IDD = IDD_TRANSPARENTPAINT_TRANSPARENTBLT_TEST02_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTransparentImage m_staticPneumaticDiagram;
};
