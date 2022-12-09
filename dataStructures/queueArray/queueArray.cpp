#include "queueArray.hpp"

int FifoError; // Переменная ошибок

void InitFifo(Fifo *f)
{
    f->Uk1 = 0;
    f->Uk2 = 0;
    f->N = 0;
}

void PutFifo(Fifo *f, BaseTypeQueueArray E)
{
    if (f->N < FifoSize)
    {
        f->Buf[f->Uk2] = E;               // Запись в очередь элемента E
        f->Uk2 = (f->Uk2 + 1) % FifoSize; // Увеличение указателя на хвост очереди на 1 (циклическое)
        f->N++;                           // Увеличение количества элементов очереди на 1
    }
    else
    {
        FifoError = FifoOver;
    }
}

void GetFifo(Fifo *f, BaseTypeQueueArray *E)
{
    if (f->N > 0)
    {
        *E = f->Buf[f->Uk1];              // Чтение из очереди элемента E
        f->Uk1 = (f->Uk1 + 1) % FifoSize; // Увеличение указателя на голову очереди на 1 (циклическое)
        f->N--;                           // Уменьшение количества элементов очереди на 1
    }
    else
    {
        FifoError = FifoUnder;
    }
}

void ReadFifo(Fifo *f, BaseTypeQueueArray *E)
{
    if (f->N > 0)
    {
        *E = f->Buf[f->Uk1]; // Чтение из очереди элемента E
    }
    else
    {
        FifoError = FifoUnder;
    }
}

int EmptyFifo(Fifo *f)
{
    return f->N == 0;
}