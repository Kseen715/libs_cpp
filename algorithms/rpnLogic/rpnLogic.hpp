#ifndef __KSI_RPN_HPP
#define __KSI_RPN_HPP

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cassert>
#include <cstdlib>

// Объявление типов.
// Токен (лексема):
typedef char Token;

// Стек токенов:
typedef std::stack<Token> Stack;

// Последовательность токенов:
typedef std::queue<Token> Queue;

// Множество различных токенов:
typedef std::set<Token> Set;

// Таблица значений переменных:
typedef std::map<Token, Token> Map;

// Пара переменная—значение:
typedef std::pair<Token, Token> VarVal;

// Строка символов:
typedef std::string String;

// Выводит в консоль Map map.
void print(std::map<Token, Token> map);

// Выводит в консоль Queue q.
void print(const Queue &q);

// Выводит в консоль Stack s.
void print(const Stack &s);

// Выводит в консоль Set s.
void print(const std::set<Token> &s);

// Возвращает результат проверки на то
// является ли токен t числом.
inline bool isNumber(Token t);

// Возвращает результат проверки на то
// является ли токен t переменной.
inline bool isVariable(Token t);

// Возвращает результат проверки на то
// является ли токен t операцией.
inline bool isOperation(Token t);

// Возвращает результат проверки на то
// является ли токен t открывающей скобкой.
inline bool isOpeningPar(Token t);

// Возвращает результат проверки на то
// является ли токен t закрывающей скобкой.
inline bool isClosingPar(Token t);

// Возвращает величину приоритета операции op
// (чем больше число, тем выше приоритет).
inline int priority(Token op);

// Преобразовает последовательность токенов input,
// представляющих выражение в инфиксной записи,
// в последовательность токенов, представляющих
// выражение в обратной польской записи
// (алгоритм Дейкстры «Сортировочная станция»).
Queue infixToPostfix(Queue input);

// Возвращает результат проверки на то
// является ли символ c пробельным.
inline bool isSpace(char c);

// Если символ c — маленькая буква, преобразовывает её в большую,
// иначе просто возвращает этот же символ.
inline char toUpperCase(char c);

// Преобразовает строку str с выражением в последовательность
// токенов (лексический анализатор).
Queue stringToSequence(const String &s);

// Выделяет из последовательности токенов seq переменные.
Set getVariables(Queue s);

// Получает значения переменных var с клавиатуры.
Map inputVarValues(const Set &var);

// Заменяет переменные в выражении expr их значениями из varVal.
Queue substValues(Queue expr, Map &varVal);

// Возвращает результат проверки на то
// является ли операция t бинарной.
inline bool isBinOp(Token t);

// Возвращает результат проверки на то
// является ли операция t унарной.
inline bool isUnarOp(Token t);

// Возвращает bool-значение токена-числа x (true или false).
inline bool logicVal(Token x);

// Преобразовает bool-значение x в токен-число.
inline Token boolToToken(bool x);

// Вычисляет результат бинарной операции op с токенами a и b.
inline Token evalBinOp(Token a, Token op, Token b);

// Вычисляет результат унарной операции op стокеном a.
inline Token evalUnarOp(Token op, Token a);

// Вычисляет значение операции op, модифицируя стек s.
// Результат помещается в стек.
void evalOpUsingStack(Token op, Stack &s);

// Вычисляет значение выражения expr, записанного
// в обратной польской записи.
Token evaluate(Queue expr);

// Возвращает результат вычисления выражения expr,
// значения вводятся с клавиатуры.
Token evalLogicStr(std::string expr);

// Возвращает количество истинных решений
// логического выражения expr.
int checkAllCombinations(std::string expr);

// Возвраащет результат проверки на противоречивость.
bool isContradiction(std::string expr);

// Возвращает результат проверки на общезначимость выражения expr.
bool isTautology(std::string expr);

void printTruthTable(std::string expr);

// Выводит истинные решения логического выражения expr.
void printTrueCombinations(std::string expr);

// Выводит ложные решения логического выражения expr.
void printFalseCombinations(std::string expr);
#endif // __KSI_RPN_HPP