#include "frame.h"
#include "Misc.h"
#include "figure.h"
#include <iostream>
#include "MButton.h"

// ��¿ �� ���� ���� ���� 1���� ����Ѵ�.
Frame* theFrame = nullptr;
class MButton;
// �����Լ��δ� ���� �޽��� ó�� �Լ��� �ִ�.
LRESULT CALLBACK WndProc(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_SIZE:
		if (theFrame != nullptr)
			theFrame->eventHandler(MEvent(Msg, wParam, lParam));
		// ��� �̺�Ʈ�� eventHandler���� ó���Ѵ�.
		// MEvent�� �̺�Ʈ�� Ŭ����ȭ �� ��
		// ���� ���콺 Ŭ���� �ϸ� �װ��� MEvent�� ����
		// �� MEvent�� eventHandler�Լ��� ����.
		// �׸��� �� �̺�Ʈ�� ó���Ѵ�.
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Hw, &ps);
		//Rectangle(hdc, 200, 200, 200, 200);
		// �׸��� �ڵ�� �̰ɷ� ��!
		if (theFrame != nullptr)
			theFrame->repaint();
		// ��� �׸��� ��� repaint���ٰ� �ִ´�

		EndPaint(Hw, &ps);  // BeginPaint�� ¦�� �ȴ�

	}
	default: return DefWindowProc(Hw, Msg, wParam, lParam);
	}
}

Frame::Frame() :Frame(L"", 800, 600) {
	// ���� ������ �ʰ� ����.
	initialize();
}

//�����ڴ� �ǵ帮�� ����
Frame::Frame(std::wstring title, int width, int height) {
	hInst_ = GetModuleHandle(NULL);
	FreeConsole(); // No console
	// Register win class
	WNDCLASSEX Wc;
	Wc.cbSize = sizeof(WNDCLASSEX);
	Wc.style = CS_HREDRAW | CS_VREDRAW;
	Wc.lpfnWndProc = WndProc;
	Wc.cbClsExtra = 0;
	Wc.cbWndExtra = 0;
	Wc.hInstance = hInst_;
	Wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wc.lpszMenuName = NULL;
	Wc.lpszClassName = L"MyWin";
	Wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&Wc);

	hWnd_ = CreateWindowExW(WS_EX_TOPMOST, L"MyWIn", (WCHAR*)title.c_str(),
		WS_OVERLAPPED |
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // ���� �ּ�ȭ �ִ�ȭ ������
		WS_THICKFRAME,  // resize�� �����ϰ�
		0, 0, width, height, // x, y, width, height
		NULL, NULL, hInst_, NULL);  // Parent, Menu, instance handle, lpParam
	if (!hWnd_) throw 0;

	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_);
	SetFocus(hWnd_);
	hDC_ = GetDC(hWnd_);
	invalidate();
}

//run�� �ǵ帮�� ����
// run �Լ��� �����ϸ� ������.
void Frame::run() {
	HACCEL hAccelTable = LoadAccelerators(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));

	MSG msg;

	// �⺻ �޽��� �����Դϴ�:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void Frame::eventHandler(MEvent e)
{
	//�̺�Ʈ e�� �޴´�
	//�� �̺�Ʈ�� ���� �׼�
	// TODO: ���⿡ ���� �ڵ� �߰�.
	OutputDebugString(L"Event\n");
	std::cout << L"Event\n" << std::endl;  // ����� cmd â���� ���

	if (e.isLButtonDownEvent() || e.isRButtonDownEvent()) {
		start_ = e.getPoint();
		OutputDebugString(L"Down\n");

		for (int i = 0; i < numButtons; i++)
		{
			if (buttons_[i]->includes(start_))
				buttons_[i]->onClick();
		}

	}

	if (e.isLButtonUpEvent()) {
		end_ = e.getPoint();

		if (figType_ == 1)
		{
			my[numFigure] = new Rect(start_.x_, start_.y_, end_.x_, end_.y_);
			
		}
		if (figType_ == 2)
		{
			my[numFigure] = new elli(start_.x_, start_.y_, end_.x_, end_.y_);
		}

		if (figType_ == 3) 
		{
			my[numFigure] = new line(start_.x_, start_.y_, end_.x_, end_.y_);
		}
		if (figType_ == 0) {

		}
		numFigure++;
		invalidate();
	}
	/*
	if (e.isRButtonUpEvent()) {
		end_ = e.getPoint();
		my[numFigure] = new elli(start_.x_, start_.y_, end_.x_, end_.y_);
		numFigure++;
		invalidate();
	}
	*/
}

//�׸��� �׸��� ����Ѵ�.
//�簢���� Ÿ�� ��ü�� �׸���� ����Ѵ�.
//�簢���� draw �޼ҵ�� �ڱ� ��ġ �����ͷ� �簢���� �׸���.
//Ÿ���� draw �޼ҵ�� �ڱ� ��ġ �����ͷ� Ÿ���� �׸���.
//���� �ǰ� �迭�� ���� ��ü�鿡 ��Ų��
// for������ draw�޼ҵ带 �����Ű�� �ȴ�.

void Frame::repaint() {
	// �׷����� ��� ���� ���⿡. �Ʒ� �� ���� �����̴� �������Ѵ�.

	//Rectangle(hDC_, 100, 100, 200, 300);
	//Rectangle(hDC_, 500, 500, 700, 600);
	drawButtons();

	for (int i = 0; i < numFigure; i++) {
		my[i]->draw(hDC_);
	}
}

void Frame::invalidate() {
	// �� �޼ҵ带 �θ��� ȭ���� �ٽ� �׸��� �ȴ�.
	InvalidateRect(hWnd_, nullptr, true);
}

void Frame::initialize() {

	MButton* b1 = new MButton("�簢��", 0, 0, 100, 30);
	MButton* b2 = new MButton("Ÿ��", 100, 0, 100, 30);
	MButton* b3 = new MButton("����", 200, 0, 100, 30);
	b1->setCommand(FIG_RECT); // 1
	b2->setCommand(FIG_ELLI); // 2
	b3->setCommand(FIG_LINE); // 3
	addButton(b1);
	addButton(b2);
	addButton(b3);
}

void Frame::addButton(MButton* mbPt) {
	buttons_[numButtons] = mbPt;
	buttons_[numButtons]->frame = this;
	numButtons++;
}

void Frame::drawButtons() {
	for (int i = 0; i < numButtons; i++)
		buttons_[i]->draw(hDC_);
}

