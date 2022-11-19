#pragma once
#include <string>
#include "Windows.h"
#include "Misc.h"
#include "frame.h"


class MButton {
public:
	MButton(std::string s, int x, int y, int width, int height);
	MButton();
	bool includes(int x, int y); 
	// 마우스 클릭 했을 때 그 위치가 버튼의 위치에 들어있는 위치인지
	bool includes(MPoint p);
	void setX(int x); // X값 변경 => 버튼 배치
	int getHeight(); // 엑세서
	int getWidth(); //
	void draw(HDC); // 그림 그리기
	void onClick() {
		OutputDebugStringA(text_.c_str());
		frame->setFigType(this->command);
	}// find에서 찾아지면
	void setFrame(Frame* f) {
		frame = f;
	}

	static const int default_width = 100; // 크기 지정
	static const int default_height = 30; // 크기 지정

	int x_, y_, width_, height_;
	std::string text_;
	Frame* frame; 
	// 버튼과 프레임이 서로 교환
	int command = 0;
	void setCommand(int cmd) {
		command = cmd;
	}
};

