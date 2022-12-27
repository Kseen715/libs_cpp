#ifndef __KSI_TREE_8_HPP
#define __KSI_TREE_8_HPP

#include <cassert>

// Элементы дерева находятся в массиве, расположенном в динамической памяти.
// Базовый тип - произвольный. Каждый элемент массива имеет признак того,
// является ли он элементом дерева или «свободен». Корень дерева находится в
// первом элементе массива. Для вершины дерева, расположенной в n-м элементе
// массива, LSon будет находиться в (2*n)-м элементе, а RSon — в (2*n + 1)-м.

// Максимальный размер дерева.
#define INDEX 1000

const short treeOk = 0;
const short treeNotMem = 1;
const short treeUnder = 2;

// Тип данных для хранения в дереве - указатель на переменную.
typedef void *tree8BaseType;

// Тип данных для хранения адреса элемента.
typedef unsigned ptrEl;

// Структура для хранения элемента дерева.
typedef struct element
{
    tree8BaseType data;
    short flag; // 0 — элемент занят, 1 — элемент свободен
} element;

// Массив элементов.
typedef element mem[INDEX];

// Указатель на массив элементов.
typedef mem *pMem;

typedef struct tree
{
    pMem pBuf;     // Указатель на массив
    unsigned size; // Размер массива
    ptrEl ptr;     // Указатель на текущий элемент
} tree;

// Переменная для хранения кода ошибки.
extern short treeError;

// Инициализация дерева.
void initTree(tree *T, unsigned size);

// Создание корня.
void createRoot(tree *T);

// Запись данных.
void writeDataTree(tree *T, tree8BaseType E);

// Чтение данных.
void readDataTree(tree *T, tree8BaseType *E);

// 1 — есть левый сын, 0 — нет.
int isLSon(tree *T);

// 1 — есть правый сын, 0 — нет.
int isRSon(tree *T);

// Перейти к левому сыну, где T — адрес ячейки, содержащей адрес текущей
// вершины, TS — адрес ячейки, содержащей адрес корня левого поддерева(левого
// сына).
void moveToLSon(tree *T_down, tree *T_up);

// Перейти к правому сыну.
void moveToRSon(tree *T_down, tree *T_up);

// 1 — пустое дерево,0 — не пустое.
int isEmptyTree(tree *T);

// Удаление.
void delTree(tree *T);

#endif // __KSI_TREE_8_HPP