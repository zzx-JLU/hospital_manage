
// HospitalManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "HospitalManage.h"
#include "HospitalManageDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "CDetailDlg.h"
#include "CAddDlg.h"
#include "CSearchDlg.h"
#include "struct.h"
#include "function.h"
#include "CInfoDlg.h"
#include "CDoctorDlg.h"
#include "CPredictDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct ZhenLiao* head = NULL; //诊疗信息链表头指针
struct ZhenLiao* p = NULL; //指向诊疗信息链表的特定结点
struct Doctor* doctor = NULL; //医生链表头指针
int flag = 0; //标识有无修改
struct money turnover; //医院营业额
char department[10][10]; //科室
int NumOfDepartment[10]; //各科室挂号数
int NumOfHospital; //医院挂号数
struct room Room[RoomNum]; //病房
struct CheckItem Check[CheckNum]; //检查项目
struct DrugItem Drug[DrugNum]; //药品
CTime CurrentTime; //系统时间
CTime SaveTime; //保存时间



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CHospitalManageDlg 对话框



CHospitalManageDlg::CHospitalManageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOSPITALMANAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHospitalManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_DATETIMEPICKER_System, m_SystemTime);
}

BEGIN_MESSAGE_MAP(CHospitalManageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CHospitalManageDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CHospitalManageDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CHospitalManageDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCLE, &CHospitalManageDlg::OnBnClickedButtonCancle)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CHospitalManageDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CHospitalManageDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CHospitalManageDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_INFO, &CHospitalManageDlg::OnBnClickedButtonInfo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_DOCTOR, &CHospitalManageDlg::OnBnClickedButtonDoctor)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_System, &CHospitalManageDlg::OnDtnDatetimechangeDatetimepickerSystem)
	ON_BN_CLICKED(IDC_BUTTON_RoomAdjust, &CHospitalManageDlg::OnBnClickedButtonRoomadjust)
	ON_BN_CLICKED(IDC_BUTTON_Predict, &CHospitalManageDlg::OnBnClickedButtonPredict)
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CHospitalManageDlg::OnBnClickedButtonFile)
END_MESSAGE_MAP()


// CHospitalManageDlg 消息处理程序

void CHospitalManageDlg::EditItem(struct ZhenLiao* p, int nItem)
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

void CHospitalManageDlg::EditList(struct ZhenLiao* head)
{
	if (head == NULL)
		return;
	struct ZhenLiao* p = head->next;
	for (int i = 0; p != NULL; i++)
	{
		m_list.InsertItem(i, L"");
		EditItem(p, i);
		p = p->next;
	}
}


BOOL CHospitalManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	//设置列表控件格式
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

	//读取文件，建立诊疗信息链表
	head = CreateZhenLiao();
	if (head == NULL)
	{
		head = (struct ZhenLiao*)malloc(sizeof(struct ZhenLiao));
		head->next = NULL;
	}
	//读取文件，建立医生链表
	doctor = CreateDoctor();
	if (doctor == NULL)
	{
		doctor = (struct Doctor*)malloc(sizeof(struct Doctor));
		doctor->next = NULL;
	}
	//读取病房
	LoadRoom(Room);
	//读取科室
	LoadDepartment(department, NumOfDepartment);
	//读取检查项目、药品文件
	LoadDrug(Drug);
	LoadCheck(Check);
	//读取系统时间
	CurrentTime = CTime::GetCurrentTime();
	m_SystemTime.SetFormat(L"yyyy-MM-dd HH:mm:ss");
	m_SystemTime.SetTime(&CurrentTime);
	//读入其他信息文件
	Time time;
	LoadOther(&turnover, &NumOfHospital, &time);
	CTime ReadTime(time.year, time.month, time.day, time.hour, time.minute, 0);
	SaveTime = ReadTime;
	//修改挂号数
	CTime BaseTime(CurrentTime.GetYear(), CurrentTime.GetMonth(), CurrentTime.GetDay(), 0, 0, 0);
	if (SaveTime < BaseTime && BaseTime <= CurrentTime)
	{
		NumOfHospital = 0;
		for (int i = 0; i < 10; i++)
			NumOfDepartment[i] = 0;
		struct Doctor* q = doctor->next;
		while (q)
		{
			q->guahaoshu = 0;
			q = q->next;
		}
		flag = 1;
	}
	//修改住院押金
	CTime temp(CurrentTime.GetYear(), CurrentTime.GetMonth(), CurrentTime.GetDay(), 8, 0, 0);
	if (temp > SaveTime)
	{
		CTimeSpan span = temp - SaveTime;
		int day = span.GetDays();
		if (CurrentTime > temp)
			day++;
		p = head->next;
		while (p)
		{
			if (p->xuan == 3)
			{
				int i = GetRoom(p->record.zhuyuan.room.id);
				p->record.zhuyuan.deposit -= day * Room[i].price; //扣费
				//调整营业额
				if (p->record.zhuyuan.deposit >= 0)
					turnover.yuan += day * Room[i].price;
				else if (day * Room[i].price + p->record.zhuyuan.deposit > 0) //扣费前押金为正，扣费后押金为负
					turnover.yuan += day * Room[i].price + p->record.zhuyuan.deposit;
				//若押金不足，给出提示
				if (p->record.zhuyuan.deposit < 1000)
				{
					CString str;
					str.Format(L"患者 %s 住院押金不足1000元，请及时补交", CStringW(p->patient.name));
					MessageBox(str, L"提示");
				}
				flag = 1;
			}
			p = p->next;
		}
	}
	//诊疗信息显示在列表上
	EditList(head);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHospitalManageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHospitalManageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHospitalManageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHospitalManageDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
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
			//修改对应行
			EditItem(p, nPos);
		}
	}
	else
		MessageBox(L"无效的选择", L"提示");
	*pResult = 0;
}

void CHospitalManageDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	//列表显示复选框
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	//控件隐藏和显示
	GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FILE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DELETE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEARCH)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_INFO)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OK)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CANCLE)->ShowWindow(TRUE);
}

void CHospitalManageDlg::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//统计选中条数
	int n = 0;
	int i;
	for (i = 0; i < m_list.GetItemCount(); i++)
		if (m_list.GetCheck(i))
			n++;
	CString str;
	str.Format(L"已选中%d条，确认删除吗？", n);
	if (MessageBox(str, L"提示", MB_OKCANCEL) == IDOK)
	{
		//删除操作
		for (i = 0; i < m_list.GetItemCount(); i++)
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
			}
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); //恢复列表格式
		m_list.DeleteAllItems(); //清空列表
		EditList(head); //重写列表
		flag = 1;
		//控件隐藏和显示
		GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON_FILE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON_DELETE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SEARCH)->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON_INFO)->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OK)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CANCLE)->ShowWindow(FALSE);
	}
}

void CHospitalManageDlg::OnBnClickedButtonCancle()
{
	// TODO: 在此添加控件通知处理程序代码
	//恢复列表格式
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//控件隐藏和显示
	GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FILE)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DELETE)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEARCH)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_INFO)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON_OK)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CANCLE)->ShowWindow(FALSE);
}


void CHospitalManageDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NumOfHospital == 500)
		MessageBox(L"今日挂号数已满", L"提示");
	else
	{
		CAddDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			//新建结点添加到链表尾部
			Add(head, p);
			//写入列表
			int n = m_list.GetItemCount();
			m_list.InsertItem(n, L"");
			EditItem(p, n);
			//修改挂号次数
			NumOfHospital++;
			//修改营业额
			if (p->xuan == 1)
			{
				turnover.yuan += p->record.check.CheckFee.yuan;
				turnover.jiao += p->record.check.CheckFee.jiao;
				turnover.fen += p->record.check.CheckFee.fen;
			}
			else if (p->xuan == 2)
			{
				turnover.yuan += p->record.drug.DrugFee.yuan;
				turnover.jiao += p->record.drug.DrugFee.jiao;
				turnover.fen += p->record.drug.DrugFee.fen;
			}
			flag = 1;
		}
	}
}


void CHospitalManageDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	CSearchDlg dlg;
	dlg.DoModal();
	m_list.DeleteAllItems();
	EditList(head);
}


void CHospitalManageDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存到文件
	Save(head);
	SaveDepartment(department, NumOfDepartment);
	SaveDoctor(doctor);
	SaveRoom(Room);

	Time time;
	time.year = CurrentTime.GetYear();
	time.month = CurrentTime.GetMonth();
	time.day = CurrentTime.GetDay();
	time.hour = CurrentTime.GetHour();
	time.minute = CurrentTime.GetMinute();
	SaveOther(turnover, NumOfHospital, time);
	flag = 0;
	MessageBox(L"保存成功", L"提示");
}


void CHospitalManageDlg::OnBnClickedButtonInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CInfoDlg dlg;
	dlg.DoModal();
}


void CHospitalManageDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (flag)
	{
		int n = MessageBox(L"您有未保存的修改，是否保存？", L"提示", MB_YESNOCANCEL);
		if (n == IDYES)
		{
			Save(head);
			SaveDepartment(department, NumOfDepartment);
			SaveDoctor(doctor);
			SaveRoom(Room);

			Time time;
			time.year = CurrentTime.GetYear();
			time.month = CurrentTime.GetMonth();
			time.day = CurrentTime.GetDay();
			time.hour = CurrentTime.GetHour();
			time.minute = CurrentTime.GetMinute();
			SaveOther(turnover, NumOfHospital, time);
			//释放链表
			Free(head, doctor);
		}
		else if (n == IDNO)
			Free(head, doctor); //释放链表
		else if (n == IDCANCEL)
			return;
	}
	else
		Free(head, doctor);
	CDialogEx::OnClose();
}


void CHospitalManageDlg::OnBnClickedButtonDoctor()
{
	// TODO: 在此添加控件通知处理程序代码
	CDoctorDlg dlg;
	dlg.DoModal();
}


void CHospitalManageDlg::OnDtnDatetimechangeDatetimepickerSystem(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//接收新时间
	CTime NewTime;
	m_SystemTime.GetTime(NewTime);
	if (NewTime <= SaveTime || NewTime <= CurrentTime)
		return;
	//修改挂号数
	CTime BaseTime(NewTime.GetYear(), NewTime.GetMonth(), NewTime.GetDay(), 0, 0, 0);
	if (NewTime >= BaseTime && BaseTime > SaveTime)
	{
		NumOfHospital = 0;
		for (int i = 0; i < 10; i++)
		{
			NumOfDepartment[i] = 0;
		}
		struct Doctor* q = doctor->next;
		while (q)
		{
			q->guahaoshu = 0;
			q = q->next;
		}
		flag = 1;
	}
	//修改押金
	CTime temp(NewTime.GetYear(), NewTime.GetMonth(), NewTime.GetDay(), 8, 0, 0);
	if (temp > SaveTime && temp > CurrentTime)
	{
		CTimeSpan span = temp - SaveTime;
		int day = span.GetDays();
		if (NewTime >= temp)
			day++;
		p = head->next;
		while (p)
		{
			if (p->xuan == 3)
			{
				int i = GetRoom(p->record.zhuyuan.room.id);
				p->record.zhuyuan.deposit -= day * Room[i].price; //扣费
				//修改营业额
				if (p->record.zhuyuan.deposit >= 0)
					turnover.yuan += day * Room[i].price;
				else if (day * Room[i].price + p->record.zhuyuan.deposit > 0)
					turnover.yuan += day * Room[i].price + p->record.zhuyuan.deposit;
				//若押金不足，给出提示
				if (p->record.zhuyuan.deposit < 1000)
				{
					CString str;
					str.Format(L"患者 %s 住院押金不足1000元，请及时补交", CStringW(p->patient.name));
					MessageBox(str, L"提示");
				}
				flag = 1;
			}
			p = p->next;
		}
	}
	//修改当前时间
	if (NewTime > CurrentTime)
		CurrentTime = NewTime;
	UpdateData(FALSE);
	*pResult = 0;
}


void CHospitalManageDlg::OnBnClickedButtonRoomadjust()
{
	// TODO: 在此添加控件通知处理程序代码
	UpDateRoom();
}


void CHospitalManageDlg::OnBnClickedButtonPredict()
{
	// TODO: 在此添加控件通知处理程序代码
	CPredictDlg dlg;
	dlg.DoModal();
}


