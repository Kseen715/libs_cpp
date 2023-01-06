#include "table8.hpp"

void InitTable(Table *T, unsigned SizeBuf, unsigned SizeEl)
{
    // Для инициализации таблицы используется конструктор структуры Table.
    *T = Table(SizeBuf, SizeEl);
}

int comp(void *a, void *b)
{
    return strcmp((char *)(((Element *)((ElTable *)a)->E)->Key).c_str(),
                  (char *)(((Element *)((ElTable *)b)->E)->Key).c_str());
}

int EmptyTable(Table *T)
{
    return T->n == 0;
}

int PutTable(Table *T, void *E, T_Key Key, cmpFunc cmp)
{
    Element *El = new Element(Key, *(int *)E); // Копируем данные в элемент
                                               // таблицы.
    ElTable ElT(El);                           // Копируем адрес элемента в
                                               // ElTable, устанавливаем флаг
                                               // Busy.

    if (T->n == T->SizeBuf) // Если таблица заполнена, то возвращаем 0.
        return 0;
    unsigned h = _Hash1(T, Key); // Вычисляем хеш-значение ключа.

    if (T->Buf[h].flag == Busy) // Если ячейка занята, то ищем свободную.
    {
        if (cmp(&T->Buf[h], &ElT) == 0) // Если элемент с таким ключом уже есть
                                        // в таблице, то возвращаем 0.
            return 0;
        unsigned h2 = _Hash2(T, Key); // Вычисляем второе хеш-значение ключа.
        unsigned i = 1;
        do // Ищем следующую ячейку.
        {
            h = (h + i * h2) % T->SizeBuf; // Вычисляем следующее хеш-значение.
            i++;
            // Если элемент с таким ключом уже есть в таблице, то возвращаем 0.
            if (T->Buf[h].flag == Busy)
                if (cmp(&T->Buf[h], &ElT) == 0) // Если элемент с таким ключом
                                                // уже есть в таблице, то
                                                // возвращаем 0.
                    return 0;
        } while (T->Buf[h].flag == Busy);
    }
    // Свободная ячейка найдена
    T->Buf[h] = ElT; // Копируем ElT в таблицу.
    T->n++;          // Увеличиваем количество элементов в таблице.
    return 1;
}

int GetTable(Table *T, void *E, T_Key Key, cmpFunc cmp)
{
    Element *key_to_search_el = new Element(Key, NULL); // Копируем данные в
                                                        // элемент таблицы.
    ElTable key_table_to_search(key_to_search_el);      // Копируем адрес
                                                        // элемента в ElTable,
                                                        // устанавливаем флаг
                                                        // Busy.

    if (T->n == 0) // Если таблица пуста, то возвращаем 0.
        return 0;
    unsigned h = _Hash1(T, Key); // Вычисляем хеш-значение ключа.

    if (T->Buf[h].flag == Busy) // Если ячейка занята, то рассматриваем ее.
    {
        ElTable T_eltable = T->Buf[h]; // Копируем ячейку таблицы в ElTable.

        if (cmp(&T_eltable, &key_table_to_search) == 0) // Если элемент с таким
                                                        // ключом есть в
                                                        // таблице.
        {
            Element *p = (Element *)T->Buf[h].E; // Копируем данные из
                                                 // элемента таблицы в E.
            *(int *)E = p->Data;                 // Копируем данные из
                                                 // элемента таблицы в E.
            T->Buf[h].flag = Deleted;            // Устанавливаем флаг Deleted.
            T->n--;                              // Уменьшаем количество
                                                 // элементов в таблице.
            T->Buf[h].E = nullptr;               // Удаляем элемент из таблицы.
            return 1;
        }
        unsigned h2 = _Hash2(T, Key); // Вычисляем второе хеш-значение ключа.
        unsigned i = 1;
        do // Ищем следующую ячейку.
        {
            h = (h + i * h2) % T->SizeBuf; // Вычисляем следующее хеш-значение.
            i++;
            if (cmp(&(T->Buf[h]), &key_table_to_search) == 0) // Если элемент с
                                                              // таким ключом
                                                              // есть в
                                                              // таблице.
            {
                Element *p = (Element *)T->Buf[h].E; // Копируем данные из
                                                     // элемента таблицы в E.
                *(int *)E = p->Data;                 // Копируем данные из
                                                     // элемента таблицы в E.
                T->Buf[h].flag = Deleted;            // Устанавливаем флаг
                                                     // Deleted.
                T->n--;                              // Уменьшаем количество
                                                     // элементов в таблице.
                T->Buf[h].E = nullptr;               // Удаляем элемент из
                                                     // таблицы.
                return 1;
            }
        } while (T->Buf[h].flag == Busy);
    }
    return 0;
}

