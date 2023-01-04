#ifndef __KSI_TREE_8_MOD_HPP
#define __KSI_TREE_8_MOD_HPP

#include <iostream>
#include <cassert>
#include <vector>
#include <string>

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
    enum branchType
    {
        ROOT = 0, // Корень.
        LEFT = 1, // Левый сын.
        RIGHT = 2 // Правый сын.
    };
    // Тип текущего узла по отношению к верхнему узлу (адрес текущего узла).
    std::vector<int> currentBranchAddr;
    // Карта элементов дерева. Используется для определения, есть ли узел в
    // дереве. Позволяет эффективно перемещаться вверх по дереву.
    std::vector<bool> branchMap;
    // Размер дерева.
    unsigned size;

    // Рекурсивная часть функции для обхода дерева в глубину.
    // Параметры:
    // > result - вектор для хранения результатов обхода.
    void _walkDeepRecursion(std::vector<T> &result)
    {
        result.push_back(read());
        if (hasLSon()) // Если есть левый сын.
        {
            moveL();                    // Переходим к нему.
            _walkDeepRecursion(result); // Рекурсивно продолжаем обход.
            moveUp();                   // Возвращаемся к верхнему узлу.
        }
        if (hasRSon()) // Если есть правый сын.
        {
            moveR();                    // Переходим к правому сыну.
            _walkDeepRecursion(result); // Рекурсивно продолжаем обход.
            moveUp();                   // Возвращаемся к верхнему узлу.
        }
    }

    // Рекурсивная часть функции для получения всех узлов с одинаковым
    // количеством листьев в поддеревьях.
    // Параметры:
    // > result - вектор для хранения результатов обхода.
    void _getEqualSubTreeRecursion(std::vector<T> &result)
    {
        if (hasLSon() && hasRSon()) // Если присутствуют оба сына.
        {
            moveL();                                 // Переходим к левому сыну.
            auto left_count = _getCountRecursion();  // Получаем количество
                                                     // листьев в левом
                                                     // поддереве.
            moveUp();                                // Возвращаемся к верхнему
                                                     // узлу.
            moveR();                                 // Переходим к правому
                                                     // сыну.
            auto right_count = _getCountRecursion(); // Получаем количество
                                                     // листьев в правом
                                                     // поддереве.
            moveUp();                                // Возвращаемся к верхнему
                                                     // узлу.
            if (left_count == right_count)           // Если количество листьев
                                                     // в поддеревьях одинаково.
            {
                result.push_back(read()); // Добавляем текущий узел в результат.
            }
        }
        if (hasLSon()) // Если есть левый сын.
        {
            moveL();                           // Переходим к левому сыну.
            _getEqualSubTreeRecursion(result); // Рекурсивно продолжаем обход.
            moveUp();                          // Возвращаемся к верхнему узлу.
        }
        if (hasRSon()) // Если есть правый сын.
        {
            moveR();                           // Переходим к правому сыну.
            _getEqualSubTreeRecursion(result); // Рекурсивно продолжаем обход.
            moveUp();                          // Возвращаемся к верхнему узлу.
        }
    }

    // Рекурсивная часть функции для подсчета количества листьев в дереве.
    // Возвращает количество листьев в поддереве.
    int _getCountRecursion()
    {
        int result = 1; // Считаем текущий узел листом.
        if (hasLSon())  // Если есть левый сын.
        {
            moveL();                        // Переходим к левому сыну.
            result += _getCountRecursion(); // Рекурсивно продолжаем обход.
            moveUp();                       // Возвращаемся к верхнему узлу.
        }
        if (hasRSon()) // Если есть правый сын.
        {
            moveR();                        // Переходим к правому сыну.
            result += _getCountRecursion(); // Рекурсивно продолжаем обход.
            moveUp();                       // Возвращаемся к верхнему узлу.
        }
        return result;
    }

    // Рекурсивная часть функции для получения всех узлов со значением элемента
    // меньше ключа key.
    // Параметры:
    // > result - вектор для записи результата.
    void _getLessThanRecursion(std::vector<T> &result, T key)
    {
        auto readed_key = read(); // Читаем значение текущего узла.
        if (readed_key < key)     // Если значение меньше ключа.
        {
            result.push_back(readed_key); // Добавляем значение в результат.
        }
        if (hasLSon()) // Если есть левый сын.
        {
            moveL();                            // Переходим к левому сыну.
            _getLessThanRecursion(result, key); // Рекурсивно продолжаем обход.
            moveUp();                           // Возвращаемся к верхнему узлу.
        }
        if (hasRSon() && readed_key < key) // Если есть правый сын и значение
                                           // меньше ключа.
        {
            moveR();                            // Переходим к правому сыну.
            _getLessThanRecursion(result, key); // Рекурсивно продолжаем обход.
            moveUp();                           // Возвращаемся к верхнему узлу.
        }
    }

    // Рекурсивная часть функции для вывода дерева.
    void _printRecursion()
    {
        std::cout << "(";    // Открываем скобку.
        std::cout << read(); // Выводим значение текущего узла.
        if (hasLSon())       // Если есть левый сын.
        {
            moveL();           // Переходим к левому сыну.
            _printRecursion(); // Рекурсивно продолжаем обход.
            moveUp();          // Возвращаемся к верхнему узлу.
        }
        else
        {
            std::cout << "()"; // Если нет левого сына, выводим пустую пару.
        }

        if (hasRSon()) // Если есть правый сын.
        {
            moveR();           // Переходим к правому сыну.
            _printRecursion(); // Рекурсивно продолжаем обход.
            moveUp();          // Возвращаемся к верхнему узлу.
        }
        else
        {
            std::cout << "()"; // Если нет правого сына, выводим пустую пару.
        }
        std::cout << ")"; // Закрываем скобку.
    }

