#include <iostream>
#include <string>

#include "PIEquationsLib.hpp"

#define PIE_UNIVERSUM       \
	std::vector<int>        \
	{                       \
		1, 2, 3, 4, 5, 6, 7 \
	}
#define PIE_LEFT PIEquation({}, PIE_UNIVERSUM)
#define PIE_RIGHT PIEquation({}, PIE_UNIVERSUM)

void print_table()
{
	std::cout
		<< "+-PIE_LEFT--+---+" << std::endl
		<< "| A   B   C | F |" << std::endl
		<< "+-----------+---+" << std::endl;
	std::vector<bool> expr1;
	for (int a = 0; a < 2; ++a)
	{
		for (int b = 0; b < 2; ++b)
		{
			for (int c = 0; c < 2; ++c)
			{
				PIEquation
					A({}, PIE_UNIVERSUM),
					B({}, PIE_UNIVERSUM),
					C({}, PIE_UNIVERSUM);
				if (a)
				{
					A.setEq(PIE_UNIVERSUM);
				}
				if (b)
				{
					B.setEq(PIE_UNIVERSUM);
				}
				if (c)
				{
					C.setEq(PIE_UNIVERSUM);
				}
				// if (x) {
				//	X.setEq(PIE_UNIVERSUM);
				// }
				PIEquation expr = PIE_LEFT;
				bool flag = (expr.getEq() == PIE_UNIVERSUM);
				std::cout << "| " << a << "   "
						  << b << "   "
						  << c << " | "
						  << flag << " |"
						  << std::endl;
				expr1.push_back(flag);
			}
		}
	}
	std::cout
		<< "+-----------+---+" << std::endl
		<< "+-PIE_RIGHT-+---+" << std::endl
		<< "| A   B   C | F |" << std::endl
		<< "+-----------+---+" << std::endl;
	std::vector<bool> expr2;
	for (int a = 0; a < 2; ++a)
	{
		for (int b = 0; b < 2; ++b)
		{
			for (int c = 0; c < 2; ++c)
			{
				PIEquation
					A({}, PIE_UNIVERSUM),
					B({}, PIE_UNIVERSUM),
					C({}, PIE_UNIVERSUM);
				if (a)
				{
					A.setEq(PIE_UNIVERSUM);
				}
				if (b)
				{
					B.setEq(PIE_UNIVERSUM);
				}
				if (c)
				{
					C.setEq(PIE_UNIVERSUM);
				}
				PIEquation expr = PIE_RIGHT;
				bool flag = expr.getEq() == PIE_UNIVERSUM;
				std::cout << "| " << a << "   "
						  << b << "   "
						  << c << " | "
						  << flag << " |"
						  << std::endl;
				expr2.push_back(flag);
			}
		}
	}
	std::cout
		<< "+-----------+---+\n"
		<< "Equation = " << ((expr1 == expr2) ? "TRUE" : "FALSE");
}

int main()
{
	system("mode con lines=30 cols=60");
	system("color F0");
	print_table();
	std::cout << std::endl;
	system("pause");
	return 0;
}