#pragma once

#include <iostream>

#include "queueArray.hpp"

// Записывет в очередь f элементы из массива array размера sizes
void PutFifo(Fifo *f, BaseTypeQueueArray *array, int size);

// Записывает в очередь f элемент E
void pushFifo(Fifo *f, BaseTypeQueueArray E);

// Возвращает элемент извлеченный из очереди f
BaseTypeQueueArray popFifo(Fifo *f);

// Возвращает результат пуста ли очередь f
bool isEmptyFifo(Fifo *f);

// Выводит на экран элементы очереди f
void printFifo(Fifo *f);

void doneFifo(Fifo *f);
