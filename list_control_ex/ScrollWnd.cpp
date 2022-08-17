// ScrollWindow.cpp : implementation file
//

#include "pch.h"
#include "list_control_ex.h"
#include "ScrollWnd.h"


// ScrollWindow
#define UNIT_WIDTH 70
#define UNIT_HEIGHT 50
IMPLEMENT_DYNAMIC(ScrollWnd, CWnd)


ScrollWnd::ScrollWnd(int x, int y, int width, int height, COLORREF bgcolor,CWnd* parent)
	:CWnd()
	,m_bgcolor(bgcolor),m_units(nullptr),m_scrollbar(nullptr)
	,x(x),y(y),width(width),height(height)
	,m_unit_width(UNIT_WIDTH)
	,m_unit_height(UNIT_HEIGHT)
	,m_cur_head_y(0),m_st_row(-1),m_ed_row(-1)

{
	
	CString s_wzClassName("ScrollWndYh");
	HINSTANCE hInstance = ::AfxGetInstanceHandle();
	WNDPROC wndProc = ::AfxGetAfxWndProc();
	WNDCLASS wc = {};
	wc.lpfnWndProc = wndProc;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(bgcolor));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = s_wzClassName;
	RegisterClass(&wc);

	if (!Create(s_wzClassName, _T(""),  WS_VISIBLE,
		CRect(x, y, x + width, y + height),parent, 0))
	{
		CString str;
		str.Format(_T("%d"), GetLastError());
		MessageBox(_T("Failed to create ScrollWnd! error code: " + str));
	}
	//SetLayeredWindowAttributes(0, (255 * 70) / 100, LWA_ALPHA);
	if (!m_units)
		m_units = new vector<vector<CWnd*>>;
	ShowWindow(SW_SHOW);
	
	
}

ScrollWnd::~ScrollWnd()
{
	if (m_units)
	{
		for (int i = 0; i < m_units->size(); i++)
		{
			for (int j = 0; j < m_units[i].size(); j++)
			{
				delete m_units->operator[](i)[j];
			}
		}
		delete m_units;
		m_units = nullptr;
	}

	if (m_scrollbar)
	{
		delete m_scrollbar;
	}
}


BEGIN_MESSAGE_MAP(ScrollWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
//	ON_WM_MOUSEHWHEEL()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_MOUSEHOVER()
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// ScrollWindow message handlers




void ScrollWnd::styDisplayCalculate()
{
	
	CRect rect;
	GetClientRect(rect);
	int width = rect.Width();
	int height = rect.Height();
	int total_height = m_units->size() * m_unit_height;
	if (height < total_height) //need to show the scroll bar
	{
		if (m_cur_head_y + height > total_height)
		{
			m_cur_head_y = total_height - height;
		}
		else if (m_cur_head_y < 0)
		{
			m_cur_head_y = 0;
		}
	}
	m_display_rows = height / this->m_unit_height;
	m_st_row = m_cur_head_y / m_unit_height;
	m_st_display_y = m_cur_head_y % m_unit_height;
	m_ed_row = m_st_row + m_display_rows;
	if (m_ed_row >= m_units->size()) m_ed_row = m_units->size() - 1;
	
}

void ScrollWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	CRect rect;
	GetClientRect(rect);
	dc.FillRect(rect,&CBrush(m_bgcolor));
}


void ScrollWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}

bool ScrollWnd::addWidget(int row, int col, CWnd* widget)//first 0x009be588
{
	bool is_row_add = false;
	
	if (!m_units)
	{
		MessageBox(_T("Failed to create m_units object!"));
		return false;
	}
	if (row < 0 || col < 0 || widget == nullptr)
	{
		MessageBox(_T("Failed to create unit because of error parameter!"));
		return false;
	}

	if (row >= m_units->size()) //overbound current row
	{
		is_row_add = true;
		while (m_units->size() <= row)
		{
			m_units->push_back(vector<CWnd*>());
		}
	}
	//overbound current column
	while (m_units->at(row).size() <= col)
	{
		m_units->at(row).push_back(nullptr);
	}
	//execute insertion
	widget->SetParent(this);
	widget->ShowWindow(SW_HIDE);
	m_units->at(row)[col] = widget;
	
//update layout
	updateLayout();
	return true;
}

bool ScrollWnd::removeWidget(int row, int col)
{
	if (row < 0 || col < 0 || row >= m_units->size() /*|| col >= m_units->at(row).size()*/)
	{
		MessageBox(_T("Failed to remove unit because of error parameter!"));
		return false;
	}
	vector<CWnd*>& the_row = m_units->at(row);
	auto _st = the_row.begin()+ col;
	RECT rect;
	::GetWindowRect(((CWnd*)(*_st))->m_hWnd, &rect);
	delete* _st;
	*_st = nullptr;
	m_units->at(row).erase(_st);
	
	if (m_units->at(row).size() == 0)
	{
		auto __st = m_units->begin() + row;
		m_units->erase(__st);
	}
	//update layout
	//todo
	updateLayout();
	return true;
}

