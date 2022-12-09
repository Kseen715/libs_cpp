#pragma once
#ifndef __BASIC_CONSOLE_WINDOW_MANAGER_LIB_H
#define __BASIC_CONSOLE_WINDOW_MANAGER_LIB_H

#include <windows.h>
#include <string>
#include <sstream>

namespace bcwm
{
	namespace _color
	{
		enum consoleColor
		{
			black = 0,
			blue = 1,
			green = 2,
			cyan = 3,
			red = 4,
			magenta = 5,
			brown = 6,
			lightGray = 7,
			darkGray = 8,
			lightBlue = 9,
			lightGreen = 10,
			lightCyan = 11,
			lightRed = 12,
			lightMagenta = 13,
			yellow = 14,
			white = 15
		};
	};

	namespace _system
	{
		void pause();

		void clear();

		void encodeUTF8();

		void exit();

		void exit(int code);
	}

	void setConsoleSize(unsigned lines, unsigned cols);

	void setTextColor(unsigned color);

	void setTextAndBackgroundColor(unsigned textColor, unsigned backgroundColor);

	void setTextBackgroundColor(unsigned color);

	void setConsoleColor(int textColor, unsigned backgroundColor);

	void setConsoleTitle(char *title);
};

#endif // __BASIC_CONSOLE_WINDOW_MANAGER_LIB_H