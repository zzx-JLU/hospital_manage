// CDepositDlg.cpp: 实现文件
//

#include "pch.h"
#include "HospitalManage.h"
#include "CDepositDlg.h"
#include "afxdialogex.h"


// CDepositDlg 对话框

IMPLEMENT_DYNAMIC(CDepositDlg, CDialogEx)

CDepositDlg::CDepositDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEPOSIT, pParent)
	, m_deposit(0)
{

}

CDepositDlg::~CDepositDlg()
{
}

void CDepositDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_YaJin, m_deposit);
	DDV_MinMaxInt(pDX, m_deposit, 0, INT_MAX);
}


BEGIN_MESSAGE_MAP(CDepositDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDepositDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDepositDlg 消息处理程序


void CDepositDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_deposit < 0)
		MessageBox(L"请输入正整数", L"提示");
	else if (m_deposit % 100)
		MessageBox(L"请输入100的整数倍", L"提示");
	else
		CDialogEx::OnOK();
}
