//车票相关文件信息类的算法设计
#include "pch.h"
#include "stdafx.h"
#include "InfoFile.h"
#include "GetSysTimeMush.h"

CInfoFile::CInfoFile()
{
}

CInfoFile::~CInfoFile()
{
}

//读取登陆信息[wjy]
void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_LOGIN); //打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //读取一行内容
	name = CString(buf);			 //char *转换为CString

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close(); //关闭文件
}

//修改密码[wjy]
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;	 //创建文件输出对象
	ofs.open(_F_LOGIN); //打开文件

	ofs << name << endl; //name写入文件
	ofs << pwd << endl;	//pwd写入文件

	ofs.close();	//关闭文件
}

//读取车辆信息[wjy]
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //输入方式打开文件

	char buf[1024] = { 0 };
	num = 0;	//初始化车辆数目为0
	ls.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行
		num++;	//车辆数目加一

		//AfxMessageBox(CString(buf));
		char* sst = strtok(buf, ":,");

		if (sst != NULL)
		{
			tmp.id = atoi(sst); //id
		}
		else
		{
			break;
		}
		//atoi:将字符串转换成整形	atof:将字符串转换成double

		sst = strtok(NULL, ":,");
		tmp.cid = sst;					//车次

		sst = strtok(NULL, ":,");
		tmp.st_time.hour = atoi(sst);
		sst = strtok(NULL, ":,");
		tmp.st_time.minute = atoi(sst);	//发车时间

		sst = strtok(NULL, ":,");
		tmp.starter = sst;				//起点站

		sst = strtok(NULL, ":,");
		tmp.destination = sst;			//终点站

		sst = strtok(NULL, ":,");
		tmp.dr_time = atof(sst);		//车程

		sst = strtok(NULL, ":,");
		tmp.price = atoi(sst);			//票价

		sst = strtok(NULL, ":,");
		tmp.people = atoi(sst);			//额定载量

		sst = strtok(NULL, ":,");
		tmp.sold = atoi(sst);			//已售票数

		mushclock temp = GetSysTimeMush();
		if (temp < tmp.st_time) tmp.available = "运行中";
		else tmp.available = "停止运行";

		ls.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//车辆写入文件
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//输出方式打开文件

	if (ls.size() > 0)	//车辆链表有内容才执行
	{
		ofs << "车辆ID,宝宝巴士,发车时间,起点站,终点站,车程(h),RMB票价,额定载量,已售票数" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“,”分隔，结尾加换行

		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << ",";
			ofs << it->cid << ",";		
			ofs << it->st_time.hour << ":";
			ofs << it->st_time.minute << ",";
			ofs << it->starter << ",";
			ofs << it->destination << ",";
			ofs << it->dr_time << ",";
			ofs << it->price << ",";
			ofs << it->people << ",";
			ofs << it->sold << endl;
		}
	}

	ofs.close();//关闭文件
}

//添加新车次
//id:公交车次
//st_time:发车时间
//starter:起点站,destination:终点站
//dr_time:车程时间
//price:票价,people:额定载量,sold:已售票数
void CInfoFile::Addline(
	CString cid, mushclock st_time, 
	CString starter, CString destination, 
	double dr_time, int price, int people,int sold)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//车次号等均有效
		if (!cid.IsEmpty() && price > 0)
		{
			tmp.id = ls.size() + 1;	//id自动加1
			CStringA str;
			str = cid;	//CString转CStirngA
			tmp.cid = str.GetBuffer(); //CStirngA转char *，公交车次
			tmp.st_time.hour = st_time.hour;			//发车时间
			tmp.st_time.minute = st_time.minute;		//发车时间
			str = starter;	//CString转CStirngA
			tmp.starter = str.GetBuffer(); //CStirngA转char *，起点站
			str = destination;	//CString转CStirngA
			tmp.destination = str.GetBuffer(); //CStirngA转char *，终点站
			tmp.dr_time = dr_time;
			tmp.price = price;
			tmp.people = people;
			tmp.sold = sold;

			ls.push_back(tmp);	//放在链表的后面
		}
	}
}
