#include "tree8.hpp"

short treeError = treeOk;

void initTree(tree *T, unsigned size)
{
    T->pBuf = new mem[size]; // Выделение памяти под массив элементов.
    T->size = size;          // Запись размера массива.
    T->ptr = 0;              // Указатель на текущий элемент.
}

void createRoot(tree *T)
{
    T->ptr = 1;                                    // Указатель на корень.
    T->pBuf[T->ptr - 1]->data = new tree8BaseType; // Выделение памяти под
                                                   // корень.
    T->pBuf[T->ptr - 1]->flag = 0;                 // Указание, что корень
                                                   // пустой.
}

void writeDataTree(tree *T, tree8BaseType E)
{
    T->pBuf[T->ptr - 1]->data = E; // Запись данных в текущий элемент.
    T->pBuf[T->ptr - 1]->flag = 1; // Указание, что элемент не пустой.
}

void readDataTree(tree *T, tree8BaseType *E)
{
    *E = T->pBuf[T->ptr - 1]->data; // Чтение данных из текущего элемента.
}

int isLSon(tree *T)
{
    if (T->ptr * 2 + 1 < T->size)                  // Если указатель на левого
                                                   // сына не выходит за
                                                   // границы массива.
        return T->pBuf[T->ptr * 2 - 1]->flag == 1; // Возвращаем 1, если левый
                                                   // сын не пустой.
    else                                           // Иначе возвращаем 0.
        return 0;
}

int isRSon(tree *T)
{
    if (T->ptr * 2 + 2 < T->size)                      // Если указатель на
                                                       // правого сына не
                                                       // выходит за границы
                                                       // массива.
        return T->pBuf[T->ptr * 2 + 1 - 1]->flag == 1; // Возвращаем 1, если
                                                       // правый сын не пустой.
    else                                               // Иначе возвращаем 0.
        return 0;
}

void moveToLSon(tree *T_down, tree *T_up)
{
    if (T_down)                          // Если указатель на текущий элемент не
                                         // равен nullptr.
        T_down->ptr = (T_down->ptr * 2); // Указатель на текущий элемент
                                         // устанавливается на левого сына.
    if (T_up)                            // Если указатель на родителя не равен
                                         // nullptr.
        T_up->ptr = (T_up->ptr) / 2;     // Указатель на родителя
                                         // устанавливается на текущий элемент.
}

void moveToRSon(tree *T_down, tree *T_up)
{
    if (T_down)                              // Если указатель на текущий
                                             // элемент не равен nullptr.
        T_down->ptr = (T_down->ptr * 2) + 1; // Указатель на текущий элемент
                                             // устанавливается на правого сына.
    if (T_up)                                // Если указатель на родителя не
                                             // равен nullptr.
        T_up->ptr = (T_up->ptr - 1) / 2;     // Указатель на родителя
                                             // устанавливается на текущий
                                             // элемент.
}

int isEmptyTree(tree *T)
{
    return T->pBuf[0]->flag == 0; // Возвращаем 1, если корень пустой.
}

void delTree(tree *T)
{
    delete[] (T->pBuf[T->ptr - 1]->data); // Удаляем данные из текущего
                                          // элемента.
    T->pBuf[T->ptr - 1]->data = nullptr;  // Указатель на данные устанавливаем
                                          // в nullptr.
    T->pBuf[T->ptr - 1]->flag = 0;        // Указание, что элемент пустой.
}