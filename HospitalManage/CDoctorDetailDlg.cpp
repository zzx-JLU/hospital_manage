// CDoctorDetailDlg.cpp: 实现文件
//

#include "pch.h"
#include "HospitalManage.h"
#include "CDoctorDetailDlg.h"
#include "afxdialogex.h"
#include "struct.h"
#include "function.h"

extern struct Doctor* pDoctor;
extern char department[10][10];
extern struct Doctor* doctor;

// CDoctorDetailDlg 对话框

IMPLEMENT_DYNAMIC(CDoctorDetailDlg, CDialogEx)

CDoctorDetailDlg::CDoctorDetailDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DoctorDetail, pParent)
	, m_department(_T(""))
	, m_id(0)
	, m_name(_T(""))
	, m_grade(_T(""))
	, m_state(_T(""))
{

}

CDoctorDetailDlg::~CDoctorDetailDlg()
{
}

void CDoctorDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_KeShi, m_ComboDepartment);
	DDX_CBString(pDX, IDC_COMBO_KeShi, m_department);
	DDX_Text(pDX, IDC_EDIT_Name, m_name);
	DDX_Control(pDX, IDC_COMBO_Grade, m_ComboGrade);
	DDX_CBString(pDX, IDC_COMBO_Grade, m_grade);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK3, m_check3);
	DDX_Control(pDX, IDC_CHECK4, m_check4);
	DDX_Control(pDX, IDC_CHECK5, m_check5);
	DDX_Control(pDX, IDC_CHECK6, m_check6);
	DDX_Control(pDX, IDC_CHECK7, m_check7);
	DDX_Control(pDX, IDC_COMBO_State, m_ComboState);
	DDX_CBString(pDX, IDC_COMBO_State, m_state);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	//DDV_MinMaxInt(pDX, m_id, 100, 999);
}


BEGIN_MESSAGE_MAP(CDoctorDetailDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDoctorDetailDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_Grade, &CDoctorDetailDlg::OnCbnSelchangeComboGrade)
	ON_CBN_SELCHANGE(IDC_COMBO_KeShi, &CDoctorDetailDlg::OnCbnSelchangeComboKeshi)
	ON_CBN_SELCHANGE(IDC_COMBO_State, &CDoctorDetailDlg::OnCbnSelchangeComboState)
END_MESSAGE_MAP()


// CDoctorDetailDlg 消息处理程序


void CDoctorDetailDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//判断工号是否重复
	struct Doctor* p = doctor->next;
	while (p)
	{
		if (p->id == m_id && p != pDoctor)
		{
			MessageBox(L"工号重复", L"提示");
			return;
		}
		p = p->next;
	}

	if (m_name == L"")
		MessageBox(L"姓名不能为空", L"提示");
	else if (m_grade == L"")
		MessageBox(L"级别不能为空", L"提示");
	else if (m_department == L"")
		MessageBox(L"科室不能为空", L"提示");
	else if (m_id < 100 || m_id > 999)
		MessageBox(L"工号范围错误，请输入100到999的整数", L"提示");
	else if (!m_check1.GetCheck() && !m_check2.GetCheck() && !m_check3.GetCheck() && !m_check4.GetCheck() &&
		!m_check5.GetCheck() && !m_check6.GetCheck() && !m_check7.GetCheck())
		MessageBox(L"出诊时间不能为空", L"提示");
	else if (m_state == L"")
		MessageBox(L"状态不能为空", L"提示");
	else
	{
		CStringToChar(m_name, pDoctor->name);
		CStringToChar(m_grade, pDoctor->grade);
		CStringToChar(m_department, pDoctor->department);
		pDoctor->id = m_id;

		if (m_state == L"请假")
			pDoctor->state = 0;
		else if (m_state == L"出诊")
			pDoctor->state = 1;
		else if (m_state == L"离职")
			pDoctor->state = 2;

		pDoctor->chuzhen[0] = m_check7.GetCheck();
		pDoctor->chuzhen[1] = m_check1.GetCheck();
		pDoctor->chuzhen[2] = m_check2.GetCheck();
		pDoctor->chuzhen[3] = m_check3.GetCheck();
		pDoctor->chuzhen[4] = m_check4.GetCheck();
		pDoctor->chuzhen[5] = m_check5.GetCheck();
		pDoctor->chuzhen[6] = m_check6.GetCheck();

		CDialogEx::OnOK();
	}
}


BOOL CDoctorDetailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_name.Format(L"%s", CStringW(pDoctor->name));
	m_grade.Format(L"%s", CStringW(pDoctor->grade));
	m_department.Format(L"%s", CStringW(pDoctor->department));
	m_id = pDoctor->id;
	//设置状态
	if (pDoctor->state == 0)
		m_state = L"请假";
	else if (pDoctor->state == 1)
		m_state = L"出诊";
	else if (pDoctor->state == 2)
		m_state = L"离职";
	//出诊时间
	m_check1.SetCheck(pDoctor->chuzhen[1]);
	m_check2.SetCheck(pDoctor->chuzhen[2]);
	m_check3.SetCheck(pDoctor->chuzhen[3]);
	m_check4.SetCheck(pDoctor->chuzhen[4]);
	m_check5.SetCheck(pDoctor->chuzhen[5]);
	m_check6.SetCheck(pDoctor->chuzhen[6]);
	m_check7.SetCheck(pDoctor->chuzhen[0]);
	//级别下拉表
	m_ComboGrade.AddString(L"主任医师");
	m_ComboGrade.AddString(L"副主任医师");
	m_ComboGrade.AddString(L"主治医师");
	m_ComboGrade.AddString(L"住院医师");
	//科室下拉表
	CString str;
	for (int i = 0; i < 10; i++)
	{
		str.Format(L"%s", CStringW(department[i]));
		m_ComboDepartment.AddString(str);
	}
	//状态下拉表
	m_ComboState.AddString(L"出诊");
	m_ComboState.AddString(L"请假");
	m_ComboState.AddString(L"离职");

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDoctorDetailDlg::OnCbnSelchangeComboGrade()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = m_ComboGrade.GetCurSel();
	m_ComboGrade.SetCurSel(n);
	m_ComboGrade.GetWindowTextW(m_grade);
}


void CDoctorDetailDlg::OnCbnSelchangeComboKeshi()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = m_ComboDepartment.GetCurSel();
	m_ComboDepartment.SetCurSel(n);
	m_ComboDepartment.GetWindowTextW(m_department);
}


void CDoctorDetailDlg::OnCbnSelchangeComboState()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = m_ComboState.GetCurSel();
	m_ComboState.SetCurSel(n);
	m_ComboState.GetWindowTextW(m_state);
}
