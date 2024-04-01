//��Ʊ����ļ���Ϣ����㷨���
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

//��ȡ��½��Ϣ[wjy]
void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs; //�����ļ��������
	ifs.open(_F_LOGIN); //���ļ�

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //��ȡһ������
	name = CString(buf);			 //char *ת��ΪCString

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close(); //�ر��ļ�
}

//�޸�����[wjy]
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;	 //�����ļ��������
	ofs.open(_F_LOGIN); //���ļ�

	ofs << name << endl; //nameд���ļ�
	ofs << pwd << endl;	//pwdд���ļ�

	ofs.close();	//�ر��ļ�
}

//��ȡ������Ϣ[wjy]
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	num = 0;	//��ʼ��������ĿΪ0
	ls.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //û���ļ���β
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��
		num++;	//������Ŀ��һ

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
		//atoi:���ַ���ת��������	atof:���ַ���ת����double

		sst = strtok(NULL, ":,");
		tmp.cid = sst;					//����

		sst = strtok(NULL, ":,");
		tmp.st_time.hour = atoi(sst);
		sst = strtok(NULL, ":,");
		tmp.st_time.minute = atoi(sst);	//����ʱ��

		sst = strtok(NULL, ":,");
		tmp.starter = sst;				//���վ

		sst = strtok(NULL, ":,");
		tmp.destination = sst;			//�յ�վ

		sst = strtok(NULL, ":,");
		tmp.dr_time = atof(sst);		//����

		sst = strtok(NULL, ":,");
		tmp.price = atoi(sst);			//Ʊ��

		sst = strtok(NULL, ":,");
		tmp.people = atoi(sst);			//�����

		sst = strtok(NULL, ":,");
		tmp.sold = atoi(sst);			//����Ʊ��

		mushclock temp = GetSysTimeMush();
		if (temp < tmp.st_time) tmp.available = "������";
		else tmp.available = "ֹͣ����";

		ls.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//����д���ļ�
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//�����ʽ���ļ�

	if (ls.size() > 0)	//�������������ݲ�ִ��
	{
		ofs << "����ID,������ʿ,����ʱ��,���վ,�յ�վ,����(h),RMBƱ��,�����,����Ʊ��" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�,���ָ�����β�ӻ���

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

	ofs.close();//�ر��ļ�
}

//����³���
//id:��������
//st_time:����ʱ��
//starter:���վ,destination:�յ�վ
//dr_time:����ʱ��
//price:Ʊ��,people:�����,sold:����Ʊ��
void CInfoFile::Addline(
	CString cid, mushclock st_time, 
	CString starter, CString destination, 
	double dr_time, int price, int people,int sold)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//���κŵȾ���Ч
		if (!cid.IsEmpty() && price > 0)
		{
			tmp.id = ls.size() + 1;	//id�Զ���1
			CStringA str;
			str = cid;	//CStringתCStirngA
			tmp.cid = str.GetBuffer(); //CStirngAתchar *����������
			tmp.st_time.hour = st_time.hour;			//����ʱ��
			tmp.st_time.minute = st_time.minute;		//����ʱ��
			str = starter;	//CStringתCStirngA
			tmp.starter = str.GetBuffer(); //CStirngAתchar *�����վ
			str = destination;	//CStringתCStirngA
			tmp.destination = str.GetBuffer(); //CStirngAתchar *���յ�վ
			tmp.dr_time = dr_time;
			tmp.price = price;
			tmp.people = people;
			tmp.sold = sold;

			ls.push_back(tmp);	//��������ĺ���
		}
	}
}
