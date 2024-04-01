#pragma once
//车票相关文件信息类的设计[wjy]

#include <list>
#include <fstream>
#include <iostream>
#include <string>

//WARNING
	//直接执行exe文件时，配置文件应与exe文件同级
	//调试程序时与工程文件同级
	//相对路径的方式破事就是多X_X
#define _F_LOGIN "login.ini"
#define _F_STOCK "BabyBus.csv"
#define _F_DIARY "Diary.txt"

using namespace std;

class mushclock {
public:
	int hour;
	int minute;
	bool operator < (mushclock b) {
		return ((this->hour) * 60 + this->minute) < ((b.hour) * 60 + b.minute);	//出发时刻比较
	}
	//应用时 系统时间/发车时间 若为true则可以处理车票[wjy]
	bool operator / (mushclock b) {
		return (((b.hour) * 60 + b.minute) - ((this->hour) * 60 + this->minute) > 10);
	}
};

class msg {
public:
	int id;					//id
	string cid;			//公交车次
	mushclock st_time;		//发车时间
	string starter;		//起点站
	string destination;	//终点站
	double dr_time;			//车程时间
	int price;				//票价
	int people;				//额定载量
	int sold;				//已售票数
	string available;			//运行状态
	bool operator < (msg b) {
		return  this->st_time < b.st_time;	//出发时刻比较
	}
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//读取登陆信息
	void ReadLogin(CString& name, CString& pwd);

	//修改密码
	void WritePwd(char* name, char* pwd);

	// 读取车辆信息
	void ReadDocline();

	//车辆写入文件
	void WirteDocline();

	//添加新车辆
	void CInfoFile::Addline(
		CString cid, mushclock st_time,
		CString starter, CString destination,
		double dr_time, int price, int people,int sold);

	list<msg> ls;	//存储车次容器
	int num;			//用来记录车次个数
};