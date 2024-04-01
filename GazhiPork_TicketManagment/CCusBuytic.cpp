// CCusBuytic.cpp: 实现文件

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CCusBuytic.h"
#include "InfoFile.h"
#include "Diary.h"
#include "GetSysTimeMush.h"

// CCusBuytic

IMPLEMENT_DYNCREATE(CCusBuytic, CFormView)

CCusBuytic::CCusBuytic()
	: CFormView(DIALOG_CUS_BUYTIC)
	, m_cusbuy_runstatic(_T(""))
	, m_cusbuy_cid(_T(""))
	, m_cusbuy_hour(0)
	, m_cusbuy_minute(0)
	, m_cusbuy_starter(_T(""))
	, m_cusbuy_desti(_T(""))
	, m_cusbuy_drtime(0)
	, m_cusbuy_price(0)
	, m_cusbuy_people(0)
	, m_cusbuy_sold(0)
	, m_cusbuy_buystatus(_T(""))
	, m_cusbuy_buynum(0)
{

}

CCusBuytic::~CCusBuytic()
{
}

void CCusBuytic::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_cusbuy_search);
	DDX_Text(pDX, IDC_EDIT20, m_cusbuy_runstatic);
	DDX_Text(pDX, IDC_EDIT1, m_cusbuy_cid);
	DDX_Text(pDX, IDC_EDIT4, m_cusbuy_hour);
	DDX_Text(pDX, IDC_EDIT9, m_cusbuy_minute);
	DDX_Text(pDX, IDC_EDIT2, m_cusbuy_starter);
	DDX_Text(pDX, IDC_EDIT3, m_cusbuy_desti);
	DDX_Text(pDX, IDC_EDIT5, m_cusbuy_drtime);
	DDX_Text(pDX, IDC_EDIT6, m_cusbuy_price);
	DDX_Text(pDX, IDC_EDIT7, m_cusbuy_people);
	DDX_Text(pDX, IDC_EDIT8, m_cusbuy_sold);
	DDX_Text(pDX, IDC_EDIT18, m_cusbuy_buystatus);
	DDX_Text(pDX, IDC_EDIT19, m_cusbuy_buynum);
}

BEGIN_MESSAGE_MAP(CCusBuytic, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CCusBuytic::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &CCusBuytic::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCusBuytic 诊断

#ifdef _DEBUG
void CCusBuytic::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCusBuytic::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCusBuytic 消息处理程序


//void CCusBuytic::OnInitialUpdate()
//{
//	CFormView::OnInitialUpdate();
//
	// TODO: 在此添加专用代码和/或调用基类
//	MessageBox(TEXT("若查询车次位于首位请选择车号刷新列表\n原谅给您带来的不便\n\t\t\t---咖波屋车站"));
//}


void CCusBuytic::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	//获取当前选中项
	int index = m_cusbuy_search.GetCurSel();
	//获取当前内容
	m_cusbuy_search.GetLBText(index, text);

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	mushclock now = GetSysTimeMush();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->cid.c_str())
		{
			m_cusbuy_cid = it->cid.c_str();
			m_cusbuy_starter = it->starter.c_str();
			m_cusbuy_desti = it->destination.c_str();
			m_cusbuy_hour = it->st_time.hour;
			m_cusbuy_minute = it->st_time.minute;
			m_cusbuy_drtime = it->dr_time;
			m_cusbuy_price = it->price;
			m_cusbuy_people = it->people;
			m_cusbuy_sold = it->sold;
			m_cusbuy_runstatic = it->available.c_str();
			//购买状态检测
			if (now / it->st_time) m_cusbuy_buystatus = TEXT("可以购票");
			else m_cusbuy_buystatus = TEXT("无法购票");
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}
}


void CCusBuytic::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.ReadDocline(); //读取车信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_cusbuy_search.AddString((CString)it->cid.c_str());
	}

	//将第一个车设为默认选中项
	m_cusbuy_search.SetCurSel(0);
	MessageBox(TEXT("若查询车次位于首位请选择车号刷新列表\n原谅给您带来的不便\n\t\t\t---咖波屋车站"));
}


void CCusBuytic::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	mushclock now = GetSysTimeMush();
	mushclock st = { m_cusbuy_hour,m_cusbuy_minute };
	if (!(now / st)) {
		MessageBox(TEXT("此时间段无法购票！需提前10min"));
		return;
	}
	UpdateData(TRUE);
	if (m_cusbuy_buynum > (m_cusbuy_people - m_cusbuy_sold)) {
		MessageBox(TEXT("购买票数过多！剩余票数不够"));
		return;
	}

	//以下程序购票并写入数据更改车票数
	CString type;
	//获取当前选中项
	int index = m_cusbuy_search.GetCurSel();
	//获取组合框当前内容
	m_cusbuy_search.GetLBText(index, type);

	CString str;
	str.Format(_T("购买车票：%s 成功\n资源已更新"), type);
	MessageBox(str);

	//以下内容书写文档日志
	string cusbuy_cid = CT2A(m_cusbuy_cid.GetString());
	string cusbuy_starter = CT2A(m_cusbuy_starter.GetString());
	string cusbuy_desti = CT2A(m_cusbuy_desti.GetString());
	DiaBuy(cusbuy_cid, st, cusbuy_starter, cusbuy_desti,
		m_cusbuy_drtime, m_cusbuy_price, m_cusbuy_people,
		m_cusbuy_sold, m_cusbuy_buynum);

	//需要包含#include "InfoFile.h"删除指定元素[wjy]
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end();) {
		if (type == it->cid.c_str()) {
			it->sold = it->sold + m_cusbuy_buynum;
			break;
		}
		else it++;
	}

	file.WirteDocline(); //更新文件内容

	m_cusbuy_search.SetCurSel(0); //选择第0项目
	m_cusbuy_cid.Empty(); m_cusbuy_starter.Empty(); m_cusbuy_desti.Empty();
	m_cusbuy_runstatic.Empty(); m_cusbuy_buystatus.Empty();
	m_cusbuy_hour = 0; m_cusbuy_minute = 0; m_cusbuy_drtime = 0;
	m_cusbuy_price = 0; m_cusbuy_people = 0; m_cusbuy_sold = 0;
	m_cusbuy_buynum = 0;
	UpdateData(FALSE); //更新到对应的控件
}
