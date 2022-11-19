#pragma once
#include "Windows.h"
#include <string>
#include <list>
#include "Misc.h"
//#include "MButton.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class MButton;
class Frame {
protected:
	// Window ���α׷����� ���� �⺻ �������̴�. �ǵ帮�� �ʴ´�.
	HINSTANCE hInst_;
	HWND hWnd_;	 // ���� �ڵ��� �����صд�.
	HDC hDC_;    // �� ������ �־�� �׸��� �׸� �� �ִ�.

	// ������ ���� �ʿ��� ����
	MButton* buttons_[100];
	int numButtons = 0;
	static const int FIG_NONE = 0;
	static const int FIG_RECT = 1;
	static const int FIG_ELLI = 2;
	static const int FIG_LINE = 3;
	MPoint start_;
	MPoint end_;
	int figType_ = FIG_NONE;
public:
	Frame();
	Frame(std::wstring, int, int);
	virtual void run();
	virtual void eventHandler(MEvent e);
	virtual void repaint();
	void invalidate();


	virtual void initialize();
	void addButton(MButton*);
	void drawButtons();
	//MButton* findButton(MPoint);
	void setFigType(int t)
	{
		figType_ = t;
	};
};