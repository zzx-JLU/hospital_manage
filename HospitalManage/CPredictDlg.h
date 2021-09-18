#pragma once


// CPredictDlg 对话框

class CPredictDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPredictDlg)

public:
	CPredictDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPredictDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PREDICT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboDepartment;
	CString m_department;
//	int m_first;
	int m_fifth;
	int m_first;
	int m_fourth;
	int m_result;
	int m_second;
	int m_third;
	afx_msg void OnBnClickedButtonStartpredict();
	afx_msg void OnCbnSelchangeComboSelect();
	virtual BOOL OnInitDialog();
};
