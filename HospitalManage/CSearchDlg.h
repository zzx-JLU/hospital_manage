#pragma once


// CSearchDlg 对话框

class CSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSearchDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	int m_Radio;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRadio1();
	void EnablePatient(bool);
	void EnableTime(bool);
	int m_PatientAge;
	CString m_PatientName;
	CDateTimeCtrl m_startTime;
	CDateTimeCtrl m_endTime;
	CComboBox m_ComboDepartment;
	CComboBox m_ComboDoctor;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
//	CString m_department;
//	CString m_doctor;
	void EditItem(struct ZhenLiao* p, int nItem);
	afx_msg void OnBnClickedButtonShanchu();
	afx_msg void OnBnClickedButtonSearchok();
	afx_msg void OnBnClickedButtonSearchcancle();
	CString m_doctor;
	CString m_department;
};
