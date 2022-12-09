#pragma once
#ifndef __P_I_EQUATIONS_LIB_H
#define __P_I_EQUATIONS_LIB_H

#include <iostream>
#include <vector>

#define PIE_UNIVERSUM std::vector<int>{}    //Redefine with some vector<int>
#define PIE_LEFT PIEquation({}, PIE_UNIVERSUM)  //Redefine with left equation
#define PIE_RIGHT PIEquation({}, PIE_UNIVERSUM) //Redefine with right equation

/*
Only typenames, that have operator<<
*/
template<typename T>
concept coutable = requires(T a) {
	{ std::cout << a };
};

/*
Operator << for std::vector<> with template type T
*/
template<coutable T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	if (vec.size() == 0) {
		os << "{}";
		return os;
	}
	os << "{";
	for (int i = 0; i < vec.size() - 1; ++i) {
		os << vec.at(i) << ", ";
	}
	os << vec.at(vec.size() - 1) << "}";
	return os;
}
/*
@brief: returns true if key is in array
@param: key - int, array - std::vector<int>
@return: bool
*/
bool _search(int key, const std::vector<int>& array);

/*
@brief: returns true if vecA == vecB
@param: vecA - std::vector<int>, vecB - std::vector<int>
@return: bool
*/
bool _isEqual(std::vector<int> vecA, std::vector<int> vecB);

/*
@brief: returns true if vecA is included in vecB
@param: vecA - std::vector<int>, vecB - std::vector<int>
@return: bool
*/
bool _isIncluded(std::vector<int> vecA, std::vector<int> vecB);

/*
@brief: returns vector of elements that are in both vecA and vecB
@param: vecA - std::vector<int>, vecB - std::vector<int>
@return: std::vector<int>
*/
std::vector<int> _and(std::vector<int> vecA, std::vector<int> vecB);

/*
@brief: returns vector of elements that are in vecA but not in vecB
@param: vecA - std::vector<int>, vecB - std::vector<int>
@return: std::vector<int>
*/
std::vector<int> _or(std::vector<int> vecA, std::vector<int> vecB);

std::vector<int> _diff(std::vector<int> vecA, std::vector<int> vecB);

std::vector<int> _xor(std::vector<int> vecA, std::vector<int> vecB);

std::vector<int> _not(std::vector<int> vecA, std::vector<int> vecU);

class PIEquation {
protected:
	std::vector<int> equation, universum;
public:
	/*
	Default constructor
	*/
	PIEquation();

	/*
	Constructor with another equation
	*/
	PIEquation(const PIEquation& other);

	/*
	Constructor with universum only
	*/
	PIEquation(std::vector<int> universum);

	/*
	Constructor with equation
	*/
	PIEquation(std::vector<int> eq, std::vector<int> universum);

	/*
	Opeartor =
	*/
	PIEquation& operator=(const PIEquation& other);

	/*
	Destructor
	*/
	~PIEquation();

	/*
	@brief: sets universum to the given vector
	@param: vec - vector of integers
	@return: void
	*/
	void setUniversum(std::vector<int> vec);

	/*
	@brief: sets equation to the given vector
	@param: vec - vector to set equation to
	@return: void
	*/
	void setEq(std::vector<int> vec);

	/*
	@brief: returns universum
	@return: vector of integers
	*/
	std::vector<int> getUniversum();

	/*
	@brief: returns equation
	@return: vector of integers
	*/
	std::vector<int> getEq();

	bool operator==(const PIEquation& other);

	bool operator!=(const PIEquation& other);

	bool operator<=(const PIEquation& other);

	bool operator>=(const PIEquation& other);

	bool operator<(const PIEquation& other);

	bool operator>(const PIEquation& other);

	PIEquation operator|(const PIEquation& other);

	PIEquation operator-(const PIEquation& other);

	PIEquation operator&(const PIEquation& other);

	PIEquation operator^(const PIEquation& other);

	PIEquation operator~();

	friend std::ostream& operator<<(std::ostream& os, const PIEquation& other);

	bool isEqualToUniversum();
};

std::ostream& operator<<(std::ostream& os, const PIEquation& other);

#endif //__P_I_EQUATIONS_LIB_H