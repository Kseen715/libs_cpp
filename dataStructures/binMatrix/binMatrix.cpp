#include "binMatrix.hpp"

binMatrix::binMatrix(std::initializer_list<std::initializer_list<bool>> list)
{
	for (auto &i : list)
	{
		mtr.push_back(std::vector<bool>(i));
	}
}

std::ostream &operator<<(std::ostream &out, const binMatrix &mtr)
{
	for (int i = 0; i < mtr.mtr.size(); i++)
	{
		for (int j = 0; j < mtr.mtr[i].size(); j++)
		{
			out << mtr.mtr[i][j] << " ";
		}
		out << std::endl;
	}
	return out;
}

binMatrix binMatrix::operator*(const binMatrix &other)
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < other.mtr[i].size(); j++)
		{
			bool sum = 0;
			for (int k = 0; k < mtr[i].size(); k++)
			{
				sum += mtr[i][k] * other.mtr[k][j];
			}
			temp.push_back(sum);
		}
		result.mtr.push_back(temp);
	}
	return result;
}

binMatrix &binMatrix::operator*=(const binMatrix &other)
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < other.mtr[i].size(); j++)
		{
			bool sum = 0;
			for (int k = 0; k < mtr[i].size(); k++)
			{
				sum += mtr[i][k] * other.mtr[k][j];
			}
			temp.push_back(sum);
		}
		result.mtr.push_back(temp);
	}
	mtr = result.mtr;
	return *this;
}

bool binMatrix::operator==(const binMatrix &other)
{
	if (mtr.size() != other.mtr.size())
	{
		return false;
	}
	for (int i = 0; i < mtr.size(); i++)
	{
		if (mtr[i].size() != other.mtr[i].size())
		{
			return false;
		}
		for (int j = 0; j < mtr[i].size(); j++)
		{
			if (mtr[i][j] != other.mtr[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

binMatrix binMatrix::operator-(const binMatrix &other)
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			temp.push_back(mtr[i][j] && !other.mtr[i][j]);
		}
		result.mtr.push_back(temp);
	}
	return result;
}

binMatrix &binMatrix::operator-=(const binMatrix &other)
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			temp.push_back(mtr[i][j] && !other.mtr[i][j]);
		}
		result.mtr.push_back(temp);
	}
	mtr = result.mtr;
	return *this;
}

binMatrix binMatrix::operator|(const binMatrix &other)
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			temp.push_back(mtr[i][j] || other.mtr[i][j]);
		}
		result.mtr.push_back(temp);
	}
	return result;
}

binMatrix &binMatrix::operator|=(const binMatrix &other)
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			temp.push_back(mtr[i][j] || other.mtr[i][j]);
		}
		result.mtr.push_back(temp);
	}
	mtr = result.mtr;
	return *this;
}

binMatrix binMatrix::operator&(const binMatrix &other)
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			temp.push_back(mtr[i][j] && other.mtr[i][j]);
		}
		result.mtr.push_back(temp);
	}
	return result;
}

binMatrix &binMatrix::operator&=(const binMatrix &other)
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			temp.push_back(mtr[i][j] && other.mtr[i][j]);
		}
		result.mtr.push_back(temp);
	}
	mtr = result.mtr;
	return *this;
}

binMatrix binMatrix::operator^(const binMatrix &other)
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			temp.push_back(mtr[i][j] ^ other.mtr[i][j]);
		}
		result.mtr.push_back(temp);
	}
	return result;
}

binMatrix &binMatrix::operator^=(const binMatrix &other)
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			temp.push_back(mtr[i][j] ^ other.mtr[i][j]);
		}
		result.mtr.push_back(temp);
	}
	mtr = result.mtr;
	return *this;
}

binMatrix binMatrix::operator~()
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			temp.push_back(!mtr[i][j]);
		}
		result.mtr.push_back(temp);
	}
	return result;
}

binMatrix binMatrix::operator!()
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			temp.push_back(mtr[j][i] == 1);
		}
		result.mtr.push_back(temp);
	}
	result &= *this;
	return result;
}

binMatrix binMatrix::identity()
{
	binMatrix result;
	for (int i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < mtr[i].size(); j++)
		{
			if (i == j)
			{
				temp.push_back(1);
			}
			else
			{
				temp.push_back(0);
			}
		}
		result.mtr.push_back(temp);
	}
	return result;
}

