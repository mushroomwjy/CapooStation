// CCusWelcome.cpp: 实现文件
//

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CCusWelcome.h"


// CCusWelcome

IMPLEMENT_DYNCREATE(CCusWelcome, CFormView)

CCusWelcome::CCusWelcome()
	: CFormView(DIALOG_CUS_WELCOME)
{

}

CCusWelcome::~CCusWelcome()
{
}

void CCusWelcome::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCusWelcome, CFormView)
END_MESSAGE_MAP()


// CCusWelcome 诊断

#ifdef _DEBUG
void CCusWelcome::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCusWelcome::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCusWelcome 消息处理程序
