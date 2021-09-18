#include "pch.h"
#include "function.h"
#include "struct.h"

extern struct CheckItem Check[CheckNum];
extern struct DrugItem Drug[DrugNum];
extern struct room Room[RoomNum];

void CStringToChar(CString cstring, char* str)
{
	int len = cstring.GetLength();
	int bytes = WideCharToMultiByte(CP_ACP, 0, cstring, len, NULL, 0, NULL, NULL);
	char* temp = (char*)malloc(bytes + 1);
	memset(temp, 0, bytes + 1);
	WideCharToMultiByte(CP_OEMCP, 0, cstring, len, temp, bytes, NULL, NULL);
	strcpy(str, temp);
	free(temp);
}

struct ZhenLiao* CreateZhenLiao()
{
	int i;     //数组循环计数用 
	FILE* fp;
	struct ZhenLiao* p, * q, * head;
	if ((fp = fopen("record.txt", "r")) == NULL)
	{
		//printf("打开失败，返回头指针指向NULL");
		MessageBox(NULL, L"打开诊疗信息文件失败", L"提示", MB_OK);
		return NULL;
	}
	head = q = (struct ZhenLiao*)malloc(sizeof(struct ZhenLiao));//哨兵节点 
	q->next = NULL;
	int flag = 1;
	getc(fp);
	while (!feof(fp))
	{
		if (flag)
		{
			rewind(fp);
			flag = 0;
		}
		p = (struct ZhenLiao*)malloc(sizeof(struct ZhenLiao));
		fscanf(fp, "%d", &(p->no));//      导入挂号 
		fscanf(fp, "%s %d %d", p->patient.name, &(p->patient.age), &(p->patient.id));//导入患者的名字和年龄
		fscanf(fp, "%s %s %s %d", p->doctor.name, p->doctor.grade, p->doctor.department, &(p->doctor.id));//导入医生的名字，等级，科室，工号 
		fscanf(fp, "%d %d %d", &(p->date.year), &(p->date.month), &(p->date.day));//导入日期年月日
		fscanf(fp, "%d", &(p->xuan));//导入选择 
		if (p->xuan == 1)
		{
			fscanf(fp, "%d %d %d", &(p->record.check.CheckFee.yuan), &(p->record.check.CheckFee.jiao), &(p->record.check.CheckFee.fen));//费用圆角分
			for (i = 0; i < 10; i++)
				fscanf(fp, "%s %d %d %d %d", p->record.check.checks[i].name, &(p->record.check.checks[i].count), &(p->record.check.checks[i].fee.yuan), &(p->record.check.checks[i].fee.jiao), &(p->record.check.checks[i].fee.fen));//检 查 名 字，次 数，单次费用 	   	
		}
		else if (p->xuan == 2)
		{
			fscanf(fp, "%d %d %d", &(p->record.drug.DrugFee.yuan), &(p->record.drug.DrugFee.jiao), &(p->record.drug.DrugFee.fen));//费用圆角分
			for (i = 0; i < 10; i++)
				fscanf(fp, "%s %d %d %d %d", p->record.drug.drugs[i].name, &(p->record.drug.drugs[i].count), &(p->record.drug.drugs[i].fee.yuan), &(p->record.drug.drugs[i].fee.jiao), &(p->record.drug.drugs[i].fee.fen));//检 查 名 字，次 数，单次费用 
		}
		else if (p->xuan == 3)
		{
			fscanf(fp, "%d %d %d", &(p->record.zhuyuan.StartDate.year), &(p->record.zhuyuan.StartDate.month), &(p->record.zhuyuan.StartDate.day));
			fscanf(fp, "%d %d %d", &(p->record.zhuyuan.EndDate.year), &(p->record.zhuyuan.EndDate.month), &(p->record.zhuyuan.EndDate.day));//开始结束日期
			fscanf(fp, "%d", &(p->record.zhuyuan.deposit));//押金
			fscanf(fp, "%d", &(p->record.zhuyuan.room.id));//病房类型的两个参数 
		}
		else if (p->xuan == 0) //已出院
		{
			fscanf(fp, "%d %d %d", &(p->record.zhuyuan.StartDate.year), &(p->record.zhuyuan.StartDate.month), &(p->record.zhuyuan.StartDate.day));//住院日期
			fscanf(fp, "%d %d %d", &(p->record.zhuyuan.EndDate.year), &(p->record.zhuyuan.EndDate.month), &(p->record.zhuyuan.EndDate.day));//出院日期
		}
		p->next = NULL;
		q->next = p;
		q = p;
	}
	fclose(fp);
	return head;
}