public:
    // Конструктор по умолчанию.
    // Параметры:
    // > size - размер дерева.
    treeClass(unsigned size);

    // Деструктор по умолчанию.
    ~treeClass();

    // Возвращает размер дерева.
    unsigned getSize();

    // Возвращает дерево.
    tree getTree();

    // Возвращает вектор с картой элементов дерева.
    std::vector<bool> getBranchMap();

    // Возвращает вектор с адресом текущего листа в дереве в виде
    // последовательности отношений к родителю.
    std::vector<int> getCurrentBranchAddr();

    // Записывает данные data в текущий лист и перемещает указатель на левого
    // сына.
    // Параметры:
    // > data - данные, которые нужно записать в лист.
    void pushNL(T data);

    // Записывает данные data в текущий лист и перемещает указатель на правого
    // сына.
    // Параметры:
    // > data - данные, которые нужно записать в лист.
    void pushNR(T data);

    // Перемещает указатель на верхний узел.
    void moveUp();

    // Перемещает указатель на левого сына.
    void moveL();

    // Перемещает указатель на правого сына.
    void moveR();

    // Перемещает указатель на корень дерева.
    void moveToRoot();

    // Записывает данные в текущий лист.
    // Параметры:
    // > data - данные, которые нужно записать в лист.
    void write(T data);

    // Возвращает копию данных из текущего листа дерева.
    T read();

    // Возвращает копию данных из текущего листа дерева и удаляет лист.
    T pop();

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

    // Проверяет, пуст ли текущий лист.
    bool emptyLeaf();

    // Обход дерева в глубину, возвращает вектор с данными.
    std::vector<T> walkDeep();

    // Выводит дерево в скобочной записи.
    void print();

    // Записывает новый элемент key в сбалансированное дерево.
    // Параметры:
    // > key - ключ, который нужно записать в дерево.
    void putBalance(T key);

    // Возвращает вектор с элементами, меньше ключа key.
    // Параметры:
    // > key - ключ, с которым нужно сравнить элементы дерева.
    std::vector<T> getLessThan(T key);

    // Выводит вершины дерева, для которых левое и правое поддерево имеют равное
    // количество вершин.
    std::vector<T> getEqualSubTree();
};

template <typename T>
bool treeClass<T>::emptyLeaf()
{
    return _tree.pBuf[_tree.ptr - 1]->flag = 0; // Если лист пустой, то
                                                // возвращаем true.
}

