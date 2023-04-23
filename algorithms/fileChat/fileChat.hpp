#ifndef B9DC9301_F6A2_42F8_91AE_2FCC3A131D13
#define B9DC9301_F6A2_42F8_91AE_2FCC3A131D13

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>

#define __KSI_DEBUG_LEVEL 0 // 0 = no debug, 1 = main debug, 2 = all debug

/**
 *@brief Функция getCurrentDateTime() возвращает строку с текущей датой и
 *временем в формате "%Y.%m.%d %X".
 *@returns Строка с текущей датой и временем в формате "%Y.%m.%d %X".
 */
std::string getCurrentDateTime();

class File
{
    std::string name;
    std::string path = "savefile.bin";
    std::string extension;
    std::fstream file;

public:
    /**
     *@brief Устанавливает путь к файлу и извлекает его имя и расширение.
     *@param path Строка с путем к файлу.
     */
    void setPath(std::string path);

    std::string getName() const;
    std::string getPath() const;
    std::string getExtension() const;

    /**
     *@brief Открывает поток для файла по указанному пути в двоичном режиме.
     *@return 1, если поток успешно открыт, иначе -1.
     */
    int openStream();

    /**
     *@brief Закрывает поток для файла.
     *@return 1, если поток успешно закрыт, иначе -1.
     */
    int close();

    /**
     *@brief Функция для чтения байт из файла и сохранения их в вектор.
     *@returns Вектор, содержащий считанные байты.
     */
    std::vector<char> readBytes();

    /**
     *@brief Функция для чтения строк из файла.
     *@returns Строка, содержащая считанные строки.
     */
    std::string read();

    /**
     *@brief Получить последние сообщения
     *Функция получает буфер прочитанных байтов и разделяет его на сообщения,
     *разделенные символом 0x00. Затем извлекается указанное количество
     *последних сообщений.
     *@param numOfMsgs Количество последних сообщений, которые необходимо
     *извлечь.
     *@returns Строка, содержащая последние сообщения, разделенные символом
     *новой строки.
     *Если нет сообщений или произошла ошибка чтения, то возвращается
     *пустая строка.
     */
    std::string getLastMessages(size_t numOfMsgs);

    /**
     *@brief Функция для записи байт в файл.
     *@param text Текст, который необходимо записать в файл.
     *@returns 1, если запись прошла успешно
     */
    int write(std::string text);
};

class Message
{
    std::string date;
    std::string sender;
    std::string text;

public:
    Message(std::string date, std::string sender, std::string text);

    ~Message();

    std::string getDate() const;
    std::string getText() const;
    std::string getSender() const;

    std::string toString() const;

    void setDate(std::string date);
    void setText(std::string text);
    void setSender(std::string sender);
};

class Encryptor
{
public:
    /**
     * @brief Функция для шифрования строки
     * @param str Строка, которую необходимо зашифровать
     * @return Зашифрованная строка
     */
    unsigned long long static hash(std::string str);

    /**
     * @brief Функция для преобразования хэша в строку
     * @param hash Хэш, который необходимо преобразовать в строку
     * @return Строка, содержащая хэш
     */
    std::string static hashToString(unsigned long long hash);

    /**
     * @brief Функция для получения хэша по строке
     * @param name Имя пользователя
     * @return Строка, содержащая хэш
     */
    std::string static hashName(std::string name);
};

extern File file;

class Server
{
public:
    /**
     * @brief Функция для записи сообщения в файл
     * @param msg Сообщение, которое необходимо записать в файл
     * @return 1, если запись прошла успешно
     */
    int static writeMessage(Message msg);

    /**
     * @brief Функция для получения последних сообщений из файла
     * @param numOfMsgs Количество последних сообщений, которые необходимо
     * извлечь
     * @return Строка, содержащая последние сообщения, разделенные символом
     * новой строки
     */
    std::string static getLastMessages(size_t numOfMsgs);
};

class Client
{
    std::string name = "";

public:
    Client(std::string name);

    std::string getName() const;

    void setName(std::string name);

    /**
     * @brief Функция для записи сообщения в файл
     * @param message Сообщение, которое необходимо записать в файл
     * @return 1, если запись прошла успешно
     */
    void sendMessage(std::string message);

    /**
     * @brief Функция для получения последних сообщений из файла
     * @return Строка, содержащая последние сообщения, разделенные символом
     * новой строки
     */
    std::string requestMessages();
};

#endif /* B9DC9301_F6A2_42F8_91AE_2FCC3A131D13 */
