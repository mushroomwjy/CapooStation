#pragma once



// CCusSearch 窗体视图

class CCusSearch : public CFormView
{
	DECLARE_DYNCREATE(CCusSearch)

protected:
	CCusSearch();           // 动态创建所使用的受保护的构造函数
	virtual ~CCusSearch();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_CUS_SEARCH };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_cussearch_search;
	CComboBox m_cussearch_find;
	CListCtrl m_cussearch_list;
	CString m_cussearch_cid;
	CString m_cussearch_starter;
	double m_cussearch_drtime;
	int m_cussearch_people;
	CString m_cussearch_avail;
	int m_cussearch_hour;
	int m_cussearch_minute;
	CString m_cussearch_desti;
	int m_cussearch_price;
	int m_cussearch_sold;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo3();
};


