#include "rpnLogic.hpp"

// Выводит в консоль Map map.
void print(std::map<Token, Token> map)
{
	for (auto it = map.begin(); it != map.end(); it++)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
}

// Выводит в консоль Queue q.
void print(const Queue &q)
{
	Queue tmp = q;
	while (!tmp.empty())
	{
		std::cout << tmp.front() << " ";
		tmp.pop();
	}
	std::cout << std::endl;
}

// Выводит в консоль Stack s.
void print(const Stack &s)
{
	Stack tmp = s;
	while (!tmp.empty())
	{
		std::cout << tmp.top() << " ";
		tmp.pop();
	}
	std::cout << std::endl;
}

// Выводит в консоль Set s.
void print(const std::set<Token> &s)
{
	for (auto it = s.begin(); it != s.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

// Возвращает результат проверки на то является ли токен t числом.
inline bool isNumber(Token t)
{
	return t == '0' || t == '1';
}

// Возвращает результат проверки на то является ли токен t переменной.
inline bool isVariable(Token t)
{
	return (t >= 'A' && t <= 'Z') || (t >= 'a' && t <= 'z');
}

// Возвращает результат проверки на то является ли токен t операцией.
inline bool isOperation(Token t)
{
	return (t == '|' || t == '&' || t == '-' || t == '>' || t == '~');
}

// Возвращает результат проверки на то является ли токен t открывающей скобкой.
inline bool isOpeningPar(Token t)
{
	return t == '(';
}

// Возвращает результат проверки на то является ли токен t закрывающей скобкой.
inline bool isClosingPar(Token t)
{
	return t == ')';
}

// Возвращает величину приоритета операции op
// (чем больше число, тем выше приоритет).
inline int priority(Token op)
{
	assert(isOperation(op));
	int res = 0;
	switch (op)
	{
	case '-':
		// Отрицание — наивысший приоритет
		res = 5;
		break;
	case '&':
		// Конъюнкция
		res = 4;
		break;
	case '|':
		// Дизъюнкция
		res = 3;
		break;
	case '>':
		// Импликация
		res = 2;
		break;
	case '~':
		// Эквивалентность — наинизший приоритет
		res = 1;
		break;
	}
	return res;
}

// Преобразовает последовательность токенов input,
// представляющих выражение в инфиксной записи,
// в последовательность токенов, представляющих
// выражение в обратной польской записи
// (алгоритм Дейкстры «Сортировочная станция»).
Queue infixToPostfix(Queue input)
{
	// Выходная последовательность (очередь вывода):
	Queue output;
	// Рабочий стек:
	Stack s;
	// Текущий входной токен:
	Token t;
	// Пока есть токены во входной последовательности:
	while (!input.empty())
	{
		// Получить токен из начала входной последовательности
		t = input.front();
		input.pop();
		// Если токен — число или переменная, то:
		if (isNumber(t) || isVariable(t))
		{
			// Добавить его в очередь вывода
			output.push(t);
			// Если токен — операция op1, то:
		}
		else if (isOperation(t))
		{
			// Пока на вершине стека присутствует токен-операция op2
			// и у op1 приоритет меньше либо равен приоритету op2, то:
			while (!s.empty() && isOperation(s.top()) && priority(t) <= priority(s.top()))
			{
				// переложить op2 из стека в выходную очередь
				output.push(s.top());
				s.pop();
			}
			// Положить op1 в стек
			s.push(t);
			// Если токен — открывающая скобка, то:
		}
		else if (isOpeningPar(t))
		{
			// Положить его в стек
			s.push(t);
			// Если токен — закрывающая скобка, то:
		}
		else if (isClosingPar(t))
		{
			// Пока токен на вершине стека не является открывающей скобкой:
			while (!s.empty() && !isOpeningPar(s.top()))
			{
				// Перекладывать токены-операции из стека
				// в выходную очередь
				assert(isOperation(s.top()));
				output.push(s.top());
				s.pop();
			}
			// Если стек закончился до того,
			// как был встречен токен-«открывающая скобка», то:
			if (s.empty())
			{
				// В выражении пропущена открывающая скобка
				throw String("Пропущена открывающая скобка!");
			}
			else
			{
				// Иначе выкинуть открывающую скобку из стека
				// (но не добавлять в очередь вывода)
				s.pop();
			}
		}
		else
		{
			// В остальных случаях входная последовательность
			// содержит токен неизвестного типа
			String msg("Unknown symbol \'");
			msg += t + String("\'!");
			throw msg;
		}
	}
	// Токенов на входе больше нет, но ещё могут остаться токены в стеке.
	// Пока стек не пустой:
	while (!s.empty())
	{
		// Если токен на вершине стека — открывающая скобка, то:
		if (isOpeningPar(s.top()))
		{
			// В выражении присутствует незакрытая скобка
			throw String("Незакрытая скобка!");
		}
		else
		{
			// Иначе переложить токен-операцию из стека в выходную очередь
			assert(isOperation(s.top()));
			output.push(s.top());
			s.pop();
		}
	}
	// Конец алгоритма.
	// Выдать полученную последовательность
	return output;
}

// Выводит в консоль последовательность токенов q.
void printSequence(Queue q)
{
	while (!q.empty())
	{
		std::cout << q.front();
		q.pop();
	}
	std::cout << std::endl;
}

// Возвращает результат проверки на то является ли символ c пробельным.
inline bool isSpace(char c)
{
	return c <= ' ';
}

// Если символ c — маленькая буква, преобразовывает её в большую,
// иначе просто возвращает этот же символ.
inline char toUpperCase(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return c - 'a' + 'A';
	}
	else
	{
		return c;
	}
}

// Преобразовает строку str с выражением в последовательность токенов
// (лексический анализатор).
Queue stringToSequence(const String &str)
{
	Queue res;
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!isSpace(str[i]))
		{
			res.push(toUpperCase(str[i]));
		}
	}
	return res;
}

