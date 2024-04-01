// CAdmSearch.cpp: 实现文件
//

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CAdmSearch.h"
#include "InfoFile.h"

// CAdmSearch

IMPLEMENT_DYNCREATE(CAdmSearch, CFormView)

CAdmSearch::CAdmSearch()
	: CFormView(DIALOG_ADM_SEARCH)
	, m_admsearch_cid(_T(""))
	, m_admsearch_starter(_T(""))
	, m_admsearch_drtime(0)
	, m_admsearch_people(0)
	, m_admsearch_hour(0)
	, m_admsearch_minute(0)
	, m_admsearch_desti(_T(""))
	, m_admsearch_price(0)
	, m_admsearch_sold(0)
	, m_admsearch_avail(_T(""))
{

}

CAdmSearch::~CAdmSearch()
{
}

void CAdmSearch::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_admsearch_search);
	DDX_Text(pDX, IDC_EDIT1, m_admsearch_cid);
	DDX_Text(pDX, IDC_EDIT2, m_admsearch_starter);
	DDX_Text(pDX, IDC_EDIT10, m_admsearch_drtime);
	DDX_Text(pDX, IDC_EDIT11, m_admsearch_people);
	DDX_Text(pDX, IDC_EDIT12, m_admsearch_hour);
	DDX_Text(pDX, IDC_EDIT16, m_admsearch_minute);
	DDX_Text(pDX, IDC_EDIT13, m_admsearch_desti);
	DDX_Text(pDX, IDC_EDIT15, m_admsearch_price);
	DDX_Text(pDX, IDC_EDIT14, m_admsearch_sold);
	DDX_Control(pDX, IDC_COMBO3, m_admsearch_find);
	DDX_Control(pDX, IDC_LIST3, m_admsearch_list);
	DDX_Text(pDX, IDC_EDIT17, m_admsearch_avail);
}

BEGIN_MESSAGE_MAP(CAdmSearch, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAdmSearch::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CAdmSearch::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// CAdmSearch 诊断

#ifdef _DEBUG
void CAdmSearch::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdmSearch::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdmSearch 消息处理程序


void CAdmSearch::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	MessageBox(TEXT("若查询车次/车站位于首位请选择车号刷新列表\n原谅给您带来的不便\n\t\t\t---咖波屋车站"));

	CInfoFile file;
	file.ReadDocline(); //读取车辆信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_admsearch_search.AddString((CString)it->cid.c_str());
	}
	//将第一车设为默认选中项
	m_admsearch_search.SetCurSel(0);

	//删除重复目的地写入combo控件[wjy]
	list<string> select;	//创建新容器存储目的地
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)	{
		select.push_back(it->destination);		//将目的地放入select中
	}
	select.sort();
	select.unique();		//select删除重复元素

	for (list<string>::iterator it = select.begin(); it != select.end(); it++)
	{
		m_admsearch_find.AddString((CString)it->c_str());	//写入combobox
	}
	//将第一个车设为默认选中项
	m_admsearch_find.SetCurSel(0);

	// 设置扩展风格
	//LVS_EX_FULLROWSELECT选中整行，LVS_EX_GRIDLINES网格
	m_admsearch_list.SetExtendedStyle
	(m_admsearch_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化表头
	CString field[] = { _T("ID"),_T("宝宝巴士"), _T("发车时间"), _T("起点站"), _T("终点站"),
		_T("车程(h)"), _T("RMB票价"), _T("额定载量"), _T("已售票数"), _T("运行状态") };

	//设置列宽
	m_admsearch_list.InsertColumn(0, field[0], LVCFMT_CENTER, 45);
	for (int i = 1; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		m_admsearch_list.InsertColumn(i, field[i], LVCFMT_CENTER, 81);
	}

	//添加数据
	int i = 0;
	CString str;
	CString type;
	//获取当前选中项
	int index = m_admsearch_find.GetCurSel();
	//获取组合框当前内容
	m_admsearch_find.GetLBText(index, type);
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
		if (type == (CString)it->destination.c_str()) {
			str.Format(_T("%.2d"), it->id);
			m_admsearch_list.InsertItem(i, str);	//插入一行

			//依次写入每一列数据
			int column = 1;
			m_admsearch_list.SetItemText(i, column++, (CString)it->cid.c_str());	//字符串转化

			str.Format(_T("%.2d:%.2d"), it->st_time.hour, it->st_time.minute);
			m_admsearch_list.SetItemText(i, column++, str);

			m_admsearch_list.SetItemText(i, column++, (CString)it->starter.c_str());

			m_admsearch_list.SetItemText(i, column++, (CString)it->destination.c_str());

			str.Format(_T("%.2f"), it->dr_time);
			m_admsearch_list.SetItemText(i, column++, str);

			str.Format(_T("%3d"), it->price);
			m_admsearch_list.SetItemText(i, column++, str);

			str.Format(_T("%2d"), it->people);
			m_admsearch_list.SetItemText(i, column++, str);

			str.Format(_T("%2d"), it->sold);
			m_admsearch_list.SetItemText(i, column++, str);

			m_admsearch_list.SetItemText(i, column++, (CString)it->available.c_str());

			i++;
		}
	}
}


