
// TransparentPaint_StretchBlt_Test02Dlg.h : ͷ�ļ�
//

#pragma once


// CTransparentPaint_StretchBlt_Test02Dlg �Ի���
class CTransparentPaint_StretchBlt_Test02Dlg : public CDialogEx
{
// ����
public:
	CTransparentPaint_StretchBlt_Test02Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	BOOL PaintTransparentBmp(char* sImage);

// �Ի�������
	enum { IDD = IDD_TRANSPARENTPAINT_STRETCHBLT_TEST02_DIALOG };

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
};
