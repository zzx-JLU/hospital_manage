// CInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "HospitalManage.h"
#include "CInfoDlg.h"
#include "afxdialogex.h"
#include "struct.h"

extern struct money turnover;
extern struct ZhenLiao* head;
extern struct room Room[10];

// CInfoDlg 对话框

IMPLEMENT_DYNAMIC(CInfoDlg, CDialogEx)

CInfoDlg::CInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFO, pParent)
	, m_turnover(0)
	, m_count(0)
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Turnover, m_turnover);
	DDV_MinMaxFloat(pDX, m_turnover, 0, FLT_MAX);
	DDX_Control(pDX, IDC_LIST_ZhuYuan, m_list);
	DDX_Text(pDX, IDC_EDIT_Count, m_count);
	DDV_MinMaxInt(pDX, m_count, 0, INT_MAX);
	DDX_Control(pDX, IDC_LIST_Room, m_listRoom);
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ZhuYuan, &CInfoDlg::OnBnClickedButtonZhuyuan)
END_MESSAGE_MAP()


// CInfoDlg 消息处理程序

void CInfoDlg::EditItem(struct ZhenLiao* p, int nItem)
{
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
	//住院时间
	str.Format(L"%d-%d-%d", p->record.zhuyuan.StartDate.year, p->record.zhuyuan.StartDate.month, p->record.zhuyuan.StartDate.day);
	m_list.SetItemText(nItem, 8, str);
	//病房
	str.Format(L"%d", p->record.zhuyuan.room.id);
	m_list.SetItemText(nItem, 9, str);
	//押金
	str.Format(L"%d", p->record.zhuyuan.deposit);
	m_list.SetItemText(nItem, 10, str);
}

BOOL CInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置列表格式
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, L"", LVCFMT_CENTER, 0);
	m_list.InsertColumn(1, L"患者姓名", LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, L"患者年龄", LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, L"挂号", LVCFMT_CENTER, 100);
	m_list.InsertColumn(4, L"医生姓名", LVCFMT_CENTER, 100);
	m_list.InsertColumn(5, L"医生级别", LVCFMT_CENTER, 100);
	m_list.InsertColumn(6, L"科室", LVCFMT_CENTER, 80);
	m_list.InsertColumn(7, L"工号", LVCFMT_CENTER, 100);
	m_list.InsertColumn(8, L"住院时间", LVCFMT_CENTER, 100);
	m_list.InsertColumn(9, L"病房", LVCFMT_CENTER, 100);
	m_list.InsertColumn(10, L"押金", LVCFMT_CENTER, 100);
	//设置病房列表格式
	m_listRoom.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listRoom.InsertColumn(0, L"", LVCFMT_CENTER, 0);
	m_listRoom.InsertColumn(1, L"病房号", LVCFMT_CENTER, 100);
	m_listRoom.InsertColumn(2, L"护理类型", LVCFMT_CENTER, 100);
	m_listRoom.InsertColumn(3, L"病房类型", LVCFMT_CENTER, 100);
	m_listRoom.InsertColumn(4, L"剩余病床数", LVCFMT_CENTER, 100);
	//写入病房列表
	for (int i = 0; i < RoomNum; i++)
	{
		m_listRoom.InsertItem(i, L"");
		CString str;
		//病房号
		str.Format(L"%d", Room[i].id);
		m_listRoom.SetItemText(i, 1, str);
		//护理类型
		m_listRoom.SetItemText(i, 2, CStringW(Room[i].nurse));
		//病房类型
		m_listRoom.SetItemText(i, 3, CStringW(Room[i].type));
		//剩余病房数
		str.Format(L"%d", Room[i].NumOfBed - Room[i].number);
		m_listRoom.SetItemText(i, 4, str);
	}
	//显示营业额
	m_turnover = turnover.yuan + turnover.jiao * 0.1 + turnover.fen * 0.01;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CInfoDlg::OnBnClickedButtonZhuyuan()
{
	// TODO: 在此添加控件通知处理程序代码
	struct ZhenLiao* q = head->next;
	m_count = 0;
	while (q)
	{
		if (q->xuan == 3)
		{
			m_list.InsertItem(m_count, L"");
			EditItem(q, m_count);
			//住院人数增加
			m_count++;
		}
		q = q->next;
	}
	if (m_count == 0)
		MessageBox(L"目前没有住院患者", L"提示");
	UpdateData(FALSE);
}
