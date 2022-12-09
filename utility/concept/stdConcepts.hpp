#pragma once

#include <iostream>

//Концепт для типа данных.
//Должны присутствовать операторы сравнения.
template <typename T>
concept comparable = requires(T a, T b) {
	{ a < b } -> std::convertible_to<bool>;
	{ a <= b } -> std::convertible_to<bool>;
	{ a > b } -> std::convertible_to<bool>;
	{ a >= b } -> std::convertible_to<bool>;
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
};

//Концепт для типов с методом ostream
template <typename T>
concept coutable = requires(T a) {
	{ std::cout << a } -> std::convertible_to<std::ostream&>;
};

//Концепт для типов с методом ввода istream
template <typename T>
concept cinable = requires(T a) {
	{ std::cin >> a } -> std::convertible_to<std::istream&>;
};

//Концепт для типов с методом присваивания
template <typename T>
concept assignable = requires(T a, T b) {
	{ a = b } -> std::convertible_to<T>;
};

//Концепт для типов данных с методами арифметических операций
template <typename T>
concept arithmetic = requires(T a, T b) {
	{ a + b } -> std::convertible_to<T>;
	{ a - b } -> std::convertible_to<T>;
	{ a* b } -> std::convertible_to<T>;
	{ a / b } -> std::convertible_to<T>;
	{ a += b } -> std::convertible_to<T>;
	{ a -= b } -> std::convertible_to<T>;
	{ a *= b } -> std::convertible_to<T>;
	{ a /= b } -> std::convertible_to<T>;
	{ a = b } -> std::convertible_to<T>;
};