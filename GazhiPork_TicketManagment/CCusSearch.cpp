// CCusSearch.cpp: 实现文件
//

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CCusSearch.h"
#include "InfoFile.h"


// CCusSearch

IMPLEMENT_DYNCREATE(CCusSearch, CFormView)

CCusSearch::CCusSearch()
	: CFormView(DIALOG_CUS_SEARCH)
	, m_cussearch_cid(_T(""))
	, m_cussearch_starter(_T(""))
	, m_cussearch_drtime(0)
	, m_cussearch_people(0)
	, m_cussearch_avail(_T(""))
	, m_cussearch_hour(0)
	, m_cussearch_minute(0)
	, m_cussearch_desti(_T(""))
	, m_cussearch_price(0)
	, m_cussearch_sold(0)
{

}

CCusSearch::~CCusSearch()
{
}

void CCusSearch::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cussearch_search);
	DDX_Control(pDX, IDC_COMBO3, m_cussearch_find);
	DDX_Control(pDX, IDC_LIST3, m_cussearch_list);
	DDX_Text(pDX, IDC_EDIT1, m_cussearch_cid);
	DDX_Text(pDX, IDC_EDIT2, m_cussearch_starter);
	DDX_Text(pDX, IDC_EDIT10, m_cussearch_drtime);
	DDX_Text(pDX, IDC_EDIT11, m_cussearch_people);
	DDX_Text(pDX, IDC_EDIT17, m_cussearch_avail);
	DDX_Text(pDX, IDC_EDIT12, m_cussearch_hour);
	DDX_Text(pDX, IDC_EDIT16, m_cussearch_minute);
	DDX_Text(pDX, IDC_EDIT13, m_cussearch_desti);
	DDX_Text(pDX, IDC_EDIT15, m_cussearch_price);
	DDX_Text(pDX, IDC_EDIT14, m_cussearch_sold);
}

BEGIN_MESSAGE_MAP(CCusSearch, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCusSearch::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CCusSearch::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// CCusSearch 诊断

#ifdef _DEBUG
void CCusSearch::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCusSearch::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCusSearch 消息处理程序


void CCusSearch::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	MessageBox(TEXT("若查询车次/车站位于首位请选择车号刷新列表\n原谅给您带来的不便\n\t\t\t---咖波屋车站"));

	CInfoFile file;
	file.ReadDocline(); //读取车辆信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_cussearch_search.AddString((CString)it->cid.c_str());
	}
	//将第一车设为默认选中项
	m_cussearch_search.SetCurSel(0);

	//删除重复目的地写入combo控件[wjy]
	list<string> select;	//创建新容器存储目的地
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
		select.push_back(it->destination);		//将目的地放入select中
	}
	select.sort();
	select.unique();		//select删除重复元素

	for (list<string>::iterator it = select.begin(); it != select.end(); it++)
	{
		m_cussearch_find.AddString((CString)it->c_str());	//写入combobox
	}
	//将第一个车设为默认选中项
	m_cussearch_find.SetCurSel(0);

	// 设置扩展风格
	//LVS_EX_FULLROWSELECT选中整行，LVS_EX_GRIDLINES网格
	m_cussearch_list.SetExtendedStyle
	(m_cussearch_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化表头
	CString field[] = { _T("ID"),_T("宝宝巴士"), _T("发车时间"), _T("起点站"), _T("终点站"),
		_T("车程(h)"), _T("RMB票价"), _T("额定载量"), _T("已售票数") , _T("运行状态") };

	//设置列宽
	m_cussearch_list.InsertColumn(0, field[0], LVCFMT_CENTER, 45);
	for (int i = 1; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		m_cussearch_list.InsertColumn(i, field[i], LVCFMT_CENTER, 81);
	}

	//添加数据
	int i = 0;
	CString str;
	CString type;
	//获取当前选中项
	int index = m_cussearch_find.GetCurSel();
	//获取组合框当前内容
	m_cussearch_find.GetLBText(index, type);
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
		if (type == (CString)it->destination.c_str()) {
			str.Format(_T("%.2d"), it->id);
			m_cussearch_list.InsertItem(i, str);	//插入一行

			//依次写入每一列数据
			int column = 1;
			m_cussearch_list.SetItemText(i, column++, (CString)it->cid.c_str());	//字符串转化

			str.Format(_T("%.2d:%.2d"), it->st_time.hour, it->st_time.minute);
			m_cussearch_list.SetItemText(i, column++, str);

			m_cussearch_list.SetItemText(i, column++, (CString)it->starter.c_str());

			m_cussearch_list.SetItemText(i, column++, (CString)it->destination.c_str());

			str.Format(_T("%.2f"), it->dr_time);
			m_cussearch_list.SetItemText(i, column++, str);

			str.Format(_T("%3d"), it->price);
			m_cussearch_list.SetItemText(i, column++, str);

			str.Format(_T("%2d"), it->people);
			m_cussearch_list.SetItemText(i, column++, str);

			str.Format(_T("%2d"), it->sold);
			m_cussearch_list.SetItemText(i, column++, str);

			m_cussearch_list.SetItemText(i, column++, (CString)it->available.c_str());

			i++;
		}
	}
}


