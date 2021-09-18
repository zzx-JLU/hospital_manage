#pragma once
#include<stdio.h>
#include "pch.h"

#define CheckNum 10
#define DrugNum 10
#define RoomNum 20

//一共需要开两个链表（诊疗记录，医生） 
struct Patient {                          //患者（名字，年龄，挂号记录）  
	char name[20];
	int age;
	int id;   //身份证后六位
};

struct Doctor {                         //医生，链表构造医生名单（名字，等级，科室，工号，出诊时间，链表指针） 
	char name[20]; 
	char grade[20]; //级别
	char department[20]; //科室
	int id; //工号
	int chuzhen[7];  //1出诊，0不出诊
	int guahaoshu;
	int state; //0代表请假，1代表正常上班，2代表离职
	struct Doctor* next;
};

struct date {                             //日期 结构体（年月日） 
	int year, month, day;
};

struct room {                            //房间，结构体数组实现 （类型1，类型2，100倍数价格，已住人数） 
	char nurse[10];//护理类型：普通或特殊 
	char type[20]; //类型：1-单人病房，2-双人病房，3-三人病房，4-单人陪护病房，5-单人陪护疗养病房
	int NumOfBed;//床位数
	int price;//价格，100的整数倍 
	int number;//已住人数；
	int id; //房间号
};

struct money {                           //费用（元：角：分） 
	int yuan, jiao, fen;
};

struct CheckItem {                                          //检查项目（项目名字，项目次数，项目单次精准费用） 
	char name[20];
	int count;
	struct money fee;       //一次的费用； 
};

struct Check {                                          //检查情况（精准费用，检查项目） 
	struct money CheckFee;
	struct CheckItem checks[CheckNum];      //  整一个构造函数，每次申请对象的时候手动调用一次构造函数 
};

struct DrugItem {                                         //药品数据 （药品费用，药品数量，药品精准单价） 
	char name[20];
	int count;
	struct money fee;     //一次的费用； 
};

struct Drug {                                        //开药情况 （精准费用，所开药品情况） 
	struct money DrugFee;
	struct DrugItem drugs[DrugNum];	 //  整一个构造函数，每次申请对象的时候手动调用一次构造函数 
};

struct ZhuYuan {                                        //住院数据 （开始结束日期，100倍数押金，房间信息） 
	struct date StartDate; //住院日期
	struct date EndDate; //预计出院日期
	int deposit; //最低1000,要求100整数倍 
	struct room room;
};

union Record {                                             //三选一共用体诊疗记录（检查情况，开药情况，住院情况） 
	struct Check check;
	struct Drug drug;
	struct ZhuYuan zhuyuan;
};

struct ZhenLiao {                                              //诊疗记录（患者信息，医生信息，选择，链表指针，共用体）  
	int no;
	struct Patient patient;
	struct Doctor doctor;
	struct date date;
	int xuan;  //1-检查，2-开药，3-住院
	union Record record;
	struct ZhenLiao* next;
};

struct Time {
	int year, month, day, hour, minute;
};