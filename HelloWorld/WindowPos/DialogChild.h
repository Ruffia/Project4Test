#pragma once


// CDialogChild 对话框

class CDialogChild : public CDialog
{
	DECLARE_DYNAMIC(CDialogChild)

public:
	CDialogChild(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogChild();

// 对话框数据
	enum { IDD = IDD_DIALOG_Child };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
