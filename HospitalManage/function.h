#pragma once
void CStringToChar(CString cstring, char str[]);

struct ZhenLiao* CreateZhenLiao(); //读文件，建立诊疗信息链表

struct ZhenLiao* Search(struct ZhenLiao* head, int id); //在诊疗信息链表中寻找挂号为id的结点

void DeleteZhenLiao(struct ZhenLiao* head, struct ZhenLiao* p); //删除指针p指向的结点

void Add(struct ZhenLiao* pHead, struct ZhenLiao* pNew); //向诊疗信息链表尾部添加结点

void Save(struct ZhenLiao* head); //保存，将诊疗信息写入文件

struct Doctor* SearchDoctor(struct Doctor* pDoctor, int id); //根据工号查找医生结点

void AddDoctor(struct Doctor* head, struct Doctor* pDoctor); //向医生链表结尾添加结点

void DeleteDoctor(struct Doctor* head, int i); //删除工号为i的医生

void SaveDoctor(struct Doctor* head); //保存医生文件

struct Doctor* CreateDoctor(); //读取医生文件，建立医生链表

//void FindDoctor(struct Doctor* head); //查找医生。此函数没有实际使用

void InitDoctor(struct Doctor* p); //医生结点初始化

void LoadRoom(struct room Room[]); //读取病房文件，建立病房数组

void SaveRoom(struct room Room[]); //保存病房文件

void LoadDepartment(char department[10][10], int NumOfDepartment[]); //读入科室信息，建立科室数组

void SaveDepartment(char department[10][10], int NumOfDepartment[]); //保存科室信息

void LoadCheck(struct CheckItem ALL[10]); //读取检查项目文件

void LoadDrug(struct DrugItem all[10]); //读取药品文件

void LoadOther(struct money* turnover, int* num, struct Time* time);//读取营业额、总挂号数、保存时间

void SaveOther(struct money turnover, int num, struct Time time);//保存营业额、总挂号数、保存时间

int LiveNow(); //计算当前住院人数

int RoomSum(); //计算床位数

void UpDateRoom(); //调整病房

int GetRoom(int id); //根据房间号得到房间数组中的下标

void Free(struct ZhenLiao* head1, struct Doctor* head2); //释放链表

int CountGuaHao(struct date date1, int j, struct ZhenLiao* head); //计算某位患者在某天的挂号次数

int JudgeDepartment(struct date time, int id, char* department, struct ZhenLiao* head); //判断某位患者在某天是否在某科室挂过号

int IndexForPredict(char a[], int year, int month, int day, struct ZhenLiao* head); //统计某科室在某天的挂号数

int Predict(int z1, int z2, int z3, int z4, int z5); //根据某科室前五天的挂号数预测后一天的挂号数