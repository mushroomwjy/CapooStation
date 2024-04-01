#pragma once



// CAdmDelbus 窗体视图

class CAdmDelbus : public CFormView
{
	DECLARE_DYNCREATE(CAdmDelbus)

protected:
	CAdmDelbus();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdmDelbus();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADM_DELBUS };
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
	// 被查询车次号
//	CString m_admdelbus_search;
	// 宝宝巴士号
	CString m_admdelbus_cid;
	// 始发站
	CString m_admdelbus_starter;
	// 车程小时
	double m_admdelbus_drtime;
	// 额定载量
	int m_admdelbus_people;
	// 出发小时
	int m_admdelbus_hour;
	// 出发分钟
	int m_admdelbus_minute;
	// 目的地
	CString m_admdelbus_desti;
	// 票价
	int m_admdelbus_price;
	// 已售票数
	int m_admdelbus_sold;
	// 查找车次
	// 查找车次
	CComboBox m_admdelbus_search;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo2();
//	afx_msg void OnEditchangeCombo2();
	afx_msg void OnBnClickedButton1();
};


