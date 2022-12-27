#ifndef __KSI_TREE_8_MOD_HPP
#define __KSI_TREE_8_MOD_HPP

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <stack>

#include "tree8.hpp"

#ifndef __KSI_TREE_8_CLASS
#define __KSI_TREE_8_CLASS
template <typename T>
class treeClass
{
protected:
    // Дерево.
    tree _tree;
    // Тип узла.
    enum branch
    {
        ROOT = 0, // Корень.
        LEFT = 1, // Левый сын.
        RIGHT = 2 // Правый сын.
    };
    // Тип текущего узла по отношению к верхнему узлу.
    std::vector<int> currentBranch;
    // Карта элементов дерева.
    std::vector<bool> branchMap;
    // Размер дерева.
    unsigned size;

    // Рекурсивная функция для обхода дерева в глубину.
    std::vector<T> walkDeepRecursion(std::vector<T> &result)
    {
        result.push_back(read());
        if (hasLSon())
        {
            moveL();
            walkDeepRecursion(result);
            moveUp();
        }
        if (hasRSon())
        {
            moveR();
            walkDeepRecursion(result);
            moveUp();
        }
        // if not root and has son, go to unchecked son
        // if not root and has no son, go to parent
        // if root, return

        return result;
    }

public:
    // Конструктор по умолчанию.
    treeClass(unsigned size);

    // Деструктор по умолчанию.
    ~treeClass();

    // Возвращает размер дерева.
    unsigned getSize();

    // Возвращает дерево.
    tree getTree();

    // Возвращает вектор с картой элементов дерева.
    std::vector<bool> getBranchMap();

    // Возвращает вектор с адресом до текущего листа.
    std::vector<int> getCurrentBranch();

    // Записывает данные в текущий лист и перемещает указатель на левого сына.
    void pushNL(T data);

    // Записывает данные в текущий лист и перемещает указатель на правого сына.
    void pushNR(T data);

    // Перемещает указатель на верхний узел.
    void moveUp();

    // Перемещает указатель на левого сына.
    void moveL();

    // Перемещает указатель на правого сына.
    void moveR();

    // Перемещает указатель на корень дерева.
    void moveToRoot();

    // Возвращает копию данных из текущего листа дерева _tree.
    T read();

    // Возвращает копию данных из текущего листа дерева _tree и удаляет лист.
    T pop();

    // ЗАписывает данные в текущий лист.
    void write(T data);

    // Выводит текущий путь от корня до текущего узла.
    void printOrder();

    // Проверяет, есть ли левый сын.
    bool hasLSon();

    // Проверяет, есть ли правый сын.
    bool hasRSon();

    // Удаляет лист дерева, находящийся над текущим узлом.
    void delLeaf();

    // Удаляет текущий лист дерева.
    void delCurrentList();

    void set(T data);

    // check if leaf is empty
    bool emptyLeaf()
    {
        return _tree.pBuf[_tree.ptr - 1]->flag = 0;
    }

    // Обход дерева в глубину, возвращает вектор с данными.
    std::vector<T> walkDeep()
    {
        std::vector<T> result;
        moveToRoot();
        walkDeepRecursion(result);
        return result;
    }

    void print()
    {
        moveToRoot();
        printRecursion();
    }

    void printRecursion()
    {
        std::cout << "(";
        std::cout << read();
        if (hasLSon())
        {
            moveL();
            printRecursion();
            moveUp();
        }
        else
        {
            std::cout << "()";
        }

        if (hasRSon())
        {
            moveR();
            printRecursion();
            moveUp();
        }
        else
        {
            std::cout << "()";
        }
        std::cout << ")";
    }

    void formDeep(std::vector<T> data)
    {
        // 1. Инициализировать стек .
        // 2. Прочитать очередной символ последовательности .
        // 3. Если прочитанный символ точка, то БД пустое, иначе создать корень,
        // записать в него символ, корень поместить в стек.
        // 4. Пока стек не пуст, выполнять п .5.
        // 5. Прочитать символ, извлечь вершину из стека.Если для вершины ле -
        // вое поддерево не построено, то построить его в соответствии с п .6,
        // если не построено правое поддерево, то построить его в соответствии
        // с п .7.
        // 6. Если символ точка, то левое поддерево пустое, вернуть вершину в
        // стек, иначе создать корень левого поддерева, записать в него символ,
        // вер - нуть в стек вершину, созданный корень поместить в стек.
        // 7. Если символ точка, то правое поддерево пустое, иначе создать ко -
        // рень правого поддерева, записать в него символ, созданный корень
        // поместить в стек.

        std::stack<T> stack;

        // write data to stack from vector
        for (unsigned i = 0; i < data.size(); i++)
        {
            stack.push(data[i]);
        }
        while (stack.size() > 0)
        {
            T data = stack.top();
            stack.pop();
            if (data == '.')
            {
                // empty tree
                return;
            }
            else
            {
                // create root
                addRoot(data);
            }
            while (stack.size() > 0)
            {
                T data = stack.top();
                stack.pop();
                if (data == '.')
                {
                    // empty tree
                    return;
                }
                else
                {
                    // create root
                    addRoot(data);
                }
            }
        }
    }
};

