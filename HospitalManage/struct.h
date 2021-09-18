#pragma once
#include<stdio.h>
#include "pch.h"

#define CheckNum 10
#define DrugNum 10
#define RoomNum 20

//һ����Ҫ�������������Ƽ�¼��ҽ���� 
struct Patient {                          //���ߣ����֣����䣬�Һż�¼��  
	char name[20];
	int age;
	int id;   //���֤����λ
};

struct Doctor {                         //ҽ����������ҽ�����������֣��ȼ������ң����ţ�����ʱ�䣬����ָ�룩 
	char name[20]; 
	char grade[20]; //����
	char department[20]; //����
	int id; //����
	int chuzhen[7];  //1���0������
	int guahaoshu;
	int state; //0������٣�1���������ϰ࣬2������ְ
	struct Doctor* next;
};

struct date {                             //���� �ṹ�壨�����գ� 
	int year, month, day;
};

struct room {                            //���䣬�ṹ������ʵ�� ������1������2��100�����۸���ס������ 
	char nurse[10];//�������ͣ���ͨ������ 
	char type[20]; //���ͣ�1-���˲�����2-˫�˲�����3-���˲�����4-�����㻤������5-�����㻤��������
	int NumOfBed;//��λ��
	int price;//�۸�100�������� 
	int number;//��ס������
	int id; //�����
};

struct money {                           //���ã�Ԫ���ǣ��֣� 
	int yuan, jiao, fen;
};

struct CheckItem {                                          //�����Ŀ����Ŀ���֣���Ŀ��������Ŀ���ξ�׼���ã� 
	char name[20];
	int count;
	struct money fee;       //һ�εķ��ã� 
};

struct Check {                                          //����������׼���ã������Ŀ�� 
	struct money CheckFee;
	struct CheckItem checks[CheckNum];      //  ��һ�����캯����ÿ����������ʱ���ֶ�����һ�ι��캯�� 
};

struct DrugItem {                                         //ҩƷ���� ��ҩƷ���ã�ҩƷ������ҩƷ��׼���ۣ� 
	char name[20];
	int count;
	struct money fee;     //һ�εķ��ã� 
};

struct Drug {                                        //��ҩ��� ����׼���ã�����ҩƷ����� 
	struct money DrugFee;
	struct DrugItem drugs[DrugNum];	 //  ��һ�����캯����ÿ����������ʱ���ֶ�����һ�ι��캯�� 
};

struct ZhuYuan {                                        //סԺ���� ����ʼ�������ڣ�100����Ѻ�𣬷�����Ϣ�� 
	struct date StartDate; //סԺ����
	struct date EndDate; //Ԥ�Ƴ�Ժ����
	int deposit; //���1000,Ҫ��100������ 
	struct room room;
};

union Record {                                             //��ѡһ���������Ƽ�¼������������ҩ�����סԺ����� 
	struct Check check;
	struct Drug drug;
	struct ZhuYuan zhuyuan;
};

struct ZhenLiao {                                              //���Ƽ�¼��������Ϣ��ҽ����Ϣ��ѡ������ָ�룬�����壩  
	int no;
	struct Patient patient;
	struct Doctor doctor;
	struct date date;
	int xuan;  //1-��飬2-��ҩ��3-סԺ
	union Record record;
	struct ZhenLiao* next;
};

struct Time {
	int year, month, day, hour, minute;
};