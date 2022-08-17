
// list_control_exDlg.h: 头文件
//

#pragma once

#include "ScrollWnd.h"

// ClistcontrolexDlg 对话框

class ClistcontrolexDlg : public CDialogEx
{
// 构造
public:
	ClistcontrolexDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIST_CONTROL_EX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	ScrollWnd*  scroll;
public:
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
