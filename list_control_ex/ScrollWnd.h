#pragma once


// ScrollWindow
#include "ScrollBar.h"
class ScrollWnd : public CWnd
{
	DECLARE_DYNAMIC(ScrollWnd)
	
public:
	ScrollWnd(int x, int y, int width, int height, COLORREF bgcolor,CWnd* parent = nullptr);
	virtual ~ScrollWnd();

	vector<vector<CWnd*>>* m_units;
	int m_unit_width; //assigned by scroll it self, maybe user can set it in later
	int m_unit_height;
	ScrollBar* m_scrollbar;

	int x;
	int y;
	int width;
	int height;
	COLORREF m_bgcolor;
public:
	bool addWidget(int row, int col, CWnd* widget);
	bool removeWidget(int row, int col);
	bool updateWidget(int row, int col, CWnd* widget);
	void setWidth(int x);
	void setHeight(int y);
	void SetSize(int x, int y);
	void setColor(COLORREF bgColor);
	void setScrollBar(ScrollBar* bar); //add a scroll bar to this 
	void updateChildWnd();
	void ShowScrollBar(bool isshow);
	void updateLayout();// used to update scroll content, the first entry to update layout of window
	void showDisplayArea(UINT isshow);
	void updateDisplayArea();
	void updateScrollBar();
public:
	int m_display_rows;
	int m_cur_head_y;
	int m_st_row; //row index
	int m_ed_row;
	int m_st_display_y;
	//int m_ed_display_y;
	void styDisplayCalculate();// used to calculate the rows need to display

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


