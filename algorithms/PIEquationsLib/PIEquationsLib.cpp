#include "PIEquationsLib.hpp"

bool _search(int key, const std::vector<int> &array)
{
	for (auto i : array)
	{
		if (i == key)
		{
			return true;
		}
	}
	return false;
}

/**
 * Функция _isEqual() проверяет равенство двух векторов.
 *
 * @param vecA Первый вектор.
 * @param vecB Второй вектор.
 *
 * @return true, если элементы двух векторов совпадают, false - иначе.
 */
bool _isEqual(std::vector<int> vecA, std::vector<int> vecB)
{
	int i = 0;
	bool flag = vecA.size() == vecB.size();
	while (i < vecA.size() && flag)
	{
		flag = vecA.at(i) == vecB.at(i);
		i++;
	}
	return flag;
}

/**
 * _isIncluded() проверяет, входит ли последовательность vecA в vecB.
 *
 * @param vecA - последовательность, которую нужно проверить.
 * @param vecB - последовательность, содержащая vecA.
 *
 * @return true, если vecA является частью vecB; false - иначе.
 */
bool _isIncluded(std::vector<int> vecA, std::vector<int> vecB)
{
	bool flag = vecA.size() <= vecB.size() && vecA.at(vecA.size() - 1) <= vecB.at(vecB.size() - 1);
	int i = 0, j = 0;
	while (i < vecA.size() && flag)
	{
		if (vecA.at(i) == vecB.at(j))
		{
			i++;
			j++;
		}
		else if (vecA.at(i) > vecB.at(j))
		{
			j++;
		}
		else
		{
			flag = false;
		}
	}
	return flag;
}

std::vector<int> _and(std::vector<int> vecA, std::vector<int> vecB)
{
	std::vector<int> vecC;
	int i = 0, j = 0;
	while (i < vecA.size() && j < vecB.size())
	{
		if (vecA.at(i) == vecB.at(j))
		{
			vecC.push_back(vecA.at(i++));
			j++;
		}
		else if (vecA.at(i) > vecB.at(j))
		{
			vecC.push_back(vecB.at(j++));
		}
		else
		{
			vecC.push_back(vecA.at(i++));
		}
	}
	while (i < vecA.size())
	{
		vecC.push_back(vecA.at(i++));
	}
	while (j < vecB.size())
	{
		vecC.push_back(vecB.at(j++));
	}
	return vecC;
}

std::vector<int> _or(std::vector<int> vecA, std::vector<int> vecB)
{
	std::vector<int> vecC;
	int i = 0, j = 0;
	while (i < vecA.size() && j < vecB.size())
	{
		if (vecA.at(i) == vecB.at(j))
		{
			vecC.push_back(vecA.at(i++));
			j++;
		}
		else if (vecA.at(i) > vecB.at(j))
		{
			j++;
		}
		else
		{
			i++;
		}
	}
	return vecC;
}

std::vector<int> _diff(std::vector<int> vecA, std::vector<int> vecB)
{
	int i = 0, j = 0;
	std::vector<int> vecC;
	while (i < vecA.size() && j < vecB.size())
	{
		if (vecA.at(i) == vecB.at(j))
		{
			i++;
			j++;
		}
		else if (vecA.at(i) > vecB.at(j))
		{
			j++;
		}
		else
		{
			vecC.push_back(vecA.at(i++));
		}
	}
	while (i < vecA.size())
	{
		vecC.push_back(vecA.at(i++));
	}
	return vecC;
}

std::vector<int> _xor(std::vector<int> vecA, std::vector<int> vecB)
{
	int i = 0, j = 0;
	std::vector<int> vecC;
	while (i < vecA.size() && j < vecB.size())
	{
		if (vecA.at(i) == vecB.at(j))
		{
			i++;
			j++;
		}
		else if (vecA.at(i) > vecB.at(j))
		{
			vecC.push_back(vecB.at(j++));
		}
		else
		{
			vecC.push_back(vecA.at(i++));
		}
	}
	while (i < vecA.size())
	{
		vecC.push_back(vecA.at(i++));
	}
	while (j < vecB.size())
	{
		vecC.push_back(vecB.at(j++));
	}
	return vecC;
}

std::vector<int> _not(std::vector<int> vecA, std::vector<int> vecU)
{
	std::vector<int> vecC;
	int u = 0, j = 0;
	while (u < vecU.size() && j < vecA.size())
	{
		if (vecU.at(u) == vecA.at(j))
		{
			u++;
			j++;
		}
		else if (vecU.at(u) > vecA.at(j))
		{
			j++;
		}
		else
		{
			vecC.push_back(vecU.at(u++));
		}
	}
	while (u < vecU.size())
	{
		vecC.push_back(vecU.at(u++));
	}
	return vecC;
}

PIEquation::PIEquation()
{
	equation = std::vector<int>();
	universum = std::vector<int>();
}

PIEquation::PIEquation(const PIEquation &other)
{
	this->equation = other.equation;
	this->universum = other.universum;
}

// constructor for a (universum) equation
PIEquation::PIEquation(std::vector<int> universum)
{
	equation = std::vector<int>();
	this->universum = universum;
}

PIEquation::PIEquation(std::vector<int> eq, std::vector<int> universum)
{
	this->equation = eq;
	this->universum = universum;
}

PIEquation &PIEquation::operator=(const PIEquation &other)
{
	this->equation = other.equation;
	this->universum = other.universum;
	return *this;
}

PIEquation::~PIEquation()
{
	equation.clear();
}

void PIEquation::setUniversum(std::vector<int> vec)
{
	this->universum = vec;
}

void PIEquation::setEq(std::vector<int> vec)
{
	this->equation = vec;
}

std::vector<int> PIEquation::getUniversum()
{
	return this->universum;
}

std::vector<int> PIEquation::getEq()
{
	return this->equation;
}

bool PIEquation::operator==(const PIEquation &other)
{
	return _isEqual(this->equation, other.equation);
}

bool PIEquation::operator!=(const PIEquation &other)
{
	return !(*this == other);
}

bool PIEquation::operator<=(const PIEquation &other)
{
	return _isIncluded(this->equation, other.equation);
}

bool PIEquation::operator>=(const PIEquation &other)
{
	return _isIncluded(other.equation, this->equation);
}

bool PIEquation::operator<(const PIEquation &other)
{
	return *this <= other && *this != other;
}

bool PIEquation::operator>(const PIEquation &other)
{
	return *this >= other && *this != other;
}

// Конъюнкция | Дуга радуга
PIEquation PIEquation::operator|(const PIEquation &other)
{
	return PIEquation(_or(this->equation, other.equation), this->universum);
}

PIEquation PIEquation::operator-(const PIEquation &other)
{
	return PIEquation(_diff(this->equation, other.equation), this->universum);
}

// Дизъюнкция | Чашка
PIEquation PIEquation::operator&(const PIEquation &other)
{
	return PIEquation(_and(this->equation, other.equation), this->universum);
}

PIEquation PIEquation::operator^(const PIEquation &other)
{
	return PIEquation(_xor(this->equation, other.equation), this->universum);
}

PIEquation PIEquation::operator~()
{
	return PIEquation(_not(this->equation, this->universum), this->universum);
}

bool PIEquation::isEqualToUniversum()
{
	return (this->equation == this->universum);
}

std::ostream &operator<<(std::ostream &os, const PIEquation &other)
{
	if (other.equation.size() == 0)
	{
		os << "Empty";
		return os;
	}
	for (int i = 0; i < other.equation.size() - 1; i++)
	{
		os << other.equation.at(i) << ",";
	}
	os << other.equation.at(other.equation.size() - 1);
	return os;
}