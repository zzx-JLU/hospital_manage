#pragma once
void CStringToChar(CString cstring, char str[]);

struct ZhenLiao* CreateZhenLiao(); //���ļ�������������Ϣ����

struct ZhenLiao* Search(struct ZhenLiao* head, int id); //��������Ϣ������Ѱ�ҹҺ�Ϊid�Ľ��

void DeleteZhenLiao(struct ZhenLiao* head, struct ZhenLiao* p); //ɾ��ָ��pָ��Ľ��

void Add(struct ZhenLiao* pHead, struct ZhenLiao* pNew); //��������Ϣ����β����ӽ��

void Save(struct ZhenLiao* head); //���棬��������Ϣд���ļ�

struct Doctor* SearchDoctor(struct Doctor* pDoctor, int id); //���ݹ��Ų���ҽ�����

void AddDoctor(struct Doctor* head, struct Doctor* pDoctor); //��ҽ�������β��ӽ��

void DeleteDoctor(struct Doctor* head, int i); //ɾ������Ϊi��ҽ��

void SaveDoctor(struct Doctor* head); //����ҽ���ļ�

struct Doctor* CreateDoctor(); //��ȡҽ���ļ�������ҽ������

//void FindDoctor(struct Doctor* head); //����ҽ�����˺���û��ʵ��ʹ��

void InitDoctor(struct Doctor* p); //ҽ������ʼ��

void LoadRoom(struct room Room[]); //��ȡ�����ļ���������������

void SaveRoom(struct room Room[]); //���没���ļ�

void LoadDepartment(char department[10][10], int NumOfDepartment[]); //���������Ϣ��������������

void SaveDepartment(char department[10][10], int NumOfDepartment[]); //���������Ϣ

void LoadCheck(struct CheckItem ALL[10]); //��ȡ�����Ŀ�ļ�

void LoadDrug(struct DrugItem all[10]); //��ȡҩƷ�ļ�

void LoadOther(struct money* turnover, int* num, struct Time* time);//��ȡӪҵ��ܹҺ���������ʱ��

void SaveOther(struct money turnover, int num, struct Time time);//����Ӫҵ��ܹҺ���������ʱ��

int LiveNow(); //���㵱ǰסԺ����

int RoomSum(); //���㴲λ��

void UpDateRoom(); //��������

int GetRoom(int id); //���ݷ���ŵõ����������е��±�

void Free(struct ZhenLiao* head1, struct Doctor* head2); //�ͷ�����

int CountGuaHao(struct date date1, int j, struct ZhenLiao* head); //����ĳλ������ĳ��ĹҺŴ���

int JudgeDepartment(struct date time, int id, char* department, struct ZhenLiao* head); //�ж�ĳλ������ĳ���Ƿ���ĳ���ҹҹ���

int IndexForPredict(char a[], int year, int month, int day, struct ZhenLiao* head); //ͳ��ĳ������ĳ��ĹҺ���

int Predict(int z1, int z2, int z3, int z4, int z5); //����ĳ����ǰ����ĹҺ���Ԥ���һ��ĹҺ���