#ifndef __KSI_LIST_8_MOD_HPP
#define __KSI_LIST_8_MOD_HPP

#include "list8.hpp"

#include <iostream>

// Ввод n элементов в список с клавиатуры
template <typename T>
void InputList(List *L, int n);

// Добавляет в список L элемент element
template <typename T>
void AddList(List *L, T element);

// Добавляет в список L элемент element по адресу
template <typename T>
void AddList(List *L, T *element);

// Добавляет в список L массив array размера size поэлементно
template <typename T>
void AddList(List *L, T *array, unsigned size);

// Выводит список L в поток cout
template <typename T>
void PrintList(List *L);

// Выводит список L в поток cout и удаляет его элементы по одному
template <typename T>
void PrintDestroyList(List *L);

// Выводит многочлен P в поток cout с переменной y
template <typename T>
void PrintPolynom(List *P, char y);

// Ввод многочлена P с клавиатуры с переменной y
template <typename T>
void WritePolynom(List *L, char y);

#endif // __KSI_LIST_8_MOD_HPP