template <typename T>
std::vector<T> treeClass<T>::walkDeep()
{
    std::vector<T> result;
    moveToRoot();               // Перемещаем указатель на корень.
    _walkDeepRecursion(result); // Рекурсивно обходим дерево.
    return result;
}

template <typename T>
void treeClass<T>::print()
{
    moveToRoot();      // Перемещаем указатель на корень.
    _printRecursion(); // Рекурсивно выводим дерево.
}

template <typename T>
void treeClass<T>::putBalance(T key)
{
    moveToRoot();            // Перемещаем указатель на корень.
    if (isEmptyTree(&_tree)) // Если дерево пустое, то вставляем корень.
    {
        write(key);
        return;
    }
    bool put_flag = false;
    while (!put_flag) // Ищем место для вставки.
    {
        if (key == read()) // Если нашли ключ в дереве, то выходим.
        {
            put_flag = true;
        }
        else if (key < read()) // Если ключ меньше, то идем влево.
        {
            if (hasLSon()) // Если есть левый сын, то идем влево.
            {
                moveL();
            }
            else // Если нет левого сына, то вставляем ключ в левое
                 // поддерево.
            {
                moveL();
                write(key);
                put_flag = true;
            }
        }
        else // Если ключ больше, то идем вправо.
        {
            if (hasRSon()) // Если есть правый сын, то идем вправо.
            {
                moveR();
            }
            else // Если нет правого сына, то вставляем ключ в правое
                 // поддерево.
            {
                moveR();
                write(key);
                put_flag = true;
            }
        }
    }
}

template <typename T>
std::vector<T> treeClass<T>::getLessThan(T key)
{
    std::vector<T> result;
    moveToRoot();                       // Перемещаем указатель на корень.
    _getLessThanRecursion(result, key); // Рекурсивно обходим дерево.
    return result;
}

template <typename T>
std::vector<T> treeClass<T>::getEqualSubTree()
{
    std::vector<T> result;
    moveToRoot();                      // Перемещаем указатель на корень.
    _getEqualSubTreeRecursion(result); // Рекурсивно обходим дерево.
    return result;
}

template <typename T>
treeClass<T>::treeClass(unsigned size)
{
    this->size = size;                 // Устанавливаем размер дерева.
    initTree(&_tree, size);            // Инициализируем дерево.
    createRoot(&_tree);                // Создаем корень.
    currentBranchAddr.push_back(ROOT); // Устанавливаем тип текущей ветки на
                                       // корень.
    branchMap.resize(size);            // Устанавливаем размер вектора
                                       // branchMap.
    for (unsigned i = 0; i < size; i++)
    {
        branchMap[i] = false; // Устанавливаем все элементы вектора branchMap
                              // в false так как дерево пустое.
    }
}

