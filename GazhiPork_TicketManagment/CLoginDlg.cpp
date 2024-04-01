// CLoginDlg.cpp: 实现文件

#include "pch.h"
#include "GazhiPork_TicketManagment.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"
#include "GlobalData.h"
#include "InfoFile.h"
#include "resource.h"
#include <WinUser.h>

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Control(pDX, IDC_PIC, mlogin_pic);
	//  DDX_Control(pDX, IDC_BUTTON3, m_loginexit);
	//  DDX_Control(pDX, IDC_BUTTON3, m_loginexit);
	DDX_Control(pDX, IDC_BUTTON3, m_loginexit);
	DDX_Control(pDX, IDC_BUTTON2, m_customer_login);
	DDX_Control(pDX, IDC_BUTTON1, m_admin_login);
	DDX_Control(pDX, IDC_CHECK1, m_showpsw);
}



BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON3, &CLoginDlg::OnBnClickedButton3)
	ON_WM_CLOSE()
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_BUTTON3, &CLoginDlg::OnBnHotItemChangeButton3)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_BUTTON2, &CLoginDlg::OnBnHotItemChangeButton2)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_BUTTON1, &CLoginDlg::OnBnHotItemChangeButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CLoginDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

//管理员登录按钮点击事件[wjy]
void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);	//将编辑框里面的值，同步到变量里面

	if (m_user.IsEmpty() || m_pwd.IsEmpty())//判断用户名密码是否为空
	{
		MessageBox(TEXT("用户名或密码不能为空"));
		return;
	}
	//获取正确的值
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);//读取配置文件用户名密码

	if (name == m_user)	//用户名一致
	{
		if (pwd == m_pwd)	//密码一致
		{
			//关闭当前对话框
			USER_IS_ADMIN = 1;
			MessageBox(TEXT("您以管理员身份登录系统！"));
			CDialog::OnCancel();
		}
		else
		{
			USER_IS_ADMIN = 0;
			MessageBox(TEXT("用户名或密码错误"));
		}
	}
	else
	{
		USER_IS_ADMIN = 0;
		MessageBox(TEXT("用户名或密码错误"));
	}
}

//顾客登录按钮点击事件[wjy]
void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	USER_IS_ADMIN = 0;
	MessageBox(TEXT("您以顾客身份登录系统！"));
	CDialog::OnCancel();
}

void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(TEXT("您将退出车票管理系统OvO  --mushroom"));
	//exit(0);
}

//重写以增加用户名对话框初始化[wjy]
BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化

	//加载对话框初始化图标
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICO_KEY));

	//加载右侧static图片
	//设置静态控件窗口风格为位图居中显示
	mlogin_pic.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);

	//通过路径获取bitmap句柄
#define HBMP(filepath,width,height) (HBITMAP)LoadImage(AfxGetInstanceHandle(),filepath,IMAGE_BITMAP,width,height,LR_LOADFROMFILE|LR_CREATEDIBSECTION)

	//静态控件设置bitmap
	CRect rect;
	mlogin_pic.GetWindowRect(rect);
	mlogin_pic.SetBitmap(HBMP(TEXT("lock.bmp"), rect.Width(), rect.Height()));

	//设置密码框为#号
	CEdit* pmyEdit = (CEdit*)GetDlgItem(IDC_EDIT2); 
	pmyEdit->SetPasswordChar('#'); // 显示格式为星号

	// 加载用户名与密码，显性加载用户名至编辑框控件。
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	m_user = name;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//Enter跳出登录系统bug修复[wjy]
void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDialogEx::OnOK();
}

//退出按钮点击事件[wjy]
void CLoginDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(TEXT("您将退出车票管理系统OvO\n\t\t--Gazhi Pork"));
	exit(0);
}

//叉号退出车票系统&跳出登录界面bug修复[wjy]
void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CDialogEx::OnClose();
	exit(0);
}

//屏蔽ESC对应oncancel防止强制登入[wjy]
void CLoginDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDialogEx::OnCancel();
}

//热键控制：移动光标至AdminLogin按钮上时改变文字信息[wjy]
void CLoginDlg::OnBnHotItemChangeButton1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 此功能要求 Internet Explorer 6 或更高版本。
	// 符号 _WIN32_IE 必须是 >= 0x0600。
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pHotItem->dwFlags & HICF_ENTERING)
		m_admin_login.SetWindowText(TEXT("Login?  =v="));
	else  m_admin_login.SetWindowText(TEXT("Administrator  Login"));
	*pResult = 0;
}

//热键控制：移动光标至CustomerLogin按钮上时改变文字信息[wjy]
void CLoginDlg::OnBnHotItemChangeButton2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 此功能要求 Internet Explorer 6 或更高版本。
	// 符号 _WIN32_IE 必须是 >= 0x0600。
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pHotItem->dwFlags & HICF_ENTERING)
		m_customer_login.SetWindowText(TEXT("Login?  =v="));
	else  m_customer_login.SetWindowText(TEXT("Customer  Login"));
	*pResult = 0;
}

//热键控制：移动光标至Exit按钮上时改变文字信息[wjy]
void CLoginDlg::OnBnHotItemChangeButton3(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 此功能要求 Internet Explorer 6 或更高版本。
	// 符号 _WIN32_IE 必须是 >= 0x0600。
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pHotItem->dwFlags & HICF_ENTERING)
		m_loginexit.SetWindowText(TEXT("EXIT?  ToT"));
	else  m_loginexit.SetWindowText(TEXT("EXIT  OvO"));

	*pResult = 0;
}

//显示密码与否的勾选栏目[wjy]
//void CLoginDlg::OnBnClickedCheck1()
//{
	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE); // 更新控件对应变量的值
//	if (m_passwordcheck.GetCheck() == 1)
//	{
//
//	}
//	else
//	{
//
//	}
//}


//void CLoginDlg::OnEnChangeEdit2()
//{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
//}

// 若在显示密码前打勾，则密码显示为明文，默认为密文（星号）[wjy]
void CLoginDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 更新控件对应变量的值
	CEdit* pswEdit = (CEdit*)GetDlgItem(IDC_EDIT2); // 密码编辑框控件的指针
	if (m_showpsw.GetCheck() == 1)
	{
		pswEdit->SetPasswordChar(0); // 显示格式为明文
		ASSERT(!(pswEdit->GetStyle() & ES_PASSWORD));
	}
	else
	{
		pswEdit->SetPasswordChar('#'); // 显示格式为星号
	}
	//RedrawWindow更新EDIT2控件，是密文转换及时更新[wjy]
	pswEdit->RedrawWindow(NULL, NULL);
}