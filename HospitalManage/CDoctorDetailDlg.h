#pragma once


// CDoctorDetailDlg 对话框

class CDoctorDetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDoctorDetailDlg)

public:
	CDoctorDetailDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDoctorDetailDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DoctorDetail };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_ComboDepartment;
	CString m_department;
//	int m_id;
	CString m_name;
	CComboBox m_ComboGrade;
	CString m_grade;
	virtual BOOL OnInitDialog();
//	CButton m_ckeck1;
	CButton m_check2;
	CButton m_check3;
//	CButton check4;
	CButton m_check4;
	CButton m_check5;
	CButton m_check6;
	CButton m_check7;
	CComboBox m_ComboState;
	CString m_state;
//	CButton m_check;
	CButton m_check1;
	afx_msg void OnCbnSelchangeComboGrade();
	afx_msg void OnCbnSelchangeComboKeshi();
	afx_msg void OnCbnSelchangeComboState();
	int m_id;
};
