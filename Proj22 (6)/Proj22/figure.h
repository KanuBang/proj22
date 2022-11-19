#pragma once
#include <iostream>
#include "Windows.h"
class Figure {
public:
	Figure() {}
	int startx, starty, endx, endy;
	Figure(int sx, int sy, int ex, int ey):startx(sx), starty(sy), endx(ex), endy(ey) {
	}
	virtual void draw(HDC hdc) {
	}
};

Figure* my[100];
int numFigure = 0;

class Rect :public Figure {
public:
	Rect(int sx, int sy, int ex, int ey) :Figure(sx, sy, ex, ey) {
		startx = sx;
		starty = sy;
		endx = ex;
		endy = ey;
	}
	void draw(HDC hdc) {
		HDC h = hdc;
		//OutputDebugString(L"Lvent\n");
		Rectangle(h, startx, starty, endx, endy);
	}
};
class elli :public Figure {
public:
	elli(int sx, int sy, int ex, int ey) :Figure(sx, sy, ex, ey) {
		startx = sx;
		starty = sy;
		endx = ex;
		endy = ey;
	}
	void draw(HDC hdc) {
		HDC h = hdc;
		//OutputDebugString(L"Rvent\n");
		Ellipse(h, startx, starty, endx, endy);

	}
};

class line :public Figure {
public:
	line(int sx, int sy, int ex, int ey) :Figure(sx, sy, ex, ey) {
		startx = sx;
		starty = sy;
		endx = ex;
		endy = ey;
	}
	void draw(HDC hdc) {
		HDC h = hdc;
		//OutputDebugString(L"Rvent\n");
		MoveToEx(h, startx, starty, NULL);
		LineTo(h, endx, endy);

	}
};