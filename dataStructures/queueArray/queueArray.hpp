#ifndef __KSI_QUEUE_ARRAY_HPP
#define __KSI_QUEUE_ARRAY_HPP

const int FifoOk = 0;
const int FifoUnder = 1;
const int FifoOver = 2;
const int FifoSize = 1000;

extern int FifoError; // Переменная ошибок

typedef int *BaseTypeQueueArray; // Определить тип элемента очереди

typedef struct Fifo
{
    BaseTypeQueueArray Buf[FifoSize];
    unsigned Uk1; // Указатель на "голову" очереди
    unsigned Uk2; // Указатель на "хвост" очереди
    unsigned N;   // Количество элементов очереди
} Fifo;

// Инициализация очереди (1000 элементов)
void InitFifo(Fifo *f);

// Поместить элемент в очередь
void PutFifo(Fifo *f, BaseTypeQueueArray E);

// Извлечь элемент из очереди
void GetFifo(Fifo *f, BaseTypeQueueArray *E);

// Прочитать элемент
void ReadFifo(Fifo *f, BaseTypeQueueArray *E);

// Проверка, пуста ли очередь?
int EmptyFifo(Fifo *f);

#endif // __KSI_QUEUE_ARRAY_HPP