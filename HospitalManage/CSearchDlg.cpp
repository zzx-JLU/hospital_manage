// CSearchDlg.cpp: 实现文件
//

#include "pch.h"
#include "HospitalManage.h"
#include "CSearchDlg.h"
#include "afxdialogex.h"
#include "struct.h"
#include "CDetailDlg.h"
#include "function.h"

extern char department[10][10];
extern struct Doctor* doctor;
extern struct ZhenLiao* head;
extern struct ZhenLiao* p;
extern struct money turnover;
extern int flag;

// CSearchDlg 对话框

IMPLEMENT_DYNAMIC(CSearchDlg, CDialogEx)

CSearchDlg::CSearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEARCH, pParent)
	, m_PatientName(_T(""))
	, m_PatientAge(0)
	, m_Radio(-1)
	, m_department(_T(""))
	, m_doctor(_T(""))
{

	m_doctor = _T("");
	m_department = _T("");
}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
	DDX_Text(pDX, IDC_EDIT_Age, m_PatientAge);
	DDV_MinMaxInt(pDX, m_PatientAge, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_Name, m_PatientName);
	DDX_Control(pDX, IDC_DATETIMEPICKER_From, m_startTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_endTime);
	DDX_Control(pDX, IDC_COMBO1, m_ComboDepartment);
	DDX_Control(pDX, IDC_COMBO2, m_ComboDoctor);
	//  DDX_CBString(pDX, IDC_COMBO1, m_department);
	//  DDX_CBString(pDX, IDC_COMBO2, m_doctor);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSearchDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSearchDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO1, &CSearchDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO5, &CSearchDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO6, &CSearchDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO7, &CSearchDlg::OnBnClickedRadio1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSearchDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSearchDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON_ShanChu, &CSearchDlg::OnBnClickedButtonShanchu)
	ON_BN_CLICKED(IDC_BUTTON_SearchOK, &CSearchDlg::OnBnClickedButtonSearchok)
	ON_BN_CLICKED(IDC_BUTTON_SearchCancle, &CSearchDlg::OnBnClickedButtonSearchcancle)
END_MESSAGE_MAP()


// CSearchDlg 消息处理程序


BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置列表格式
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, L"", LVCFMT_CENTER, 25);
	m_list.InsertColumn(1, L"患者姓名", LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, L"患者年龄", LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, L"挂号", LVCFMT_CENTER, 100);
	m_list.InsertColumn(4, L"医生姓名", LVCFMT_CENTER, 100);
	m_list.InsertColumn(5, L"医生级别", LVCFMT_CENTER, 100);
	m_list.InsertColumn(6, L"科室", LVCFMT_CENTER, 80);
	m_list.InsertColumn(7, L"工号", LVCFMT_CENTER, 100);
	m_list.InsertColumn(8, L"检查总费用", LVCFMT_CENTER, 100);
	m_list.InsertColumn(9, L"药品总价", LVCFMT_CENTER, 100);
	m_list.InsertColumn(10, L"是否住院", LVCFMT_CENTER, 80);
	//设置科室下拉表
	CString str;
	for (int i = 0; i < 10; i++)
	{
		str.Format(L"%s", CStringW(department[i]));
		m_ComboDepartment.AddString(str);
	}
	//设置医生下拉表
	struct Doctor* q = doctor->next;
	while (q)
	{
		str.Format(L"%s，%s", CStringW(q->name), CStringW(q->department));
		m_ComboDoctor.AddString(str);
		q = q->next;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CSearchDlg::EditItem(struct ZhenLiao* p, int nItem)
{
	if (p == NULL)
		return;
	CString str;
	//患者姓名
	str.Format(L"%s", CStringW(p->patient.name));
	m_list.SetItemText(nItem, 1, str);
	//患者年龄
	str.Format(L"%d", p->patient.age);
	m_list.SetItemText(nItem, 2, str);
	//挂号
	str.Format(L"%d", p->no);
	m_list.SetItemText(nItem, 3, str);
	//医生姓名
	str.Format(L"%s", CStringW(p->doctor.name));
	m_list.SetItemText(nItem, 4, str);
	//医生级别
	str.Format(L"%s", CStringW(p->doctor.grade));
	m_list.SetItemText(nItem, 5, str);
	//科室
	str.Format(L"%s", CStringW(p->doctor.department));
	m_list.SetItemText(nItem, 6, str);
	//工号
	str.Format(L"%d", p->doctor.id);
	m_list.SetItemText(nItem, 7, str);

	if (p->xuan == 1) //检查
	{
		float fee = p->record.check.CheckFee.yuan + p->record.check.CheckFee.jiao * 0.1 + p->record.check.CheckFee.fen * 0.01;
		str.Format(L"%.2f", fee);
		m_list.SetItemText(nItem, 8, str);
		m_list.SetItemText(nItem, 9, L"0");
		m_list.SetItemText(nItem, 10, L"否");
	}
	else if (p->xuan == 2) //开药
	{
		float fee = p->record.drug.DrugFee.yuan + p->record.drug.DrugFee.jiao * 0.1 + p->record.drug.DrugFee.fen * 0.01;
		str.Format(L"%.2f", fee);
		m_list.SetItemText(nItem, 9, str);
		m_list.SetItemText(nItem, 8, L"0");
		m_list.SetItemText(nItem, 10, L"否");
	}
	else if (p->xuan == 3) //住院
	{
		m_list.SetItemText(nItem, 8, L"0");
		m_list.SetItemText(nItem, 9, L"0");
		m_list.SetItemText(nItem, 10, L"是");
	}
	else if (p->xuan == 0) //已出院
	{
		m_list.SetItemText(nItem, 8, L"0");
		m_list.SetItemText(nItem, 9, L"0");
		m_list.SetItemText(nItem, 10, L"已出院");
	}
}


void CSearchDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	POSITION pos = m_list.GetFirstSelectedItemPosition(); //得到点击位置
	int nPos = m_list.GetNextSelectedItem(pos); //得到行号
	if (nItem >= 0 && nItem < m_list.GetItemCount())
	{
		//得到相应位置的结点
		p = Search(head, _ttoi(m_list.GetItemText(nPos, 3)));
		if (p == NULL)
			MessageBox(L"找不到此信息", L"提示");
		else
		{
			//打开详细信息对话框
			CDetailDlg dlg;
			dlg.DoModal();
			EditItem(p, nPos);
		}
	}
	else
		MessageBox(L"无效的选择", L"提示");
	*pResult = 0;
}


void CSearchDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int i = 0;
	p = head->next;
	m_list.DeleteAllItems();
	if (m_Radio == 0) //按患者
	{
		char name[20];
		CStringToChar(m_PatientName, name);
		while (p)
		{
			if (strcmp(name, p->patient.name) == 0 && m_PatientAge == p->patient.age)
			{
				m_list.InsertItem(i, L"");
				EditItem(p, i);
				i++;
			}
			p = p->next;
		}
	}
	else if (m_Radio == 1) //按科室
	{
		char keshi[20];
		CStringToChar(m_department, keshi);
		while (p)
		{
			if (strcmp(keshi, p->doctor.department) == 0)
			{
				m_list.InsertItem(i, L"");
				EditItem(p, i);
				i++;
			}
			p = p->next;
		}
	}
	else if (m_Radio == 2) //按医生
	{
		char keshi[20], yisheng[20];
		CStringToChar(m_department, keshi);
		CStringToChar(m_doctor, yisheng);
		while (p)
		{
			if (strcmp(keshi, p->doctor.department) == 0 && strcmp(yisheng, p->doctor.name) == 0)
			{
				m_list.InsertItem(i, L"");
				EditItem(p, i);
				i++;
			}
			p = p->next;
		}
	}
	else if (m_Radio == 3) //按时间段
	{
		CTime startTime, endTime;
		m_startTime.GetTime(startTime);
		m_endTime.GetTime(endTime);
		CTime Time1(startTime.GetYear(), startTime.GetMonth(), startTime.GetDay(), 0, 0, 0);
		CTime Time2(endTime.GetYear(), endTime.GetMonth(), endTime.GetDay(), 0, 0, 0);
		if (Time1 >= Time2)
		{
			MessageBox(L"结束时间不能晚于开始时间", L"提示");
			return;
		}
		while (p)
		{
			CTime time(p->date.year, p->date.month, p->date.day, 0, 0, 0);
			if (Time1 <= time && time <= Time2)
			{
				m_list.InsertItem(i, L"");
				EditItem(p, i);
				i++;
			}
			p = p->next;
		}
	}
	if (i == 0)
		MessageBox(L"没有相关信息", L"提示");
	GetDlgItem(IDC_BUTTON_ShanChu)->EnableWindow(TRUE);
}

void CSearchDlg::EnablePatient(bool flag)
{
	GetDlgItem(IDC_EDIT_Name)->EnableWindow(flag);
	GetDlgItem(IDC_EDIT_Age)->EnableWindow(flag);
}

