#pragma once


// ScrollBar
class ScrollWnd;
class ScrollBar : public CWnd
{
	DECLARE_DYNAMIC(ScrollBar)
	int m_btn_fixed_width = 30;
	int m_btn_fixed_height = 30;
public:
	ScrollBar(int x, int y, int wnd_width, int wnd_height, int width, COLORREF bgcolor, COLORREF barcolor, CWnd* parent = nullptr);
	virtual ~ScrollBar();

	int m_wnd_width;//scroll bar wnd width
	int m_wnd_height;
	int m_width; //scroll bar width
	int m_height;
	
	int x;
	int y;
	int _st_x;// the x start position of long piece
	int _st_y;// the y start position of long piece
	COLORREF m_bgcolor;
	COLORREF m_barcolor;
	CButton* m_up_arrow_btn;
	CButton* m_dw_arrow_btn;

	bool isupmost;
	bool isdown;
	bool isshow;
public:
	void initControl();
	void setWidth(int width);
	void setHeight(int height);
	void setWndWidth(int wnd_width);
	void setWndHeight(int wnd_height);
	void setStX(int x);
	void setStY(int y);
	void setBgColor(COLORREF bgcolor);
	void setBarColor(COLORREF barcolor);
	void setX(int x);
	void setY(int y);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


