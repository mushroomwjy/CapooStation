#pragma once



// CAdmUserDlg 窗体视图

class CAdmUserDlg : public CFormView
{
	DECLARE_DYNCREATE(CAdmUserDlg)

protected: 
	CAdmUserDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdmUserDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADM_USER };
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
	CString m_adm_user;
	CString m_adm_name;
public:
	CString m_adm_newpwd;
private:
	CString m_adm_rightpwd;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};