// Выводит в консоль сообщение об ошибке err.
inline void printErrorMessage(const String &err)
{
	std::cerr << "*** ERROR! " << err << std::endl;
}

// Ввод выражения с клавиатуры.
inline String inputExpr()
{
	String expr;
	std::cout << "Формула логики высказываний: ";
	std::getline(std::cin, expr);
	return expr;
}

// Выделяет из последовательности токенов seq переменные.
Set getVariables(Queue seq)
{
	Set res;
	while (!seq.empty())
	{
		if (isVariable(seq.front()) && res.count(seq.front()) == 0)
		{
			res.insert(seq.front());
		}
		seq.pop();
	}
	return res;
}

// Получает значения переменных var с клавиатуры.
Map inputVarValues(const Set &var)
{
	Token val;
	Map res;
	for (Set::const_iterator i = var.begin(); i != var.end(); ++i)
	{
		do
		{
			std::cout << *i << " = ";
			std::cin >> val;
			if (!isNumber(val))
			{
				std::cerr << "Input 0 or 1!" << std::endl;
			}
		} while (!isNumber(val));
		res.insert(VarVal(*i, val));
	}
	return res;
}

// Заменяет переменные в выражении expr их значениями из varVal.
Queue substValues(Queue expr, Map &varVal)
{
	Queue res;
	while (!expr.empty())
	{
		if (isVariable(expr.front()))
		{
			res.push(varVal[expr.front()]);
		}
		else
		{
			res.push(expr.front());
		}
		expr.pop();
	}
	return res;
}

// Возвращает результат проверки на то является ли операция t бинарной.
inline bool isBinOp(Token t)
{
	return t == '&' || t == '|' || t == '>' || t == '~';
}

// Возвращает результат проверки на то является ли операция t унарной.
inline bool isUnarOp(Token t)
{
	return t == '-';
}

// Возвращает bool-значение токена-числа x (true или false).
inline bool logicVal(Token x)
{
	assert(isNumber(x));
	return x == '1';
}

// Преобразовает bool-значение x в токен-число.
inline Token boolToToken(bool x)
{
	if (x)
	{
		return '1';
	}
	else
	{
		return '0';
	}
}

// Вычисляет результат бинарной операции op с токенами a и b.
inline Token evalBinOp(Token a, Token op, Token b)
{
	assert(isNumber(a) && isBinOp(op) && isNumber(b));
	bool res;
	// Получить bool-значения операндов
	bool left = logicVal(a);
	bool right = logicVal(b);
	switch (op)
	{
	case '&':
		// Конъюнкция
		res = left && right;
		break;
	case '|':
		// Дизъюнкция
		res = left || right;
		break;
	case '>':
		// Импликация
		res = !left || right;
		break;
	case '~':
		// Эквивалентность
		res = (!left || right) && (!right || left);
		break;
	}
	return boolToToken(res);
}

