// CDetailDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "HospitalManage.h"
#include "CDetailDlg.h"
#include "afxdialogex.h"
#include "HospitalManageDlg.h"
#include "resource.h"
#include "afxdialogex.h"
#include "CCheckDlg.h"
#include "CDrugDlg.h"
#include "struct.h"
#include "function.h"
#include "CDepositDlg.h"

extern struct ZhenLiao* p;
extern int flag;
extern struct money turnover;
extern struct room Room[RoomNum];
extern struct CheckItem Check[CheckNum];
extern struct DrugItem Drug[DrugNum];
extern CTime CurrentTime;

// CDetailDlg 对话框

IMPLEMENT_DYNAMIC(CDetailDlg, CDialogEx)

CDetailDlg::CDetailDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DETAIL, pParent)
	, m_checkFee(0)
	, m_deposit(0)
	, m_doctorGrade(_T(""))
	, m_doctorID(_T(""))
	, m_drugFee(0)
	, m_patientAge(0)
	, m_patientID(_T(""))
	, m_patientName(_T(""))
	, m_department(_T(""))
	, m_doctorName(_T(""))
	, m_room(0)
{

}

CDetailDlg::~CDetailDlg()
{
}

void CDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	DDX_Control(pDX, IDC_LIST_CHECK, m_listCheck);
	DDX_Control(pDX, IDC_LIST_DRUG, m_listDrug);
	DDX_Text(pDX, IDC_EDIT_CheckYuan, m_checkFee);
	DDV_MinMaxFloat(pDX, m_checkFee, 0, FLT_MAX);
	DDX_Text(pDX, IDC_EDIT_DoctorGrade, m_doctorGrade);
	DDX_Text(pDX, IDC_EDIT_DoctorID, m_doctorID);
	DDX_Text(pDX, IDC_EDIT_DrugYuan, m_drugFee);
	DDV_MinMaxFloat(pDX, m_drugFee, 0, FLT_MAX);
	DDX_Text(pDX, IDC_EDIT_PatientAge, m_patientAge);
	DDV_MinMaxInt(pDX, m_patientAge, 0, 150);
	DDX_Text(pDX, IDC_EDIT_PatientID, m_patientID);
	DDX_Text(pDX, IDC_EDIT_PatientName, m_patientName);
	DDX_Control(pDX, IDC_DATETIMEPICKER_Start, m_startDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_End, m_endDate);
	DDX_Text(pDX, IDC_EDIT_Department, m_department);
	DDX_Text(pDX, IDC_EDIT_DoctorName, m_doctorName);
	DDX_Text(pDX, IDC_EDIT_Deposit, m_deposit);
	DDX_Text(pDX, IDC_EDIT_Room, m_room);
}


BEGIN_MESSAGE_MAP(CDetailDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDetailDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_ChangeBasic, &CDetailDlg::OnBnClickedButtonChangebasic)
	ON_BN_CLICKED(IDC_BUTTON_YES, &CDetailDlg::OnBnClickedButtonYes)
	ON_BN_CLICKED(IDC_BUTTON_NO, &CDetailDlg::OnBnClickedButtonNo)
	ON_BN_CLICKED(IDC_BUTTON_AddDeposit, &CDetailDlg::OnBnClickedButtonAdddeposit)
	ON_BN_CLICKED(IDC_BUTTON_OUT, &CDetailDlg::OnBnClickedButtonOut)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_End, &CDetailDlg::OnDtnDatetimechangeDatetimepickerEnd)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CHECK, &CDetailDlg::OnNMDblclkListCheck)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DRUG, &CDetailDlg::OnNMDblclkListDrug)
END_MESSAGE_MAP()


// CDetailDlg 消息处理程序

void CDetailDlg::ShowTAB1(bool flag)
{
	GetDlgItem(IDC_STATIC1)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_PatientName)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC2)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_PatientAge)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC3)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_PatientID)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC7)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_Department)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC4)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_DoctorName)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC5)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_DoctorGrade)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC8)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_DoctorID)->ShowWindow(flag);
	GetDlgItem(IDC_BUTTON_ChangeBasic)->ShowWindow(flag);
}

void CDetailDlg::ShowTAB2(bool flag)
{
	GetDlgItem(IDC_LIST_CHECK)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC10)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_CheckYuan)->ShowWindow(flag);
}

void CDetailDlg::ShowTAB3(bool flag)
{
	GetDlgItem(IDC_LIST_DRUG)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC14)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_DrugYuan)->ShowWindow(flag);
}

