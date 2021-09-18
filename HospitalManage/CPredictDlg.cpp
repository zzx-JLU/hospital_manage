// CPredictDlg.cpp: 实现文件
//

#include "pch.h"
#include "HospitalManage.h"
#include "CPredictDlg.h"
#include "afxdialogex.h"
#include "function.h"
#include "struct.h"


// CPredictDlg 对话框
extern char department[10][10];
extern CTime CurrentTime;
extern struct ZhenLiao* head;

IMPLEMENT_DYNAMIC(CPredictDlg, CDialogEx)

CPredictDlg::CPredictDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PREDICT, pParent)
	, m_department(_T(""))
	, m_first(0)
	, m_fifth(0)
	, m_fourth(0)
	, m_result(0)
	, m_second(0)
	, m_third(0)
{

}

CPredictDlg::~CPredictDlg()
{
}

void CPredictDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_Select, m_ComboDepartment);
	DDX_CBString(pDX, IDC_COMBO_Select, m_department);
	//  DDX_Text(pDX, IDC_EDIT_Fifth, m_first);
	DDX_Text(pDX, IDC_EDIT_Fifth, m_fifth);
	DDX_Text(pDX, IDC_EDIT_First, m_first);
	DDX_Text(pDX, IDC_EDIT_Fourth, m_fourth);
	DDX_Text(pDX, IDC_EDIT_Result, m_result);
	DDX_Text(pDX, IDC_EDIT_Second, m_second);
	DDX_Text(pDX, IDC_EDIT_Third, m_third);
}


BEGIN_MESSAGE_MAP(CPredictDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_StartPredict, &CPredictDlg::OnBnClickedButtonStartpredict)
	ON_CBN_SELCHANGE(IDC_COMBO_Select, &CPredictDlg::OnCbnSelchangeComboSelect)
END_MESSAGE_MAP()


// CPredictDlg 消息处理程序


void CPredictDlg::OnBnClickedButtonStartpredict()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_department == L"")
		MessageBox(L"请选择科室", L"提示");
	else
	{
		char department[20];
		CStringToChar(m_department, department);
		CTimeSpan span(1, 0, 0, 0);
		CTime time = CurrentTime - span;
		m_fifth = IndexForPredict(department, time.GetYear(), time.GetMonth(), time.GetDay(), head);
		time -= span;
		m_fourth = IndexForPredict(department, time.GetYear(), time.GetMonth(), time.GetDay(), head);
		time -= span;
		m_third = IndexForPredict(department, time.GetYear(), time.GetMonth(), time.GetDay(), head);
		time -= span;
		m_second = IndexForPredict(department, time.GetYear(), time.GetMonth(), time.GetDay(), head);
		time -= span;
		m_first = IndexForPredict(department, time.GetYear(), time.GetMonth(), time.GetDay(), head);
		m_result = Predict(m_first, m_second, m_third, m_fourth, m_fifth);
		UpdateData(FALSE);
	}
}


void CPredictDlg::OnCbnSelchangeComboSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = m_ComboDepartment.GetCurSel();
	m_ComboDepartment.SetCurSel(n);
	m_ComboDepartment.GetWindowTextW(m_department);
}


BOOL CPredictDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ComboDepartment.ResetContent();
	CString str;
	for (int i = 0; i < 10; i++)
	{
		str.Format(L"%s", CStringW(department[i]));
		m_ComboDepartment.AddString(str);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
