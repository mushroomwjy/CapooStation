// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "CSelectView.h"
#include "GlobalData.h"
#include "MainFrm.h"

// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//-----admin初始化代码[wjy]
	if (USER_IS_ADMIN) {
		//加载图标
		HICON icon[8];
		icon[0] = AfxGetApp()->LoadIconW(IDI_ICO_SPEECH);
		icon[1] = AfxGetApp()->LoadIconW(IDI_ICO_SETTING);
		icon[2] = AfxGetApp()->LoadIconW(IDI_ICO_FORYOU);
		icon[3] = AfxGetApp()->LoadIconW(IDI_ICO_BINOCULARS);
		icon[4] = AfxGetApp()->LoadIconW(IDI_ICO_SEARCH);
		icon[5] = AfxGetApp()->LoadIconW(IDI_ICO_TRASHCAN);
		icon[6] = AfxGetApp()->LoadIconW(IDI_ICO_MAILBOX);
		icon[7] = AfxGetApp()->LoadIconW(IDI_ICO_SUN);
		//1.准备图片集合
		madm_imageList.Create(26, 26, ILC_COLOR32, 8, 8);

		//图片列表追加图标
		for (int i = 0; i < 8; i++)
		{
			madm_imageList.Add(icon[i]);
		}

		//获取树控件
		madm_treeCtrl = &GetTreeCtrl();
		madm_treeCtrl->SetImageList(&madm_imageList, TVSIL_NORMAL);

		//2.树控件设置节点 CTreeCtrl::InsertItem
		madm_treeCtrl->InsertItem(TEXT("Current Login : Administrator"), 0, 0, NULL);
		madm_treeCtrl->InsertItem(TEXT("管理员个人中心"), 1, 1, NULL);
		madm_treeCtrl->InsertItem(TEXT("增加单车次信息"), 2, 2, NULL);
		madm_treeCtrl->InsertItem(TEXT("全车次一键查询"), 3, 3, NULL);
		madm_treeCtrl->InsertItem(TEXT("部分车信息查询"), 4, 4, NULL);
		madm_treeCtrl->InsertItem(TEXT("注销指定单车次"), 5, 5, NULL);
		madm_treeCtrl->InsertItem(TEXT("退出管理员账号"), 6, 6, NULL);
		madm_treeCtrl->InsertItem(TEXT("退出管理员系统"), 7, 7, NULL);
	}
	if (!USER_IS_ADMIN) {
		//加载图标
		HICON icon[6];
		icon[0] = AfxGetApp()->LoadIconW(IDI_ICO_SPEECH);
		icon[1] = AfxGetApp()->LoadIconW(IDI_ICO_BOX);
		icon[2] = AfxGetApp()->LoadIconW(IDI_ICO_TOOLBOX);
		icon[3] = AfxGetApp()->LoadIconW(IDI_ICO_TRASHCAN);
		icon[4] = AfxGetApp()->LoadIconW(IDI_ICO_MAILBOX);
		icon[5] = AfxGetApp()->LoadIconW(IDI_ICO_SUN);
		//1.准备图片集合
		mcus_imageList.Create(26, 26, ILC_COLOR32, 6, 6);

		//图片列表追加图标
		for (int i = 0; i < 6; i++)
		{
			mcus_imageList.Add(icon[i]);
		}

		//获取树控件
		mcus_treeCtrl = &GetTreeCtrl();
		mcus_treeCtrl->SetImageList(&mcus_imageList, TVSIL_NORMAL);

		//2.树控件设置节点 CTreeCtrl::InsertItem
		mcus_treeCtrl->InsertItem(TEXT("Current Login : Customer"), 0, 0, NULL);
		mcus_treeCtrl->InsertItem(TEXT("车辆信息查询"), 1, 1, NULL);
		mcus_treeCtrl->InsertItem(TEXT("单程车票购买"), 2, 2, NULL);
		mcus_treeCtrl->InsertItem(TEXT("申请车票退改"), 3, 3, NULL);
		mcus_treeCtrl->InsertItem(TEXT("退出顾客账号"), 4, 4, NULL);
		mcus_treeCtrl->InsertItem(TEXT("退出顾客系统"), 5, 5, NULL);
	}
}


void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//可以在这里查询信息接口位置
	if (USER_IS_ADMIN) {
		//获取当前节点选中项目 CTreeCtrl::GetSelectedItem
		HTREEITEM item = madm_treeCtrl->GetSelectedItem();

		//获取选中项的文本内容 CTreeCtrl::GetItemText
		CString str = madm_treeCtrl->GetItemText(item);
		//MessageBox(str);

		//需要包含框架类头文件#include "MainFrm.h" [wjy]
		//CWnd::PostMessage 将一个消息放入窗口的消息队列
		//AfxGetMainWnd()：框架窗口对象的指针
		//AfxGetMainWnd()->GetSafeHwnd()：获取返回窗口的句柄，CWnd::GetSafeHwnd
		//NM_A：发送自定义消息
		//(WPARAM)NM_A：指定了附加的消息信息
		//(LPARAM)0：指定了附加的消息信息，此参数这里没有意义
		if (str == TEXT("Current Login : Administrator")){
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADM_A, (WPARAM)NM_ADM_A, (LPARAM)0);
		}
		else if (str == TEXT("管理员个人中心")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADM_B, (WPARAM)NM_ADM_B, (LPARAM)0);
		}
		else if (str == TEXT("增加单车次信息")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADM_C, (WPARAM)NM_ADM_C, (LPARAM)0);
		}
		else if (str == TEXT("全车次一键查询")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADM_D, (WPARAM)NM_ADM_D, (LPARAM)0);
		}
		else if (str == TEXT("部分车信息查询")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADM_E, (WPARAM)NM_ADM_E, (LPARAM)0);
		}
		else if (str == TEXT("注销指定单车次")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADM_F, (WPARAM)NM_ADM_F, (LPARAM)0);
		}
		else if (str == TEXT("退出管理员账号")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADM_G, (WPARAM)NM_ADM_G, (LPARAM)0);
		}
		else if (str == TEXT("退出管理员系统")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADM_H, (WPARAM)NM_ADM_H, (LPARAM)0);
		}
	}
	if (!USER_IS_ADMIN) {
		//获取当前节点选中项目 CTreeCtrl::GetSelectedItem
		HTREEITEM item = mcus_treeCtrl->GetSelectedItem();

		//获取选中项的文本内容 CTreeCtrl::GetItemText
		CString str = mcus_treeCtrl->GetItemText(item);
		//MessageBox(str);

		if (str == TEXT("Current Login : Customer")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_CUS_A, (WPARAM)NM_CUS_A, (LPARAM)0);
		}
		else if (str == TEXT("车辆信息查询")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_CUS_B, (WPARAM)NM_CUS_B, (LPARAM)0);
		}
		else if (str == TEXT("单程车票购买")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_CUS_C, (WPARAM)NM_CUS_C, (LPARAM)0);
		}
		else if (str == TEXT("申请车票退改")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_CUS_D, (WPARAM)NM_CUS_D, (LPARAM)0);
		}
		else if (str == TEXT("退出顾客账号")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_CUS_E, (WPARAM)NM_CUS_E, (LPARAM)0);
		}
		else if (str == TEXT("退出顾客系统")) {
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_CUS_F, (WPARAM)NM_CUS_F, (LPARAM)0);
		}
	}
}