// Вычисляет результат унарной операции op стокеном a.
inline Token evalUnarOp(Token op, Token a)
{
	assert(isUnarOp(op) && isNumber(a));
	bool res = logicVal(a);
	switch (op)
	{
	case '-':
		// Отрицание
		res = !res;
		break;
	}
	return boolToToken(res);
}

// Вычисляет значение операции op, модифицируя стек s.
// Результат помещается в стек.
void evalOpUsingStack(Token op, Stack &s)
{
	assert(isOperation(op));
	// Если операция бинарная, то:
	if (isBinOp(op))
	{
		// В стеке должны быть два операнда
		if (s.size() >= 2)
		{
			// Если это так, то извлекаем правый операнд-число
			Token b = s.top();
			if (!isNumber(b))
			{
				throw String("Wrong expression!");
			}
			s.pop();
			// Затем извлекаем левый операнд-число
			Token a = s.top();
			if (!isNumber(a))
			{
				throw String("Wrong expression!");
			}
			s.pop();
			// Помещаем в стек результат операции
			s.push(evalBinOp(a, op, b));
		}
		else
		{
			throw String("Wrong expression!");
		}
		// Иначе операция унарная
	}
	else if (isUnarOp(op) && !s.empty())
	{
		// Извлекаем операнд
		Token a = s.top();
		if (!isNumber(a))
		{
			throw String("Wrong expression!");
		}
		s.pop();
		// Помещаем в стек результат операции
		s.push(evalUnarOp(op, a));
	}
	else
	{
		throw String("Wrong expression!");
	}
}

// Вычисляет значение выражения expr, записанного в обратной польской записи.
Token evaluate(Queue expr)
{
	// Рабочий стек
	Stack s;
	// Текущий токен
	Token t;
	// Пока входная последовательность содержит токены:
	while (!expr.empty())
	{
		// Считать очередной токен
		t = expr.front();
		if (!(isNumber(t) || isOperation(t)))
		{
			std::cerr << "Token: " << t << " (" << (unsigned)t << ")" << std::endl;
			throw std::string("Wrong expression!");
		}
		expr.pop();
		// Если это число, то:
		if (isNumber(t))
		{
			// Поместить его в стек
			s.push(t);
			// Если это операция, то:
		}
		else if (isOperation(t))
		{
			// Вычислить её, модифицируя стек
			// (результат также помещается в стек)
			evalOpUsingStack(t, s);
		}
	}
	// Результат — единственный элемент в стеке
	if (s.size() == 1)
	{
		// Вернуть результат
		return s.top();
	}
	else
	{
		throw String("Неверное выражение!");
	}
}

// Выводит результат вычисления r в консоль.
void printResult(Token r)
{
	assert(isNumber(r));
	std::cout << "Значение выражения: " << r << std::endl;
}

// Возвращает результат вычисления выражения expr, значения вводятся с клавиатуры.
Token evalLogicStr(std::string expr)
{
	// Преобразовать выражение в последовательность токенов
	Queue input = stringToSequence(expr);
	Token res;
	// Напечатать полученную последовательность токенов
	// printSequence(input);
	try
	{
		// Преобразовать последовательность токенов в ОПЗ
		Queue output = infixToPostfix(input);
		// Напечатать полученную последовательность токенов
		printSequence(output);
		// Ввести значения переменных с клавиатуры
		Map varVal = inputVarValues(getVariables(output));
		// Подставить значения переменных в выражение
		Queue rpn = substValues(output, varVal);
		// Напечатать получившееся выражение
		printSequence(rpn);
		// Вычислить полученное выражение
		res = evaluate(rpn);
	}
	catch (const String &err)
	{
		// Если возникла ошибка, вывести сообщение
		printErrorMessage(err);
		// И выйти из программы с неудачным кодом завершения
		exit(1);
	}
	return res;
}

// Возвращает число a в степени b.
int pow(int a, int b)
{
	if (a == 2)
	{
		return 1 << b;
	}
	int res = 1;
	for (int i = 0; i < b; i++)
	{
		res *= a;
	}
	return res;
}

// Возвращает количество истинных решений логического выражения expr.
int checkAllCombinations(std::string expr)
{
	int res_count = 0;

	Set vars = getVariables(stringToSequence(expr));

	int n = vars.size();
	int m = pow(2, n);

	for (int i = 0; i < m; i++)
	{
		Token val;
		Map res;
		int j = 0;
		for (Set::const_iterator k = vars.begin(); k != vars.end(); ++k, ++j)
		{
			do
			{
				val = '0' + (i >> j) % 2;
				if (!isNumber(val))
				{
					std::cerr << "Input 0 or 1!" << std::endl;
				}
			} while (!isNumber(val));
			res.insert(VarVal(*k, val));
		}
		Queue rpn = substValues(infixToPostfix(stringToSequence(expr)), res);
		if (evaluate(rpn) == '1')
		{
			res_count++;
		}
	}

	return res_count;
}