bool ScrollWnd::updateWidget(int row, int col, CWnd* widget)
{
	if (row < 0 || col < 0 || row >= m_units->size() || col >= m_units->at(row).size())
	{
		MessageBox(_T("Failed to update unit because of error parameter!"));
		return false;
	}
	delete m_units->at(row)[col];
	m_units->at(row)[col] = widget;
	updateLayout();
	return true;
}

void ScrollWnd::setWidth(int width)
{
	this->width = width;
}

void ScrollWnd::setHeight(int height)
{
	this->height = height;
}

void ScrollWnd::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void ScrollWnd::setColor(COLORREF bgColor)
{
	this->m_bgcolor = bgColor;
}

void ScrollWnd::setScrollBar(ScrollBar* bar)
{
	this->m_scrollbar = bar;
	this->m_scrollbar->SetWindowPos(0, this->width - m_scrollbar->m_wnd_width, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	ShowScrollBar(false);
}

void ScrollWnd::updateChildWnd() /*deprecated*/
{
	m_scrollbar->setStY(0);
	m_scrollbar->setHeight(30);
	::PostMessage(m_scrollbar->m_hWnd, WM_PAINT, 0, 0);
}

void ScrollWnd::ShowScrollBar(bool isshow)
{
	if (isshow)
	{
		this->m_scrollbar->ShowWindow(SW_SHOW);
		m_scrollbar->isshow = true;
	}
	else {
		this->m_scrollbar->ShowWindow(SW_HIDE);
		m_scrollbar->isshow = false;
	}
}

void ScrollWnd::updateLayout()
{
	CRect rect;
	this->GetWindowRect(rect);
	float height = (float)rect.Height(); // page height
	float total_height = (float)m_units->size() * m_unit_height;//content height

	//showDisplayArea(SW_HIDE);
	styDisplayCalculate();
	updateDisplayArea();//errror!!!!!!!!!!!!
	if (total_height < height)
	{
		ShowScrollBar(false);
	}
	else
	{
		updateScrollBar();
		ShowScrollBar(true);
	}
	showDisplayArea(SW_SHOW);
}

void ScrollWnd::showDisplayArea(UINT isshow)
{
	if (m_st_row == -1 || m_ed_row == -1) return;
	for (int i = m_st_row; i <= m_ed_row; i++)
	{
		for (int j = 0; j < m_units->at(i).size(); j++)
		{
			m_units->at(i)[j]->ShowWindow(isshow);
		}
	}
}

void ScrollWnd::updateDisplayArea()
{
	/*vector<CWnd*>& rows = m_units->at(m_st_row);
	for (int i = 0; i < rows.size(); i++)
	{
		rows[i]->SetWindowPos(0, x, 0 - m_st_display_y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
	int offset = ;*/
	int dis_row = 0;
	//vector<CWnd*>& cols = m_units->at(m_st_row);
	
	for (int i = m_st_row; i <= m_ed_row; i++, dis_row++)
	{	
		for (int j = 0; j < m_units->at(i).size(); j++)
		{
			/*int x = j * m_unit_width;
			int y = dis_row * m_unit_height - m_st_display_y;
			CString str;
			str.Format(_T("x: %d, y: %d"), x, y);
			MessageBox(str);*/
			m_units->at(i)[j]->SetWindowPos(0, j * m_unit_width, dis_row * m_unit_height - m_st_display_y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		}
	}
	//int last_row_offset = m_st_display_y;
}

void ScrollWnd::updateScrollBar()
{
	CRect rect;
	this->GetWindowRect(rect);
	float height =(float) rect.Height(); // page height
	float total_height = (float)m_units->size() * m_unit_height;//content height
	float ratio_scroll = height / total_height;
	float ratio_ball = (float)m_cur_head_y / total_height;
	float fixed_height = this->m_scrollbar->m_wnd_height - 2. * this->m_scrollbar->m_btn_fixed_height;
	float height_scroll = fixed_height  * ratio_scroll;
	float start_ball = fixed_height * ratio_ball;

	m_scrollbar->setStY(start_ball);
	m_scrollbar->setHeight(height_scroll);
	m_scrollbar->InvalidateRect(NULL);
	::SendMessage(m_scrollbar->m_hWnd, WM_PAINT, 0, 0);
}


//void ScrollWnd::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// This feature requires Windows Vista or greater.
//	// The symbol _WIN32_WINNT must be >= 0x0600.
//	// TODO: Add your message handler code here and/or call default
//	CString str;
//	int x = zDelta / WHEEL_DELTA;
//	str.Format(_T("%d"), x);
//	MessageBox(_T("ScrollWnd"), 0, 0);
//	
//	this->m_cur_head_y -= x * 10;
//	updateLayout();
//	
//	CWnd::OnMouseHWheel(nFlags, zDelta, pt);
//}

//void ScrollWnd::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//	CWnd::OnLButtonDown(nFlags, point);
//}


//void ScrollWnd::OnMouseHover(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//	
//	CWnd::OnMouseHover(nFlags, point);
//}


BOOL ScrollWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	int x = zDelta / WHEEL_DELTA;
	str.Format(_T("%d"), x);
	this->m_cur_head_y -= x * 10;
	updateLayout();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