struct ZhenLiao* Search(struct ZhenLiao* head, int id)
{
	if (head == NULL)
		return NULL;
	struct ZhenLiao* p = head->next;
	while (p && id != p->no)
		p = p->next;
	return p;
}

void DeleteZhenLiao(struct ZhenLiao* head, struct ZhenLiao* p)
{
	struct ZhenLiao* q = head;
	while (q && q->next != p)
		q = q->next;
	if (q == NULL)
	{
		//printf("无此诊疗信息");
		MessageBox(NULL, L"无此诊疗信息", L"提示", MB_OK);
		return;
	}
	q->next = p->next;
	free(p);
	p = NULL;
}

void Add(struct ZhenLiao* pHead, struct ZhenLiao* pNew)
{
	struct ZhenLiao* p = pHead;
	while (p && p->next)
		p = p->next;
	if (p && p->next == NULL)
		p->next = pNew;
}

void Save(struct ZhenLiao* head)
{
	FILE* fp;
	if ((fp = fopen("record.txt", "w")) == NULL)
	{
		//printf("Faile to open the file!");
		MessageBox(NULL, L"打开诊疗信息文件失败", L"提示", MB_OK);
		return;
	}//打开文件

	struct ZhenLiao* p = head->next;
	while (p != NULL)
	{
		fprintf(fp, "%d\n", p->no);//存诊疗记录编号
		fprintf(fp, "%s %d %d\n", p->patient.name, p->patient.age, p->patient.id);//先存患者的name与age
		fprintf(fp, "%s %s %s %d\n", p->doctor.name, p->doctor.grade, p->doctor.department, p->doctor.id);//医生姓名 医生等级 医生科室 医生工号
		fprintf(fp, "%d %d %d\n", p->date.year, p->date.month, p->date.day);//导入日期年月日
		fprintf(fp, "%d\n", p->xuan);//存选择项目
		if (p->xuan == 1)//检查
		{
			fprintf(fp, "%d %d %d\n", p->record.check.CheckFee.yuan, p->record.check.CheckFee.jiao, p->record.check.CheckFee.fen);//存钱(已经消费项目总费用)
			int i;
			for (i = 0; i < 9; i++)
			{
				fprintf(fp, "%s %d %d %d %d\n", p->record.check.checks[i].name, p->record.check.checks[i].count, p->record.check.checks[i].fee.yuan, p->record.check.checks[i].fee.jiao, p->record.check.checks[i].fee.fen);//项目名称 检查次数 费用
			}
			fprintf(fp, "%s %d %d %d %d", p->record.check.checks[9].name, p->record.check.checks[9].count, p->record.check.checks[9].fee.yuan, p->record.check.checks[9].fee.jiao, p->record.check.checks[9].fee.fen);
		}
		else if (p->xuan == 2)//开药
		{
			fprintf(fp, "%d %d %d\n", p->record.drug.DrugFee.yuan, p->record.drug.DrugFee.jiao, p->record.drug.DrugFee.fen);//存钱(已经消费项目总费用)
			int i;
			for (i = 0; i < 9; i++)
			{
				fprintf(fp, "%s %d %d %d %d\n", p->record.drug.drugs[i].name, p->record.drug.drugs[i].count, p->record.drug.drugs[i].fee.yuan, p->record.drug.drugs[i].fee.jiao, p->record.drug.drugs[i].fee.fen);//药品名称 数量 费用
			}
			fprintf(fp, "%s %d %d %d %d", p->record.drug.drugs[9].name, p->record.drug.drugs[9].count, p->record.drug.drugs[9].fee.yuan, p->record.drug.drugs[9].fee.jiao, p->record.drug.drugs[9].fee.fen);
		}
		else if (p->xuan == 3)//住院
		{
			fprintf(fp, "%d %d %d\n", p->record.zhuyuan.StartDate.year, p->record.zhuyuan.StartDate.month, p->record.zhuyuan.StartDate.day);//住院日期
			fprintf(fp, "%d %d %d\n", p->record.zhuyuan.EndDate.year, p->record.zhuyuan.EndDate.month, p->record.zhuyuan.EndDate.day);//预计出院日期
			fprintf(fp, "%d\n", p->record.zhuyuan.deposit);//押金
			fprintf(fp, "%d", p->record.zhuyuan.room.id);//住院床位信息
		}
		else if (p->xuan == 0) //已出院
		{
			fprintf(fp, "%d %d %d\n", p->record.zhuyuan.StartDate.year, p->record.zhuyuan.StartDate.month, p->record.zhuyuan.StartDate.day);//住院日期
			fprintf(fp, "%d %d %d", p->record.zhuyuan.EndDate.year, p->record.zhuyuan.EndDate.month, p->record.zhuyuan.EndDate.day);//出院日期
		}
		if (p->next)
			fprintf(fp, "\n");
		p = p->next;
		/*else//最后一条 不加换行
		{
			if (p->xuan == 1)//检查
			{
				fprintf(fp, "%d %d %d\n", p->c.a.feiyong.yuan, p->c.a.feiyong.jiao, p->c.a.feiyong.fen);//存钱(已经消费项目总费用)
				int i;
				for (i = 0; i <= 9; i++)
				{
					fprintf(fp, "%s %d %d %d %d", p->c.a.a[i].name, p->c.a.a[i].count, p->c.a.a[i].feiyong.yuan, p->c.a.a[i].feiyong.jiao, p->c.a.a[i].feiyong.fen);//项目名称 检查次数 费用
				}
			}
			if (p->xuan == 2)//开药
			{
				fprintf(fp, "%d %d %d\n", p->c.b.feiyong.yuan, p->c.b.feiyong.jiao, p->c.b.feiyong.fen);//存钱(已经消费项目总费用)
				int i;
				for (i = 0; i <= 9; i++)
				{
					fprintf(fp, "%s %d %d %d %d", p->c.b.a[i].name, p->c.b.a[i].count, p->c.b.a[i].feiyong.yuan, p->c.b.a[i].feiyong.jiao, p->c.b.a[i].feiyong.fen);//药品名称 数量 费用
				}
			}
			if (p->xuan == 3)//住院
			{
				fprintf(fp, "%d %d %d\n", p->c.c.a.year, p->c.c.a.month, p->c.c.a.day);//住院日期
				fprintf(fp, "%d %d %d\n", p->c.c.b.year, p->c.c.b.month, p->c.c.b.day);//预计出院日期
				fprintf(fp, "%d\n", p->c.c.deposit);//押金
				fprintf(fp, "%d", p->c.c.c.id);//住院床位信息
			}
			if (p->xuan == 0) //已出院
			{
				fprintf(fp, "%d %d %d\n", p->c.c.a.year, p->c.c.a.month, p->c.c.a.day);//住院日期
				fprintf(fp, "%d %d %d", p->c.c.b.year, p->c.c.b.month, p->c.c.b.day);//出院日期
			}
			p = p->next;
		}*/
	}
	fclose(fp);
}

