#pragma once



// CAdmSearch 窗体视图

class CAdmSearch : public CFormView
{
	DECLARE_DYNCREATE(CAdmSearch)

protected:
	CAdmSearch();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdmSearch();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADM_SEARCH };
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
	CComboBox m_admsearch_search;
	CString m_admsearch_cid;
	CString m_admsearch_starter;
	double m_admsearch_drtime;
	int m_admsearch_people;
	int m_admsearch_hour;
	int m_admsearch_minute;
	CString m_admsearch_desti;
	int m_admsearch_price;
	int m_admsearch_sold;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
private:
	CComboBox m_admsearch_find;
	CListCtrl m_admsearch_list;
public:
	afx_msg void OnCbnSelchangeCombo3();
private:
	CString m_admsearch_avail;
};


