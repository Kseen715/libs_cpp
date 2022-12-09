#pragma once

// Интерфейс стека

#include "stack8.hpp"

// Ввод стека s размера n с клавиатуры
template <typename T>
void inputStack(Stack *s, int n);

// Добавление элемента element в стек s
template <typename T>
void pushStack(Stack *s, T element)
{
    PutStack(s, (void **)&element);
}

// Добавление элемента element в стек s по указателю
template <typename T>
void pushStack(Stack *s, T *element)
{
    PutStack(s, (void **)element);
}

// Добавление элементов массива array размера size в стек s
template <typename T>
void pushStack(Stack *s, T *array, unsigned size);

// Вывод стека s на экран
template <typename T>
void printStack(Stack *s)
{
    unsigned tempPtrHolder = s->ptr;
    unsigned n = s->N;
    s->ptr = 1;
    for (unsigned i = 0; i < n; i++)
    {
        BaseTypeList8 E = new T[1];
        std::cout << i + 1 << ": ";
        ReadStack(*s, &E);
        MovePtr((List *)s);
        std::cout << *(T *)E << " " << std::endl;
        delete[](T *) E;
    }
    s->ptr = tempPtrHolder;
}

// Вывод стека s на экран и удаление всех элементов
template <typename T>
void printDestroyStack(Stack *s);

// Получить верхний элемент стека s
template <typename T>
T popStack(Stack *s)
{
    BaseTypeList8 E = new T[1];
    GetStack(s, &E);
    T temp = *(T *)E;
    delete[](T *) E;
    return temp;
}

// Возвращает пустой ли стек
bool isEmptyStack(Stack *s);