struct Doctor* SearchDoctor(struct Doctor* pDoctor, int id)
{
	struct Doctor* p = pDoctor->next;
	while (p)
	{
		if (p->id == id)
			return p;
		p = p->next;
	}
	return p;
}

void AddDoctor(struct Doctor* head, struct Doctor* pDoctor)
{
	struct Doctor* p = head;
	while (p && p->next)
		p = p->next;
	if (p && p->next == NULL)
		p->next = pDoctor;
}

void DeleteDoctor(struct Doctor* head, int i)
{
	struct Doctor* q, * p;
	p = head;
	q = head->next;
	while (q != NULL && q->id != i)
	{
		p = q;
		q = q->next;
	}
	if (q == NULL)
	{
		//printf("无此诊疗信息");
		MessageBox(NULL, L"无此医生信息", L"提示", MB_OK);
		return;
	}
	p->next = q->next;
	free(q);
	//printf("删除成功");
	MessageBox(NULL, L"删除成功", L"提示", MB_OK);
}

void SaveDoctor(struct Doctor* head)
{
	int i;     //数组循环计数用 
	FILE* fp;
	if ((fp = fopen("doctor.txt", "w")) == NULL)
	{
		//printf("打开失败");
		MessageBox(NULL, L"打开医生文件失败", L"提示", MB_OK);
		return;
	}
	struct Doctor* p = head->next;
	while (p != NULL) {
		fprintf(fp, "%s %s %s %d %d %d\n", p->name, p->grade, p->department, p->state, p->id, p->guahaoshu);
		for (i = 0; i < 7; i++)
			fprintf(fp, "%d ", p->chuzhen[i]);
		fprintf(fp, "\n");
		p = p->next;
	}
	fclose(fp);
}

