#include "bcwm.hpp"

unsigned currentBackgroundColor = 0;

void bcwm::_system::pause()
{
	system("pause");
}

void bcwm::setConsoleSize(unsigned lines, unsigned cols)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);										// stores the console's current dimensions
	MoveWindow(console, r.left, r.top, cols * 8, lines * 16, TRUE); // 8 pixel width, 16 pixel height
}

void bcwm::setTextColor(unsigned color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (currentBackgroundColor << 4) | color);
}

void bcwm::setTextAndBackgroundColor(unsigned textColor, unsigned backgroundColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
	currentBackgroundColor = backgroundColor;
}

void bcwm::setTextBackgroundColor(unsigned color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	SetConsoleTextAttribute(hConsole, (color << 4) | csbi.wAttributes);
	currentBackgroundColor = color;
}

void bcwm::setConsoleColor(int textColor, unsigned backgroundColor)
{
	std::ostringstream ss;
	ss << "color " << std::hex << backgroundColor << std::hex << textColor;
	system(ss.str().c_str());
	currentBackgroundColor = backgroundColor;
}

void bcwm::setConsoleTitle(char *title)
{
	std::ostringstream ss;
	ss << "title " << title;
	system(ss.str().c_str());
}

void bcwm::_system::clear()
{
	system("cls");
}

void bcwm::_system::encodeUTF8()
{
	system("chcp 65001");
}

void bcwm::_system::exit()
{
	std::exit(0);
}

void bcwm::_system::exit(int code)
{
	std::exit(code);
}