#pragma once



// CAdmAllmsg 窗体视图

class CAdmAllmsg : public CFormView
{
	DECLARE_DYNCREATE(CAdmAllmsg)

protected:
	CAdmAllmsg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdmAllmsg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADM_ALLMSG };
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
	virtual void OnInitialUpdate();
private:
	CListCtrl m_admallmsg_list;
};


