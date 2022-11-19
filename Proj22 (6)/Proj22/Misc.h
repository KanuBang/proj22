#pragma once
#include "Windows.h"

// ȭ����� ���� ��Ÿ���� Ŭ����.
class MPoint {
public:
	int x_, y_;
	MPoint(int x, int y);
	MPoint();
};

// �̺�Ʈ�� Ŭ����ȭ �Ѵ�.
class MEvent {
private:
	UINT msg_;
	WPARAM wParam_;
	LPARAM lParam_;
public:
	// ó��
	//
	MEvent(UINT msg, WPARAM wParam, LPARAM lParam);
	bool isLButtonDownEvent();
	//bool isLButtonDownEvent(); �̰����� ��� �Ƴ�?
	//ppt�� �ִ�
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