template <typename T>
treeClass<T>::~treeClass()
{
    for (unsigned i = 0; i < size; i++)
    {
        if (branchMap[i]) // Если ветка существует, то удаляем ее.
        {
            moveUp();             // Перемещаем указатель на родителя.
            delLeaf();            // Удаляем лист.
            branchMap[i] = false; // Устанавливаем ветку в false.
        }
    }
    delete[] _tree.pBuf; // Удаляем дерево.
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
std::vector<int> treeClass<T>::getCurrentBranchAddr()
{
    return currentBranchAddr;
}

template <typename T>
void treeClass<T>::pushNL(T data)
{
    T *pData = new T;                                    // Выделяем память под
                                                         // новый элемент.
    *pData = data;                                       // Записываем данные в
                                                         // новый элемент.
    writeDataTree((tree *)&_tree, (tree8BaseType)pData); // Записываем данные в
                                                         // дерево.
    moveL();                                             // Перемещаем указатель
                                                         // на левого сына.
    branchMap[_tree.ptr - 1] = true;                     // Устанавливаем карту
                                                         // в true.
}

template <typename T>
void treeClass<T>::pushNR(T data)
{
    T *pData = new T;                                    // Выделяем память под
                                                         // новый элемент.
    *pData = data;                                       // Записываем данные в
                                                         // новый элемент.
    writeDataTree((tree *)&_tree, (tree8BaseType)pData); // Записываем данные в
                                                         // дерево.
    moveR();                                             // Перемещаем указатель
                                                         // на правого сына.
    branchMap[_tree.ptr - 1] = true;                     // Устанавливаем карту
                                                         // в true.
}

template <typename T>
void treeClass<T>::moveUp()
{
    if (currentBranchAddr.back() == ROOT) // Если текущая ветка корень, то
                                          // ничего не делаем.
        return;
    else if (currentBranchAddr.back() == LEFT) // Если текущая ветка левый сын,
                                               // то перемещаем указатель на
                                               // родителя.
    {
        moveToLSon(nullptr, &_tree);  // Перемещаем указатель на родителя.
        currentBranchAddr.pop_back(); // Удаляем последний элемент вектора
                                      // currentBranchAddr.
    }
    else if (currentBranchAddr.back() == RIGHT) // Если текущая ветка правый
                                                // сын, то перемещаем указатель
                                                // на родителя.
    {
        moveToRSon(nullptr, &_tree);  // Перемещаем указатель на родителя.
        currentBranchAddr.pop_back(); // Удаляем последний элемент вектора
                                      // currentBranchAddr.
    }
}

template <typename T>
void treeClass<T>::moveL()
{
    moveToLSon(&_tree, nullptr);       // Перемещаем указатель на левого сына.
    currentBranchAddr.push_back(LEFT); // Добавляем в вектор currentBranchAddr
                                       // элемент LEFT.
}

template <typename T>
void treeClass<T>::moveR()
{
    moveToRSon(&_tree, nullptr);        // Перемещаем указатель на правого сына.
    currentBranchAddr.push_back(RIGHT); // Добавляем в вектор currentBranchAddr
                                        // элемент RIGHT.
}

template <typename T>
void treeClass<T>::moveToRoot()
{
    while (currentBranchAddr.back() != ROOT) // Пока текущая ветка не корень,
                                             // перемещаем указатель на
                                             // родителя.
        moveUp();                            // Перемещаем указатель на
                                             // родителя.
}

template <typename T>
T treeClass<T>::read()
{
    tree8BaseType E;          // Создаем переменную типа tree8BaseType.
    readDataTree(&_tree, &E); // Читаем данные из дерева.
    return *(T *)E;           // Возвращаем данные.
}

template <typename T>
T treeClass<T>::pop()
{
    T temp = read(); // Читаем данные из дерева.
    delLeaf();       // Удаляем лист.
    return temp;     // Возвращаем данные.
}

template <typename T>
void treeClass<T>::write(T data)
{
    T *pData = new T;                                    // Создаем указатель на
                                                         // данные.
    *pData = data;                                       // Записываем данные в
                                                         // указатель.
    writeDataTree((tree *)&_tree, (tree8BaseType)pData); // Записываем данные в
                                                         // дерево.
}

template <typename T>
void treeClass<T>::printOrder()
{
    for (auto i : currentBranchAddr) // Перебираем вектор currentBranchAddr.
    {
        if (i == ROOT)         // Если текущая ветка корень, то выводим 0.
            std::cout << "0 "; //
        else if (i == LEFT)    // Если текущая ветка левый сын, то выводим L.
            std::cout << "L "; //
        else if (i == RIGHT)   // Если текущая ветка правый сын, то выводим R.
            std::cout << "R "; //
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
    delTree((tree *)&_tree);      // Удаляем текущий лист.
    branchMap[_tree.ptr] = false; // Удаляем текущий лист из branchMap.
}

template <typename T>
void treeClass<T>::delLeaf()
{
    moveUp();                     // Перемещаем указатель на родителя.
    delTree((tree *)&_tree);      // Удаляем текущий лист.
    branchMap[_tree.ptr] = false; // Удаляем текущий лист из branchMap.
}

#endif // __KSI_TREE_8_CLASS

// Возвращает последовательность элементов из скобочной записи strTree дерева.
std::vector<int> parseStrToInt(std::string strTree);

#endif // __KSI_TREE_8_MOD_HPP