#pragma once


// CCheckDlg 对话框

class CCheckDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckDlg)

public:
	CCheckDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCheckDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHECK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonY();
	virtual BOOL OnInitDialog();
	int m_count;
	float m_price;
	CString m_checkName;
};
