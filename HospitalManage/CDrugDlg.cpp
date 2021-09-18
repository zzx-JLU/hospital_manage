// CDrugDlg.cpp: 实现文件
//

#include "pch.h"
#include "HospitalManage.h"
#include "CDrugDlg.h"
#include "afxdialogex.h"


// CDrugDlg 对话框

IMPLEMENT_DYNAMIC(CDrugDlg, CDialogEx)

CDrugDlg::CDrugDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DRUG, pParent)
	, m_drugName(_T(""))
	, m_num(0)
	, m_price(0)
{

}

CDrugDlg::~CDrugDlg()
{
}

void CDrugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DrugName, m_drugName);
	DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	DDV_MinMaxInt(pDX, m_num, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_price);
	DDV_MinMaxFloat(pDX, m_price, 0, FLT_MAX);
}


BEGIN_MESSAGE_MAP(CDrugDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDrugDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDrugDlg 消息处理程序


void CDrugDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


BOOL CDrugDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