void CAdmSearch::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	//获取当前选中项
	int index = m_admsearch_search.GetCurSel();
	//获取当前内容
	m_admsearch_search.GetLBText(index, text);

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->cid.c_str())
		{
			m_admsearch_cid = it->cid.c_str();
			m_admsearch_starter = it->starter.c_str();
			m_admsearch_desti = it->destination.c_str();
			m_admsearch_hour = it->st_time.hour;
			m_admsearch_minute = it->st_time.minute;
			m_admsearch_drtime = it->dr_time;
			m_admsearch_price = it->price;
			m_admsearch_people = it->people;
			m_admsearch_sold = it->sold;
			m_admsearch_avail = it->available.c_str();
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}
}


void CAdmSearch::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
	// //需要包含#include "InfoFile.h"删除指定元素[wjy]
	CInfoFile file;
	file.ReadDocline(); //读取商品信息

	//实现按目的地升序[wjy]
	list<msg> sorted;	//创建新容器存储发车时间排序
	sorted = file.ls;
	sorted.sort();

	//添加数据
	int i = 0;
	CString str;
	CString type;
	m_admsearch_list.DeleteAllItems();	//清空所有表项
	//获取当前选中项
	int index = m_admsearch_find.GetCurSel();
	//获取组合框当前内容
	m_admsearch_find.GetLBText(index, type);
	for (list<msg>::iterator it = sorted.begin(); it != sorted.end(); it++) {
		if (type == (CString)it->destination.c_str()) {
			str.Format(_T("%.2d"), it->id);
			m_admsearch_list.InsertItem(i, str);	//插入一行

			//依次写入每一列数据
			int column = 1;
			m_admsearch_list.SetItemText(i, column++, (CString)it->cid.c_str());	//字符串转化

			str.Format(_T("%.2d:%.2d"), it->st_time.hour, it->st_time.minute);
			m_admsearch_list.SetItemText(i, column++, str);

			m_admsearch_list.SetItemText(i, column++, (CString)it->starter.c_str());

			m_admsearch_list.SetItemText(i, column++, (CString)it->destination.c_str());

			str.Format(_T("%.2f"), it->dr_time);
			m_admsearch_list.SetItemText(i, column++, str);

			str.Format(_T("%3d"), it->price);
			m_admsearch_list.SetItemText(i, column++, str);

			str.Format(_T("%2d"), it->people);
			m_admsearch_list.SetItemText(i, column++, str);

			str.Format(_T("%2d"), it->sold);
			m_admsearch_list.SetItemText(i, column++, str);

			m_admsearch_list.SetItemText(i, column++, (CString)it->available.c_str());

			i++;
		}
	}
}