struct Doctor* CreateDoctor()
{
	int i;     //数组循环计数用 
	FILE* fp;
	struct Doctor* p, * q, * head;
	if ((fp = fopen("doctor.txt", "r")) == NULL)
	{
		//printf("打开失败，返回头指针指向NULL");
		MessageBox(NULL, L"打开医生文件失败", L"提示", MB_OK);
		return NULL;
	}
	head = q = (struct Doctor*)malloc(sizeof(struct Doctor));//哨兵节点 
	q->next = NULL;
	int flag = 1;
	getc(fp);
	while (!feof(fp))
	{
		if (flag)
		{
			rewind(fp);
			flag = 0;
		}
		p = (struct Doctor*)malloc(sizeof(struct Doctor));
		fscanf(fp, "%s %s %s %d %d %d\n", p->name, p->grade, p->department, &(p->state), &(p->id), &(p->guahaoshu));//名字等级科室工号 
		for (i = 0; i < 7; i++)
			fscanf(fp, "%d ", &(p->chuzhen[i]));//1为出诊，0不出
		p->next = NULL;
		q->next = p;
		q = p;
	}
	fclose(fp);
	return head;
}

/*void FindDoctor(struct Doctor* head, char* keshi, char* name)
{
	struct Doctor* p = head->next;
	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0 && strcmp(p->department, keshi) == 0)
		{
			//操作
		}
		p = p->next;
	}
}*/

void InitDoctor(struct Doctor* p)
{
	p->name[0] = '\0';
	p->grade[0] = '\0';
	p->id = 0;
	p->guahaoshu = 0;
	p->department[0] = '\0';
	p->next = NULL;
	p->state = -1;
	for (int i = 0; i < 7; i++)
		p->chuzhen[i] = 0;
}

void LoadRoom(struct room Room[])
{
	FILE* fp;
	if ((fp = fopen("room.txt", "r")) == NULL)
	{
		//printf("房间文件打开失败！\n");
		MessageBox(NULL, L"房间文件打开失败", L"提示", MB_OK);
		return;
	}
	int i;
	for (i = 0; i < RoomNum; i++)
	{
		fscanf(fp, "%s %s %d %d %d %d\n", Room[i].nurse, Room[i].type, &Room[i].NumOfBed, &Room[i].price, &Room[i].number, &Room[i].id);
	}
	fclose(fp);
}

void SaveRoom(struct room Room[])
{
	FILE* fp;
	if ((fp = fopen("room.txt", "w")) == NULL)
	{
		//printf("房间文件打开失败！（保存）\n");
		MessageBox(NULL, L"房间文件打开失败", L"提示", MB_OK);
		return;
	}
	int i;
	for (i = 0; i < RoomNum; i++)
	{
		fprintf(fp, "%s %s %d %d %d %d\n", Room[i].nurse, Room[i].type, Room[i].NumOfBed, Room[i].price, Room[i].number, Room[i].id);
	}
	fclose(fp);
}

void LoadDepartment(char department[10][10], int NumOfDepartment[])
{
	FILE* fp;
	if ((fp = fopen("department.txt", "r")) == NULL)
	{
		//printf("科室文件打开失败！（保存）\n");
		MessageBox(NULL, L"科室文件打开失败", L"提示", MB_OK);
		return;
	}
	int i;
	for (i = 0; i < 10; i++)
	{
		fscanf(fp, "%s %d\n", department[i], &NumOfDepartment[i]);
	}
	fclose(fp);
}

