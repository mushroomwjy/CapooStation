#pragma once



// CAdmAddbus 窗体视图

class CAdmAddbus : public CFormView
{
	DECLARE_DYNCREATE(CAdmAddbus)

protected:
	CAdmAddbus();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdmAddbus();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADM_ADDBUS };
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
	// 宝宝巴士[wjy]
	CString m_admaddbus_cid;
	// 发车小时
	int m_admaddbus_hour;
	// 发车分钟
	int m_admaddbus_minute;
	// 始发站
	CString m_admaddbus_starter;
	// 终点站
	CString m_admaddbus_desti;
	// 车程小时
	double m_admaddbus_drtime;
	// 票价
	int m_admaddbus_price;
	// 额定载量
	int m_admaddbus_people;
	// 已售车票
	int m_admaddbus_sold;
public:
//	virtual void OnInitialUpdate();
//	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
};


