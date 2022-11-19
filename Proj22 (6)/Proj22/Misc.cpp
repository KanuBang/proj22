#include "Misc.h"
#include <stdio.h>
MEvent::MEvent(UINT msg, WPARAM wParam, LPARAM lParam) :
	msg_(msg), wParam_(wParam), lParam_(lParam) 
{
	//  Nothing to do here.
}

bool MEvent::isLButtonDownEvent() {
	if (this->msg_ == WM_LBUTTONDOWN) {
		return true;
	} 
	else {
		return false;
	}
}
bool MEvent::isLButtonUpEvent() {
	if (msg_ == WM_LBUTTONUP) {
		return true;
	}
	else {
		return false;
	}
}
bool MEvent::isRButtonDownEvent() {
	if (msg_ == WM_RBUTTONDOWN) {
		return true;
	}
	else {
		return false;
	}
}
bool MEvent::isRButtonUpEvent() {
	if (msg_ == WM_RBUTTONUP) {
		return true;
	}
	else {
		return false;
	}
}


MPoint::MPoint(int x, int y): x_(x), y_(y){

}

MPoint::MPoint() : x_(0), y_(0) {

}