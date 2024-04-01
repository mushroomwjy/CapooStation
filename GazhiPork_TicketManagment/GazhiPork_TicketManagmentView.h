
// GazhiPork_TicketManagmentView.h: CGazhiPorkTicketManagmentView 类的接口
//

#pragma once

class CGazhiPorkTicketManagmentView : public CView
{
protected: // 仅从序列化创建
	CGazhiPorkTicketManagmentView() noexcept;
	DECLARE_DYNCREATE(CGazhiPorkTicketManagmentView)

// 特性
public:
	CGazhiPorkTicketManagmentDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGazhiPorkTicketManagmentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GazhiPork_TicketManagmentView.cpp 中的调试版本
inline CGazhiPorkTicketManagmentDoc* CGazhiPorkTicketManagmentView::GetDocument() const
   { return reinterpret_cast<CGazhiPorkTicketManagmentDoc*>(m_pDocument); }
#endif