void CCusSearch::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	//获取当前选中项
	int index = m_cussearch_search.GetCurSel();
	//获取当前内容
	m_cussearch_search.GetLBText(index, text);

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->cid.c_str())
		{
			m_cussearch_cid = it->cid.c_str();
			m_cussearch_starter = it->starter.c_str();
			m_cussearch_desti = it->destination.c_str();
			m_cussearch_hour = it->st_time.hour;
			m_cussearch_minute = it->st_time.minute;
			m_cussearch_drtime = it->dr_time;
			m_cussearch_price = it->price;
			m_cussearch_people = it->people;
			m_cussearch_sold = it->sold;
			m_cussearch_avail = (CString)it->available.c_str();
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}
}


void CCusSearch::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	// //需要包含#include "InfoFile.h"删除指定元素[wjy]
	CInfoFile file;
	file.ReadDocline(); //读取商品信息

	//删实现按目的地升序[wjy]
	list<msg> sorted;	//创建新容器存储发车时间排序
	sorted = file.ls;
	sorted.sort();

	//添加数据
	int i = 0;
	CString str;
	CString type;
	m_cussearch_list.DeleteAllItems();	//清空所有表项
	//获取当前选中项
	int index = m_cussearch_find.GetCurSel();
	//获取组合框当前内容
	m_cussearch_find.GetLBText(index, type);
	for (list<msg>::iterator it = sorted.begin(); it != sorted.end(); it++) {
		if (type == (CString)it->destination.c_str()) {
			str.Format(_T("%.2d"), it->id);
			m_cussearch_list.InsertItem(i, str);	//插入一行

			//依次写入每一列数据
			int column = 1;
			m_cussearch_list.SetItemText(i, column++, (CString)it->cid.c_str());	//字符串转化

			str.Format(_T("%.2d:%.2d"), it->st_time.hour, it->st_time.minute);
			m_cussearch_list.SetItemText(i, column++, str);

			m_cussearch_list.SetItemText(i, column++, (CString)it->starter.c_str());

			m_cussearch_list.SetItemText(i, column++, (CString)it->destination.c_str());

			str.Format(_T("%.2f"), it->dr_time);
			m_cussearch_list.SetItemText(i, column++, str);

			str.Format(_T("%3d"), it->price);
			m_cussearch_list.SetItemText(i, column++, str);

			str.Format(_T("%2d"), it->people);
			m_cussearch_list.SetItemText(i, column++, str);

			str.Format(_T("%2d"), it->sold);
			m_cussearch_list.SetItemText(i, column++, str);

			m_cussearch_list.SetItemText(i, column++, (CString)it->available.c_str());

			i++;
		}
	}
}