void CDetailDlg::ShowTAB4(bool flag)
{
	GetDlgItem(IDC_STATIC18)->ShowWindow(flag);
	GetDlgItem(IDC_DATETIMEPICKER_Start)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC19)->ShowWindow(flag);
	GetDlgItem(IDC_DATETIMEPICKER_End)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC20)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_Deposit)->ShowWindow(flag);
	GetDlgItem(IDC_BUTTON_AddDeposit)->ShowWindow(flag);
	GetDlgItem(IDC_BUTTON_OUT)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC21)->ShowWindow(flag);
	GetDlgItem(IDC_EDIT_Room)->ShowWindow(flag);
	GetDlgItem(IDC_STATIC11)->ShowWindow(flag);
}

BOOL CDetailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//Tab控件初始化
	m_TabCtrl.InsertItem(0, L"基本信息");
	m_TabCtrl.InsertItem(1, L"检查信息");
	m_TabCtrl.InsertItem(2, L"开药信息");
	m_TabCtrl.InsertItem(3, L"住院信息");
	//设置检查列表格式
	m_listCheck.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listCheck.InsertColumn(0, L"", LVCFMT_CENTER, 0);
	m_listCheck.InsertColumn(1, L"检查项目", LVCFMT_CENTER, 80);
	m_listCheck.InsertColumn(2, L"检查费用", LVCFMT_CENTER, 80);
	m_listCheck.InsertColumn(3, L"检查次数", LVCFMT_CENTER, 80);
	//设置开药列表格式
	m_listDrug.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listDrug.InsertColumn(0, L"", LVCFMT_CENTER, 0);
	m_listDrug.InsertColumn(1, L"药品名称", LVCFMT_CENTER, 80);
	m_listDrug.InsertColumn(2, L"单价", LVCFMT_CENTER, 80);
	m_listDrug.InsertColumn(3, L"数量", LVCFMT_CENTER, 80);
	//录入基本信息
	CString str;
	str.Format(L"%s", CStringW(p->patient.name));
	m_patientName = str;
	m_patientAge = p->patient.age;
	str.Format(L"%d", p->no);
	m_patientID = str;
	str.Format(L"%s", CStringW(p->doctor.department));
	m_department = str;
	str.Format(L"%s", CStringW(p->doctor.name));
	m_doctorName = str;
	str.Format(L"%s", CStringW(p->doctor.grade));
	m_doctorGrade = str;
	str.Format(L"%d", p->doctor.id);
	m_doctorID = str;
	//选择启用选项卡
	if (p->xuan == 1) //检查
	{
		m_checkFee = p->record.check.CheckFee.yuan + p->record.check.CheckFee.jiao * 0.1 + p->record.check.CheckFee.fen * 0.01;
		GetDlgItem(IDC_EDIT_CheckYuan)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_CHECK)->EnableWindow(TRUE);
		//检查信息写入列表
		for (int i = 0; i < CheckNum; i++)
		{
			m_listCheck.InsertItem(i, L"");
			str.Format(L"%s", CStringW(p->record.check.checks[i].name));
			m_listCheck.SetItemText(i, 1, str);

			float price = p->record.check.checks[i].fee.yuan + p->record.check.checks[i].fee.jiao * 0.1 + p->record.check.checks[i].fee.fen * 0.01;
			str.Format(L"%.2f", price);
			m_listCheck.SetItemText(i, 2, str);
			
			str.Format(L"%d", p->record.check.checks[i].count);
			m_listCheck.SetItemText(i, 3, str);
		}
	}
	else if (p->xuan == 2) //开药
	{
		m_drugFee = p->record.drug.DrugFee.yuan + p->record.drug.DrugFee.jiao * 0.1 + p->record.drug.DrugFee.fen * 0.01;
		GetDlgItem(IDC_EDIT_DrugYuan)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_DRUG)->EnableWindow(TRUE);
		//开药信息写入列表
		for (int i = 0; i < DrugNum; i++)
		{
			m_listDrug.InsertItem(i, L"");
			str.Format(L"%s", CStringW(p->record.drug.drugs[i].name));
			m_listDrug.SetItemText(i, 1, str);
			
			float price = p->record.drug.drugs[i].fee.yuan + p->record.drug.drugs[i].fee.jiao * 0.1 + p->record.drug.drugs[i].fee.fen * 0.01;
			str.Format(L"%.2f", price);
			m_listDrug.SetItemText(i, 2, str);
			
			str.Format(L"%d", p->record.drug.drugs[i].count);
			m_listDrug.SetItemText(i, 3, str);
		}
	}
	else if (p->xuan == 3) //住院
	{
		m_deposit = p->record.zhuyuan.deposit;
		//时间显示
		CTime startTime(p->record.zhuyuan.StartDate.year, p->record.zhuyuan.StartDate.month, p->record.zhuyuan.StartDate.day, 0, 0, 0);
		m_startDate.SetTime(&startTime);
		CTime endTime(p->record.zhuyuan.EndDate.year, p->record.zhuyuan.EndDate.month, p->record.zhuyuan.EndDate.day, 0, 0, 0);
		m_endDate.SetTime(&endTime);
		m_room = p->record.zhuyuan.room.id;
		GetDlgItem(IDC_DATETIMEPICKER_End)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_Deposit)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_AddDeposit)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_Room)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDetailDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int iCurSel = m_TabCtrl.GetCurSel();
	switch (iCurSel) //界面切换
	{
	case 0: //基本信息
		ShowTAB1(TRUE);
		ShowTAB2(FALSE);
		ShowTAB3(FALSE);
		ShowTAB4(FALSE);
		break;
	case 1: //检查信息
		ShowTAB1(FALSE);
		ShowTAB2(TRUE);
		ShowTAB3(FALSE);
		ShowTAB4(FALSE);
		break;
	case 2: //开药信息
		ShowTAB1(FALSE);
		ShowTAB2(FALSE);
		ShowTAB3(TRUE);
		ShowTAB4(FALSE);
		break;
	case 3: //住院信息
		ShowTAB1(FALSE);
		ShowTAB2(FALSE);
		ShowTAB3(FALSE);
		ShowTAB4(TRUE);
		break;
	}
	*pResult = 0;
}

