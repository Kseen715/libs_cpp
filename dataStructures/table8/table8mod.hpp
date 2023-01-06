#ifndef __KSI_TABLE_8_MOD_HPP
#define __KSI_TABLE_8_MOD_HPP

#include <iomanip>

#include <table8.hpp>

// Вывод таблицы на экран.
void print(Table *T);

// Вывод элемента таблицы на экран.
void print(ElTable *ElT);

// Вывод элемента таблицы на экран.
void print(Element *E);

// Запись элемента в таблицу по значению.
int PutTable(Table *T, int E_Data, T_Key E_Key, cmpFunc cmp);

#endif // __KSI_TABLE_8_MOD_HPP