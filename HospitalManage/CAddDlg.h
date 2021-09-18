#pragma once


// CAddDlg 对话框

class CAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDlg)

public:
	CAddDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_PatientName;
	int m_PatientAge;
	CDateTimeCtrl m_Time;
	CString m_DoctorGrade;
	int m_DoctorID;
//	long long m_PatientID;
	int m_Radio;
	float m_CheckFee;
	float m_DrugFee;
	CDateTimeCtrl m_StartTime;
	CDateTimeCtrl m_EndTime;
	int m_deposit;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio2();
	CListCtrl m_listCheck;
	CListCtrl m_listDrug;
	void EnableCheck(bool);
	void EnableDrug(bool);
	void EnableZhuYuan(bool);
	afx_msg void OnCbnSelchangeComboDepartment();
	afx_msg void OnCbnSelchangeComboDoctorname();
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	CComboBox m_ComboDepartment;
	CComboBox m_ComboName;
	CString m_department;
	CString m_DoctorName;
	struct Doctor* target;
	afx_msg void OnDtnDatetimechangeDatetimepicker3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	int m_PatientID;
	CComboBox m_ComboRoom;
	int m_room;
	CComboBox m_ComboType;
	CString m_type;
	afx_msg void OnCbnSelchangeComboType();
	CComboBox m_ComboNurse;
	afx_msg void OnCbnSelchangeComboNurse();
	CString m_nurse;
	afx_msg void OnCbnSelchangeComboRoom();
	int m_ID;
};
