#include <iostream>

#include "stack8mod.hpp"

template <typename T>
void inputStack(Stack *s, int n)
{
    std::cout << "inputStack " << n << " elements: " << std::endl;
    int i;
    for (i = 0; i < n; i++)
    {
        T tempElement;
        std::cin >> tempElement;
        PutStack(s, (BaseTypeList8 *)&tempElement);
    }
}

template <typename T>
void pushStack(Stack *s, T *array, unsigned size)
{
    for (size_t i = 0; i < size; i++)
    {
        pushStack(s, array[i]);
    }
}



template <typename T>
void printDestroyStack(Stack *s)
{
    unsigned n = s->N;
    for (unsigned i = 0; i < n; i++)
    {
        BaseTypeList8 E = new T[1];
        GetStack(s, &E);
        std::cout << *(T *)E << " " << std::endl;
        delete[](T *) E;
    }
}

// use already existeing function
bool isEmptyStack(Stack *s)
{
    return EmptyList((List *)s);
}

void linker()
{
    inputStack<int>(new Stack, 5);
    pushStack<int>(nullptr, 0);
    pushStack<int>(nullptr, nullptr);
    pushStack<int>(nullptr, nullptr, 0);
    printStack<int>(nullptr);
    printDestroyStack<int>(nullptr);
    printStack<int>(nullptr);
    popStack<char>(nullptr);
    printStack<char>(nullptr);
    isEmptyStack(nullptr);
}