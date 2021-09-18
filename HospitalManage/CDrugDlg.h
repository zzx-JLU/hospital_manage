#pragma once


// CDrugDlg 对话框

class CDrugDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugDlg)

public:
	CDrugDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDrugDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DRUG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_drugName;
	int m_num;
	float m_price;
	virtual BOOL OnInitDialog();
};
