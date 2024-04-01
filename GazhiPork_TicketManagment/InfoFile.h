#pragma once
//��Ʊ����ļ���Ϣ������[wjy]

#include <list>
#include <fstream>
#include <iostream>
#include <string>

//WARNING
	//ֱ��ִ��exe�ļ�ʱ�������ļ�Ӧ��exe�ļ�ͬ��
	//���Գ���ʱ�빤���ļ�ͬ��
	//���·���ķ�ʽ���¾��Ƕ�X_X
#define _F_LOGIN "login.ini"
#define _F_STOCK "BabyBus.csv"
#define _F_DIARY "Diary.txt"

using namespace std;

class mushclock {
public:
	int hour;
	int minute;
	bool operator < (mushclock b) {
		return ((this->hour) * 60 + this->minute) < ((b.hour) * 60 + b.minute);	//����ʱ�̱Ƚ�
	}
	//Ӧ��ʱ ϵͳʱ��/����ʱ�� ��Ϊtrue����Դ���Ʊ[wjy]
	bool operator / (mushclock b) {
		return (((b.hour) * 60 + b.minute) - ((this->hour) * 60 + this->minute) > 10);
	}
};

class msg {
public:
	int id;					//id
	string cid;			//��������
	mushclock st_time;		//����ʱ��
	string starter;		//���վ
	string destination;	//�յ�վ
	double dr_time;			//����ʱ��
	int price;				//Ʊ��
	int people;				//�����
	int sold;				//����Ʊ��
	string available;			//����״̬
	bool operator < (msg b) {
		return  this->st_time < b.st_time;	//����ʱ�̱Ƚ�
	}
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//��ȡ��½��Ϣ
	void ReadLogin(CString& name, CString& pwd);

	//�޸�����
	void WritePwd(char* name, char* pwd);

	// ��ȡ������Ϣ
	void ReadDocline();

	//����д���ļ�
	void WirteDocline();

	//����³���
	void CInfoFile::Addline(
		CString cid, mushclock st_time,
		CString starter, CString destination,
		double dr_time, int price, int people,int sold);

	list<msg> ls;	//�洢��������
	int num;			//������¼���θ���
};