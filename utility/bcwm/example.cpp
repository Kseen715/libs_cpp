#include <iostream>

#include "bcwm.hpp"

int main()
{
	std::cout << "Hello World!\n";
	bcwm::_system::pause();
	bcwm::setConsoleSize(40, 60);
	bcwm::_system::pause();
	bcwm::setTextColor(6);
	std::cout << "Hello World!\n";
	bcwm::_system::pause();
	bcwm::setTextColor(bcwm::_color::red);
	std::cout << "Hello World!\n";
	bcwm::_system::pause();
	bcwm::setTextAndBackgroundColor(bcwm::_color::green, bcwm::_color::red);
	std::cout << "Hello World!\n";
	bcwm::_system::pause();
	bcwm::setTextBackgroundColor(bcwm::_color::white);
	std::cout << "Hello World!\n";
	bcwm::_system::pause();
	bcwm::setConsoleColor(bcwm::_color::red, bcwm::_color::white);
	std::cout << "Hello World!\n";
	bcwm::_system::pause();
	bcwm::setTextColor(bcwm::_color::green);
	std::cout << "Hello World!\n";
	bcwm::_system::pause();
	bcwm::setTextColor(bcwm::_color::blue);
	std::cout << "Hello World!\n";
	bcwm::_system::pause();

	return 0;
}