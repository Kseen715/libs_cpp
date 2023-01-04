#include "list8.hpp"

short ListError;

void InitList(List *L, unsigned SizeMem)
{
	L->PMemList = new TMemList[SizeMem];
	L->ptr = 0;
	L->N = 0;
	L->SizeMem = SizeMem;
	ListError = ListOk;
}

void PutList(List *L, tree8BaseType E)
{
	if (L->N < L->SizeMem)
	{
		void *tmp = new char[sizeof(tree8BaseType)]; // Выделение памяти под информационную часть элемента
		*(int *)tmp = *(int *)E;				// Копирование информационной части элемента
		(*L->PMemList)[L->ptr++] = tmp;			// Запись адреса в массив адресов
		L->N++;									// Увеличение количества элементов в списке
	}
	else
	{
		ListError = ListNotMem;
	}
}

void GetList(List *L, tree8BaseType *E)
{
	if (L->N > 0)
	{
		// E - указатель на указатель на информационную часть элемента
		//*(int *)E - указатель на информационную часть элемента
		//*(int *)*(int *)E - информационная часть элемента
		*(int *)*(int *)E = *(int *)(*L->PMemList)[--L->ptr]; // Копирование информационной части элемента
		delete[](*L->PMemList)[L->ptr];						  // Освобождение памяти
		L->N--;												  // Уменьшение количества элементов в списке
	}
	else
	{
		ListError = ListUnder;
	}
}

// Checked
void ReadList(List *L, tree8BaseType *E)
{
	if (L->N > 0)
	{
		*(int *)*(int *)E = *(int *)(*L->PMemList)[L->ptr - 1]; // Копирование информационной части элемента
	}
	else
	{
		ListError = ListUnder;
	}
}

// Checked
int FullList(List *L)
{
	return (L->N == L->SizeMem);
}

// Checked
int EndList(List *L)
{
	return (L->N == 0);
}

// Checked
unsigned int Count(List *L)
{
	return L->N;
}

// Checked
void BeginPtr(List *L)
{
	L->ptr = 0;
}

// Checked
void EndPtr(List *L)
{
	L->ptr = L->N;
}

// Checked
void MovePtr(List *L)
{
	(L->ptr < L->N) ? (L->ptr++) : (ListError = ListEnd);
}

// Checked
void MoveTo(List *L, unsigned int n)
{
	(n < L->N) ? (L->ptr = n) : (ListError = ListEnd);
}

// Checked
void DoneList(List *L)
{
	for (unsigned int i = 0; i < L->N; i++)
	{
		delete[](*L->PMemList)[--L->ptr]; // Освобождение памяти
		L->N--;							  // Уменьшение количества элементов в списке
	}
	delete[] L->PMemList; // Освобождение памяти
}

// Checked
void CopyList(List *L1, List *L2)
{
	L2->PMemList = new TMemList[L1->SizeMem];
	L2->ptr = L1->ptr;
	L2->N = L1->N;
	for (unsigned int i = 0; i < L1->N; i++)
	{
		void *tmp = new char[sizeof(tree8BaseType)];	  // Выделение памяти под информационную часть элемента
		*(int *)tmp = *(int *)(*L1->PMemList)[i]; // Копирование информационной части элемента
		(*L2->PMemList)[i] = tmp;				  // Запись адреса в массив адресов
	}
}

// Checked
int EmptyList(List *L)
{
	return (L->N == 0);
}