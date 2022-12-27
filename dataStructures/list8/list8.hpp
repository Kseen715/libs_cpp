#ifndef __KSI_LIST_8_HPP
#define __KSI_LIST_8_HPP

// ���.
// ������, �� ������ �������� ����������� ���, ��������� � �� -
// ���������� ������(������� ��� �������� � Pointer).
// ������ ��� ������ ���������� ��� ������������� ���
// � ���������� ��������� ����������� �
// �����������.
// ��������� ������ ��� �������������� ����� �������� ���
// � ������ � ��� �������� ���������� ��� ���������� ��������� PutList.
// ��� ���������� ��������� GetList ������, ���������� ��������������
// ������ ��������, �������������.
// ������ �������������� ����� ��������
// �������� ��� ������������� ��� � ����������� � �����������.

constexpr int SizeList = 100;
constexpr int Index = 1000;

const short ListOk = 0;		// ��� ������
const short ListNotMem = 1; // � ������ ����������� ��������� ������
const short ListUnder = 2;	// � ������ ��� ���������
const short ListEnd = 3;	// ��������� ��������� � ����� ������

typedef void *tree8BaseType;

typedef tree8BaseType TMemList[Index];

typedef unsigned ptrel;

typedef struct List
{
	TMemList *PMemList;
	ptrel ptr;
	unsigned int N;		  // ����� ������
	unsigned int SizeMem; // ������ �������
} List;

extern short ListError;

// InitList � ������������� ������.
void InitList(List *L, unsigned SizeMem);

// PutList � ��������� �������� � ������.
void PutList(List *L, tree8BaseType E);

// GetList � ���������� �������� �� ������.
void GetList(List *L, tree8BaseType *E);

// ReadList � ������ �������� ������.
void ReadList(List *L, tree8BaseType *E);

// FullList - �������� : ������ �� ������.
int FullList(List *L);

// EndList � �������� : �������� �� ������� ���������.
int EndList(List *L);

// Count � ���������� ���������� ��������� � ������.
unsigned int Count(List *L);

// BeginPtr � ����������� � ������ ������.
void BeginPtr(List *L);

// EndPtr � ����������� � ����� ������.
void EndPtr(List *L);

// MovePtr � ������� � ���������� ��������.
void MovePtr(List *L);

// MoveTo � ������� � n - �� ��������.
void MoveTo(List *L, unsigned int n);

// DoneList � �������� ������.
void DoneList(List *L);

// CopyList � ����������� ������ L1 � ������ L2.
void CopyList(List *L1, List *L2);

// EmptyList � �������� : �������� �� ������.
int EmptyList(List *L);

#endif // __KSI_LIST_8_HPP