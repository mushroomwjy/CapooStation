// CAdmWelcome.cpp: 实现文件
//

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CAdmWelcome.h"


// CAdmWelcome

IMPLEMENT_DYNCREATE(CAdmWelcome, CFormView)

CAdmWelcome::CAdmWelcome()
	: CFormView(DIALOG_ADM_WELCOME)
{

}

CAdmWelcome::~CAdmWelcome()
{
}

void CAdmWelcome::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAdmWelcome, CFormView)
END_MESSAGE_MAP()


// CAdmWelcome 诊断

#ifdef _DEBUG
void CAdmWelcome::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdmWelcome::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdmWelcome 消息处理程序
