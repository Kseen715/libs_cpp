#include "list8mod.hpp"

template <typename T>
void InputList(List *L, int n)
{
    std::cout << "InputList " << n << " elements: " << std::endl;
    int i;
    for (i = 0; i < n; i++)
    {
        T tempElement;
        std::cin >> tempElement;
        PutList(L, &tempElement);
    }
}

template <typename T>
void AddList(List *L, T element)
{
    PutList(L, &element);
}

template <typename T>
void AddList(List *L, T *element)
{
    PutList(L, element);
}

template <typename T>
void AddList(List *L, T *array, unsigned size)
{
    for (size_t i = 0; i < size; i++)
    {
        AddList(L, array[i]);
    }
}

template <typename T>
void PrintList(List *L)
{
    unsigned tempPtrHolder = L->ptr;
    unsigned n = L->N;
    L->ptr = 1;
    for (unsigned i = 0; i < n; i++)
    {
        BaseType E = new T[1];
        std::cout << i + 1 << ": ";
        ReadList(L, &E);
        MovePtr(L);
        std::cout << *(T *)E << " " << std::endl;
        delete[](T *) E;
    }
    L->ptr = tempPtrHolder;
}

template <typename T>
void PrintDestroyList(List *L)
{
    unsigned n = L->N;
    for (unsigned i = 0; i < n; i++)
    {
        BaseType E = new T[1];
        std::cout << i + 1 << ": ";
        GetList(L, &E);
        std::cout << *(T *)E << " " << std::endl;
        delete[](T *) E;
    }
}

// Многочлен P(x) = anxn + an-1xn-1 + ... + a1x + a0 с целыми коэффици-
// ентами можно представить в виде списка, причем если ai = 0, то соответ-
// ствующее звено не включать в список. Определить процедуру ВЫ-
// ВОД(p,y), которая печатает многочлен р как многочлен от переменной, од-
// нобуквенное имя которой является значением литерного параметра y.
// Применить процедуру ВЫВОД к многочлену P(x) = 3x3 + 2x2 + 5x + 1.

template <typename T>
void PrintPolynom(List *P, char y)
{
    unsigned tempPtrHolder = P->ptr;
    unsigned n = P->N;
    P->ptr = 1;
    for (unsigned i = 0; i < n; i++)
    {
        BaseType E = new T[1];
        ReadList(P, &E);
        MovePtr(P);
        if (*(T *)E != 0)
        {
            if (i == 0)
            {
                std::cout << *(T *)E;
            }
            else
            {
                if (*(T *)E > 0)
                {
                    std::cout << " + " << *(T *)E;
                }
                else
                {
                    std::cout << " - " << -*(T *)E;
                }
            }
            if (i != n - 1)
            {
                std::cout << y;
                if (i != n - 2)
                {
                    std::cout << "^" << n - i - 1;
                }
            }
        }
        delete[](T *) E;
    }
    P->ptr = tempPtrHolder;
}

template <typename T>
void WritePolynom(List *L, char y)
{
    unsigned n;
    std::cout << "Введите степень многочлена: ";
    std::cin >> n;
    for (unsigned i = 0; i < n + 1; i++)
    {
        T E;
        std::cout << "Введите коэффициент при " << y;
        std::cout << "^" << n - i;
        std::cout << ": ";
        std::cin >> E;
        AddList(L, E);
    }
}

void linker()
{
    // call every template function here with null
    // to force linker to include them in the executable
    // and not to throw an error
    InputList<int>(nullptr, 0);
    AddList<int>(nullptr, NULL);
    AddList<int>(nullptr, nullptr);
    AddList<int>(nullptr, nullptr, 0);
    PrintList<int>(nullptr);
    PrintDestroyList<int>(nullptr);
    PrintPolynom<int>(nullptr, 0);
    WritePolynom<int>(nullptr, 0);
}