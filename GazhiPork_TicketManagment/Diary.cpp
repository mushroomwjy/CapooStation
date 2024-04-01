#include "pch.h"
#include "InfoFile.h"
#include "GetSysTimeMush.h"
#include <fstream>
void DiaBuy(
	string cid, mushclock st_time,
	string starter, string destination,
	double dr_time, int price,
	int people, int sold,
	int buynum)
{
	ofstream ofile;
	ofile.open(_F_DIARY,ios::app);
	mushclock now = GetSysTimeMush();
	ofile << "------------------------------" << endl;
	ofile << "宝宝巴士:" << cid << "\t";
	ofile << "发车时间:" << st_time.hour << " : " << st_time.minute << endl;
	ofile << "起点站:" << starter << "\t";
	ofile << "终点站:" << destination << endl;
	ofile << "车程时间:" << dr_time << "时" << "\t";
	ofile << "票价:" << price << endl;
	ofile << "额定载量:" << people << "\t";
	ofile << "已售票数:" << sold << endl;
	ofile << "------------------------------" << endl;
	ofile << "购票时间:" << "\t";
	ofile << now.hour << " : " << now.minute << endl;
	ofile << "购票数量:" << "\t";
	ofile << buynum << endl;
	ofile << "------------------------------" << endl << endl;
	ofile.close();
}
void DelBuy(
	string cid, mushclock st_time,
	string starter, string destination,
	double dr_time, int price,
	int people, int sold,
	int delnum)
{
	ofstream ofile;
	ofile.open(_F_DIARY,ios::app);
	mushclock now = GetSysTimeMush();
	ofile << "------------------------------" << endl;
	ofile << "宝宝巴士:" << cid << "\t";
	ofile << "发车时间:" << st_time.hour << " : " << st_time.minute << endl;
	ofile << "起点站:" << starter << "\t";
	ofile << "终点站:" << destination << endl;
	ofile << "车程时间:" << dr_time << "时" << "\t";
	ofile << "票价:" << price << endl;
	ofile << "额定载量:" << people << "\t";
	ofile << "已售票数:" << sold << endl;
	ofile << "------------------------------" << endl;
	ofile << "退票时间:" << "\t";
	ofile << now.hour << " : " << now.minute << endl;
	ofile << "退票数量:" << "\t";
	ofile << delnum << endl;
	ofile << "退票金额:" << "\t";
	ofile << price * 0.2 * delnum << endl;
	ofile << "------------------------------" << endl << endl;
	ofile.close();
}