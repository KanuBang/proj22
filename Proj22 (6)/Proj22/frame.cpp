#include "frame.h"
#include "Misc.h"
#include "figure.h"
#include <iostream>
#include "MButton.h"

// 어쩔 수 없이 전역 변수 1개는 사용한다.
Frame* theFrame = nullptr;
class MButton;
// 전역함수로는 윈도 메시지 처리 함수가 있다.
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
		// 모든 이벤트는 eventHandler에서 처리한다.
		// MEvent는 이벤트가 클래스화 된 것
		// 왼쪽 마우스 클릭을 하면 그것이 MEvent로 들어가고
		// 그 MEvent가 eventHandler함수로 들어간다.
		// 그리고 그 이벤트를 처리한다.
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Hw, &ps);
		//Rectangle(hdc, 200, 200, 200, 200);
		// 그리기 코드는 이걸로 끝!
		if (theFrame != nullptr)
			theFrame->repaint();
		// 모든 그리는 기능 repaint에다가 넣는다

		EndPaint(Hw, &ps);  // BeginPaint의 짝이 된다

	}
	default: return DefWindowProc(Hw, Msg, wParam, lParam);
	}
}

Frame::Frame() :Frame(L"", 800, 600) {
	// 현재 사용되지 않고 있음.
	initialize();
}

//생성자는 건드리지 말자
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
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // 종료 최소화 최대화 아이콘
		WS_THICKFRAME,  // resize가 가능하게
		0, 0, width, height, // x, y, width, height
		NULL, NULL, hInst_, NULL);  // Parent, Menu, instance handle, lpParam
	if (!hWnd_) throw 0;

	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_);
	SetFocus(hWnd_);
	hDC_ = GetDC(hWnd_);
	invalidate();
}

//run은 건드리지 말자
// run 함수는 수정하면 위험함.
void Frame::run() {
	HACCEL hAccelTable = LoadAccelerators(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));

	MSG msg;

	// 기본 메시지 루프입니다:
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
	//이벤트 e를 받는다
	//이 이벤트에 따라 액션
	// TODO: 여기에 구현 코드 추가.
	OutputDebugString(L"Event\n");
	std::cout << L"Event\n" << std::endl;  // 여기는 cmd 창으로 출력

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

//그림을 그릴때 사용한다.
//사각형과 타원 객체에 그리라고 명령한다.
//사각형의 draw 메소드는 자기 위치 데이터로 사각형을 그린다.
//타원의 draw 메소드는 자기 위치 데이터로 타원을 그린다.
//도형 피겨 배열을 만들어서 객체들에 시킨다
// for문으로 draw메소드를 실행시키면 된다.

void Frame::repaint() {
	// 그려야할 모든 것은 여기에. 아래 두 줄은 샘플이니 지워야한다.

	//Rectangle(hDC_, 100, 100, 200, 300);
	//Rectangle(hDC_, 500, 500, 700, 600);
	drawButtons();

	for (int i = 0; i < numFigure; i++) {
		my[i]->draw(hDC_);
	}
}

void Frame::invalidate() {
	// 이 메소드를 부르면 화면을 다시 그리게 된다.
	InvalidateRect(hWnd_, nullptr, true);
}

void Frame::initialize() {

	MButton* b1 = new MButton("사각형", 0, 0, 100, 30);
	MButton* b2 = new MButton("타원", 100, 0, 100, 30);
	MButton* b3 = new MButton("선분", 200, 0, 100, 30);
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

