// CAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "HospitalManage.h"
#include "CAddDlg.h"
#include "afxdialogex.h"
#include "struct.h"
#include "function.h"
#include "CCheckDlg.h"
#include "CDrugDlg.h"

extern struct ZhenLiao* head;
extern struct ZhenLiao* p;
extern struct Doctor* doctor;
extern char department[10][10];
extern int NumOfDepartment[10];
extern struct room Room[RoomNum];
extern struct DrugItem Drug[DrugNum];
extern struct CheckItem Check[DrugNum];
extern CTime CurrentTime;

// CAddDlg 对话框

IMPLEMENT_DYNAMIC(CAddDlg, CDialogEx)

CAddDlg::CAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
	, m_PatientName(_T(""))
	, m_PatientAge(0)
	, m_DoctorGrade(_T(""))
	, m_DoctorID(0)
	, m_PatientID(0)
	, m_Radio(-1)
	, m_CheckFee(0)
	, m_DrugFee(0)
	, m_deposit(0)
	, m_department(_T(""))
	, m_DoctorName(_T(""))
	, m_room(0)
	, m_type(_T(""))
	, m_nurse(_T(""))
	, m_ID(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_PatientName);
	DDX_Text(pDX, IDC_EDIT2, m_PatientAge);
	DDV_MinMaxInt(pDX, m_PatientAge, 0, INT_MAX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_Time);
	DDX_Text(pDX, IDC_EDIT5, m_DoctorGrade);
	DDX_Text(pDX, IDC_EDIT6, m_DoctorID);
	DDV_MinMaxInt(pDX, m_DoctorID, 0, INT_MAX);
	DDX_Radio(pDX, IDC_RADIO2, m_Radio);
	DDX_Text(pDX, IDC_EDIT7, m_CheckFee);
	DDX_Text(pDX, IDC_EDIT8, m_DrugFee);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_StartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_EndTime);
	DDX_Text(pDX, IDC_EDIT9, m_deposit);
	DDV_MinMaxInt(pDX, m_deposit, 0, INT_MAX);
	DDX_Control(pDX, IDC_LIST1, m_listCheck);
	DDX_Control(pDX, IDC_LIST2, m_listDrug);
	DDX_Control(pDX, IDC_COMBO_Department, m_ComboDepartment);
	DDX_Control(pDX, IDC_COMBO_DoctorName, m_ComboName);
	DDX_CBString(pDX, IDC_COMBO_Department, m_department);
	DDX_CBString(pDX, IDC_COMBO_DoctorName, m_DoctorName);
	DDX_Text(pDX, IDC_EDIT3, m_PatientID);
	DDX_Control(pDX, IDC_COMBO_Room, m_ComboRoom);
	DDX_CBIndex(pDX, IDC_COMBO_Room, m_room);
	DDX_Control(pDX, IDC_COMBO_Type, m_ComboType);
	DDX_CBString(pDX, IDC_COMBO_Type, m_type);
	DDX_Control(pDX, IDC_COMBO_Nurse, m_ComboNurse);
	DDX_CBString(pDX, IDC_COMBO_Nurse, m_nurse);
	DDX_Text(pDX, IDC_EDIT_PateintID, m_ID);
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO2, &CAddDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CAddDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &CAddDlg::OnBnClickedRadio2)
	ON_CBN_SELCHANGE(IDC_COMBO_Department, &CAddDlg::OnCbnSelchangeComboDepartment)
	ON_CBN_SELCHANGE(IDC_COMBO_DoctorName, &CAddDlg::OnCbnSelchangeComboDoctorname)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CAddDlg::OnNMDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CAddDlg::OnNMDblclkList2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER3, &CAddDlg::OnDtnDatetimechangeDatetimepicker3)
	ON_BN_CLICKED(IDOK, &CAddDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAddDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_Type, &CAddDlg::OnCbnSelchangeComboType)
	ON_CBN_SELCHANGE(IDC_COMBO_Nurse, &CAddDlg::OnCbnSelchangeComboNurse)
	ON_CBN_SELCHANGE(IDC_COMBO_Room, &CAddDlg::OnCbnSelchangeComboRoom)
END_MESSAGE_MAP()


// CAddDlg 消息处理程序


