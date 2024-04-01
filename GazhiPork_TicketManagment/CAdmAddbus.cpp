// CAdmAddbus.cpp: 实现文件
//

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CAdmAddbus.h"

#include "InfoFile.h"

// CAdmAddbus

IMPLEMENT_DYNCREATE(CAdmAddbus, CFormView)

CAdmAddbus::CAdmAddbus()
	: CFormView(DIALOG_ADM_ADDBUS)
	, m_admaddbus_cid(_T(""))
	, m_admaddbus_hour(0)
	, m_admaddbus_minute(0)
	, m_admaddbus_starter(_T(""))
	, m_admaddbus_desti(_T(""))
	, m_admaddbus_drtime(0)
	, m_admaddbus_price(0)
	, m_admaddbus_people(0)
	, m_admaddbus_sold(0)
{

}

CAdmAddbus::~CAdmAddbus()
{
}

void CAdmAddbus::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_admaddbus_cid);
	DDX_Text(pDX, IDC_EDIT4, m_admaddbus_hour);
	DDX_Text(pDX, IDC_EDIT9, m_admaddbus_minute);
	DDX_Text(pDX, IDC_EDIT2, m_admaddbus_starter);
	DDX_Text(pDX, IDC_EDIT3, m_admaddbus_desti);
	DDX_Text(pDX, IDC_EDIT5, m_admaddbus_drtime);
	DDX_Text(pDX, IDC_EDIT6, m_admaddbus_price);
	DDX_Text(pDX, IDC_EDIT7, m_admaddbus_people);
	DDX_Text(pDX, IDC_EDIT8, m_admaddbus_sold);
}

BEGIN_MESSAGE_MAP(CAdmAddbus, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdmAddbus::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CAdmAddbus::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAdmAddbus 诊断

#ifdef _DEBUG
void CAdmAddbus::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdmAddbus::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdmAddbus 消息处理程序

void CAdmAddbus::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE); //获取控件内容

	if (m_admaddbus_price <= 0 || m_admaddbus_hour < 0 || m_admaddbus_minute < 0 ||
		m_admaddbus_drtime <= 0 || m_admaddbus_people <= 0 || m_admaddbus_cid.IsEmpty()) {
		MessageBox(TEXT("输入信息有误，请重新输入"));
		return;
	}

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息

	//检测输入车次号是否重复
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (m_admaddbus_cid == (CString)it->cid.c_str()) {
			MessageBox(TEXT("已存在该车次号列车，请重新输入"));
			return;
		}
	}


	file.Addline(m_admaddbus_cid,mushclock{m_admaddbus_hour,m_admaddbus_minute},
		m_admaddbus_starter,m_admaddbus_desti,
		m_admaddbus_drtime,m_admaddbus_price,m_admaddbus_people,m_admaddbus_sold); //添加商品
	file.WirteDocline(); //写文件
	file.ls.clear(); //清空list的内容
	MessageBox(_T("添加成功"));

	m_admaddbus_cid.Empty(); m_admaddbus_starter.Empty(); m_admaddbus_desti.Empty();
	m_admaddbus_hour = 0; m_admaddbus_minute = 0;
	m_admaddbus_drtime = 0; m_admaddbus_price = 0; m_admaddbus_people = 0;
	m_admaddbus_sold = 0;
	UpdateData(FALSE);
}


void CAdmAddbus::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_admaddbus_cid.Empty(); m_admaddbus_starter.Empty(); m_admaddbus_desti.Empty();
	m_admaddbus_hour = 0; m_admaddbus_minute = 0;
	m_admaddbus_drtime = 0; m_admaddbus_price = 0; m_admaddbus_people = 0;
	UpdateData(FALSE);
}
