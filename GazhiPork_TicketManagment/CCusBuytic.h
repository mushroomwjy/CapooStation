#pragma once



// CCusBuytic 窗体视图

class CCusBuytic : public CFormView
{
	DECLARE_DYNCREATE(CCusBuytic)

protected:
	CCusBuytic();           // 动态创建所使用的受保护的构造函数
	virtual ~CCusBuytic();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_CUS_BUYTIC };
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
public:
//	virtual void OnInitialUpdate();
private:
	CComboBox m_cusbuy_search;
	CString m_cusbuy_runstatic;
	CString m_cusbuy_cid;
	int m_cusbuy_hour;
	int m_cusbuy_minute;
	CString m_cusbuy_starter;
	CString m_cusbuy_desti;
	double m_cusbuy_drtime;
	int m_cusbuy_price;
	int m_cusbuy_people;
	int m_cusbuy_sold;
	CString m_cusbuy_buystatus;
public:
	int m_cusbuy_buynum;
	afx_msg void OnCbnSelchangeCombo2();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();
};


