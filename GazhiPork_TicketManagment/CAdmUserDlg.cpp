// CAdmUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CAdmUserDlg.h"
#include "InfoFile.h"

// CAdmUserDlg

IMPLEMENT_DYNCREATE(CAdmUserDlg, CFormView)

CAdmUserDlg::CAdmUserDlg()
	: CFormView(DIALOG_ADM_USER)
	, m_adm_user(_T(""))
	, m_adm_name(_T(""))
	, m_adm_newpwd(_T(""))
	, m_adm_rightpwd(_T(""))
{

}

CAdmUserDlg::~CAdmUserDlg()
{
}

void CAdmUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_adm_user);
	DDX_Text(pDX, IDC_EDIT2, m_adm_name);
	DDX_Text(pDX, IDC_EDIT3, m_adm_newpwd);
	DDX_Text(pDX, IDC_EDIT4, m_adm_rightpwd);
}

BEGIN_MESSAGE_MAP(CAdmUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdmUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAdmUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAdmUserDlg 诊断

#ifdef _DEBUG
void CAdmUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdmUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdmUserDlg 消息处理程序


void CAdmUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	CInfoFile file;	//需要头文件#include "InfoFile.h"
	CString name, pwd;
	file.ReadLogin(name, pwd); //读取文件的用户名和密码

	//初始化个人信息
	m_adm_user = TEXT("咖波屋车站管理员OwO");	//身份
	m_adm_name = name;	//用户名

	UpdateData(FALSE); //把数据更新到控件上

}

//确认修改密码[wjy]
void CAdmUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);//更新控件内容到对应的变量中

	if (m_adm_newpwd.IsEmpty() || m_adm_rightpwd.IsEmpty())
	{
		MessageBox(TEXT("输入密码不能为空"));
		return;
	}

	if (m_adm_newpwd != m_adm_rightpwd)
	{
		MessageBox(TEXT("输入密码和确定密码不相等"));
		return;
	}

	CInfoFile file;	//需要头文件#include "InfoFile.h"
	CString name, pwd;
	file.ReadLogin(name, pwd); //读取文件的用户名和密码

	if (m_adm_rightpwd == pwd)
	{
		MessageBox(TEXT("输入密码和旧密码相等"));
		return;
	}

	//把用户名和密码的CString类型转为char *
	char *tmpName, *tmpPwd;
	//用户名
	CStringA tmp1;
	tmp1 = name;
	tmpName = tmp1.GetBuffer();
	//密码
	CStringA tmp2;
	tmp2 = m_adm_rightpwd;
	tmpPwd = tmp2.GetBuffer();

	file.WritePwd(tmpName, tmpPwd); //修改密码

	MessageBox(TEXT("密码修改成功"));

	//输入框内容清空
	m_adm_rightpwd.Empty();
	m_adm_newpwd.Empty();

	UpdateData(FALSE); //把数据更新到控件上
}

//取消更改密码处理[wjy]
void CAdmUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//输入框内容清空
	m_adm_newpwd.Empty();
	m_adm_rightpwd.Empty();
	UpdateData(FALSE); //把数据更新到控件上
}
