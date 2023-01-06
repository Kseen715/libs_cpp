// Хэш-таблица с открытой адресацией
// (с помощью двойного хеширования).

#ifndef __KSI_TABLE_8_HPP
#define __KSI_TABLE_8_HPP

#include <string>
#include <iostream>
#include <cassert>

const short TableOk = 0;
const short TableNotMem = 1;
const short TableUnder = 2;

typedef std::string T_Key; // Тип ключа элемента таблицы - строка.

enum T_Flag
{
    Deleted = -1, // Элемент массива был занят.
    Empty = 0,    // Элемент массива свободен.
    Busy = 1,     // Элемент массива занят.
};

typedef struct Element
{
    T_Key Key; // Ключ.
    int Data;  // Данные.

    // Конструктор по умолчанию.
    Element() : Key(""), Data(0) {}

    // Конструктор с параметрами.
    Element(T_Key k, int d) : Key(k), Data(d) {}

    // Конструктор копирования.
    Element(const Element &e) : Key(e.Key), Data(e.Data) {}

    // Деструктор.
    ~Element() {}
} Element;

// Элемент таблицы. Содержит статус элемента массива и указатель на элемент.
typedef struct ElTable
{
    int flag; // Статус элемента массива.
    void *E;  // Указатель на элемент таблицы.

    // Конструктор по умолчанию.
    ElTable() : flag(Empty), E(nullptr) {}

    // Конструктор с параметрами, флаг = Busy по умолчанию.
    ElTable(void *e) : flag(Busy), E(e) {}

    // Конструктор с параметрами.
    ElTable(int f, void *e) : flag(f), E(e) {}

    // Деструктор по умолчанию.
    ~ElTable() {}
} ElTable;

typedef struct Table
{
    ElTable *Buf;     // Указатель на массив элементов таблицы.
    unsigned n;       // Количество элементов в таблице.
    unsigned SizeBuf; // Максимальное количество элементов в массиве.
    unsigned SizeEl;  // Размер элемента таблицы.

    // Конструктор по умолчанию.
    Table() : Buf(nullptr), n(0), SizeBuf(0), SizeEl(0) {}

    // Конструктор с параметрами. Выделяет память под массив элементов таблицы.
    Table(unsigned SizeBuf, unsigned SizeEl) : n(0), SizeBuf(SizeBuf),
                                               SizeEl(SizeEl)
    {
        Buf = new ElTable[SizeBuf * 100];
    }

    // Деструктор. Освобождает память, занятую массивом элементов таблицы.
    ~Table()
    {
        for (unsigned i = 0; i < SizeBuf; i++)
        {
            if (Buf[i].E != nullptr)
            {
                delete (Element *)Buf[i].E;
                Buf[i].E = nullptr;
            }
            if (Buf[i].flag == Busy)
                Buf[i].flag = Deleted;
        }
        if (Buf != nullptr)
        {
            delete[] Buf;
        }
    }
} Table;

// Сравнивает ключи элементов таблицы, адреса которых находятся в параметрах
// a и b. Возвращает –1, если ключ элемента по адресу a меньше ключа элемента
// по адресу b, 0 — если ключи равны и +1 — если ключ элемента по адресу a
// больше ключа элемента по адресу b.
typedef int (*cmpFunc)(void *a, void *b);

// Сравнивает ключи элементов таблицы, адреса которых находятся в параметрах
// a и b. Возвращает –1, если ключ элемента по адресу a меньше ключа элемента
// по адресу b, 0 — если ключи равны и +1 — если ключ элемента по адресу a
// больше ключа элемента по адресу b.
// Принимает указатель на ElTable, сравнивает ключи (Key) элементов таблицы.
int comp(void *a, void *b);

extern int TableError; // 0..2

// Инициализация таблицы. Выделяет память под массив элементов таблицы.
void InitTable(Table *T, unsigned SizeBuf, unsigned SizeEl);

// Возвращает 1 , если таблица пуста, иначе — 0.
int EmptyTable(Table *T);

// Включение элемента в таблицу. Возвращает 1, если элемент включен в таблицу,
// иначе — 0(если в таблице уже есть элемент с заданным ключем или нехватает
// памяти).
int PutTable(Table *T, void *E, T_Key Key, cmpFunc f);

// Исключение элемента. Возвращает 1 , если элемент с ключем Key был в таблице,
// иначе — 0.
int GetTable(Table *T, void *E, T_Key Key, cmpFunc f);

// Чтение элемента. Возвращает 1 , если элемент с ключем Key есть в таблице,
// иначе — 0.
int ReadTable(Table *T, void *E, T_Key Key, cmpFunc f);

// Изменение элемента. Возвращает 1, если элемент с ключем Key есть в таблице,
// иначе — 0.
int WriteTable(Table *T, void *E, T_Key Key, cmpFunc f);

// Уничтожение таблицы.
void DoneTable(Table *T);

// Хэш-функция первого типа. Хэш из строки.
unsigned _Hash1(Table *T, T_Key Key);

// Хэш-функция второго типа. Хэш из строки.
unsigned _Hash2(Table *T, T_Key Key);

#endif // __KSI_TABLE_8_HPP