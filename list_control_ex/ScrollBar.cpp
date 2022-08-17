// ScrollBar.cpp : implementation file
//

#include "pch.h"
#include "list_control_ex.h"
#include "ScrollBar.h"
#include "ScrollWnd.h"

// ScrollBar

IMPLEMENT_DYNAMIC(ScrollBar, CWnd)

ScrollBar::ScrollBar(int x, int y, int wnd_width, int wnd_height, int width, COLORREF bgcolor, COLORREF barcolor, CWnd* parent)
	:CWnd(),
	m_wnd_width(wnd_width),
	m_wnd_height(wnd_height),
	m_width(width),
	m_height(0),
	m_bgcolor(bgcolor),
	m_barcolor(barcolor)
{
	m_btn_fixed_width = m_wnd_width;
	m_btn_fixed_height = m_btn_fixed_width;
	CString s_wzClassName("ScrollBarYh");
	HINSTANCE hInstance = ::AfxGetInstanceHandle();
	WNDPROC wndProc = ::AfxGetAfxWndProc();
	WNDCLASS wc = {};
	wc.lpfnWndProc = wndProc;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(GetStockObject(NULL_BRUSH));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = s_wzClassName;
	RegisterClass(&wc);

	if (!Create(s_wzClassName, _T(""),  WS_VISIBLE, CRect(x, y, x + m_wnd_width, x + m_wnd_height), parent, 0))
	{
		CString str;
		str.Format(_T("%d"), GetLastError());
		MessageBox(_T("Failed to create ScrollBar! error code: " + str));
	}
	initControl();

}

ScrollBar::~ScrollBar()
{
	delete m_dw_arrow_btn;
	delete m_up_arrow_btn;
}


BEGIN_MESSAGE_MAP(ScrollBar, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// ScrollBar message handlers



void ScrollBar::initControl()
{
	this->m_dw_arrow_btn = new CButton();
	this->m_up_arrow_btn = new CButton();
	this->m_dw_arrow_btn->Create(_T("bt2"), 
		WS_CHILD | WS_VISIBLE,
		CRect(0, m_wnd_height - m_btn_fixed_height, m_btn_fixed_width, m_wnd_height), 
		this,
		IDC_BTN_DW);
	this->m_up_arrow_btn->Create(_T("bt1"),
		WS_CHILD | WS_VISIBLE,
		CRect(0, 0, m_btn_fixed_width, m_btn_fixed_height),
		this,
		IDC_BTN_UP);
	m_dw_arrow_btn->SetParent(this);
	m_up_arrow_btn->SetParent(this);
	m_dw_arrow_btn->SetWindowText(_T("dw"));
	m_up_arrow_btn->SetWindowText(_T("up"));
	m_dw_arrow_btn->ShowWindow(SW_SHOW);
	m_up_arrow_btn->ShowWindow(SW_SHOW);
}

void ScrollBar::setWidth(int width)
{
	this->m_width = width;
}

void ScrollBar::setHeight(int height)
{
	this->m_height = height;
}

void ScrollBar::setWndWidth(int wnd_width)
{
	this->m_wnd_width = wnd_width;
}

void ScrollBar::setWndHeight(int wnd_height)
{
	this->m_wnd_width = wnd_height;
}

void ScrollBar::setStX(int x)
{
	this->_st_x = x;
}

void ScrollBar::setStY(int y)
{
	this->_st_y = y + m_btn_fixed_height;
}

void ScrollBar::setBgColor(COLORREF bgcolor)
{
	this->m_bgcolor = bgcolor;
}

void ScrollBar::setBarColor(COLORREF barcolor)
{
	this->m_barcolor = barcolor;
}

void ScrollBar::setX(int x)
{
	this->x = x;
}

void ScrollBar::setY(int y)
{
	this->y = y;
}


void ScrollBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	dc.FillRect(CRect(0, m_btn_fixed_height, 0 + m_wnd_width, m_btn_fixed_height + (m_wnd_height - m_btn_fixed_height * 2)), &CBrush(m_bgcolor));
	_st_x = (m_wnd_width - m_width) / 2 + 1;
	dc.FillRect(CRect(_st_x, _st_y, _st_x + m_width, _st_y + m_height),&CBrush(m_barcolor));
}


BOOL ScrollBar::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	/*MessageBox(_T("ScrollTrack"), 0, 0);*/
	int x = zDelta / WHEEL_DELTA;
	//	str.Format(_T("%d"), x);
	((ScrollWnd*)this->GetParent())->m_cur_head_y -= x * 10;
	((ScrollWnd*)this->GetParent())->updateLayout();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