void SaveDepartment(char department[10][10], int NumOfDepartment[])
{
	FILE* fp;
	if ((fp = fopen("department.txt", "w")) == NULL)
	{
		//printf("科室文件打开失败！（保存）\n");
		MessageBox(NULL, L"房间文件打开失败", L"提示", MB_OK);
		return;
	}
	int i;
	for (i = 0; i < 10; i++)
	{
		fprintf(fp, "%s %d\n", department[i], NumOfDepartment[i]);
	}
	fclose(fp);
}

void LoadCheck(struct CheckItem ALL[10])
{
	FILE* fp;
	int i;
	fp = fopen("xiangmu.txt", "r");
	if (fp == NULL)
	{
		MessageBox(NULL, L"检查项目文件打开失败", L"提示", MB_OK);
		return;
	}
	for (i = 0; i < 10; i++)
	{
		fscanf(fp, "%s %d", ALL[i].name, &(ALL[i].count));   //这里我直接count自带0了，不用再初始化了 
		fscanf(fp, "%d %d %d", &(ALL[i].fee.yuan), &(ALL[i].fee.jiao), &(ALL[i].fee.fen));
	}
	fclose(fp);
}

void LoadDrug(struct DrugItem all[10])
{
	FILE* fp;
	int i;
	fp = fopen("yaopin.txt", "r");
	if (fp == NULL)
	{
		MessageBox(NULL, L"药品文件打开失败", L"提示", MB_OK);
		return;
	}
	for (i = 0; i < 10; i++)
	{
		fscanf(fp, "%s %d", all[i].name, &(all[i].count));   //这里我直接count自带0了，不用再初始化了 
		fscanf(fp, "%d %d %d", &(all[i].fee.yuan), &(all[i].fee.jiao), &(all[i].fee.fen));
	}
	fclose(fp);
}

void LoadOther(struct money* turnover, int* num, Time* time)
{
	FILE* fp;
	fp = fopen("TNT.txt", "r");
	if (fp == NULL)
	{
		MessageBox(NULL, L"其他信息文件打开失败", L"提示", MB_OK);
		return;
	}
	fscanf(fp, "%d%d%d", &(turnover->yuan), &(turnover->jiao), &(turnover->fen));//文件里先是总营业额的圆角分
	fscanf(fp, "%d", num);//然后是总挂号数
	fscanf(fp, "%d%d%d%d%d", &(time->year), &(time->month), &(time->day), &(time->hour), &(time->minute)); //上次关系统保存的时间
	fclose(fp);
}

void SaveOther(struct money turnover, int num, struct Time time)
{
	FILE* fp;
	fp = fopen("TNT.txt", "w");
	if (fp == NULL)
	{
		MessageBox(NULL, L"其他信息文件打开失败", L"提示", MB_OK);
		return;
	}
	fprintf(fp, "%d %d %d\n", turnover.yuan, turnover.jiao, turnover.fen);//文件里先是总营业额的圆角分
	fprintf(fp, "%d\n", num);//然后是总挂号数
	fprintf(fp, "%d %d %d %d %d\n", time.year, time.month, time.day, time.hour, time.minute); //上次关系统保存的时间 
	fclose(fp);
}

int LiveNow()
{
	int now = 0;
	int i;
	for (i = 0; i < RoomNum; i++)
	{
		now += Room[i].number;
	}
	return now;
}

int RoomSum()
{
	int all = 0;
	int i;
	for (i = 0; i < RoomNum; i++)
	{
		all += Room[i].NumOfBed;
		/*if (strcmp(Room[i].type, "单人病房") == 0)
			all += 1;
		if (strcmp(Room[i].type, "双人病房") == 0)
			all += 2;
		if (strcmp(Room[i].type, "三人病房") == 0)
			all += 3;
		if (strcmp(Room[i].type, "单人陪护病房") == 0)
			all += 1;
		if (strcmp(Room[i].type, "单人陪护疗养病房") == 0)
			all += 1;*/
	}
	return all;
}

