#pragma once
//这一个头文件必须加上才可使用CTreeView[wjy]
#include <afxcview.h>

// CSelectView 视图

class CSelectView : public CTreeView
{
	DECLARE_DYNCREATE(CSelectView)

protected:
	CSelectView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSelectView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP();
private:
	CTreeCtrl* madm_treeCtrl;	//树控件
	CImageList madm_imageList;	//图标列表
	CTreeCtrl* mcus_treeCtrl;	//树控件
	CImageList mcus_imageList;	//图标列表
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
};


