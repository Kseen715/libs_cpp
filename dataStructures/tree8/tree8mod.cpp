#include "tree8mod.hpp"

std::vector<int> parseStrToInt(std::string strTree)
{
    std::vector<int> result; // Вектор для хранения результата.
    std::string temp;        // Временная строка для хранения числа.
    for (unsigned i = 0; i < strTree.size(); i++)
    {
        if (strTree[i] == '(' || strTree[i] == ')') // Если встретили скобку, то
                                                    // добавляем число в вектор.
        {
            if (temp.size() > 0) // Если в строке что-то есть, то добавляем в
                                 // вектор.
            {

                result.push_back(std::stoi(temp));
                temp.clear(); // Очищаем строку.
            }
        }
        else // Если не скобка, то добавляем символ в строку.
        {
            temp += strTree[i]; // Добавляем символ в строку.
        }
    }
    return result;
}