void CSearchDlg::EnableTime(bool flag)
{
	GetDlgItem(IDC_DATETIMEPICKER_From)->EnableWindow(flag);
	GetDlgItem(IDC_DATETIMEPICKER_TO)->EnableWindow(flag);
}

void CSearchDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	switch (m_Radio)
	{
	case 0: //按患者
		EnablePatient(TRUE);
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
		EnableTime(FALSE);
		m_PatientName = L"";
		m_PatientAge = 0;
		GetDlgItem(IDC_COMBO1)->SetWindowTextW(L"");
		GetDlgItem(IDC_COMBO2)->SetWindowTextW(L"");
		UpdateData(FALSE);
		break;
	case 1: //按科室
		EnablePatient(FALSE);
		GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
		EnableTime(FALSE);
		m_PatientName = L"";
		m_PatientAge = 0;
		GetDlgItem(IDC_COMBO1)->SetWindowTextW(L"");
		GetDlgItem(IDC_COMBO2)->SetWindowTextW(L"");
		UpdateData(FALSE);
		break;
	case 2: //按医生
		EnablePatient(FALSE);
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
		EnableTime(FALSE);
		m_PatientName = L"";
		m_PatientAge = 0;
		GetDlgItem(IDC_COMBO1)->SetWindowTextW(L"");
		GetDlgItem(IDC_COMBO2)->SetWindowTextW(L"");
		UpdateData(FALSE);
		break;
	case 3: //按时间段
		EnablePatient(FALSE);
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
		EnableTime(TRUE);
		m_PatientName = L"";
		m_PatientAge = 0;
		m_ComboDepartment.SetWindowTextW(L"");
		m_ComboDoctor.SetWindowTextW(L"");
		UpdateData(FALSE);
		break;
	}
}


void CSearchDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = m_ComboDepartment.GetCurSel();
	m_ComboDepartment.SetCurSel(n);
	m_ComboDepartment.GetLBText(n, m_department);
}


void CSearchDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = m_ComboDoctor.GetCurSel();
	CString str;
	m_ComboDoctor.SetCurSel(n);
	m_ComboDoctor.GetLBText(n, str);
	int i = str.Find(L"，");
	m_doctor = str.Left(i);
	m_department = str.Mid(i + 1);
}


void CSearchDlg::OnBnClickedButtonShanchu()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SearchOK)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SearchCancle)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ShanChu)->ShowWindow(FALSE);
}


void CSearchDlg::OnBnClickedButtonSearchok()
{
	// TODO: 在此添加控件通知处理程序代码
	//统计选中条数
	int n = 0;
	int i; //行号
	int count = 0; //记录已删除条数
	for (i = 0; i < m_list.GetItemCount(); i++)
		if (m_list.GetCheck(i))
			n++;
	CString str;
	str.Format(L"已选中%d条，确认删除吗？", n);
	if (MessageBox(str, L"提示", MB_OKCANCEL) == IDOK)
	{
		//删除操作
		for (i = 0; i < m_list.GetItemCount(); i++)
		{
			if (m_list.GetCheck(i))
			{
				//获取结点指针
				p = Search(head, _ttoi(m_list.GetItemText(i, 3)));
				if (p == NULL)
				{
					MessageBox(L"无此诊疗记录", L"提示");
					continue;
				}
				//营业额减少
				if (p->xuan == 1)
				{
					turnover.yuan -= p->record.check.CheckFee.yuan;
					turnover.jiao -= p->record.check.CheckFee.jiao;
					turnover.fen -= p->record.check.CheckFee.fen;
				}
				else if (p->xuan == 2)
				{
					turnover.yuan -= p->record.drug.DrugFee.yuan;
					turnover.jiao -= p->record.drug.DrugFee.jiao;
					turnover.fen -= p->record.drug.DrugFee.fen;
				}
				//删除结点
				DeleteZhenLiao(head, p);
				//计数器+1
				count++;
			}
			else
			{
				//列表当前行不删除，向前移动
				CString str;
				for (int j = 1; j <= 10; j++)
				{
					str = m_list.GetItemText(i, j);
					m_list.SetItemText(i - count, j, str);
				}
			}
		}
		//最后n行删除
		for (i = m_list.GetItemCount() - 1; count > 0; i--)
		{
			m_list.DeleteItem(i);
			count--;
		}
		//恢复界面
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SearchOK)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SearchCancle)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ShanChu)->ShowWindow(TRUE);
		flag = 1;
	}
	
}


void CSearchDlg::OnBnClickedButtonSearchcancle()
{
	// TODO: 在此添加控件通知处理程序代码
	//恢复界面
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SearchOK)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SearchCancle)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ShanChu)->ShowWindow(TRUE);
}
