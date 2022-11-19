#pragma once
#include "Windows.h"

// 화면상의 점을 나타내는 클래스.
class MPoint {
public:
	int x_, y_;
	MPoint(int x, int y);
	MPoint();
};

// 이벤트를 클래스화 한다.
class MEvent {
private:
	UINT msg_;
	WPARAM wParam_;
	LPARAM lParam_;
public:
	// 처리
	//
	MEvent(UINT msg, WPARAM wParam, LPARAM lParam);
	bool isLButtonDownEvent();
	//bool isLButtonDownEvent(); 이거인지 어떻게 아냐?
	//ppt에 있다
	bool isLButtonUpEvent();
	bool isRButtonDownEvent();
	bool isRButtonUpEvent();
	//bool isCtrlKeyDown();
	//bool isShiftKeyDown();
	
	int getX() {
		return LOWORD(lParam_);
	}
	int getY() {
		return HIWORD(lParam_);
	}

	MPoint getPoint() {
		static int x;
		static int y;
		x = getX();
		y = getY();
		MPoint* a = new MPoint(x, y);
		return *a;
	}

};
