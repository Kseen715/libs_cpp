#ifndef __KSI_STD_CONCEPTS_HPP
#define __KSI_STD_CONCEPTS_HPP

#include <iostream>

//������� ��� ���� ������.
//������ �������������� ��������� ���������.
template <typename T>
concept comparable = requires(T a, T b) {
	{ a < b } -> std::convertible_to<bool>;
	{ a <= b } -> std::convertible_to<bool>;
	{ a > b } -> std::convertible_to<bool>;
	{ a >= b } -> std::convertible_to<bool>;
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
};

//������� ��� ����� � ������� ostream
template <typename T>
concept coutable = requires(T a) {
	{ std::cout << a } -> std::convertible_to<std::ostream&>;
};

//������� ��� ����� � ������� ����� istream
template <typename T>
concept cinable = requires(T a) {
	{ std::cin >> a } -> std::convertible_to<std::istream&>;
};

//������� ��� ����� � ������� ������������
template <typename T>
concept assignable = requires(T a, T b) {
	{ a = b } -> std::convertible_to<T>;
};

//������� ��� ����� ������ � �������� �������������� ��������
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

#endif // __KSI_STD_CONCEPTS_HPP