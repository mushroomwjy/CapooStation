#pragma once



// CCusDeltic 窗体视图

class CCusDeltic : public CFormView
{
	DECLARE_DYNCREATE(CCusDeltic)

protected:
	CCusDeltic();           // 动态创建所使用的受保护的构造函数
	virtual ~CCusDeltic();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_CUS_DELTIC };
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
	CComboBox m_cusdel_search;
	CString m_cusdel_runstatic;
	CString m_cusdel_cid;
	int m_cusdel_hour;
	int m_cusdel_minute;
	CString m_cusdel_starter;
	CString m_cusdel_desti;
	double m_cusdel_drtime;
	int m_cusdel_price;
	int m_cusdel_people;
	int m_cusdel_sold;
	CString m_cusdel_delstatus;
	int m_cusdel_delnum;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton1();
};


