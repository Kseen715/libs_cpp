#include <iostream>

#include "binMatrix.h"

int ex_main()
{
	binMatrix A = {
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 1, 1, 1, 1} };
	binMatrix B = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 1, 0, 1, 0, 1} };
	binMatrix C = {
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 1, 1, 1, 1} };
	std::cout << "((A * !B) & A) - C =" << std::endl
		<< ((A * !B) & A) - C;

	std::cout << "A:" << std::endl
		<< "isReflexive: " << A.isReflexive() << std::endl
		<< "isAntiReflexive: " << A.isAntiReflexive() << std::endl
		<< "isSymmetric: " << A.isSymmetric() << std::endl
		<< "isAntiSymmetric: " << A.isAntiSymmetric() << std::endl
		<< "isTransitive: " << A.isTransitive() << std::endl
		<< "isAntiTransitive: " << A.isAntiTransitive() << std::endl
		<< "isFull: " << A.isFull() << std::endl
		<< "isTolerant: " << A.isTolerant() << std::endl
		<< "isEquivalent: " << A.isEquivalent() << std::endl
		<< "isOrder: " << A.isOrder() << std::endl
		<< "isWeakOrder: " << A.isWeakOrder() << std::endl
		<< "isStrictOrder: " << A.isStrictOrder() << std::endl
		<< "isLinearOrder: " << A.isLinearOrder() << std::endl
		<< "isWeakLenearOreder: " << A.isWeakLinearOrder() << std::endl
		<< "isStrictLinearOrder: " << A.isStrictLinearOrder() << std::endl;

	std::cout << "B:" << std::endl
		<< "isReflexive: " << B.isReflexive() << std::endl
		<< "isAntiReflexive: " << B.isAntiReflexive() << std::endl
		<< "isSymmetric: " << B.isSymmetric() << std::endl
		<< "isAntiSymmetric:  " << B.isAntiSymmetric() << std::endl
		<< "isTransitive: " << B.isTransitive() << std::endl
		<< "isAntiTransitive: " << B.isAntiTransitive() << std::endl
		<< "isFull: " << B.isFull() << std::endl
		<< "isTolerant: " << B.isTolerant() << std::endl
		<< "isEquivalent: " << B.isEquivalent() << std::endl
		<< "isOrder: " << B.isOrder() << std::endl
		<< "isWeakOrder: " << B.isWeakOrder() << std::endl
		<< "isStrictOrder: " << B.isStrictOrder() << std::endl
		<< "isLinearOrder: " << B.isLinearOrder() << std::endl
		<< "isWeakLenearOreder: " << B.isWeakLinearOrder() << std::endl
		<< "isStrictLinearOrder: " << B.isStrictLinearOrder() << std::endl;

	std::cout << "C:" << std::endl
		<< "isReflexive: " << C.isReflexive() << std::endl
		<< "isAntiReflexive: " << C.isAntiReflexive() << std::endl
		<< "isSymmetric: " << C.isSymmetric() << std::endl
		<< "isAntiSymmetric:  " << C.isAntiSymmetric() << std::endl
		<< "isTransitive: " << C.isTransitive() << std::endl
		<< "isAntiTransitive: " << C.isAntiTransitive() << std::endl
		<< "isFull: " << C.isFull() << std::endl
		<< "isTolerant: " << C.isTolerant() << std::endl
		<< "isEquivalent: " << C.isEquivalent() << std::endl
		<< "isOrder: " << C.isOrder() << std::endl
		<< "isWeakOrder: " << C.isWeakOrder() << std::endl
		<< "isStrictOrder: " << C.isStrictOrder() << std::endl
		<< "isLinearOrder: " << C.isLinearOrder() << std::endl
		<< "isWeakLenearOreder: " << C.isWeakLinearOrder() << std::endl
		<< "isStrictLinearOrder: " << C.isStrictLinearOrder() << std::endl;

	std::cin.get();
	std::cin.get();
	return 0;
}