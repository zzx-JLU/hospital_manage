#pragma once


// CInfoDlg 对话框

class CInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoDlg)

public:
	CInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_turnover;
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	int m_count;
	afx_msg void OnBnClickedButtonZhuyuan();
	void EditItem(struct ZhenLiao* p, int nItem);
	CListCtrl m_listRoom;
};