BOOL CAddDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//新建结点
	p = (struct ZhenLiao*)malloc(sizeof(struct ZhenLiao));
	p->next = NULL;
	//检查列表格式控制
	m_listCheck.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listCheck.InsertColumn(0, L"", LVCFMT_CENTER, 0);
	m_listCheck.InsertColumn(1, L"检查项目", LVCFMT_CENTER, 80);
	m_listCheck.InsertColumn(2, L"检查费用", LVCFMT_CENTER, 80);
	m_listCheck.InsertColumn(3, L"检查次数", LVCFMT_CENTER, 80);
	//检查列表内容初始化
	CString str;
	for (int i = 0; i < CheckNum; i++)
	{
		m_listCheck.InsertItem(i, L"");

		str.Format(L"%s", CStringW(Check[i].name));
		m_listCheck.SetItemText(i, 1, str);

		float price = Check[i].fee.yuan + Check[i].fee.jiao * 0.1 + Check[i].fee.fen * 0.01;
		str.Format(L"%.2f", price);
		m_listCheck.SetItemText(i, 2, str);

		m_listCheck.SetItemText(i, 3, L"0");
	}
	//开药列表格式控制
	m_listDrug.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listDrug.InsertColumn(0, L"", LVCFMT_CENTER, 0);
	m_listDrug.InsertColumn(1, L"药品名称", LVCFMT_CENTER, 80);
	m_listDrug.InsertColumn(2, L"单价", LVCFMT_CENTER, 70);
	m_listDrug.InsertColumn(3, L"数量", LVCFMT_CENTER, 70);
	//开药列表内容初始化
	for (int i = 0; i < DrugNum; i++)
	{
		m_listDrug.InsertItem(i, L"");
		
		str.Format(L"%s", CStringW(Drug[i].name));
		m_listDrug.SetItemText(i, 1, str);

		float price = Drug[i].fee.yuan + Drug[i].fee.jiao * 0.1 + Drug[i].fee.fen * 0.01;
		str.Format(L"%.2f", price);
		m_listDrug.SetItemText(i, 2, str);

		m_listDrug.SetItemText(i, 3, L"0");
	}
	//时间控件设置成当前时间
	m_Time.SetTime(&CurrentTime);
	m_StartTime.SetTime(&CurrentTime);
	m_EndTime.SetTime(&CurrentTime);
	p->date.year = CurrentTime.GetYear();
	p->date.month = CurrentTime.GetMonth();
	p->date.day = CurrentTime.GetDay();
	//科室下拉表初始化
	m_ComboDepartment.ResetContent();
	for (int i = 0; i < 10; i++)
	{
		str.Format(L"%s", CStringW(department[i]));
		m_ComboDepartment.AddString(str);
	}
	//护理类型下拉表初始化
	m_ComboNurse.AddString(L"普通病房");
	m_ComboNurse.AddString(L"特殊病房");
	//病房类型下拉表初始化
	m_ComboType.AddString(L"单人病房");
	m_ComboType.AddString(L"双人病房");
	m_ComboType.AddString(L"三人病房");
	m_ComboType.AddString(L"单人陪护病房");
	m_ComboType.AddString(L"单人陪护疗养病房");

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CAddDlg::EnableCheck(bool flag)
{
	GetDlgItem(IDC_EDIT7)->EnableWindow(flag);
	GetDlgItem(IDC_LIST1)->EnableWindow(flag);
}

void CAddDlg::EnableDrug(bool flag)
{
	GetDlgItem(IDC_EDIT8)->EnableWindow(flag);
	GetDlgItem(IDC_LIST2)->EnableWindow(flag);
}

void CAddDlg::EnableZhuYuan(bool flag)
{
	GetDlgItem(IDC_EDIT9)->EnableWindow(flag);
	GetDlgItem(IDC_DATETIMEPICKER3)->EnableWindow(flag);
	GetDlgItem(IDC_COMBO_Type)->EnableWindow(flag);
	GetDlgItem(IDC_COMBO_Nurse)->EnableWindow(flag);
}

void CAddDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	switch (m_Radio)
	{
	case 0: //检查
		EnableCheck(TRUE);
		EnableDrug(FALSE);
		EnableZhuYuan(FALSE);
		GetDlgItem(IDC_COMBO_Room)->EnableWindow(FALSE);
		p->record.check.CheckFee.yuan = 0;
		p->record.check.CheckFee.jiao = 0;
		p->record.check.CheckFee.fen = 0;
		for (int i = 0; i < CheckNum; i++)
		{
			m_listCheck.SetItemText(i, 3, L"0");
			p->record.check.checks[i] = Check[i];
		}
		break;
	case 1: //开药
		EnableCheck(FALSE);
		EnableDrug(TRUE);
		EnableZhuYuan(FALSE);
		GetDlgItem(IDC_COMBO_Room)->EnableWindow(FALSE);
		p->record.drug.DrugFee.yuan = 0;
		p->record.drug.DrugFee.jiao = 0;
		p->record.drug.DrugFee.fen = 0;
		for (int i = 0; i < DrugNum; i++)
		{
			m_listDrug.SetItemText(i, 3, L"0");
			p->record.drug.drugs[i] = Drug[i];
		}
		break;
	case 2: //住院
		EnableCheck(FALSE);
		EnableDrug(FALSE);
		EnableZhuYuan(TRUE);
		if (m_nurse != L"" && m_type != L"")
			GetDlgItem(IDC_COMBO_Room)->EnableWindow(TRUE);
		break;
	}
}


void CAddDlg::OnCbnSelchangeComboDepartment()
{
	// TODO: 在此添加控件通知处理程序代码
	//获得选中科室
	int nPos = m_ComboDepartment.GetCurSel(); //获取选中行
	m_ComboDepartment.SetCurSel(nPos);
	m_ComboDepartment.GetWindowTextW(m_department);
	m_ComboName.EnableWindow(TRUE);
	//设置医生姓名下拉表
	m_ComboName.ResetContent(); //重置下拉表
	char keshi[20];
	CStringToChar(m_department, keshi);
	CTime time;
	m_Time.GetTime(time); //获得时间控件中的时间
	int day = time.GetDayOfWeek(); //获得星期数，1代表星期日，2代表星期一，以此类推
	struct Doctor* q = doctor->next;
	while (q != NULL)
	{
		CString name;
		if (strcmp(keshi, q->department) == 0 && q->chuzhen[day - 1] == 1 && q->guahaoshu < 20 && q->state == 1) //若科室相符且当天出诊
		{
			name.Format(L"%s", CStringW(q->name));
			m_ComboName.AddString(name);
		}
		q = q->next;
	}
	//修改界面
	UpdateData(TRUE);
	m_DoctorGrade = L"";
	m_DoctorID = 0;
	m_PatientID = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnCbnSelchangeComboDoctorname()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//获得选中医生姓名
	int nPos = m_ComboName.GetCurSel();
	m_ComboName.SetCurSel(nPos);
	m_ComboName.GetWindowTextW(m_DoctorName);
	//找到目标结点
	target = doctor->next;
	char keshi[20], name[20];
	CStringToChar(m_department, keshi);
	CStringToChar(m_DoctorName, name);
	while (target != NULL)
	{
		if (strcmp(keshi, target->department) == 0 && strcmp(name, target->name) == 0)
			break;
		else
			target = target->next;
	}
	if (target == NULL)
		MessageBox(L"找不到该医生", L"提示");
	else
	{
		//生成挂号
		int i;
		for (i = 0; i < 10; i++)
			if (strcmp(department[i], target->department) == 0)
				break;
		CString id;
		id.Format(L"%d%d%d%d%d", p->date.year % 100, p->date.month, p->date.day, i, NumOfDepartment[i] + 1);
		m_PatientID = _ttoi(id);
		p->no = m_PatientID;
		//显示其他信息
		m_DoctorGrade.Format(L"%s", CStringW(target->grade));
		m_DoctorID = target->id;
		//修改新建结点
		p->doctor = *target;
	}
	UpdateData(FALSE);
}


void CAddDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	POSITION pos = m_listCheck.GetFirstSelectedItemPosition(); //得到点击位置
	int nPos = m_listCheck.GetNextSelectedItem(pos); //得到行号
	if (nItem >= 0 && nItem < m_listCheck.GetItemCount())
	{
		//打开检查信息对话框
		CCheckDlg CheckDlg;
		CheckDlg.m_checkName.Format(L"%s", CStringW(Check[nPos].name));
		CheckDlg.m_price = Check[nPos].fee.yuan + Check[nPos].fee.jiao * 0.1 + Check[nPos].fee.fen * 0.01;
		CheckDlg.m_count = p->record.check.checks[nPos].count;
		int count = CheckDlg.m_count;
		if (CheckDlg.DoModal() == IDOK)
		{
			//修改链表结点
			p->record.check.checks[nPos].count = CheckDlg.m_count;
			p->record.check.CheckFee.yuan = p->record.check.CheckFee.yuan - count * p->record.check.checks[nPos].fee.yuan + CheckDlg.m_count * p->record.check.checks[nPos].fee.yuan;
			p->record.check.CheckFee.jiao = p->record.check.CheckFee.jiao - count * p->record.check.checks[nPos].fee.jiao + CheckDlg.m_count * p->record.check.checks[nPos].fee.jiao;
			p->record.check.CheckFee.fen = p->record.check.CheckFee.fen - count * p->record.check.checks[nPos].fee.fen + CheckDlg.m_count * p->record.check.checks[nPos].fee.fen;
			//修改界面
			CString str;
			str.Format(L"%d", CheckDlg.m_count);
			m_listCheck.SetItemText(nPos, 3, str);
			m_CheckFee = p->record.check.CheckFee.yuan + p->record.check.CheckFee.jiao * 0.1 + p->record.check.CheckFee.fen * 0.01;
			UpdateData(FALSE);
		}
	}
	else
		MessageBox(L"无效的选择", L"提示");
	*pResult = 0;
}


void CAddDlg::OnNMDblclkList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	POSITION pos = m_listDrug.GetFirstSelectedItemPosition(); //得到点击位置
	int nPos = m_listDrug.GetNextSelectedItem(pos); //得到行号
	if (nItem >= 0 && nItem < m_listDrug.GetItemCount())
	{
		//打开药品信息对话框
		CDrugDlg DrugDlg;
		DrugDlg.m_drugName.Format(L"%s", CStringW(Drug[nPos].name));
		DrugDlg.m_num = p->record.drug.drugs[nPos].count;
		DrugDlg.m_price = Drug[nPos].fee.yuan + Drug[nPos].fee.jiao * 0.1 + Drug[nPos].fee.fen * 0.01;
		int count = DrugDlg.m_num;
		if (DrugDlg.DoModal() == IDOK)
		{
			//修改链表结点
			p->record.drug.drugs[nPos].count = DrugDlg.m_num;
			p->record.drug.DrugFee.yuan = p->record.drug.DrugFee.yuan - count * p->record.drug.drugs[nPos].fee.yuan + DrugDlg.m_num * p->record.drug.drugs[nPos].fee.yuan;
			p->record.drug.DrugFee.jiao = p->record.drug.DrugFee.jiao - count * p->record.drug.drugs[nPos].fee.jiao + DrugDlg.m_num * p->record.drug.drugs[nPos].fee.jiao;
			p->record.drug.DrugFee.fen = p->record.drug.DrugFee.fen - count * p->record.drug.drugs[nPos].fee.fen + DrugDlg.m_num * p->record.drug.drugs[nPos].fee.fen;
			//修改界面
			CString str;
			str.Format(L"%d", DrugDlg.m_num);
			m_listDrug.SetItemText(nPos, 3, str);
			m_DrugFee = p->record.drug.DrugFee.yuan + p->record.drug.DrugFee.jiao * 0.1 + p->record.drug.DrugFee.fen * 0.01;
			UpdateData(FALSE);
		}
	}
	else
		MessageBox(L"无效的选择", L"提示");
	*pResult = 0;
}


void CAddDlg::OnDtnDatetimechangeDatetimepicker3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CTime endTime;
	m_EndTime.GetTime(endTime);
	CTime startTime;
	m_StartTime.GetTime(startTime);
	if (startTime >= endTime)
	{
		MessageBox(L"出院时间不能早于住院时间", L"提示");
		m_EndTime.SetTime(&startTime);
	}
	else
	{
		p->record.zhuyuan.StartDate.year = startTime.GetYear();
		p->record.zhuyuan.StartDate.month = startTime.GetMonth();
		p->record.zhuyuan.StartDate.day = startTime.GetDay();
		p->record.zhuyuan.EndDate.year = endTime.GetYear();
		p->record.zhuyuan.EndDate.month = endTime.GetMonth();
		p->record.zhuyuan.EndDate.day = endTime.GetDay();
	}
	*pResult = 0;
}


void CAddDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//判断住院押金是否合法
	if (m_Radio == 2)
	{
		CTime startTime, endTime;
		m_StartTime.GetTime(startTime);
		m_EndTime.GetTime(endTime);
		CTimeSpan timeSpan = endTime - startTime;
		//计算最少押金
		int leastDeposit;
		if (timeSpan.GetDays() < 5)
			leastDeposit = 1000;
		else
			leastDeposit = 200 * timeSpan.GetDays();
		if (m_deposit < leastDeposit) //押金不够
		{
			CString str;
			str.Format(L"住院押金不能少于%d元", leastDeposit);
			MessageBox(str, L"提示");
			return;
		}
		else if (m_deposit % 100) //押金不是100的整数倍
		{
			MessageBox(L"押金应为100的整数倍", L"提示");
			return;
		}
		else
			p->record.zhuyuan.deposit = m_deposit;
	}
	//判断信息是否完整
	struct date time;
	time.year = CurrentTime.GetYear();
	time.month = CurrentTime.GetMonth();
	time.day = CurrentTime.GetDay();
	if (m_PatientName == "")
		MessageBox(L"患者姓名不能为空", L"提示");
	else if (m_ID < 100000 || m_ID > 999999)
		MessageBox(L"身份证号后六位应为六位整数", L"提示");
	else if (m_department == "")
		MessageBox(L"科室不能为空", L"提示");
	else if (m_DoctorName == "")
		MessageBox(L"医生姓名不能为空", L"提示");
	else if (CountGuaHao(time, m_ID, head) >= 5)
		MessageBox(L"该患者今日挂号数已满", L"提示");
	else if (JudgeDepartment(time, m_ID, p->doctor.department, head))
		MessageBox(L"今日已挂过该科室的号", L"提示");
	else
	{	//修改结点
		CStringToChar(m_PatientName, p->patient.name);
		p->patient.age = m_PatientAge;
		p->patient.id = m_ID;

		p->xuan = m_Radio + 1;
		p->no = m_PatientID;

		//修改挂号数量
		target->guahaoshu++;
		for (int i = 0; i < 10; i++)
			if (strcmp(department[i], p->doctor.department) == 0)
			{
				NumOfDepartment[i]++;
				break;
			}
		//修改病房人数
		if (p->xuan == 3)
		{
			int i = GetRoom(p->record.zhuyuan.room.id);
			Room[i].number++;
		}
		CDialogEx::OnOK();
	}
}


void CAddDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	free(p);
	p = NULL;
	CDialogEx::OnCancel();
}


void CAddDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	free(p);
	p = NULL;
	CDialogEx::OnClose();
}


void CAddDlg::OnCbnSelchangeComboType()
{
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_ComboType.GetCurSel();
	m_ComboType.SetCurSel(nPos);
	m_ComboType.GetWindowTextW(m_type);
	if (m_type != L"" && m_nurse != L"")
	{
		GetDlgItem(IDC_COMBO_Room)->EnableWindow(TRUE);
		char type[20], nurse[10];
		CStringToChar(m_type, type);
		CStringToChar(m_nurse, nurse);
		m_ComboRoom.ResetContent();
		for (int i = 0; i < RoomNum; i++)
		{
			CString str;
			if (strcmp(type, Room[i].type) == 0 && strcmp(nurse, Room[i].nurse) == 0 && Room[i].number < Room[i].NumOfBed)
			{
				str.Format(L"%d", Room[i].id);
				m_ComboRoom.AddString(str);
			}
		}
	}
}


void CAddDlg::OnCbnSelchangeComboNurse()
{
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_ComboNurse.GetCurSel();
	m_ComboNurse.SetCurSel(nPos);
	m_ComboNurse.GetWindowTextW(m_nurse);
	if (m_type != L"" && m_nurse != L"")
	{
		GetDlgItem(IDC_COMBO_Room)->EnableWindow(TRUE);
		char type[20], nurse[10];
		CStringToChar(m_type, type);
		CStringToChar(m_nurse, nurse);
		m_ComboRoom.ResetContent();
		for (int i = 0; i < RoomNum; i++)
		{
			CString str;
			if (strcmp(type, Room[i].type) == 0 && strcmp(nurse, Room[i].nurse) == 0 && Room[i].number < Room[i].NumOfBed)
			{
				str.Format(L"%d", Room[i].id);
				m_ComboRoom.AddString(str);
			}
		}
	}
}


void CAddDlg::OnCbnSelchangeComboRoom()
{
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_ComboRoom.GetCurSel();
	m_ComboRoom.SetCurSel(nPos);
	CString str;
	m_ComboRoom.GetWindowTextW(str);
	m_room = _ttoi(str);
	int i = GetRoom(m_room);
	p->record.zhuyuan.room = Room[i];
}
