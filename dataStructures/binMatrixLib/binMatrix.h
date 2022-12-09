#pragma once
#ifndef __BIN_MATRIX_H
#define __BIN_MATRIX_H

#include <iostream>
#include <vector>

#ifndef __BIN_MATRIX_CLASS
#define __BIN_MATRIX_CLASS
class binMatrix
{
protected:
	std::vector<std::vector<bool>> mtr;

public:
	//Стандартный конструктор.
	binMatrix() = default;

	//Стандартный деструктор.
	~binMatrix() = default;

	//Конструктор для листа инициализации.
	binMatrix(std::initializer_list<std::initializer_list<bool>> list);

	//Конструктор для копирования матрицы.
	binMatrix(const binMatrix& other) = default;

	//Конструктор для перемещения матрицы.
	binMatrix(binMatrix&& other) = default;

	//operator= | Оператор присваивания для копирования матрицы.
	binMatrix& operator=(const binMatrix& other) = default;

	//operator= | Оператор присваивания для перемещения матрицы.
	binMatrix& operator=(binMatrix&& other) = default;

	//operator<< | Вывод матрицы в поток.
	friend std::ostream& operator<<(std::ostream& out, const binMatrix& mtr);

	//operator* | Композиция | Суперпозиция |
	//Умножение | Кружок.
	binMatrix operator*(const binMatrix& other);

	//operator*= | Композиция | Суперпозиция |
	//Умножение | Кружок.
	binMatrix& operator*=(const binMatrix& other);

	//operator== | Равенство.
	bool operator==(const binMatrix& other);

	//operator- | Разность.
	binMatrix operator-(const binMatrix& other);

	//operator-= | Разность.
	binMatrix& operator-=(const binMatrix& other);

	//operator| | Объединение | Дизъюнкция.
	binMatrix operator|(const binMatrix& other);

	//operator|= | Объединение | Дизъюнкция.
	binMatrix& operator|=(const binMatrix& other);

	//operator& | Пересечение | Конъюнкция.
	binMatrix operator&(const binMatrix& other);

	//operator&= | Пересечение | Конъюнкция.
	binMatrix& operator&=(const binMatrix& other);

	//operator^ | Исключающее ИЛИ | Симметрическая
	//разность | XOR.
	binMatrix operator^(const binMatrix& other);

	//operator^= | Исключающее ИЛИ | Симметрическая
	//разность | XOR.
	binMatrix& operator^=(const binMatrix& other);

	//operator~ | Дополнение | НЕ.
	binMatrix operator~();

	//operator! | Обращание | A^-1.
	binMatrix operator!();

	//Identity matrix | Единичная матрица.
	binMatrix identity();

	//Степень отношения | A^pairCount.
	binMatrix pow(int n);

	//Пустая матрица.
	binMatrix empty();

	//Полная матрица.
	binMatrix full();

	//Возвращает результат проверки матрицы отношения
	//на рефлексивность. R рефлексивно, если
	//xRx для всех xA.
	bool isReflexive();

	//Возвращает результат проверки матрицы отношения
	//на антирефлексивность. R антирефлексивно, если
	//!xRx для всех xA.
	bool isAntiReflexive();

	//Возвращает результат проверки матрицы отношения
	//на симметричность. R симметрично, если
	//из xRy следует yRx для всех xAy.
	bool isSymmetric();

	//Возвращает результат проверки матрицы отношения
	//на антисимметричность. R антисимметрично, если
	//из xRy следует !yRx для всех xAy.
	bool isAntiSymmetric();

	//Возвращает результат проверки матрицы отношения
	//на транзитивность. R транзитивно, если
	//из xRz и zRy следует xRy для всех xAyAz.
	bool isTransitive();

	//Возвращает результат проверки матрицы отношения
	//на пустое отношение.
	bool isEmpty();

	//Возвращает результат проверки матрицы отношения
	//на антитранзитивность. R антитранзитивно, если
	//из xRz и zRy следует !xRy для всех xAyAz.
	bool isAntiTransitive();

	//Возвращает результат проверки матрицы отношения
	//на полноту. R полно, если из x!=y следует,
	//что xRy или yRx для всех xAy.
	bool isFull();

	//Возвращает результат проверки матрицы отношения
	//на ассимитричность.
	bool isAsymmetric();

	//Возвращает результат проверки матрицы отношения
	//на толерантность.
	bool isTolerant();

	//Возвращает результат проверки матрицы отношения
	//на эквивалентность.
	bool isEquivalent();

	//Возвращает результат проверки матрицы отношения
	//на порядок.
	bool isOrder();

	//Возвращает результат проверки матрицы отношения
	//на нестрогий порядок.
	bool isWeakOrder();

	//Возвращает результат проверки матрицы отношения
	//на строгий порядок.
	bool isStrictOrder();

	//Возвращает результат проверки матрицы отношения
	//на линейный порядок.
	bool isLinearOrder();

	//Возвращает результат проверки матрицы отношения
	//на нестрогий линейный порядок.
	bool isWeakLinearOrder();

	//Возвращает результат проверки матрицы отношения
	//на строгий линейный порядок.
	bool isStrictLinearOrder();

	//Возвращает транзитивное замыкание матрицы отношения.
	//Алгоритм объединения степеней.
	binMatrix getTransitiveClosurePowerUnion();

	//Возвращает транзитивное замыкание матрицы отношения.
	//Алгоритм Уоршалла.
	binMatrix getTransitiveClosureWarshall();

	//Возвращает случайное отношение с мощностью
	//size и числом пар pairCount.
	binMatrix static getRandomRelation(int size, int pairCount);
};
#endif // __BIN_MATRIX_CLASS

#endif // __BIN_MATRIX_H