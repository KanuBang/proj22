
#include "MButton.h"
MButton::MButton(std::string s, int x, int y, int width, int height)
{
	text_ = s;
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height; 
}
MButton::MButton()
{
	text_ = "noname";
	x_ = 0;
	y_ = 0;
	width_ = default_width;
	height_ = default_height;
}
bool MButton::includes(int x, int y)
{
	return (x_ <= x && x <= (x_ + width_) &&
		(y_ <= y && y <= (y_ + height_)));

}
	// 마우스 클릭 했을 때 그 위치가 버튼의 위치에 들어있는 위치인지
bool MButton::includes(MPoint p)
{
	return includes(p.x_, p.y_);
}
void MButton::setX(int x)
{
	x_ = x;
}
int MButton::getHeight()
{
	return height_;
}
int MButton::getWidth()
{
	return width_;
}
void MButton::draw(HDC hdc)
{
	HDC h = hdc;
	
	Rectangle(h, x_, y_, x_+width_,y_+height_);
	
	TextOutA(h, x_,y_+10, text_.c_str(), text_.length());
	
	
}


