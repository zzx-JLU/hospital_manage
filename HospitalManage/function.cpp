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
	int i;     //����ѭ�������� 
	FILE* fp;
	struct ZhenLiao* p, * q, * head;
	if ((fp = fopen("record.txt", "r")) == NULL)
	{
		//printf("��ʧ�ܣ�����ͷָ��ָ��NULL");
		MessageBox(NULL, L"��������Ϣ�ļ�ʧ��", L"��ʾ", MB_OK);
		return NULL;
	}
	head = q = (struct ZhenLiao*)malloc(sizeof(struct ZhenLiao));//�ڱ��ڵ� 
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
		fscanf(fp, "%d", &(p->no));//      ����Һ� 
		fscanf(fp, "%s %d %d", p->patient.name, &(p->patient.age), &(p->patient.id));//���뻼�ߵ����ֺ�����
		fscanf(fp, "%s %s %s %d", p->doctor.name, p->doctor.grade, p->doctor.department, &(p->doctor.id));//����ҽ�������֣��ȼ������ң����� 
		fscanf(fp, "%d %d %d", &(p->date.year), &(p->date.month), &(p->date.day));//��������������
		fscanf(fp, "%d", &(p->xuan));//����ѡ�� 
		if (p->xuan == 1)
		{
			fscanf(fp, "%d %d %d", &(p->record.check.CheckFee.yuan), &(p->record.check.CheckFee.jiao), &(p->record.check.CheckFee.fen));//����Բ�Ƿ�
			for (i = 0; i < 10; i++)
				fscanf(fp, "%s %d %d %d %d", p->record.check.checks[i].name, &(p->record.check.checks[i].count), &(p->record.check.checks[i].fee.yuan), &(p->record.check.checks[i].fee.jiao), &(p->record.check.checks[i].fee.fen));//�� �� �� �֣��� �������η��� 	   	
		}
		else if (p->xuan == 2)
		{
			fscanf(fp, "%d %d %d", &(p->record.drug.DrugFee.yuan), &(p->record.drug.DrugFee.jiao), &(p->record.drug.DrugFee.fen));//����Բ�Ƿ�
			for (i = 0; i < 10; i++)
				fscanf(fp, "%s %d %d %d %d", p->record.drug.drugs[i].name, &(p->record.drug.drugs[i].count), &(p->record.drug.drugs[i].fee.yuan), &(p->record.drug.drugs[i].fee.jiao), &(p->record.drug.drugs[i].fee.fen));//�� �� �� �֣��� �������η��� 
		}
		else if (p->xuan == 3)
		{
			fscanf(fp, "%d %d %d", &(p->record.zhuyuan.StartDate.year), &(p->record.zhuyuan.StartDate.month), &(p->record.zhuyuan.StartDate.day));
			fscanf(fp, "%d %d %d", &(p->record.zhuyuan.EndDate.year), &(p->record.zhuyuan.EndDate.month), &(p->record.zhuyuan.EndDate.day));//��ʼ��������
			fscanf(fp, "%d", &(p->record.zhuyuan.deposit));//Ѻ��
			fscanf(fp, "%d", &(p->record.zhuyuan.room.id));//�������͵��������� 
		}
		else if (p->xuan == 0) //�ѳ�Ժ
		{
			fscanf(fp, "%d %d %d", &(p->record.zhuyuan.StartDate.year), &(p->record.zhuyuan.StartDate.month), &(p->record.zhuyuan.StartDate.day));//סԺ����
			fscanf(fp, "%d %d %d", &(p->record.zhuyuan.EndDate.year), &(p->record.zhuyuan.EndDate.month), &(p->record.zhuyuan.EndDate.day));//��Ժ����
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
		//printf("�޴�������Ϣ");
		MessageBox(NULL, L"�޴�������Ϣ", L"��ʾ", MB_OK);
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
		MessageBox(NULL, L"��������Ϣ�ļ�ʧ��", L"��ʾ", MB_OK);
		return;
	}//���ļ�

	struct ZhenLiao* p = head->next;
	while (p != NULL)
	{
		fprintf(fp, "%d\n", p->no);//�����Ƽ�¼���
		fprintf(fp, "%s %d %d\n", p->patient.name, p->patient.age, p->patient.id);//�ȴ滼�ߵ�name��age
		fprintf(fp, "%s %s %s %d\n", p->doctor.name, p->doctor.grade, p->doctor.department, p->doctor.id);//ҽ������ ҽ���ȼ� ҽ������ ҽ������
		fprintf(fp, "%d %d %d\n", p->date.year, p->date.month, p->date.day);//��������������
		fprintf(fp, "%d\n", p->xuan);//��ѡ����Ŀ
		if (p->xuan == 1)//���
		{
			fprintf(fp, "%d %d %d\n", p->record.check.CheckFee.yuan, p->record.check.CheckFee.jiao, p->record.check.CheckFee.fen);//��Ǯ(�Ѿ�������Ŀ�ܷ���)
			int i;
			for (i = 0; i < 9; i++)
			{
				fprintf(fp, "%s %d %d %d %d\n", p->record.check.checks[i].name, p->record.check.checks[i].count, p->record.check.checks[i].fee.yuan, p->record.check.checks[i].fee.jiao, p->record.check.checks[i].fee.fen);//��Ŀ���� ������ ����
			}
			fprintf(fp, "%s %d %d %d %d", p->record.check.checks[9].name, p->record.check.checks[9].count, p->record.check.checks[9].fee.yuan, p->record.check.checks[9].fee.jiao, p->record.check.checks[9].fee.fen);
		}
		else if (p->xuan == 2)//��ҩ
		{
			fprintf(fp, "%d %d %d\n", p->record.drug.DrugFee.yuan, p->record.drug.DrugFee.jiao, p->record.drug.DrugFee.fen);//��Ǯ(�Ѿ�������Ŀ�ܷ���)
			int i;
			for (i = 0; i < 9; i++)
			{
				fprintf(fp, "%s %d %d %d %d\n", p->record.drug.drugs[i].name, p->record.drug.drugs[i].count, p->record.drug.drugs[i].fee.yuan, p->record.drug.drugs[i].fee.jiao, p->record.drug.drugs[i].fee.fen);//ҩƷ���� ���� ����
			}
			fprintf(fp, "%s %d %d %d %d", p->record.drug.drugs[9].name, p->record.drug.drugs[9].count, p->record.drug.drugs[9].fee.yuan, p->record.drug.drugs[9].fee.jiao, p->record.drug.drugs[9].fee.fen);
		}
		else if (p->xuan == 3)//סԺ
		{
			fprintf(fp, "%d %d %d\n", p->record.zhuyuan.StartDate.year, p->record.zhuyuan.StartDate.month, p->record.zhuyuan.StartDate.day);//סԺ����
			fprintf(fp, "%d %d %d\n", p->record.zhuyuan.EndDate.year, p->record.zhuyuan.EndDate.month, p->record.zhuyuan.EndDate.day);//Ԥ�Ƴ�Ժ����
			fprintf(fp, "%d\n", p->record.zhuyuan.deposit);//Ѻ��
			fprintf(fp, "%d", p->record.zhuyuan.room.id);//סԺ��λ��Ϣ
		}
		else if (p->xuan == 0) //�ѳ�Ժ
		{
			fprintf(fp, "%d %d %d\n", p->record.zhuyuan.StartDate.year, p->record.zhuyuan.StartDate.month, p->record.zhuyuan.StartDate.day);//סԺ����
			fprintf(fp, "%d %d %d", p->record.zhuyuan.EndDate.year, p->record.zhuyuan.EndDate.month, p->record.zhuyuan.EndDate.day);//��Ժ����
		}
		if (p->next)
			fprintf(fp, "\n");
		p = p->next;
		/*else//���һ�� ���ӻ���
		{
			if (p->xuan == 1)//���
			{
				fprintf(fp, "%d %d %d\n", p->c.a.feiyong.yuan, p->c.a.feiyong.jiao, p->c.a.feiyong.fen);//��Ǯ(�Ѿ�������Ŀ�ܷ���)
				int i;
				for (i = 0; i <= 9; i++)
				{
					fprintf(fp, "%s %d %d %d %d", p->c.a.a[i].name, p->c.a.a[i].count, p->c.a.a[i].feiyong.yuan, p->c.a.a[i].feiyong.jiao, p->c.a.a[i].feiyong.fen);//��Ŀ���� ������ ����
				}
			}
			if (p->xuan == 2)//��ҩ
			{
				fprintf(fp, "%d %d %d\n", p->c.b.feiyong.yuan, p->c.b.feiyong.jiao, p->c.b.feiyong.fen);//��Ǯ(�Ѿ�������Ŀ�ܷ���)
				int i;
				for (i = 0; i <= 9; i++)
				{
					fprintf(fp, "%s %d %d %d %d", p->c.b.a[i].name, p->c.b.a[i].count, p->c.b.a[i].feiyong.yuan, p->c.b.a[i].feiyong.jiao, p->c.b.a[i].feiyong.fen);//ҩƷ���� ���� ����
				}
			}
			if (p->xuan == 3)//סԺ
			{
				fprintf(fp, "%d %d %d\n", p->c.c.a.year, p->c.c.a.month, p->c.c.a.day);//סԺ����
				fprintf(fp, "%d %d %d\n", p->c.c.b.year, p->c.c.b.month, p->c.c.b.day);//Ԥ�Ƴ�Ժ����
				fprintf(fp, "%d\n", p->c.c.deposit);//Ѻ��
				fprintf(fp, "%d", p->c.c.c.id);//סԺ��λ��Ϣ
			}
			if (p->xuan == 0) //�ѳ�Ժ
			{
				fprintf(fp, "%d %d %d\n", p->c.c.a.year, p->c.c.a.month, p->c.c.a.day);//סԺ����
				fprintf(fp, "%d %d %d", p->c.c.b.year, p->c.c.b.month, p->c.c.b.day);//��Ժ����
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
		//printf("�޴�������Ϣ");
		MessageBox(NULL, L"�޴�ҽ����Ϣ", L"��ʾ", MB_OK);
		return;
	}
	p->next = q->next;
	free(q);
	//printf("ɾ���ɹ�");
	MessageBox(NULL, L"ɾ���ɹ�", L"��ʾ", MB_OK);
}

void SaveDoctor(struct Doctor* head)
{
	int i;     //����ѭ�������� 
	FILE* fp;
	if ((fp = fopen("doctor.txt", "w")) == NULL)
	{
		//printf("��ʧ��");
		MessageBox(NULL, L"��ҽ���ļ�ʧ��", L"��ʾ", MB_OK);
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
	int i;     //����ѭ�������� 
	FILE* fp;
	struct Doctor* p, * q, * head;
	if ((fp = fopen("doctor.txt", "r")) == NULL)
	{
		//printf("��ʧ�ܣ�����ͷָ��ָ��NULL");
		MessageBox(NULL, L"��ҽ���ļ�ʧ��", L"��ʾ", MB_OK);
		return NULL;
	}
	head = q = (struct Doctor*)malloc(sizeof(struct Doctor));//�ڱ��ڵ� 
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
		fscanf(fp, "%s %s %s %d %d %d\n", p->name, p->grade, p->department, &(p->state), &(p->id), &(p->guahaoshu));//���ֵȼ����ҹ��� 
		for (i = 0; i < 7; i++)
			fscanf(fp, "%d ", &(p->chuzhen[i]));//1Ϊ���0����
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
			//����
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
		//printf("�����ļ���ʧ�ܣ�\n");
		MessageBox(NULL, L"�����ļ���ʧ��", L"��ʾ", MB_OK);
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
		//printf("�����ļ���ʧ�ܣ������棩\n");
		MessageBox(NULL, L"�����ļ���ʧ��", L"��ʾ", MB_OK);
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
		//printf("�����ļ���ʧ�ܣ������棩\n");
		MessageBox(NULL, L"�����ļ���ʧ��", L"��ʾ", MB_OK);
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
		//printf("�����ļ���ʧ�ܣ������棩\n");
		MessageBox(NULL, L"�����ļ���ʧ��", L"��ʾ", MB_OK);
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
		MessageBox(NULL, L"�����Ŀ�ļ���ʧ��", L"��ʾ", MB_OK);
		return;
	}
	for (i = 0; i < 10; i++)
	{
		fscanf(fp, "%s %d", ALL[i].name, &(ALL[i].count));   //������ֱ��count�Դ�0�ˣ������ٳ�ʼ���� 
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
		MessageBox(NULL, L"ҩƷ�ļ���ʧ��", L"��ʾ", MB_OK);
		return;
	}
	for (i = 0; i < 10; i++)
	{
		fscanf(fp, "%s %d", all[i].name, &(all[i].count));   //������ֱ��count�Դ�0�ˣ������ٳ�ʼ���� 
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
		MessageBox(NULL, L"������Ϣ�ļ���ʧ��", L"��ʾ", MB_OK);
		return;
	}
	fscanf(fp, "%d%d%d", &(turnover->yuan), &(turnover->jiao), &(turnover->fen));//�ļ���������Ӫҵ���Բ�Ƿ�
	fscanf(fp, "%d", num);//Ȼ�����ܹҺ���
	fscanf(fp, "%d%d%d%d%d", &(time->year), &(time->month), &(time->day), &(time->hour), &(time->minute)); //�ϴι�ϵͳ�����ʱ��
	fclose(fp);
}

void SaveOther(struct money turnover, int num, struct Time time)
{
	FILE* fp;
	fp = fopen("TNT.txt", "w");
	if (fp == NULL)
	{
		MessageBox(NULL, L"������Ϣ�ļ���ʧ��", L"��ʾ", MB_OK);
		return;
	}
	fprintf(fp, "%d %d %d\n", turnover.yuan, turnover.jiao, turnover.fen);//�ļ���������Ӫҵ���Բ�Ƿ�
	fprintf(fp, "%d\n", num);//Ȼ�����ܹҺ���
	fprintf(fp, "%d %d %d %d %d\n", time.year, time.month, time.day, time.hour, time.minute); //�ϴι�ϵͳ�����ʱ�� 
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
		/*if (strcmp(Room[i].type, "���˲���") == 0)
			all += 1;
		if (strcmp(Room[i].type, "˫�˲���") == 0)
			all += 2;
		if (strcmp(Room[i].type, "���˲���") == 0)
			all += 3;
		if (strcmp(Room[i].type, "�����㻤����") == 0)
			all += 1;
		if (strcmp(Room[i].type, "�����㻤��������") == 0)
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
		while (i < RoomNum && (LiveNow() / ((1.0) * RoomSum())) < 0.8)//���з��䲢��ʣ�ലλ���ڰٷ�֮20
		{
			if (strcmp(Room[i].type, "˫�˲���") == 0)
			{
				if (Room[i].number < 2)
				{
					strcpy(Room[i].type, "���˲���");
					Room[i].price += 100;
					Room[i].NumOfBed = 1;
					//printf("�ѽ�˫�˲���:%d ��Ϊ���˲���\n", Room[i].id);
					CString str;
					str.Format(L"�ѽ�˫�˲���: %d ��Ϊ���˲���", Room[i].id);
					MessageBox(NULL, str, L"��ʾ", MB_OK);
				}
			}
			if (strcmp(Room[i].type, "���˲���") == 0)
			{
				if (Room[i].number < 2)
				{
					strcpy(Room[i].type, "˫�˲���");
					Room[i].price += 100;
					Room[i].NumOfBed = 2;
					//printf("�ѽ����˲���:%d ��Ϊ˫�˲���\n", Room[i].id);
					CString str;
					str.Format(L"�ѽ����˲���:%d ��Ϊ˫�˲���", Room[i].id);
					MessageBox(NULL, str, L"��ʾ", MB_OK);
				}
			}
			i++;
		}
	}
	else if (left >= 0.8)//��λ��������
	{
		int i;
		for (i = 0; i <= 9; i++)
		{
			if (strcmp(Room[i].type, "�����㻤��������") == 0)
			{
				//printf("�ѽ������㻤��������:%d ��Ϊ˫�˲���\n", Room[i].id);
				Room[i].price -= 300;
				strcpy(Room[i].type, "˫�˲���");
				Room[i].NumOfBed = 2;
				CString str;
				str.Format(L"�ѽ������㻤��������:%d ��Ϊ˫�˲���", Room[i].id);
				MessageBox(NULL, str, L"��ʾ", MB_OK);
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
	p1 = head1;//ָ���ڱ��ڵ� 
	q1 = head2; //ָ���ڱ��ڵ�
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
	int i = 0;//��¼����ڼ��γ���
	struct ZhenLiao* p;
	p = head->next;//�����ڱ��ڵ� 
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
	p = head->next;//�����ڱ��ڵ� 
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
		if (p->date.day == day && p->date.month == month && p->date.year == year && (!strcmp(a, p->doctor.department)))//�ַ�����ͬ����0��ȡ���� 
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