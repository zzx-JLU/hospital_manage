// CCheckDlg.cpp: 实现文件
//

#include "pch.h"
#include "HospitalManage.h"
#include "CCheckDlg.h"
#include "afxdialogex.h"


// CCheckDlg 对话框

IMPLEMENT_DYNAMIC(CCheckDlg, CDialogEx)

CCheckDlg::CCheckDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHECK, pParent)
	, m_count(0)
	, m_price(0)
	, m_checkName(_T(""))
{

}

CCheckDlg::~CCheckDlg()
{
}

void CCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Count, m_count);
	DDV_MinMaxInt(pDX, m_count, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_FEE, m_price);
	DDV_MinMaxFloat(pDX, m_price, 0, FLT_MAX);
	DDX_Text(pDX, IDC_EDIT_Item, m_checkName);
}


BEGIN_MESSAGE_MAP(CCheckDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Y, &CCheckDlg::OnBnClickedButtonY)
END_MESSAGE_MAP()


// CCheckDlg 消息处理程序


void CCheckDlg::OnBnClickedButtonY()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_count < 0)
		MessageBox(L"请输入正整数", L"提示");
	else
		CDialog::OnOK();
}


BOOL CCheckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


