
// BitmapColorTable02Dlg.h : ͷ�ļ�
//

#pragma once


// CBitmapColorTable02Dlg �Ի���
class CBitmapColorTable02Dlg : public CDialogEx
{
// ����
public:
	CBitmapColorTable02Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BITMAPCOLORTABLE02_DIALOG };

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