binMatrix binMatrix::pow(int n)
{
	binMatrix result;
	if (n == 0)
	{
		result = identity();
	}
	else if (n == 1)
	{
		result = *this;
	}
	else
	{
		result = *this;
		for (int i = 1; i < n; i++)
		{
			result *= *this;
		}
	}
	return result;
}

binMatrix binMatrix::empty()
{
	binMatrix result;
	for (size_t i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (size_t j = 0; j < mtr.size(); j++)
		{
			temp.push_back(0);
		}
		result.mtr.push_back(temp);
	}
	return result;
}

binMatrix binMatrix::full()
{
	binMatrix result;
	for (size_t i = 0; i < mtr.size(); i++)
	{
		std::vector<bool> temp;
		for (size_t j = 0; j < mtr.size(); j++)
		{
			temp.push_back(1);
		}
		result.mtr.push_back(temp);
	}
	return result;
}

bool binMatrix::isReflexive()
{
	for (size_t i = 0; i < mtr.size(); i++)
	{
		if (!mtr[i][i])
		{
			return false;
		}
	}
	return true;
}

bool binMatrix::isAntiReflexive()
{
	for (size_t i = 0; i < mtr.size(); i++)
	{
		if (mtr[i][i])
		{
			return false;
		}
	}
	return true;
}

bool binMatrix::isSymmetric()
{
	return (*this == (!*this));
}

bool binMatrix::isAntiSymmetric()
{
	return ((*this & !*this) == identity());
}

bool binMatrix::isTransitive()
{
	return ((*this * *this) == *this);
}

bool binMatrix::isEmpty()
{
	for (size_t i = 0; i < mtr.size(); i++)
	{
		for (size_t j = 0; j < mtr.size(); j++)
		{
			if (i != j && mtr[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool binMatrix::isAntiTransitive()
{
	return (((*this * *this) & *this) == empty());
}

bool binMatrix::isFull()
{
	return ((*this | identity() | !*this) == full());
}

bool binMatrix::isAsymmetric()
{
	return !(*this == (!*this));
}

bool binMatrix::isTolerant()
{
	return (isReflexive() && isSymmetric());
}

bool binMatrix::isEquivalent()
{
	return (isReflexive() && isSymmetric() && isTransitive());
}

bool binMatrix::isOrder()
{
	return (isAntiSymmetric() && isTransitive());
}

bool binMatrix::isWeakOrder()
{
	return (isOrder() && isReflexive());
}

bool binMatrix::isStrictOrder()
{
	return (isOrder() && isAntiReflexive());
}

bool binMatrix::isLinearOrder()
{
	return (isOrder() && isFull());
}

bool binMatrix::isWeakLinearOrder()
{
	return (isWeakOrder() && isFull());
}

bool binMatrix::isStrictLinearOrder()
{
	return (isStrictOrder() && isFull());
}

binMatrix binMatrix::getTransitiveClosurePowerUnion()
{
	binMatrix result = *this;
	for (int i = 1; i < mtr.size(); i++)
	{
		result |= (result.pow(i));
	}
	return result;
}

binMatrix binMatrix::getTransitiveClosureWarshall()
{
	binMatrix result = *this;
	for (int z = 0; z < mtr.size(); z++)
	{
		for (int x = 0; x < mtr.size(); x++)
		{
			for (int y = 0; y < mtr.size(); y++)
			{
				result.mtr[x][y] = result.mtr[x][y] || (result.mtr[x][z] && result.mtr[z][y]);
			}
		}
	}
	return result;
}

binMatrix binMatrix::getRandomRelation(int size, int pairCount)
{
	if (pairCount > size * size)
	{
		throw std::invalid_argument("Error: n is too big");
		exit(1);
	}
	binMatrix result;
	for (int i = 0; i < size; i++)
	{
		std::vector<bool> temp;
		for (int j = 0; j < size; j++)
		{
			temp.push_back(0);
		}
		result.mtr.push_back(temp);
	}
	for (int i = 0; i < pairCount; i++)
	{
		int x, y;
		do
		{
			x = rand() % size;
			y = rand() % size;
		} while (result.mtr[x][y]);
		result.mtr[x][y] = 1;
	}
	return result;
}
static;