void UpDateRoom()
{
	float left;
	left = LiveNow() / ((1.0) * RoomSum());
	if(left < 0.8)
	{
		int i = 0;
		while (i < RoomNum && (LiveNow() / ((1.0) * RoomSum())) < 0.8)//所有房间并且剩余床位大于百分之20
		{
			if (strcmp(Room[i].type, "双人病房") == 0)
			{
				if (Room[i].number < 2)
				{
					strcpy(Room[i].type, "单人病房");
					Room[i].price += 100;
					Room[i].NumOfBed = 1;
					//printf("已将双人病房:%d 改为单人病房\n", Room[i].id);
					CString str;
					str.Format(L"已将双人病房: %d 改为单人病房", Room[i].id);
					MessageBox(NULL, str, L"提示", MB_OK);
				}
			}
			if (strcmp(Room[i].type, "三人病房") == 0)
			{
				if (Room[i].number < 2)
				{
					strcpy(Room[i].type, "双人病房");
					Room[i].price += 100;
					Room[i].NumOfBed = 2;
					//printf("已将三人病房:%d 改为双人病房\n", Room[i].id);
					CString str;
					str.Format(L"已将三人病房:%d 改为双人病房", Room[i].id);
					MessageBox(NULL, str, L"提示", MB_OK);
				}
			}
			i++;
		}
	}
	else if (left >= 0.8)//床位紧张条件
	{
		int i;
		for (i = 0; i <= 9; i++)
		{
			if (strcmp(Room[i].type, "单人陪护疗养病房") == 0)
			{
				//printf("已将单人陪护疗养病房:%d 改为双人病房\n", Room[i].id);
				Room[i].price -= 300;
				strcpy(Room[i].type, "双人病房");
				Room[i].NumOfBed = 2;
				CString str;
				str.Format(L"已将单人陪护疗养病房:%d 改为双人病房", Room[i].id);
				MessageBox(NULL, str, L"提示", MB_OK);
			}
		}
	}
}

int GetRoom(int id)
{
	for (int i = 0; i < RoomNum; i++)
		if (id == Room[i].id)
			return i;
	return RoomNum;
}

void Free(struct ZhenLiao* head1, struct Doctor* head2) 
{
	struct ZhenLiao* p, * p1;
	struct Doctor* q, * q1; 
	p1 = head1;//指向哨兵节点 
	q1 = head2; //指向哨兵节点
	while (p1 != NULL) 
	{
		p = p1;
		p1 = p1->next;
		free(p);
	}
	while (q1 != NULL) 
	{
		q = q1;
		q1 = q1->next;
		free(q);
	}
}

int CountGuaHao(struct date date1, int j, struct ZhenLiao* head)
{
	int i = 0;//记录今天第几次出现
	struct ZhenLiao* p;
	p = head->next;//跳过哨兵节点 
	while (p != NULL)
	{
		if (p->date.year == date1.year && p->date.month == date1.month && p->date.day == date1.day && p->patient.id == j)
			i++;
		p = p->next;
	}
	return i;
}

int JudgeDepartment(struct date time, int id, char* department, struct ZhenLiao* head)
{
	struct ZhenLiao* p;
	p = head->next;//跳过哨兵节点 
	while (p != NULL)
	{
		if (p->date.year == time.year && p->date.month == time.month && p->date.day == time.day && p->patient.id == id && strcmp(department, p->doctor.department) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}

int IndexForPredict(char a[], int year, int month, int day, struct ZhenLiao* head)
{
	int i = 0;
	struct ZhenLiao* p;
	p = head->next;
	while (p != NULL)
	{
		if (p->date.day == day && p->date.month == month && p->date.year == year && (!strcmp(a, p->doctor.department)))//字符串相同返回0，取反， 
			i++;
		p = p->next;
	}
	return i;
}

int Predict(int z1, int z2, int z3, int z4, int z5)
{
	double a, b, y, y1, y2, y3, y4, y5, j;
	int x, i;
	y1 = log(z1);
	y2 = log(z2);
	y3 = log(z3);
	y4 = log(z4);
	y5 = log(z5);
	x = 3;
	y = (y1 + y2 + y3 + y4 + y5) / 5;
	b = (2 * (y - y1) + (y - y2) + (y4 - y) + 2 * (y5 - y)) / 10;
	a = y - b * x;
	j = 6 * b + a;
	i = (int)(exp(j) + 0.5);
	return i;
}