int ReadTable(Table *T, void *E, T_Key Key, cmpFunc cmp)
{
    // E - указатель на элемент, который нужно вернуть.
    // Key - ключ, по которому ищем элемент в таблице.
    Element *key_to_search_el = new Element(Key, NULL); // Создаем элемент с
                                                        // ключом Key.

    ElTable key_table_to_search(key_to_search_el); // Создаем элемент таблицы
                                                   // с ключом Key.

    if (T->n == 0) // Если таблица пуста, то возвращаем 0.
        return 0;
    unsigned h = _Hash1(T, Key); // Вычисляем хеш-значение ключа.

    if (T->Buf[h].flag == Busy) // Рассматриваем ячейку, если она занята.
    {
        ElTable T_eltable = T->Buf[h]; // Создаем элемент таблицы с ключом
                                       // T->Buf[h].

        if (cmp(&T_eltable, &key_table_to_search) == 0) // Если элемент с таким
                                                        // ключом есть в
                                                        // таблице.

        {
            Element *p = (Element *)T->Buf[h].E; // Копируем данные из элемента
                                                 // таблицы в E.
            *(int *)E = p->Data;                 // Копируем данные из
                                                 // элемента таблицы в E.
            return 1;
        }
        unsigned h2 = _Hash2(T, Key); // Вычисляем второе хеш-значение.
        unsigned i = 1;
        do
        {
            h = (h + i * h2) % T->SizeBuf; // Вычисляем следующее хеш-значение.
            i++;                           // Увеличиваем счетчик.

            if (cmp(&(T->Buf[h]), &key_table_to_search) == 0) // Если элемент с
                                                              // таким ключом
                                                              // есть в таблице.

            {
                Element *p = (Element *)T->Buf[h].E; // Копируем данные из
                                                     // элемента таблицы в E.
                *(int *)E = p->Data;                 // Копируем данные из
                                                     // элемента таблицы в E.
                return 1;
            }
        } while (T->Buf[h].flag == Busy);
    }
    return 0;
}

int WriteTable(Table *T, void *E, T_Key Key, cmpFunc cmp)
{
    Element *El = new Element(Key, NULL); // Копируем данные в элемент
                                          // таблицы.
    ElTable ElT(El);                      // Копируем адрес элемента в
                                          // ElTable, устанавливаем флаг
                                          // Busy.

    if (T->n == T->SizeBuf) // Если таблица заполнена, то возвращаем 0.
        return 0;
    unsigned h = _Hash1(T, Key); // Вычисляем хеш-значение ключа.

    if (T->Buf[h].flag == Busy) // Рассматриваем ячейку, если она занята.
    {
        if (cmp(&T->Buf[h], &ElT) == 0) // Если элемент с таким ключем уже
                                        // есть в таблице, то возвращаем 0.
        {
            Element *p = (Element *)T->Buf[h].E; // Копируем данные из
                                                 // элемента таблицы в E.
            p->Data = *(int *)E;                 // Копируем данные из
                                                 // элемента таблицы в E.
            return 1;
        }
        unsigned h2 = _Hash2(T, Key); // Вычисляем второе хеш-значение.
        unsigned i = 1;
        do
        {
            h = (h + i * h2) % T->SizeBuf; // Вычисляем следующее хеш-значение.
            i++;
            // Если элемент с таким ключом уже есть в таблице, то возвращаем 0.
            if (T->Buf[h].flag == Busy) // Рассматриваем ячейку, если она
                                        // занята.

                if (cmp(&T->Buf[h], &ElT) == 0) // Если элемент с таким ключем
                                                // уже есть в таблице, то
                                                // возвращаем 0.
                {
                    Element *p = (Element *)T->Buf[h].E; // Копируем данные из
                                                         // элемента таблицы в
                                                         // E.
                    p->Data = *(int *)E;                 // Копируем данные из
                                                         // элемента таблицы в
                                                         // E.
                    return 1;
                }
        } while (T->Buf[h].flag == Busy);
    }
    return 0;
}

void DoneTable(Table *T)
{
    T->~Table(); // Удаляем таблицу, вызывая деструктор.
}

unsigned _Hash1(Table *T, T_Key Key)
{
    unsigned i, h = 0;
    for (i = 0; i < Key.size(); i++)
        h = (h + Key[i]) % T->SizeBuf;
    return h;
}

unsigned _Hash2(Table *T, T_Key Key)
{
    unsigned i, h = 0;
    for (i = 0; i < Key.size(); i++)
        h = (h ^ 0b1010100101101010111001001010 + Key[i]) % T->SizeBuf;
    return h;
}