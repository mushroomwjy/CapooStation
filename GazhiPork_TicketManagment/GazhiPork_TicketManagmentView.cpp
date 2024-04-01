
// GazhiPork_TicketManagmentView.cpp: CGazhiPorkTicketManagmentView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GazhiPork_TicketManagment.h"
#endif

#include "GazhiPork_TicketManagmentDoc.h"
#include "GazhiPork_TicketManagmentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGazhiPorkTicketManagmentView

IMPLEMENT_DYNCREATE(CGazhiPorkTicketManagmentView, CView)

BEGIN_MESSAGE_MAP(CGazhiPorkTicketManagmentView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGazhiPorkTicketManagmentView 构造/析构

CGazhiPorkTicketManagmentView::CGazhiPorkTicketManagmentView() noexcept
{
	// TODO: 在此处添加构造代码

}

CGazhiPorkTicketManagmentView::~CGazhiPorkTicketManagmentView()
{
}

BOOL CGazhiPorkTicketManagmentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGazhiPorkTicketManagmentView 绘图

void CGazhiPorkTicketManagmentView::OnDraw(CDC* /*pDC*/)
{
	CGazhiPorkTicketManagmentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGazhiPorkTicketManagmentView 打印

BOOL CGazhiPorkTicketManagmentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGazhiPorkTicketManagmentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGazhiPorkTicketManagmentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGazhiPorkTicketManagmentView 诊断

#ifdef _DEBUG
void CGazhiPorkTicketManagmentView::AssertValid() const
{
	CView::AssertValid();
}

void CGazhiPorkTicketManagmentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGazhiPorkTicketManagmentDoc* CGazhiPorkTicketManagmentView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGazhiPorkTicketManagmentDoc)));
	return (CGazhiPorkTicketManagmentDoc*)m_pDocument;
}
#endif //_DEBUG


// CGazhiPorkTicketManagmentView 消息处理程序