void CHospitalManageDlg::OnBnClickedButtonFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString PathName;
	CFileDialog filedlg(true, L"txt", L"*.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"txt files (*.txt)", NULL);
	if (filedlg.DoModal() == IDOK)
	{
		PathName = filedlg.GetPathName(); //得到文件路径
		char name[500];
		CStringToChar(PathName, name);
		//打开文件，读取信息，建立一个新链表
		int i;     //数组循环计数用 
		FILE* fp;
		struct ZhenLiao* t, * q, * pHead;
		if ((fp = fopen(name, "r")) == NULL)
		{
			//printf("打开失败，返回头指针指向NULL");
			MessageBox(L"打开诊疗信息文件失败", L"提示", MB_OK);
			return;
		}
		pHead = q = (struct ZhenLiao*)malloc(sizeof(struct ZhenLiao));//哨兵节点 
		q->next = NULL;
		int temp = 1;
		getc(fp);
		while (!feof(fp))
		{
			if (temp)
			{
				rewind(fp);
				temp = 0;
			}
			t = (struct ZhenLiao*)malloc(sizeof(struct ZhenLiao));
			fscanf(fp, "%d", &(t->no));//      导入挂号 
			fscanf(fp, "%s %d %d", t->patient.name, &(t->patient.age), &(t->patient.id));//导入患者的名字和年龄
			fscanf(fp, "%s %s %s %d", t->doctor.name, t->doctor.grade, t->doctor.department, &(t->doctor.id));//导入医生的名字，等级，科室，工号 
			fscanf(fp, "%d %d %d", &(t->date.year), &(t->date.month), &(t->date.day));//导入日期年月日
			fscanf(fp, "%d", &(t->xuan));//导入选择 
			if (t->xuan == 1)
			{
				fscanf(fp, "%d %d %d", &(t->record.check.CheckFee.yuan), &(t->record.check.CheckFee.jiao), &(t->record.check.CheckFee.fen));//费用圆角分
				for (i = 0; i < 10; i++)
					fscanf(fp, "%s %d %d %d %d", t->record.check.checks[i].name, &(t->record.check.checks[i].count), &(t->record.check.checks[i].fee.yuan), &(t->record.check.checks[i].fee.jiao), &(t->record.check.checks[i].fee.fen));//检 查 名 字，次 数，单次费用 	   	
			}
			if (t->xuan == 2)
			{
				fscanf(fp, "%d %d %d", &(t->record.drug.DrugFee.yuan), &(t->record.drug.DrugFee.jiao), &(t->record.drug.DrugFee.fen));//费用圆角分
				for (i = 0; i < 10; i++)
					fscanf(fp, "%s %d %d %d %d", t->record.drug.drugs[i].name, &(t->record.drug.drugs[i].count), &(t->record.drug.drugs[i].fee.yuan), &(t->record.drug.drugs[i].fee.jiao), &(t->record.drug.drugs[i].fee.fen));//检 查 名 字，次 数，单次费用 
			}
			if (t->xuan == 3)
			{
				fscanf(fp, "%d %d %d", &(t->record.zhuyuan.StartDate.year), &(t->record.zhuyuan.StartDate.month), &(t->record.zhuyuan.StartDate.day));
				fscanf(fp, "%d %d %d", &(t->record.zhuyuan.EndDate.year), &(t->record.zhuyuan.EndDate.month), &(t->record.zhuyuan.EndDate.day));//开始结束日期
				fscanf(fp, "%d", &(t->record.zhuyuan.deposit));//押金
				fscanf(fp, "%d", &(t->record.zhuyuan.room.id));//病房类型的两个参数 
			}
			else if (t->xuan == 0) //已出院
			{
				fscanf(fp, "%d %d %d", &(t->record.zhuyuan.StartDate.year), &(t->record.zhuyuan.StartDate.month), &(t->record.zhuyuan.StartDate.day));//住院日期
				fscanf(fp, "%d %d %d", &(t->record.zhuyuan.EndDate.year), &(t->record.zhuyuan.EndDate.month), &(t->record.zhuyuan.EndDate.day));//出院日期
			}
			//写入列表
			int n = m_list.GetItemCount();
			m_list.InsertItem(n, L"");
			EditItem(t, n);
			//链表连接
			t->next = NULL;
			q->next = t;
			q = t;
		}
		fclose(fp);
		Add(head, pHead->next); //将新链表接到原链表之后
		free(pHead); //释放新链表的哨兵结点
		flag = 1;
	}
}
