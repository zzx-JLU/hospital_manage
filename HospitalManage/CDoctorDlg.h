#pragma once


// CDoctorDlg 对话框

class CDoctorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDoctorDlg)

public:
	CDoctorDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDoctorDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Doctor };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listDoctor;
	virtual BOOL OnInitDialog();
	void EditItem(struct Doctor* pDoctor, int nItem);
	void EditList(struct Doctor* pHead);
	afx_msg void OnNMDblclkListDoctor(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonAdddoctor();
};
