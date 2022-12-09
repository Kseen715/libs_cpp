#include "searchAlgs.hpp"

template <comparable T>
size_t search::linear<T>(T* array, size_t arraySize, T key)
{
	if (arraySize == 0)
		return -1;
	else if (arraySize == 1)
		return array[0] == key ? 1 : -1;
	size_t cmpCount = 0;
	for (size_t i = 0; i < arraySize; i++)
	{
		cmpCount++;
		if (array[i] == key)
			return cmpCount;
	}
	return -1;
}

template <comparable T>
size_t search::fastLinear(T* array, size_t arraySize, T key)
{
	if (arraySize == 0)
		return -1;
	else if (arraySize == 1)
		return array[0] == key ? 1 : -1;
	size_t cmpCount = 0;
	array[arraySize + 1] = key;
	size_t i = 0;
	while (array[i] != key)
	{
		cmpCount++;
		i++;
	}
	if (i == arraySize)
		return -1;
	return cmpCount;
}

template <comparable T>
size_t search::fastLinSrt(T* array, size_t arraySize, T key)
{
	if (arraySize == 0)
		return -1;
	else if (arraySize == 1)
		return array[0] == key ? 1 : -1;
	size_t cmpCount = 0;
	array[arraySize + 1] = key;
	size_t i = 0;
	while (array[i] < key)
	{
		cmpCount++;
		i++;
	}
	if (i == arraySize || array[i] != key)
		return -1;
	return cmpCount;
}

template <comparable T>
size_t search::binary(T* array, size_t arraySize, T key)
{
	if (arraySize == 0)
		return -1;
	else if (arraySize == 1)
		return array[0] == key ? 1 : -1;
	size_t cmpCount = 0;
	size_t left = 0; //Левая граница
	size_t right = arraySize - 1; //Правая граница
	while (left <= right)
	{
		size_t middle = (left + right) / 2; //Середина
		cmpCount++;
		if (array[middle] == key)
			return cmpCount;
		else if (array[middle] < key)
			left = middle + 1;
		else
			right = middle - 1;
		if (middle == 0)
			return -1;
	}
	return -1;
}

template <comparable T>
size_t search::block(T* array, size_t arraySize, T key)
{
	if (arraySize == 0)
		return -1;
	else if (arraySize == 1)
		return array[0] == key ? 1 : -1;
	size_t blockSize = (size_t)sqrt(arraySize);
	size_t cmpCount = 0;
	size_t i = blockSize;
	while (i < arraySize && array[i] <= key) //Ищем нужный блок
	{
		cmpCount++;
		i += blockSize;
	}
	i -= blockSize;
	while (i < arraySize && array[i] <= key) //Ищем нужный элемент в блоке
	{
		cmpCount++;
		if (array[i] == key)
			return cmpCount;
		i++;
	}
	return -1;
}

//Функция для линковщика в VisualStudio.
void linker() {
	search::linear((int*)nullptr, (size_t)NULL, (int)NULL);
	search::fastLinear((int*)nullptr, (size_t)NULL, (int)NULL);
	search::fastLinSrt((int*)nullptr, (size_t)NULL, (int)NULL);
	search::binary((int*)nullptr, (size_t)NULL, (int)NULL);
	search::block((int*)nullptr, (size_t)NULL, (int)NULL);
}