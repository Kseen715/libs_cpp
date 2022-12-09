#ifndef __KSI_WORK_TIME_LIB_HPP
#define __KSI_WORK_TIME_LIB_HPP

#include <chrono>
#include <iostream>
#include <string>

#ifndef __KSI_WORK_TIME_CLASS
#define __KSI_WORK_TIME_CLASS
// Класс для подсчета времени выполнения программы.
class workTime
{
protected:
	// Точка начала и завершения отсчета времени.
	std::chrono::time_point<std::chrono::high_resolution_clock> startPoint, endPoint;
	// Продолжительность отсчета времени.
	std::chrono::duration<float> duration;

public:
	// Стандартный конструктор.
	workTime() = default;

	// Стандартный деструктор.
	~workTime() = default;

	// Запуск таймера.
	void start();

	// Остановка таймера.
	void stop();

	// Перезапуск таймера.
	void restart();

	// Оператор << для вывода времени в поток (в секундах).
	friend std::ostream &operator<<(std::ostream &os, const workTime &wt);

	// Возвращает строку с временем в секундах.
	std::string getStringTime();

	// Оператор присваивания.
	workTime &operator=(const workTime &other);

	// Возвращает время в секундах.
	std::chrono::duration<float> getDuration();
};
#endif // __WORK_TIME_CLASS

#ifndef __KSI_TIME_DURATION_CLASS
#define __KSI_TIME_DURATION_CLASS
// Класс для работы со временем.
class timeDuration
{
protected:
	// Продолэительность времени.
	std::chrono::duration<float> duration;

public:
	// Стандартный конструктор.
	timeDuration();

	// Стандартный деструктор.
	~timeDuration() = default;

	// Возвращает строку с временем в секундах.
	std::string getStringTime();

	// Оператор вывода в поток (в секундах).
	friend std::ostream &operator<<(std::ostream &os, const timeDuration &wt);

	// Оператор присваивания.
	timeDuration &operator=(const timeDuration &other);

	// Оператор присваивания для работы с типом float (в секундах).
	timeDuration &operator=(float other);

	// Возвращает время.
	std::chrono::duration<float> getTime();

	// Возвращает время в секундах.
	float getSeconds();

	// Возвращает время в минутах.
	float getMinutes();

	// Возвращает время в часах.
	float getHours();

	// Возвращает время в днях.
	float getDays();

	// Оператор сравнения >.
	bool operator>(timeDuration &other);

	// Оператор сравнения <.
	bool operator<(timeDuration &other);

	// Оператор сравнения >=.
	bool operator>=(timeDuration &other);

	// Оператор сравнения <=.
	bool operator<=(timeDuration &other);

	// Оператор сравнения ==.
	bool operator==(timeDuration &other);

	// Оператор сравнения !=.
	bool operator!=(timeDuration &other);

	// Оператор сложения.
	timeDuration operator+(timeDuration &other);

	// Оператор сложения с присваиванием.
	timeDuration &operator+=(timeDuration &other);

	// Оператор вычитания.
	timeDuration operator-(timeDuration &other);

	// Оператор вычитания с присваиванием.
	timeDuration &operator-=(timeDuration &other);

#ifdef __KSI_WORK_TIME_CLASS
	// Оператор присваивания для работы с классом workTime.
	timeDuration &operator=(workTime &other);

	// Оператор сравнения > для класса workTime.
	bool operator>(workTime &other);

	// Оператор сравнения < для класса workTime.
	bool operator<(workTime &other);

	// Оператор сравнения >= для класса workTime.
	bool operator>=(workTime &other);

	// Оператор сравнения <= для класса workTime.
	bool operator<=(workTime &other);

	// Оператор сравнения == для класса workTime.
	bool operator==(workTime &other);

	// Оператор сравнения != для класса workTime.
	bool operator!=(workTime &other);

	// Оператор сложения для класса workTime.
	timeDuration operator+(workTime &other);

	// Оператор сложения с присваиванием для класса workTime.
	timeDuration &operator+=(workTime &other);

	// Оператор вычитания для класса workTime.
	timeDuration operator-(workTime &other);

	// Оператор вычитания с присваиванием для класса workTime.
	timeDuration &operator-=(workTime &other);
#endif // __KSI_WORK_TIME_CLASS
};
#endif // __KSI_TIME_DURATION_ClASS

#endif // __KSI_WORK_TIME_LIB_HPP