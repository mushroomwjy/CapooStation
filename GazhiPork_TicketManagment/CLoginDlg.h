#pragma once
#include "afxdialogex.h"


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_user;
	CString m_pwd;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnClose();
private:
	CStatic mlogin_pic;
	virtual void OnCancel();
public:
	afx_msg void OnBnHotItemChangeButton3(NMHDR* pNMHDR, LRESULT* pResult);
private:
//	CButton m_loginexit;
//	CString m_loginexit;
	CButton m_loginexit;
public:
	afx_msg void OnBnHotItemChangeButton2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnHotItemChangeButton1(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CButton m_customer_login;
	CButton m_admin_login;
public:
//	afx_msg void OnEnChangeEdit2();
//	afx_msg void OnBnClickedCheck1();
private:
//	CButton m_passwordcheck;
public:
//	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedCheck1();
private:
	CButton m_showpsw;
};
