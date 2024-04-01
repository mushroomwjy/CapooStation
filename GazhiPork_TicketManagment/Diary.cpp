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
	ofile << "������ʿ:" << cid << "\t";
	ofile << "����ʱ��:" << st_time.hour << " : " << st_time.minute << endl;
	ofile << "���վ:" << starter << "\t";
	ofile << "�յ�վ:" << destination << endl;
	ofile << "����ʱ��:" << dr_time << "ʱ" << "\t";
	ofile << "Ʊ��:" << price << endl;
	ofile << "�����:" << people << "\t";
	ofile << "����Ʊ��:" << sold << endl;
	ofile << "------------------------------" << endl;
	ofile << "��Ʊʱ��:" << "\t";
	ofile << now.hour << " : " << now.minute << endl;
	ofile << "��Ʊ����:" << "\t";
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
	ofile << "������ʿ:" << cid << "\t";
	ofile << "����ʱ��:" << st_time.hour << " : " << st_time.minute << endl;
	ofile << "���վ:" << starter << "\t";
	ofile << "�յ�վ:" << destination << endl;
	ofile << "����ʱ��:" << dr_time << "ʱ" << "\t";
	ofile << "Ʊ��:" << price << endl;
	ofile << "�����:" << people << "\t";
	ofile << "����Ʊ��:" << sold << endl;
	ofile << "------------------------------" << endl;
	ofile << "��Ʊʱ��:" << "\t";
	ofile << now.hour << " : " << now.minute << endl;
	ofile << "��Ʊ����:" << "\t";
	ofile << delnum << endl;
	ofile << "��Ʊ���:" << "\t";
	ofile << price * 0.2 * delnum << endl;
	ofile << "------------------------------" << endl << endl;
	ofile.close();
}