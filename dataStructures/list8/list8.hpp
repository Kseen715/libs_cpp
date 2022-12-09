#pragma once

// ѕЋ—.
// ћассив, на основе которого реализуетс€ ѕЋ—, находитс€ в ди -
// намической пам€ти(базовый тип элемента Ч Pointer).
// ѕам€ть под массив выдел€етс€ при инициализации ѕЋ—
// и количество элементов сохран€етс€ в
// дескрипторе.
// ¬ыделение пам€ти под информационную часть элемента ѕЋ—
// и запись в нее значени€ происходит при выполнении процедуры PutList.
// ѕри выполнении процедуры GetList пам€ть, занимаема€ информационной
// частью элемента, освобождаетс€.
// –азмер информационной части элемента
// задаетс€ при инициализации ѕЋ— и сохран€етс€ в дескрипторе.

constexpr int SizeList = 100;
constexpr int Index = 1000;

const short ListOk = 0;		//¬се хорошо
const short ListNotMem = 1; //¬ списке закончилась свободна€ пам€ть
const short ListUnder = 2;	//¬ списке нет элементов
const short ListEnd = 3;	//”казатель находитс€ в конце списка

typedef void *BaseType;

typedef BaseType TMemList[Index];

typedef unsigned ptrel;

typedef struct List
{
	TMemList *PMemList;
	ptrel ptr;
	unsigned int N;		  //ƒлина списка
	unsigned int SizeMem; //–азмер массива
} List;

extern short ListError;

// InitList Ч инициализаци€ списка.
void InitList(List *L, unsigned SizeMem);

// PutList Ч включение элемента в список.
void PutList(List *L, BaseType E);

// GetList Ч исключение элемента из списка.
void GetList(List *L, BaseType *E);

// ReadList Ч чтение элемента списка.
void ReadList(List *L, BaseType *E);

// FullList - проверка : пустой ли список.
int FullList(List *L);

// EndList Ч проверка : €вл€етс€ ли элемент последним.
int EndList(List *L);

// Count Ч возвращает количество элементов в списке.
unsigned int Count(List *L);

// BeginPtr Ч устанановка в начало списка.
void BeginPtr(List *L);

// EndPtr Ч устанановка в конец списка.
void EndPtr(List *L);

// MovePtr Ч переход к следующему элементу.
void MovePtr(List *L);

// MoveTo Ч переход к n - му элементу.
void MoveTo(List *L, unsigned int n);

// DoneList Ч удаление списка.
void DoneList(List *L);

// CopyList Ч копирование списка L1 в список L2.
void CopyList(List *L1, List *L2);

// EmptyList Ч проверка : свободен ли список.
int EmptyList(List *L);