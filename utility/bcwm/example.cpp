#include <iostream>

#include "bcwm.hpp"

int main()
{
	std::cout << "Hello World!\n";
	bcwm::systemPause();
	bcwm::setConsoleSize(40, 60);
	bcwm::systemPause();
	bcwm::setTextColor(6);
	std::cout << "Hello World!\n";
	bcwm::systemPause();
	bcwm::setTextColor(bcwm::red);
	std::cout << "Hello World!\n";
	bcwm::systemPause();
	bcwm::setTextAndBackgroundColor(bcwm::green, bcwm::red);
	std::cout << "Hello World!\n";
	bcwm::systemPause();
	bcwm::setTextBackgroundColor(bcwm::white);
	std::cout << "Hello World!\n";
	bcwm::systemPause();
	bcwm::setConsoleColor(bcwm::red, bcwm::white);
	std::cout << "Hello World!\n";
	bcwm::systemPause();
	bcwm::setTextColor(bcwm::green);
	std::cout << "Hello World!\n";
	bcwm::systemPause();
	bcwm::setTextColor(bcwm::blue);
	std::cout << "Hello World!\n";
	bcwm::systemPause();

	return 0;
}