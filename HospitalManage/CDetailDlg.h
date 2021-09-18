#pragma once


// CDetailDlg 对话框

class CDetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailDlg)

public:
	CDetailDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDetailDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl m_TabCtrl;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	void ShowTAB1(bool);
	void ShowTAB2(bool);
	void ShowTAB3(bool);
	void ShowTAB4(bool);
	afx_msg void OnBnClickedButtonChangebasic();
	afx_msg void OnBnClickedButtonYes();
	afx_msg void OnBnClickedButtonNo();
	CListCtrl m_listCheck;
	CListCtrl m_listDrug;
//	afx_msg void OnNMClickListCheck(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnNMClickListDrug(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonAdddeposit();
	afx_msg void OnBnClickedButtonOut();
	float m_checkFee;
	CString m_doctorGrade;
	CString m_doctorID;
	float m_drugFee;
	int m_patientAge;
	CString m_patientID;
	CString m_patientName;
	CDateTimeCtrl m_startDate;
	CDateTimeCtrl m_endDate;
	CString m_department;
	CString m_doctorName;
	afx_msg void OnDtnDatetimechangeDatetimepickerEnd(NMHDR* pNMHDR, LRESULT* pResult);
	int m_deposit;
	int m_room;
	afx_msg void OnNMDblclkListCheck(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnLvnItemchangedListDrug(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkListDrug(NMHDR* pNMHDR, LRESULT* pResult);
};