void CDetailDlg::OnBnClickedButtonChangebasic()
{
	// TODO: 在此添加控件通知处理程序代码
	//显示和隐藏控件
	GetDlgItem(IDC_BUTTON_YES)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_NO)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ChangeBasic)->ShowWindow(FALSE);
	GetDlgItem(IDOK)->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_EDIT_PatientName))->SetReadOnly(FALSE);
	((CEdit*)GetDlgItem(IDC_EDIT_PatientAge))->SetReadOnly(FALSE);
}

void CDetailDlg::OnBnClickedButtonYes()
{
	// TODO: 在此添加控件通知处理程序代码
	//显示和隐藏控件
	GetDlgItem(IDC_BUTTON_YES)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_NO)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ChangeBasic)->ShowWindow(TRUE);
	GetDlgItem(IDOK)->ShowWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_PatientName))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_PatientAge))->SetReadOnly(TRUE);
	//修改结点信息
	UpdateData(TRUE);
	CStringToChar(m_patientName, p->patient.name);
	p->patient.age = m_patientAge;
	flag = 1;
}

void CDetailDlg::OnBnClickedButtonNo()
{
	// TODO: 在此添加控件通知处理程序代码
	//显示和隐藏控件
	GetDlgItem(IDC_BUTTON_YES)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_NO)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ChangeBasic)->ShowWindow(TRUE);
	GetDlgItem(IDOK)->ShowWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_PatientName))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_PatientAge))->SetReadOnly(TRUE);
}


void CDetailDlg::OnBnClickedButtonAdddeposit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDepositDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_deposit += dlg.m_deposit;
		if (p->record.zhuyuan.deposit < 0 && m_deposit > 0)
			turnover.yuan += -p->record.zhuyuan.deposit;
		p->record.zhuyuan.deposit = m_deposit;
		UpdateData(FALSE);
		flag = 1;
	}
}


void CDetailDlg::OnBnClickedButtonOut()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox(L"确定出院？", L"出院", MB_YESNO) == IDYES)
	{
		//修改结点
		p->record.zhuyuan.deposit = 0;
		p->xuan = 0;
		p->record.zhuyuan.EndDate.year = CurrentTime.GetYear();
		p->record.zhuyuan.EndDate.month = CurrentTime.GetMonth();
		p->record.zhuyuan.EndDate.day = CurrentTime.GetDay();
		//押金为负，需要补交，营业额增加
		if (m_deposit < 0)
			turnover.yuan += -m_deposit;
		//修改病房信息
		for (int i = 0; i < RoomNum; i++)
			if (Room[i].id == p->record.zhuyuan.room.id)
			{
				Room[i].number--;
				break;
			}
		//修改界面
		m_deposit = 0;
		m_room = 0;
		CTime time = CTime::GetCurrentTime();
		m_endDate.SetTime(&time);
		UpdateData(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_End)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Deposit)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_AddDeposit)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OUT)->EnableWindow(FALSE);
		flag = 1;
	}
}


void CDetailDlg::OnDtnDatetimechangeDatetimepickerEnd(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//获取修改后时间
	CTime endTime;
	m_endDate.GetTime(endTime);
	CTime startTime;
	m_startDate.GetTime(startTime);
	if (startTime >= endTime)
	{
		MessageBox(L"出院时间不能早于住院时间", L"提示");
		CTime time(p->record.zhuyuan.EndDate.year, p->record.zhuyuan.EndDate.month, p->record.zhuyuan.EndDate.day, 0, 0, 0);
		m_endDate.SetTime(&time);
	}
	else
	{	//修改结点
		p->record.zhuyuan.EndDate.year = endTime.GetYear();
		p->record.zhuyuan.EndDate.month = endTime.GetMonth();
		p->record.zhuyuan.EndDate.day = endTime.GetDay();
		flag = 1;
	}
	*pResult = 0;
}


