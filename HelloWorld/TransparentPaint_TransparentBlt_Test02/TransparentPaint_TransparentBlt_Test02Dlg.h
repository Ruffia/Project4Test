
// TransparentPaint_TransparentBlt_Test02Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "TransparentImage.h"


// CTransparentPaint_TransparentBlt_Test02Dlg �Ի���
class CTransparentPaint_TransparentBlt_Test02Dlg : public CDialogEx
{
// ����
public:
	CTransparentPaint_TransparentBlt_Test02Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	BOOL PaintTransparentBmp(HWND hWnd,int nPosX,int nPosY);

// �Ի�������
	enum { IDD = IDD_TRANSPARENTPAINT_TRANSPARENTBLT_TEST02_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTransparentImage m_staticPneumaticDiagram;
};
