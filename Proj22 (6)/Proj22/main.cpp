#include "frame.h"
#include <iostream>
#include <exception>

// 일단은 전역 변수 1개는 사용한다.
extern Frame* theFrame ; // 다른 곳에 선언 된 것을 사용하겠다.
// 메인에서는 run만

int main() {
	try {

		theFrame = new Frame(L"객체1프로젝트2022", 1000,800);
		theFrame->initialize();
		theFrame->run();

	} 
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
}