// Возвраащет результат проверки на противоречивость выражения expr.
bool isContradiction(std::string expr)
{
	return checkAllCombinations(expr) == 0;
}

// Возвращает возможное колчиество решений выражения expr.
int getCombinationsCount(std::string expr)
{
	return pow(2, getVariables(stringToSequence(expr)).size());
}

// Возвращает результат проверки на общезначимость выражения expr.
bool isTautology(std::string expr)
{
	return checkAllCombinations(expr) == getCombinationsCount(expr);
}

// Выводит таблицу истинности выражения expr в консоль.
void printTruthTable(std::string expr)
{
	Set vars = getVariables(stringToSequence(expr));

	int n = vars.size();
	int m = pow(2, n);

	for (Set::const_iterator i = vars.begin(); i != vars.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << expr << std::endl;

	for (int i = 0; i < m; i++)
	{
		Token val;
		Map res;
		int j = 0;
		for (Set::const_iterator k = vars.begin(); k != vars.end(); ++k, ++j)
		{
			do
			{
				val = '0' + (i >> j) % 2;
				if (!isNumber(val))
				{
					std::cerr << "Input 0 or 1!" << std::endl;
				}
			} while (!isNumber(val));
			res.insert(VarVal(*k, val));
		}
		Queue rpn = substValues(infixToPostfix(stringToSequence(expr)), res);
		for (Map::const_iterator k = res.begin(); k != res.end(); ++k)
		{
			std::cout << k->second << " ";
		}
		std::cout << evaluate(rpn) << std::endl;
	}
}

// Выводит истинные решения логического выражения expr в консоль.
void printTrueCombinations(std::string expr)
{
	Set vars = getVariables(stringToSequence(expr));
	bool isSolution = false;
	int n = vars.size();
	int m = pow(2, n);

	for (Set::const_iterator i = vars.begin(); i != vars.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << expr << std::endl;

	for (int i = 0; i < m; i++)
	{
		Token val;
		Map res;
		int j = 0;
		for (Set::const_iterator k = vars.begin(); k != vars.end(); ++k, ++j)
		{
			do
			{
				val = '0' + (i >> j) % 2;
				if (!isNumber(val))
				{
					std::cerr << "Input 0 or 1!" << std::endl;
				}
			} while (!isNumber(val));
			res.insert(VarVal(*k, val));
		}
		Queue rpn = substValues(infixToPostfix(stringToSequence(expr)), res);
		if (evaluate(rpn) == '1')
		{
			for (Map::const_iterator k = res.begin(); k != res.end(); ++k)
			{
				isSolution = true;
				std::cout << k->second << " ";
			}
			std::cout << evaluate(rpn) << std::endl;
		}
	}
	if (!isSolution)
	{
		std::cout << "No solution!" << std::endl;
	}
}

// Выводит ложные решения логического выражения expr в консоль.
void printFalseCombinations(std::string expr)
{
	Set vars = getVariables(stringToSequence(expr));
	bool isSolution = false;
	int n = vars.size();
	int m = pow(2, n);

	for (Set::const_iterator i = vars.begin(); i != vars.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << expr << std::endl;

	for (int i = 0; i < m; i++)
	{
		Token val;
		Map res;
		int j = 0;
		for (Set::const_iterator k = vars.begin(); k != vars.end(); ++k, ++j)
		{
			do
			{
				val = '0' + (i >> j) % 2;
				if (!isNumber(val))
				{
					std::cerr << "Input 0 or 1!" << std::endl;
				}
			} while (!isNumber(val));
			res.insert(VarVal(*k, val));
		}
		Queue rpn = substValues(infixToPostfix(stringToSequence(expr)), res);
		if (evaluate(rpn) == '0')
		{
			for (Map::const_iterator k = res.begin(); k != res.end(); ++k)
			{
				isSolution = true;
				std::cout << k->second << " ";
			}
			std::cout << evaluate(rpn) << std::endl;
		}
	}
	if (!isSolution)
	{
		std::cout << "No solution!" << std::endl;
	}
}