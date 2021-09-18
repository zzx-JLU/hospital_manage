
// HospitalManageDlg.h: 头文件
//

#pragma once


// CHospitalManageDlg 对话框
class CHospitalManageDlg : public CDialogEx
{
// 构造
public:
	CHospitalManageDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSPITALMANAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancle();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonSave();
	void EditItem(struct ZhenLiao* p, int nItem); //将诊疗信息结点写在列表第nItem行
	void EditList(struct ZhenLiao* head); //将诊疗信息链表写入列表
	afx_msg void OnBnClickedButtonInfo();
	afx_msg void OnClose();
	CDateTimeCtrl m_SystemTime;
	afx_msg void OnBnClickedButtonDoctor();
	afx_msg void OnDtnDatetimechangeDatetimepickerSystem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonRoomadjust();
	afx_msg void OnBnClickedButtonPredict();
	afx_msg void OnBnClickedButtonFile();
};