void CDetailDlg::OnNMDblclkListCheck(NMHDR* pNMHDR, LRESULT* pResult)
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
			//修改营业额
			turnover.yuan = turnover.yuan - count * p->record.check.checks[nPos].fee.yuan + CheckDlg.m_count * p->record.check.checks[nPos].fee.yuan;
			turnover.jiao = turnover.jiao - -count * p->record.check.checks[nPos].fee.jiao + CheckDlg.m_count * p->record.check.checks[nPos].fee.jiao;
			turnover.fen = turnover.fen - count * p->record.check.checks[nPos].fee.fen + CheckDlg.m_count * p->record.check.checks[nPos].fee.fen;
			//修改链表结点
			p->record.check.checks[nPos].count = CheckDlg.m_count;
			p->record.check.CheckFee.yuan = p->record.check.CheckFee.yuan - count * p->record.check.checks[nPos].fee.yuan + CheckDlg.m_count * p->record.check.checks[nPos].fee.yuan;
			p->record.check.CheckFee.jiao = p->record.check.CheckFee.jiao - count * p->record.check.checks[nPos].fee.jiao + CheckDlg.m_count * p->record.check.checks[nPos].fee.jiao;
			p->record.check.CheckFee.fen = p->record.check.CheckFee.fen - count * p->record.check.checks[nPos].fee.fen + CheckDlg.m_count * p->record.check.checks[nPos].fee.fen;
			//修改界面
			CString str;
			str.Format(L"%d", CheckDlg.m_count);
			m_listCheck.SetItemText(nPos, 3, str);
			m_checkFee = p->record.check.CheckFee.yuan + p->record.check.CheckFee.jiao * 0.1 + p->record.check.CheckFee.fen * 0.01;
			UpdateData(FALSE);
			flag = 1;
		}
	}
	else
		MessageBox(L"无效的选择", L"提示");
	*pResult = 0;
}


void CDetailDlg::OnNMDblclkListDrug(NMHDR* pNMHDR, LRESULT* pResult)
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
		DrugDlg.m_drugName.Format(L"%s", CStringW(p->record.drug.drugs[nPos].name));
		DrugDlg.m_num = p->record.drug.drugs[nPos].count;
		DrugDlg.m_price = Drug[nPos].fee.yuan + Drug[nPos].fee.jiao * 0.1 + Drug[nPos].fee.fen * 0.01;
		int count = DrugDlg.m_num;
		if (DrugDlg.DoModal() == IDOK)
		{
			//修改营业额
			turnover.yuan = turnover.yuan - count * p->record.drug.drugs[nPos].fee.yuan + DrugDlg.m_num * p->record.drug.drugs[nPos].fee.yuan;
			turnover.jiao = turnover.jiao - count * p->record.drug.drugs[nPos].fee.jiao + DrugDlg.m_num * p->record.drug.drugs[nPos].fee.jiao;
			turnover.fen = turnover.fen - count * p->record.drug.drugs[nPos].fee.fen + DrugDlg.m_num * p->record.drug.drugs[nPos].fee.fen;
			//修改链表结点
			p->record.drug.drugs[nPos].count = DrugDlg.m_num;
			p->record.drug.DrugFee.yuan = p->record.drug.DrugFee.yuan - count * p->record.drug.drugs[nPos].fee.yuan + DrugDlg.m_num * p->record.drug.drugs[nPos].fee.yuan;
			p->record.drug.DrugFee.jiao = p->record.drug.DrugFee.jiao - count * p->record.drug.drugs[nPos].fee.jiao + DrugDlg.m_num * p->record.drug.drugs[nPos].fee.jiao;
			p->record.drug.DrugFee.fen = p->record.drug.DrugFee.fen - count * p->record.drug.drugs[nPos].fee.fen + DrugDlg.m_num * p->record.drug.drugs[nPos].fee.fen;
			//修改列表
			CString str;
			str.Format(L"%d", DrugDlg.m_num);
			m_listDrug.SetItemText(nPos, 3, str);
			m_drugFee = p->record.drug.DrugFee.yuan + p->record.drug.DrugFee.jiao * 0.1 + p->record.drug.DrugFee.fen * 0.01;
			UpdateData(FALSE);
			flag = 1;
		}
	}
	else
		MessageBox(L"无效的选择", L"提示");
	*pResult = 0;
}
