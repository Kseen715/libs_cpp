#pragma once

#include <iostream>
#include <cmath>

#include "concept/stdConcepts.hpp"

namespace search
{
	//Линейный поиск элемента key в массиве
	//array размера arraySize.
	//Если элемент найден, возращает количество сравнений.
	template <comparable T>
	size_t linear(T* array, size_t arraySize, T key);

	//Быстрый линейный поиск элемента key в массиве
	//array размера arraySize.
	//Если элемент найден, возращает количество сравнений.
	template <comparable T>
	size_t fastLinear(T* array, size_t arraySize, T key);

	//Быстрый линейный поиск элемента key в упорядоченном массиве
	//array размера arraySize.
	//Если элемент найден, возращает количество сравнений.
	template <comparable T>
	size_t fastLinSrt(T* array, size_t arraySize, T key);

	//Бинарный поиск элемента key в упорядоченном
	//массиве array размера arraySize.
	//Если элемент найден, возращает количество сравнений.
	template <comparable T>
	size_t binary(T* array, size_t arraySize, T key);

	//Блочный поиск элемента key с размером блока blockSize
	//на упорядоченном массиве array размера arraySize.
	//Если элемент найден, возращает количество сравнений.
	template <comparable T>
	size_t block(T* array, size_t arraySize, T key);
}