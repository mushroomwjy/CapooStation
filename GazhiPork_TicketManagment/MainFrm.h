
// MainFrm.h: CMainFrame 类的接口
//

#pragma once
//WM_USER+100是为了区分系统消息和用户消息，避免冲突
//自定义消息宏[wjy]
#define NM_ADM_A	(WM_USER + 100)
#define NM_ADM_B	(WM_USER + 101)
#define NM_ADM_C	(WM_USER + 102)
#define NM_ADM_D	(WM_USER + 103)
#define NM_ADM_E	(WM_USER + 104)
#define NM_ADM_F	(WM_USER + 105)
#define NM_ADM_G	(WM_USER + 106)
#define NM_ADM_H	(WM_USER + 107)

#define NM_CUS_A	(WM_USER + 108)
#define NM_CUS_B	(WM_USER + 109)
#define NM_CUS_C	(WM_USER + 110)
#define NM_CUS_D	(WM_USER + 111)
#define NM_CUS_E	(WM_USER + 112)
#define NM_CUS_F	(WM_USER + 113)


class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:


// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	CSplitterWnd m_spliter; // 切分窗口类对象[wjy]
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	//自定义消息处理函数
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
};


