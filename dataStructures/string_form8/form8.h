#pragma once
#ifndef __FORM8_H
#define __FORM8_H

#include <cstdio>
#include <malloc.h>
#include <iostream>

typedef char *string1;

// Ошибок нет.
const char StrOk = 0;

// Строка пуста.
const char StrEmpty = 1;

// Строка не инициализирована.
const char StrNotInit = 2;

// Переменная ошибок.
extern char StrError;

/* Первые два байта содержат  максимальную длину строки, которая
определяется при инициализации. Признак конца строки - символ '\0' */

// Ввод строки st с клавиатуры.
void InputStr(string1 s);

// Вывод строки s на экран монитора.
void OutputStr(string1 s);

// Выделение динамической памяти под строку st,
// содержащую от 0 до n символов. Значением n определяется
// максимальное количество символов, которое может
// вместить строка (зависит от кол-ва выделенной памяти).
// Динамическая длина строки есть ее текущая длина.
void InitStr(string1 *st, unsigned n);

// Запись данных в строку st из
// строки s. Строка s заканчивается нулевым символом '\0'.
void WriteToStr(string1 st, char *s);

// Запись данных в строку s из
// строки st. Строка s заканчивается нулевым символом '\0'
void WriteFromStr(char *s, string1 st);

// Сравнивает строки s1 и s2.
// Возвращает 0 если s1 = s2; 1, если s1 > s2; -1, если s1 < s2.
int Comp(string1 s1, string1 s2);

// Удаляет Count символов из строки s,
// начиная с позиции Index.
void Delete(string1 s, unsigned Index, unsigned Count);

// Вставляет подстроку SubS в
// строку s, начиная с позиции Index.
void Insert(string1 Subs, string1 s, unsigned Index);

// Выполняет конкатенацию строк
// s1 и s2. Результат помещает в srez.
void Concat(string1 s1, string1 s2, string1 srez);

// Записывает Count символов в строку Subs из строки s,
// начиная с позиции Index.
void Copy(string1 s, unsigned Index, unsigned Count, string1 Subs);

// Возвращает текущую длину строки S.
unsigned Length(string1 s);

// Возвращает позицию, начиная
// с которой в строке s располагается подстрока SubS.
unsigned Pos(string1 SubS, string1 s);

// Удаляет строку s из динамической памяти.
void DoneStr(string1 s);

#endif // __FORM8_H
