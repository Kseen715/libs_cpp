#include "tree8.hpp"

short treeError = treeOk;

// Инициализация дерева.
void initTree(tree *T, unsigned size)
{
    T->pBuf = new mem[size];
    T->size = size;
    T->ptr = 0;
}

// Создание корня.
void createRoot(tree *T)
{
    T->ptr = 1;
    T->pBuf[T->ptr - 1]->data = new tree8BaseType;
    T->pBuf[T->ptr - 1]->flag = 0;
}

// Запись данных по текущему указателю.
void writeDataTree(tree *T, tree8BaseType E)
{
    T->pBuf[T->ptr - 1]->data = E;
    T->pBuf[T->ptr - 1]->flag = 1;
}

// Чтение данных.
void readDataTree(tree *T, tree8BaseType *E)
{
    *E = T->pBuf[T->ptr - 1]->data;
}

// 1 — есть левый сын, 0 — нет.
int isLSon(tree *T)
{
    if (T->ptr * 2 + 1 < T->size)
        return T->pBuf[T->ptr * 2 - 1]->flag == 1;
    else
        return 0;
}

// 1 — есть правый сын, 0 — нет.
int isRSon(tree *T)
{
    if (T->ptr * 2 + 2 < T->size)
        return T->pBuf[T->ptr * 2 + 1 - 1]->flag == 1;
    else
        return 0;
}

// Перейти к левому сыну, где T — адрес ячейки, содержащей адрес текущей
// вершины, TS — адрес ячейки, содержащей адрес корня левого поддерева(левого
// сына).
void moveToLSon(tree *T_down, tree *T_up)
{
    if (T_down)
        T_down->ptr = (T_down->ptr * 2);
    if (T_up)
        T_up->ptr = (T_up->ptr) / 2;
}

// Перейти к правому сыну.
void moveToRSon(tree *T_down, tree *T_up)
{
    if (T_down)
        T_down->ptr = (T_down->ptr * 2) + 1;
    if (T_up)
        T_up->ptr = (T_up->ptr - 1) / 2;
}

// 1 — пустое дерево,0 — не пустое.
int isEmptyTree(tree *T)
{
    return T->pBuf[0]->flag == 0;
}

// Удаление листа и данных в нем.
void delTree(tree *T)
{
    delete[] (T->pBuf[T->ptr - 1]->data);
    T->pBuf[T->ptr - 1]->data = nullptr;
    T->pBuf[T->ptr - 1]->flag = 0;
}