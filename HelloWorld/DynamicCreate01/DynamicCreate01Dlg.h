
// DynamicCreate01Dlg.h : ͷ�ļ�
//

#pragma once


// CDynamicCreate01Dlg �Ի���
class CDynamicCreate01Dlg : public CDialogEx
{
// ����
public:
	CDynamicCreate01Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DYNAMICCREATE01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	void _CreateButton();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();

	void _DrawCircle();

	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonClick(UINT uID);
	DECLARE_MESSAGE_MAP()
};
