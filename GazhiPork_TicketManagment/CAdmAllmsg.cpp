// CAdmAllmsg.cpp: 实现文件
//

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CAdmAllmsg.h"
#include "InfoFile.h"

// CAdmAllmsg

IMPLEMENT_DYNCREATE(CAdmAllmsg, CFormView)

CAdmAllmsg::CAdmAllmsg()
	: CFormView(DIALOG_ADM_ALLMSG)
{

}

CAdmAllmsg::~CAdmAllmsg()
{
}

void CAdmAllmsg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_admallmsg_list);
}

BEGIN_MESSAGE_MAP(CAdmAllmsg, CFormView)
END_MESSAGE_MAP()


// CAdmAllmsg 诊断

#ifdef _DEBUG
void CAdmAllmsg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdmAllmsg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdmAllmsg 消息处理程序

//展示列表初始化啊[wjy]
void CAdmAllmsg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	// 设置扩展风格
	//LVS_EX_FULLROWSELECT选中整行，LVS_EX_GRIDLINES网格
	m_admallmsg_list.SetExtendedStyle
	(m_admallmsg_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化表头
	CString field[] = { _T("ID"),_T("宝宝巴士"), _T("发车时间"), _T("起点站"), _T("终点站"),
		_T("车程(h)"), _T("RMB票价"), _T("额定载量"), _T("已售票数"), _T("运行状态") };
	
	//设置列宽
	m_admallmsg_list.InsertColumn(0, field[0], LVCFMT_CENTER, 34);
	for (int i = 1; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		m_admallmsg_list.InsertColumn(i, field[i], LVCFMT_CENTER, 80);
	}

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息

	//添加数据
	int i = 0;
	CString str;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		str.Format(_T("%.2d"), it->id);
		m_admallmsg_list.InsertItem(i, str);	//插入一行

		//依次写入每一列数据
		int column = 1;
		m_admallmsg_list.SetItemText(i, column++, (CString)it->cid.c_str());	//字符串转化
		
		str.Format(_T("%.2d:%.2d"), it->st_time.hour, it->st_time.minute);
		m_admallmsg_list.SetItemText(i, column++, str);

		m_admallmsg_list.SetItemText(i, column++, (CString)it->starter.c_str());

		m_admallmsg_list.SetItemText(i, column++, (CString)it->destination.c_str());

		str.Format(_T("%.2f"), it->dr_time);
		m_admallmsg_list.SetItemText(i, column++, str);

		str.Format(_T("%3d"), it->price);
		m_admallmsg_list.SetItemText(i, column++, str);

		str.Format(_T("%2d"), it->people);
		m_admallmsg_list.SetItemText(i, column++, str);

		str.Format(_T("%2d"), it->sold);
		m_admallmsg_list.SetItemText(i, column++, str);

		m_admallmsg_list.SetItemText(i, column++, (CString)it->available.c_str());

		i++;
	}
}

