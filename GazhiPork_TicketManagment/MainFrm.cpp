
// MainFrm.cpp: CMainFrame 类的实现

#include "pch.h"
#include "framework.h"
#include "GazhiPork_TicketManagment.h"

#include "MainFrm.h"
#include "InfoFile.h"
#include "CSelectView.h"
#include "CDisplayView.h"

#include "CAdmWelcome.h"
#include "CAdmUserDlg.h"
#include "CAdmAddbus.h"
#include "CAdmAllmsg.h"
#include "CAdmSearch.h"
#include "CAdmDelbus.h"
#include "CCusWelcome.h"
#include "CCusSearch.h"
#include "CCusBuytic.h"
#include "CCusDeltic.h"
#include "CLoginDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE响应的是自定义消息
//产生NM_X消息，自动调用OnMyChange函数[wjy]
ON_MESSAGE(NM_ADM_A, OnMyChange)
ON_MESSAGE(NM_ADM_B, OnMyChange)
ON_MESSAGE(NM_ADM_C, OnMyChange)
ON_MESSAGE(NM_ADM_D, OnMyChange)
ON_MESSAGE(NM_ADM_E, OnMyChange)
ON_MESSAGE(NM_ADM_F, OnMyChange)
ON_MESSAGE(NM_ADM_G, OnMyChange)
ON_MESSAGE(NM_ADM_H, OnMyChange)

ON_MESSAGE(NM_CUS_A, OnMyChange)
ON_MESSAGE(NM_CUS_B, OnMyChange)
ON_MESSAGE(NM_CUS_C, OnMyChange)
ON_MESSAGE(NM_CUS_D, OnMyChange)
ON_MESSAGE(NM_CUS_E, OnMyChange)
ON_MESSAGE(NM_CUS_F, OnMyChange)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	//设置图标，IDI_ICON_WIN为图标资源ID，此为WINAPI函数[wjy]
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICO_HOME));

	//设置窗口标题，CDocument::SetTitle，右侧标题[wjy]
	SetTitle(TEXT(">    By: Gazhi Pork    mail: novawjy@vip.qq.com"));

	//设置窗口大小位置[wjy]
	//设置窗口的位置和大小：CWnd::MoveWindow
	//0, 0, 起点坐标x和y		1200, 725, 窗口宽度和高度
	MoveWindow(0, 0, 1200, 750);
	//将窗口移动到屏幕中央，CWnd::CenterWindow
	CenterWindow();

	//测试InfoFile类的设计[wjy]
	//CInfoFile file;
	//CString name, pwd;
	// 
	//file.ReadLogin(name, pwd);
	//file.ReadDocline();
	//MessageBox(name);
	//MessageBox(pwd);
	// 
	//file.WritePwd("Mushroom", "123456");
	//file.ReadLogin(name, pwd);
	//file.ReadDocline();
	//MessageBox(name);
	//MessageBox(pwd);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类

	// 静态拆分窗口，1行2列，CSplitterWnd::CreateStatic
	m_spliter.CreateStatic(this, 1, 2);

	// 创建视图：CSplitterWnd::CreateView
	//0, 0 ： 放在第0行第0列的位置
	//RUNTIME_CLASS(CSelectView) ：需要头文件#include "SelectView.h"， CSelectView在SelectView.h中声明
	// CSize(250, 500)：指定视图宽度和高度
	//pContext ： 为OnCreateClient()最后一个形参
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(300, 750), pContext);

	//0, 1： 放在第0行第1列的位置
	//CDispalyView，需要头文件#include "DispalyView.h"
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(900, 750), pContext);
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	//自定义消息处理与界面挂载
	CCreateContext   Context;
	switch (wParam) {
	case NM_ADM_A: {
		Context.m_pNewViewClass = RUNTIME_CLASS(CAdmWelcome);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAdmWelcome), CSize(600, 500), &Context);
		CAdmWelcome* pNewView = (CAdmWelcome*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		MessageBox(TEXT("欢迎您以管理员身份登入系统！"));
		break;
	}
	case NM_ADM_B: {
		//CAdmUserDlg类需要包含头文件#include "CAdmUserDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CAdmUserDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAdmUserDlg), CSize(600, 500), &Context);
		CAdmUserDlg* pNewView = (CAdmUserDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}

	case NM_ADM_C: {
		Context.m_pNewViewClass = RUNTIME_CLASS(CAdmAddbus);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAdmAddbus), CSize(600, 0), &Context);
		CAdmAddbus* pNewView = (CAdmAddbus*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}
	case NM_ADM_D: {
		Context.m_pNewViewClass = RUNTIME_CLASS(CAdmAllmsg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAdmAllmsg), CSize(600, 0), &Context);
		CAdmAllmsg* pNewView = (CAdmAllmsg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}
	case NM_ADM_E: {
		Context.m_pNewViewClass = RUNTIME_CLASS(CAdmSearch);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAdmSearch), CSize(600, 0), &Context);
		CAdmSearch* pNewView = (CAdmSearch*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}

	case NM_ADM_F: {
		Context.m_pNewViewClass = RUNTIME_CLASS(CAdmDelbus);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAdmDelbus), CSize(600, 0), &Context);
		CAdmDelbus* pNewView = (CAdmDelbus*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}

	case NM_ADM_G: {
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
		break;
	}
	case NM_ADM_H: {
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
		break;
	}
	case NM_CUS_A: {
		Context.m_pNewViewClass = RUNTIME_CLASS(CCusWelcome);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CCusWelcome*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CCusWelcome), CSize(600, 500), &Context);
		CCusWelcome* pNewView = (CCusWelcome*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		MessageBox(TEXT("欢迎您以客户身份登入系统！"));
		break;
	}
	case NM_CUS_B: {
		Context.m_pNewViewClass = RUNTIME_CLASS(CCusSearch);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CCusSearch), CSize(600, 0), &Context);
		CCusSearch* pNewView = (CCusSearch*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}

	case NM_CUS_C: {
		Context.m_pNewViewClass = RUNTIME_CLASS(CCusBuytic);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CCusBuytic), CSize(600, 0), &Context);
		CCusBuytic* pNewView = (CCusBuytic*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}
	case NM_CUS_D: {
		Context.m_pNewViewClass = RUNTIME_CLASS(CCusDeltic);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CCusDeltic), CSize(600, 0), &Context);
		CCusDeltic* pNewView = (CCusDeltic*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}
	case NM_CUS_E: {
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
		break;
	}
	case NM_CUS_F: {
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
		break;
	}
	default:
		MessageBox(_T("error"));
	}



	return LRESULT();
}
