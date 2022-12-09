#include "queueArrayMod.hpp"

BaseTypeQueueArray GetFifo(Fifo *f)
{
    BaseTypeQueueArray E;
    GetFifo(f, &E);
    return E;
}

void PutFifo(Fifo *f, BaseTypeQueueArray *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        PutFifo(f, array[i]);
    }
}

void pushFifo(Fifo *f, BaseTypeQueueArray E)
{
    PutFifo(f, E);
}

BaseTypeQueueArray popFifo(Fifo *f)
{
    BaseTypeQueueArray E;
    GetFifo(f, &E);
    return E;
}

bool isEmptyFifo(Fifo *f)
{
    return f->N == 0;
}

void printFifo(Fifo *f)
{
    for (int i = 0; i < f->N; i++)
    {
        std::cout << *f->Buf[i] << " ";
    }
    std::cout << std::endl;
}