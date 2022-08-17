
// list_control_exDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "list_control_ex.h"
#include "list_control_exDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ClistcontrolexDlg 对话框



ClistcontrolexDlg::ClistcontrolexDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIST_CONTROL_EX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ClistcontrolexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ClistcontrolexDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// ClistcontrolexDlg 消息处理程序

BOOL ClistcontrolexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	
	scroll = new ScrollWnd(0, 0, 700, 500, RGB(255, 255, 255), this);
	ScrollBar* bar = new ScrollBar(270, 0, 30, 500, 25, RGB(0, 0, 0), RGB(255, 255, 255), scroll);
	scroll->setScrollBar(bar);
	CButton* btn;
	CString str;

	for (int i = 0; i < 20; i++)
	{
		str.Format(_T("bt%d"), i);
		for (int j = 0; j < 9; j++)
		{
			btn = new CButton();
			btn->Create(str,
			WS_CHILD | WS_VISIBLE,
			CRect(0, 0, 60, 50),
			scroll,
			0);
			scroll->addWidget(i, j, btn);
		}	
		
		scroll->m_cur_head_y += 50;
	}
	
	scroll->removeWidget(1, 1);
	/*for (int i = 0; i < 20; i++)
	{
		scroll->m_cur_head_y -= 50;
	}
	scroll->updateLayout();*/
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void ClistcontrolexDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR ClistcontrolexDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//BOOL ClistcontrolexDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// TODO: Add your message handler code here and/or call default
//	/*int x = zDelta / WHEEL_DELTA;
//	this->scroll->m_cur_head_y -= x * 10;
//	scroll->updateLayout();*/
//	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
//}