std::vector<int> parseStrToInt(std::string str)
{
    // parse data from string like
    // "(42(43(45(49()())(50()()))(46(51()())(52()())))(44(47"
    // "(53()())(54()()))(48(55()())(56()()))))"
    std::vector<int> result;
    std::string temp;
    // convert data in string to its type
    for (unsigned i = 0; i < str.size(); i++)
    {
        if (str[i] == '(' || str[i] == ')')
        {
            if (temp.size() > 0)
            {

                result.push_back(std::stoi(temp));
                temp.clear();
            }
        }
        else
        {
            temp += str[i];
        }
    }
    return result;
}

template <typename T>
void treeClass<T>::set(T data)
{
    T *pData = new T;
    *pData = data;
    writeDataTree((tree *)&_tree, (tree8BaseType)pData);
}

template <typename T>
treeClass<T>::treeClass(unsigned size)
{
    this->size = size;
    initTree(&_tree, size);
    createRoot(&_tree);
    currentBranch.push_back(ROOT);
    branchMap.resize(size);
    for (unsigned i = 0; i < size; i++)
    {
        branchMap[i] = false;
    }
}

template <typename T>
treeClass<T>::~treeClass()
{
    for (unsigned i = 0; i < size; i++)
    {
        if (branchMap[i])
        {
            moveUp();
            delLeaf();
            branchMap[i] = false;
        }
    }
    delete[] _tree.pBuf;
}

template <typename T>
unsigned treeClass<T>::getSize()
{
    return size;
}

template <typename T>
tree treeClass<T>::getTree()
{
    return _tree;
}

template <typename T>
std::vector<bool> treeClass<T>::getBranchMap()
{
    return branchMap;
}

template <typename T>
std::vector<int> treeClass<T>::getCurrentBranch()
{
    return currentBranch;
}

template <typename T>
void treeClass<T>::pushNL(T data)
{
    T *pData = new T;
    *pData = data;
    writeDataTree((tree *)&_tree, (tree8BaseType)pData);
    moveL();
    branchMap[_tree.ptr - 1] = true;
}

template <typename T>
void treeClass<T>::pushNR(T data)
{
    T *pData = new T;
    *pData = data;
    writeDataTree((tree *)&_tree, (tree8BaseType)pData);
    moveR();
    branchMap[_tree.ptr - 1] = true;
}

template <typename T>
void treeClass<T>::moveUp()
{
    if (currentBranch.back() == ROOT)
        return;
    else if (currentBranch.back() == LEFT)
    {
        moveToLSon(nullptr, &_tree);
        currentBranch.pop_back();
    }
    else if (currentBranch.back() == RIGHT)
    {
        moveToRSon(nullptr, &_tree);
        currentBranch.pop_back();
    }
}

template <typename T>
void treeClass<T>::moveL()
{
    moveToLSon(&_tree, nullptr);
    currentBranch.push_back(LEFT);
}

template <typename T>
void treeClass<T>::moveR()
{
    moveToRSon(&_tree, nullptr);
    currentBranch.push_back(RIGHT);
}

template <typename T>
void treeClass<T>::moveToRoot()
{
    while (currentBranch.back() != ROOT)
        moveUp();
}

template <typename T>
T treeClass<T>::read()
{
    tree8BaseType E;
    readDataTree(&_tree, &E);
    return *(T *)E;
}

template <typename T>
T treeClass<T>::pop()
{
    T temp = read();
    delLeaf();
    return temp;
}

template <typename T>
void treeClass<T>::write(T data)
{
    T *pData = new T;
    *pData = data;
    writeDataTree((tree *)&_tree, (tree8BaseType)pData);
}

template <typename T>
void treeClass<T>::printOrder()
{
    for (auto i : currentBranch)
    {
        if (i == ROOT)
            std::cout << "0 ";
        else if (i == LEFT)
            std::cout << "L ";
        else if (i == RIGHT)
            std::cout << "R ";
    }
    std::cout << std::endl;
}

template <typename T>
bool treeClass<T>::hasLSon()
{
    return isLSon(&_tree);
}

template <typename T>
bool treeClass<T>::hasRSon()
{
    return isRSon(&_tree);
}

template <typename T>
void treeClass<T>::delCurrentList()
{
    delTree((tree *)&_tree);
    branchMap[_tree.ptr] = false;
}

template <typename T>
void treeClass<T>::delLeaf()
{
    moveUp();
    delTree((tree *)&_tree);
    branchMap[_tree.ptr] = false;
}

#endif // __KSI_TREE_8_CLASS

#endif // __KSI_TREE_8_MOD_HPP