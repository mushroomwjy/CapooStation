#pragma once



// CAdmWelcome 窗体视图

class CAdmWelcome : public CFormView
{
	DECLARE_DYNCREATE(CAdmWelcome)

protected:
	CAdmWelcome();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdmWelcome();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADM_WELCOME };
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
};


