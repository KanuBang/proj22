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
	// ���콺 Ŭ�� ���� �� �� ��ġ�� ��ư�� ��ġ�� ����ִ� ��ġ����
	bool includes(MPoint p);
	void setX(int x); // X�� ���� => ��ư ��ġ
	int getHeight(); // ������
	int getWidth(); //
	void draw(HDC); // �׸� �׸���
	void onClick() {
		OutputDebugStringA(text_.c_str());
		frame->setFigType(this->command);
	}// find���� ã������
	void setFrame(Frame* f) {
		frame = f;
	}

	static const int default_width = 100; // ũ�� ����
	static const int default_height = 30; // ũ�� ����

	int x_, y_, width_, height_;
	std::string text_;
	Frame* frame; 
	// ��ư�� �������� ���� ��ȯ
	int command = 0;
	void setCommand(int cmd) {
		command = cmd;
	}
};

