
// GetDeviceCapsDlg.h : ͷ�ļ�
//

#pragma once


// CGetDeviceCapsDlg �Ի���
class CGetDeviceCapsDlg : public CDialogEx
{
// ����
public:
	CGetDeviceCapsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GETDEVICECAPS_DIALOG };

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
	int m_nWidth;
	int m_nHeight;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonDebug();
	afx_msg void OnBnClickedButtonInch();
};
