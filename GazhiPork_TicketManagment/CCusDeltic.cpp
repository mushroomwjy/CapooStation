// CCusDeltic.cpp: 实现文件
//

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CCusDeltic.h"
#include "InfoFile.h"
#include "Diary.h"
#include "GetSysTimeMush.h"

// CCusDeltic

IMPLEMENT_DYNCREATE(CCusDeltic, CFormView)

CCusDeltic::CCusDeltic()
	: CFormView(DIALOG_CUS_DELTIC)
	, m_cusdel_runstatic(_T(""))
	, m_cusdel_cid(_T(""))
	, m_cusdel_hour(0)
	, m_cusdel_minute(0)
	, m_cusdel_starter(_T(""))
	, m_cusdel_desti(_T(""))
	, m_cusdel_drtime(0)
	, m_cusdel_price(0)
	, m_cusdel_people(0)
	, m_cusdel_sold(0)
	, m_cusdel_delstatus(_T(""))
	, m_cusdel_delnum(0)
{

}

CCusDeltic::~CCusDeltic()
{
}

void CCusDeltic::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_cusdel_search);
	DDX_Text(pDX, IDC_EDIT20, m_cusdel_runstatic);
	DDX_Text(pDX, IDC_EDIT1, m_cusdel_cid);
	DDX_Text(pDX, IDC_EDIT4, m_cusdel_hour);
	DDX_Text(pDX, IDC_EDIT9, m_cusdel_minute);
	DDX_Text(pDX, IDC_EDIT2, m_cusdel_starter);
	DDX_Text(pDX, IDC_EDIT3, m_cusdel_desti);
	DDX_Text(pDX, IDC_EDIT5, m_cusdel_drtime);
	DDX_Text(pDX, IDC_EDIT6, m_cusdel_price);
	DDX_Text(pDX, IDC_EDIT7, m_cusdel_people);
	DDX_Text(pDX, IDC_EDIT8, m_cusdel_sold);
	DDX_Text(pDX, IDC_EDIT18, m_cusdel_delstatus);
	DDX_Text(pDX, IDC_EDIT19, m_cusdel_delnum);
}

BEGIN_MESSAGE_MAP(CCusDeltic, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CCusDeltic::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &CCusDeltic::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCusDeltic 诊断

#ifdef _DEBUG
void CCusDeltic::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCusDeltic::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCusDeltic 消息处理程序


void CCusDeltic::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.ReadDocline(); //读取车信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_cusdel_search.AddString((CString)it->cid.c_str());
	}

	//将第一个车设为默认选中项
	m_cusdel_search.SetCurSel(0);
	MessageBox(TEXT("若查询车次位于首位请选择车号刷新列表\n原谅给您带来的不便\n\t\t\t---咖波屋车站"));
}


void CCusDeltic::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	//获取当前选中项
	int index = m_cusdel_search.GetCurSel();
	//获取当前内容
	m_cusdel_search.GetLBText(index, text);

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	mushclock now = GetSysTimeMush();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->cid.c_str())
		{
			m_cusdel_cid = it->cid.c_str();
			m_cusdel_starter = it->starter.c_str();
			m_cusdel_desti = it->destination.c_str();
			m_cusdel_hour = it->st_time.hour;
			m_cusdel_minute = it->st_time.minute;
			m_cusdel_drtime = it->dr_time;
			m_cusdel_price = it->price;
			m_cusdel_people = it->people;
			m_cusdel_sold = it->sold;
			m_cusdel_runstatic = it->available.c_str();
			//购买状态检测
			if (now / it->st_time) m_cusdel_delstatus = TEXT("可以退票");
			else m_cusdel_delstatus = TEXT("无法退票");
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}
}


void CCusDeltic::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	mushclock now = GetSysTimeMush();
	mushclock st = { m_cusdel_hour,m_cusdel_minute };
	if (!(now / st)) {
		MessageBox(TEXT("此时间段无法退票！需提前10min"));
		return;
	}
	UpdateData(TRUE);
	if (m_cusdel_delnum > m_cusdel_sold) {
		MessageBox(TEXT("您没有这么多票？小伙子不讲武德"));
		return;
	}

	//以下程序购票并写入数据更改车票数
	CString type;
	//获取当前选中项
	int index = m_cusdel_search.GetCurSel();
	//获取组合框当前内容
	m_cusdel_search.GetLBText(index, type);

	CString str;
	str.Format(_T("退订车票：%s 成功\n资源已更新"), type);
	MessageBox(str);

	//以下内容书写文档日志
	string cusdel_cid = CT2A(m_cusdel_cid.GetString());
	string cusdel_starter = CT2A(m_cusdel_starter.GetString());
	string cusdel_desti = CT2A(m_cusdel_desti.GetString());
	DelBuy(cusdel_cid, st, cusdel_starter, cusdel_desti,
		m_cusdel_drtime, m_cusdel_price, m_cusdel_people,
		m_cusdel_sold, m_cusdel_delnum);

	//需要包含#include "InfoFile.h"删除指定元素[wjy]
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end();) {
		if (type == it->cid.c_str()) {
			it->sold = it->sold - m_cusdel_delnum;
			break;
		}
		else it++;
	}

	file.WirteDocline(); //更新文件内容

	m_cusdel_search.SetCurSel(0); //选择第0项目
	m_cusdel_cid.Empty(); m_cusdel_starter.Empty(); m_cusdel_desti.Empty();
	m_cusdel_runstatic.Empty(); m_cusdel_delstatus.Empty();
	m_cusdel_hour = 0; m_cusdel_minute = 0; m_cusdel_drtime = 0;
	m_cusdel_price = 0; m_cusdel_people = 0; m_cusdel_sold = 0;
	m_cusdel_delnum = 0;
	UpdateData(FALSE); //更新到对应的控件
}
