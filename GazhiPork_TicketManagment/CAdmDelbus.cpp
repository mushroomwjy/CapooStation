// CAdmDelbus.cpp: 实现文件
//

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CAdmDelbus.h"
#include "InfoFile.h"
#pragma warning(disable:6284)
// CAdmDelbus

IMPLEMENT_DYNCREATE(CAdmDelbus, CFormView)

CAdmDelbus::CAdmDelbus()
	: CFormView(DIALOG_ADM_DELBUS)
	, m_admdelbus_cid(_T(""))
	, m_admdelbus_starter(_T(""))
	, m_admdelbus_drtime(0)
	, m_admdelbus_people(0)
	, m_admdelbus_hour(0)
	, m_admdelbus_minute(0)
	, m_admdelbus_desti(_T(""))
	, m_admdelbus_price(0)
	, m_admdelbus_sold(0)
{

}

CAdmDelbus::~CAdmDelbus()
{
}

void CAdmDelbus::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_admdelbus_cid);
	DDX_Text(pDX, IDC_EDIT2, m_admdelbus_starter);
	DDX_Text(pDX, IDC_EDIT5, m_admdelbus_drtime);
	DDX_Text(pDX, IDC_EDIT7, m_admdelbus_people);
	DDX_Text(pDX, IDC_EDIT4, m_admdelbus_hour);
	DDX_Text(pDX, IDC_EDIT9, m_admdelbus_minute);
	DDX_Text(pDX, IDC_EDIT3, m_admdelbus_desti);
	DDX_Text(pDX, IDC_EDIT6, m_admdelbus_price);
	DDX_Text(pDX, IDC_EDIT8, m_admdelbus_sold);
	DDX_Control(pDX, IDC_COMBO2, m_admdelbus_search);
}

BEGIN_MESSAGE_MAP(CAdmDelbus, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CAdmDelbus::OnCbnSelchangeCombo2)
	//	ON_CBN_EDITCHANGE(IDC_COMBO2, &CAdmDelbus::OnEditchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdmDelbus::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAdmDelbus 诊断

#ifdef _DEBUG
void CAdmDelbus::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdmDelbus::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdmDelbus 消息处理程序


void CAdmDelbus::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//读取文件，获取商品名，给组合框添加字符串
	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取车信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_admdelbus_search.AddString((CString)it->cid.c_str());
	}

	//将第一个车设为默认选中项
	m_admdelbus_search.SetCurSel(0);
	MessageBox(TEXT("若查询车次位于首位请选择车号刷新列表\n原谅给您带来的不便\n\t\t\t---咖波屋车站"));
}

void CAdmDelbus::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	//获取当前选中项
	int index = m_admdelbus_search.GetCurSel();
	//获取当前内容
	m_admdelbus_search.GetLBText(index, text);

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->cid.c_str())
		{
			m_admdelbus_cid = it->cid.c_str();
			m_admdelbus_starter = it->starter.c_str();
			m_admdelbus_desti = it->destination.c_str();
			m_admdelbus_hour = it->st_time.hour;
			m_admdelbus_minute = it->st_time.minute;
			m_admdelbus_drtime = it->dr_time;
			m_admdelbus_price = it->price;
			m_admdelbus_people = it->people;
			m_admdelbus_sold = it->sold;
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}
}


void CAdmDelbus::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取控件上的内容，更新到对应关联的变量中
	UpdateData(TRUE);

	CString type;
	//获取当前选中项
	int index = m_admdelbus_search.GetCurSel();
	//获取组合框当前内容
	m_admdelbus_search.GetLBText(index, type);

	CString str;
	str.Format(_T("删除列车：%s 成功\n资源已更新"), type);
	MessageBox(str);

	//需要包含#include "InfoFile.h"删除指定元素[wjy]
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end();) {
		if (type == it->cid.c_str()) {
			it = file.ls.erase(it);		//删除该元素
			// 对后续元素的id减一
			while (it != file.ls.end()) {
				it->id--;
				it++;
			}
			break;
		}
		else it++;
	}

	file.WirteDocline(); //更新文件内容

	m_admdelbus_search.SetCurSel(0); //选择第0项目
	m_admdelbus_cid.Empty(); m_admdelbus_starter.Empty(); m_admdelbus_desti.Empty();
	m_admdelbus_hour = 0; m_admdelbus_minute = 0; m_admdelbus_drtime = 0;
	m_admdelbus_price = 0; m_admdelbus_people = 0; m_admdelbus_sold = 0;
	UpdateData(FALSE); //更新到对应的控件

}
