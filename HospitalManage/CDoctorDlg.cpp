// CDoctorDlg.cpp: 实现文件
//

#include "pch.h"
#include "HospitalManage.h"
#include "CDoctorDlg.h"
#include "afxdialogex.h"
#include "struct.h"
#include "function.h"
#include "CDoctorDetailDlg.h"

extern struct Doctor* doctor;
struct Doctor* pDoctor;
extern int flag;

// CDoctorDlg 对话框

IMPLEMENT_DYNAMIC(CDoctorDlg, CDialogEx)

CDoctorDlg::CDoctorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Doctor, pParent)
{

}

CDoctorDlg::~CDoctorDlg()
{
}

void CDoctorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Doctor, m_listDoctor);
}


BEGIN_MESSAGE_MAP(CDoctorDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_Doctor, &CDoctorDlg::OnNMDblclkListDoctor)
	ON_BN_CLICKED(IDC_BUTTON_AddDoctor, &CDoctorDlg::OnBnClickedButtonAdddoctor)
END_MESSAGE_MAP()


// CDoctorDlg 消息处理程序

void CDoctorDlg::EditItem(struct Doctor* pDoctor, int nItem)
{
	CString str;
	//姓名
	str.Format(L"%s", CStringW(pDoctor->name));
	m_listDoctor.SetItemText(nItem, 1, str);
	//工号
	str.Format(L"%d", pDoctor->id);
	m_listDoctor.SetItemText(nItem, 2, str);
	//科室
	str.Format(L"%s", CStringW(pDoctor->department));
	m_listDoctor.SetItemText(nItem, 3, str);
	//等级
	str.Format(L"%s", CStringW(pDoctor->grade));
	m_listDoctor.SetItemText(nItem, 4, str);
	//状态
	if (pDoctor->state == 0)
		str = L"请假";
	else if (pDoctor->state == 1)
		str = L"出诊";
	else if (pDoctor->state == 2)
		str = L"离职";
	m_listDoctor.SetItemText(nItem, 5, str);
}

void CDoctorDlg::EditList(struct Doctor* pHead)
{
	struct Doctor* q = pHead->next;
	int n = 0;
	while (q)
	{
		m_listDoctor.InsertItem(n, L"");
		EditItem(q, n);
		q = q->next;
		n++;
	}
}

BOOL CDoctorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置列表格式
	m_listDoctor.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listDoctor.InsertColumn(0, L"", LVCFMT_CENTER, 0);
	m_listDoctor.InsertColumn(1, L"姓名", LVCFMT_CENTER, 100);
	m_listDoctor.InsertColumn(2, L"工号", LVCFMT_CENTER, 100);
	m_listDoctor.InsertColumn(3, L"科室", LVCFMT_CENTER, 100);
	m_listDoctor.InsertColumn(4, L"等级", LVCFMT_CENTER, 100);
	m_listDoctor.InsertColumn(5, L"状态", LVCFMT_CENTER, 100);
	//显示医生信息
	EditList(doctor);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDoctorDlg::OnNMDblclkListDoctor(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	POSITION pos = m_listDoctor.GetFirstSelectedItemPosition(); //得到点击位置
	int nPos = m_listDoctor.GetNextSelectedItem(pos); //得到行号
	if (nItem >= 0 && nItem < m_listDoctor.GetItemCount())
	{
		//得到相应位置的结点
		pDoctor = SearchDoctor(doctor, _ttoi(m_listDoctor.GetItemText(nPos, 2)));
		if (pDoctor == NULL)
			MessageBox(L"找不到此信息", L"提示");
		else
		{
			//打开详细信息对话框
			CDoctorDetailDlg dlg;
			if (dlg.DoModal() == IDOK)
			{
				EditItem(pDoctor, nPos); //修改对应行
				flag = 1;
			}
		}
	}
	else
		MessageBox(L"无效的选择", L"提示");
	*pResult = 0;
}


void CDoctorDlg::OnBnClickedButtonAdddoctor()
{
	// TODO: 在此添加控件通知处理程序代码
	pDoctor = (struct Doctor*)malloc(sizeof(struct Doctor));
	InitDoctor(pDoctor); //医生结点初始化
	CDoctorDetailDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		int n = m_listDoctor.GetItemCount();
		m_listDoctor.InsertItem(n, L"");
		EditItem(pDoctor, n); //修改对应行
		AddDoctor(doctor, pDoctor);
		flag = 1;
	}
	else
		free(pDoctor);
}
