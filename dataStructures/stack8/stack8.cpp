#include "stack8.hpp"

int StackError; // Переменная ошибок

typedef List Stack;

/* Инициализация стека */
void InitStack(Stack *s, unsigned int size)
{
    InitList(s, size);
}

/* Поместить элемент в стек */
// without addlist
void PutStack(Stack *s, BaseTypeList8 *E)
{
    PutList(s, E);
}

/* Извлечь элемент из стека */
void GetStack(Stack *s, BaseTypeList8 *E)
{
    GetList(s, E);
}

// Проверка: стек пуст?
int EmptyStack(Stack s)
{
    return EmptyList(&s);
}

/* Прочитать элемент из вершины стека */
void ReadStack(Stack s, BaseTypeList8 *E)
{
    ReadList(&s, E);
}

// Уничтожить стек
void DoneStack(Stack *s)
{
    DoneList(s);
}