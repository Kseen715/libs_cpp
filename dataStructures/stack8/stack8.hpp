#pragma once

#include "list8mod.hpp"

const short StackOk = ListOk;
const short StackUnder = ListUnder;
const short StackOver = ListNotMem;

extern int StackError; // Переменная ошибок

typedef List Stack;

void InitStack(Stack *s, unsigned int size); /* Инициализация стека */

void PutStack(Stack *s, BaseTypeList8 *E); /* Поместить элемент в стек */

void GetStack(Stack *s, BaseTypeList8 *E); /* Извлечь элемент из стека */

int EmptyStack(Stack s); // Проверка: стек пуст?

void ReadStack(Stack s, BaseTypeList8 *E); /* Прочитать элемент из вершины стека */

void DoneStack(Stack *s); // Уничтожить стек