/*
RUS:

Матрица представляет собой двумерный вектор, в котором каждый элемент
является вектором, содержащим элементы строки.

Она предствалена в виде: (номер столбца, номер строки)
     0---0---0---0---0---0---0
     |   |   |   |   |   |   |
     0   0   0   0   0   0   0
     |   |   |   |   |   |   |
     0   0   0   0   0   0   0

MIT License
Copyright (c) 2023 by Denis Korenev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

This file is part of KSI.
*/

#ifndef __KSI_MATRIX_HPP
#define __KSI_MATRIX_HPP

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

namespace KSI
{
    /**
     * @brief Класс матрицы.
     * Класс матрицы с возможностью задания типа данных.
     * @tparam T Тип данных, по умолчанию double.
     */
    template <typename T = double>
    class Matrix
    {
    protected:
        std::vector<std::vector<T>> data;
        size_t cols;
        size_t rows;

    public:
        Matrix();

        /**
         * @brief Функция создания матрицы.
         * Функция создает матрицу размером size_t rows на size_t cols.
         * @param cols Количество столбцов.
         * @param rows Количество строк.
         * @return Двумерный вектор (матрица).
         */
        Matrix(size_t cols_, size_t rows_);

        /**
         * @brief Конструктор копирования матрицы с параметрами.
         * @param other Копируемая матрица.
         * @return Новый экземпляр матрицы.
         */
        Matrix(const Matrix &other);

        /**
         * @param Matrix &&other Конструктор копирования с перемещением для
         * класса Matrix
         * @return Создание нового экземпляра класс Matrix
         */
        Matrix(Matrix &&other);

        /**
         * @brief Функция приравнивает текущий массив к заданному массиву
         * @param other массив, к которому приравнивается текущий
         * @return текущий массив
         */
        Matrix &operator=(const Matrix &other);

        /**
         * @brief Оператор присваивания для матрицы
         * @param other ссылка на другую матрицу
         * @return *this
         */
        Matrix &operator=(Matrix &&other);

        /**
         * @brief Создает матрицу и инициалзирует ее определенными значениями.
         * @param list Список для инициализации матрицы.
         */
        Matrix(std::initializer_list<std::initializer_list<T>> list);

        /**
         * @brief Функция возвращает количество строк в матрице.
         * @return Количество строк.
         */
        size_t getRows() const;

        /**
         * @brief Функция возвращает количество столбцов в матрице.
         * @return Количество столбцов.
         */
        size_t getColumns() const;

        /**
         * @brief Функция возвращает двумерный вектор (матрицу).
         * @return Двумерный вектор (матрица).
         */
        std::vector<std::vector<T>> getData() const;

        /**
         * @brief Функция возвращает элемент матрицы по индексу.
         * @param col Индекс столбца.
         * @param row Индекс строки.
         * @return Элемент матрицы.
         */
        T &at(size_t col, size_t row);

        /**
         * @brief Функция возвращает элемент матрицы по индексу.
         * @param col Индекс столбца.
         * @return Элемент матрицы.
         */
        std::vector<T> &operator[](size_t col);

        /**
         * @brief Операция умножения матрицы на другую матрицу.
         * @param other Матрица, на которую будет производиться операция
         * умножения
         * @return Новая матрица результат произведённой операции
         */
        Matrix operator*(const Matrix &other) const;

        /**
         * @brief Умножает матрицу на константу
         * @param scalar Константа
         * @return  Матрица, представляющая умноженную матрицу
         */
        Matrix operator*(const T &scalar) const;

        // TODO: Операторы для работы в обратном порядке (скаляр * матрица и тд) работают некорректно
        /**
         * @brief Переопределение оператора умножения для матрицы и скаляра
         * @param scalar Скаляр типа T
         * @param m Матрица типа matrix
         * @return Новая матрица с применением оператора умножения
         */
        friend Matrix operator*(const T &scalar, const Matrix &m);

        /**
         * @brief Оператор для перемножения матрицы размера
         * NxM с вектором длины M
         * @param vec Вектор, к которому применяется оператор, размера M
         * @return Вектор размера N
         */
        std::vector<T> operator*(const std::vector<T> &vec) const;

        /**
         * @brief Неявное вычитание матрицы m из матрицы this
         * @param m вычитаемая матрица
         * @return Возвращает измененную матрицу this
         */
        Matrix &operator-=(const Matrix &m);

        /**
         * @brief Оператор присваивания сложения для двух матриц
         * @param m объект класса Matrix, на который указывает аргумент
         * @return ссылку на объект *this
         * Функция используется для прибавления к текущему матричному объекту
         * другого матричного аргумента m. После этого элементы первого объекта
         * прибавляются к соответствующим элементам второго объекта. В случае,
         * если размеры двух матриц не совпадают, выбрасывается
         * исключение std::invalid_argument.
         */
        Matrix &operator+=(const Matrix &m);

        /**
         * @brief Оператор доступа к элементу матрицы
         * @param col Номер столбца
         * @param row Номер строки
         * @return Ссылку на элемент матрицы
         * Функция используется для доступа к элементу матрицы по индексам
         * row и col. В случае, если индексы выходят за границы матрицы,
         * выбрасывается исключение std::out_of_range.
         */
        T &operator()(size_t col, size_t row);

        /**
         * @brief Функция изменяет размеры таблицы до заданного new_rows и
         * new_cols,
         * и присаивает новые значения rows и cols.
         * @param new_cols Новое количество столбцов
         * @param new_rows Новое количество строк
         */
        void resize(size_t new_cols, size_t new_rows);

        /**
         * @brief Функция возвращает транспонированную матрицу.
         * Для каждого элемента столбца входной матрицы присваивается
         * соответствующий элемент строки в выходной матрице.
         * @return транспонированная матрица
         */
        Matrix transpose() const;

        /**
         * @brief Функция проверяющая, является ли матрица квадратной
         * @return true, если матрица квадратная, иначе возвращается false
         */
        bool isSquare() const;

        /**
         * @brief Обменивает две строки матрицы
         * @param row1 Индекс первой строки
         * @param row2 Индекс второй строки
         * @return void
         */
        void swapRows(size_t row1, size_t row2);

        /**
         * @brief Обменивает два столбца матрицы
         * @param col1 Индекс первого столбца
         * @param col2 Индекс второго столбца
         * @return void
         */
        void swapColumns(size_t col1, size_t col2);

        /**
         * @brief Вычисляет обратную матрицу.
         * @return Обратная матрица
         */
        Matrix inverse() const;

        /**
         * @brief Вычисляет определитель матрицы.
         * @return Детерминант матрицы
         */
        T determinant() const;

        /**
         * @brief Эта функция склеивает столбец матрицы и заданный вектор.
         * @param[in] vec - Вектор, с которым будет
         * клеиваться столбец матрицы.
         * @return bool - true, если вектор одного размера с матрицей;
         * false, если указан неверный вектор.
         */
        Matrix<T> glueVectorColumn(const std::vector<T> &vec);

        /**
         * @brief Эта функция склеивает строку матрицы и заданный вектор.
         * @param[in] vec - Вектор, с которым будет
         * клеиваться строка матрицы.
         * @return bool - true, если вектор одного размера с матрицей;
         * false, если указан неверный вектор.
         */
        Matrix<T> glueVectorRow(const std::vector<T> &vec);

        /**
         * @brief Эта функция вставляет столбец в матрицу.
         * @param[in] vec - Вектор, который будет вставлен в матрицу.
         * @param[in] col - Номер столбца, в который будет вставлен вектор.
         * @return bool - true, если вектор одного размера с матрицей;
         * false, если указан неверный вектор.
         */
        Matrix<T> insertColumn(const std::vector<T> &vec, size_t col);

        /**
         * @brief Эта функция вставляет строку в матрицу.
         * @param[in] vec - Вектор, который будет вставлен в матрицу.
         * @param[in] row - Номер строки, в которую будет вставлен вектор.
         * @return bool - true, если вектор одного размера с матрицей;
         * false, если указан неверный вектор.
         */
        Matrix<T> insertRow(const std::vector<T> &vec, size_t row);

        /**
         * @brief Функция, которая создает квадратную матрицу из неквадратной.
         * @return true, если преобразование было произведено успешно и false,
         * в противном случае.
         */
        Matrix<T> makeSquare();
    };

    template <typename T>
    Matrix<T>::Matrix() : rows(0), cols(0) {}

    template <typename T>
    Matrix<T>::Matrix(size_t cols_, size_t rows_)
    {
        if (cols_ == 0 || rows_ == 0)
        {
            throw std::invalid_argument("Invalid matrix size");
        }
        cols = cols_;
        rows = rows_;
        data.resize(cols);
        for (size_t i = 0; i < cols; i++)
        {
            data[i].resize(rows);
        }

        for (size_t i = 0; i < cols; i++)
        {
            for (size_t j = 0; j < rows; j++)
            {
                data[i][j] = 0;
            }
        }
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix &other)
        : rows(other.rows), cols(other.cols), data(other.data)
    {
    }

    template <typename T>
    Matrix<T>::Matrix(Matrix &&other)
        : rows(other.rows), cols(other.cols), data(std::move(other.data))
    {
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator=(const Matrix &other)
    {
        Matrix<T> tmp(other.getColumns(), other.getRows());
        for (size_t i = 0; i < other.getColumns(); i++)
        {
            for (size_t j = 0; j < other.getRows(); j++)
            {
                tmp[i][j] = other.data[i][j];
            }
        }

        cols = tmp.getColumns();
        rows = tmp.getRows();
        data = tmp.data;
        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator=(Matrix &&other)
    {
        cols = other.getColumns();
        rows = other.getRows();
        data = std::move(other.data);
        return *this;
    }

    template <typename T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list)
    {
        cols = list.begin()->size();
        rows = list.size();
        data.resize(cols);
        for (size_t i = 0; i < cols; i++)
        {
            data[i].resize(rows);
        }

        size_t i = 0;
        for (auto &row : list)
        {
            if (row.size() != cols)
            {
                throw std::invalid_argument("Invalid matrix size");
            }
            size_t j = 0;
            for (auto &col : row)
            {
                data[j][i] = col;
                j++;
            }
            i++;
        }
    }

    template <typename T>
    size_t Matrix<T>::getRows() const
    {
        return rows;
    }

    template <typename T>
    size_t Matrix<T>::getColumns() const
    {
        return cols;
    }

    template <typename T>
    std::vector<std::vector<T>> Matrix<T>::getData() const
    {
        return data;
    }

    template <typename T>
    T &Matrix<T>::at(size_t col, size_t row)
    {
        if (col >= cols)
        {
            throw std::out_of_range("Invalid matrix column index "
                                    "[at(size_t col, size_t row)]");
        }
        else if (row >= rows)
        {
            throw std::out_of_range("Invalid matrix row index "
                                    "[at(size_t col, size_t row)]");
        }
        return data.at(col).at(row);
    }

    template <typename T>
    std::vector<T> &Matrix<T>::operator[](size_t col)
    {
        return data[col];
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator*(const Matrix &other) const
    {
        if (cols != other.rows)
        {
            throw std::invalid_argument("Invalid matrix size");
        }

        Matrix<T> result(other.cols, rows);

        for (size_t i = 0; i < result.cols; ++i)
        {
            for (size_t j = 0; j < result.rows; ++j)
            {
                for (size_t k = 0; k < cols; ++k)
                {
                    result.at(i, j) += getData()[k][j] * other.getData()[i][k];
                }
            }
        }

        return result;
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator*(const T &scalar) const
    {
        Matrix<T> result(cols, rows);

        for (size_t i = 0; i < cols; ++i)
        {
            for (size_t j = 0; j < rows; ++j)
            {
                result.at(i, j) = getData()[i][j] * scalar;
            }
        }

        return result;
    }

    // scalar * matrix operator
    template <typename T>
    Matrix<T> operator*(const T &scalar, const Matrix<T> &m)
    {
        return m * scalar;
    }

    template <typename T>
    std::vector<T> Matrix<T>::operator*(const std::vector<T> &vec) const
    {
        if (cols != vec.size())
        {
            throw std::invalid_argument("Invalid matrix dimensions");
        }

        std::vector<T> result(rows);

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result[i] += getData()[j][i] * vec[j];
            }
        }

        return result;
    }

    template <typename T>
    std::vector<T> &operator*(const std::vector<T> &vec, const Matrix<T> &m)
    {
        return m * vec;
    }

    template <typename T>
    std::istream &operator>>(std::istream &in, Matrix<T> &m)
    {
        for (size_t i = 0; i < m.getRows(); ++i)
        {
            for (size_t j = 0; j < m.getColumns(); ++j)
            {
                std::cout << "[" << i << "][" << j << "] = ";
                in >> m.at(i, j);
            }
        }
        return in;
    }

    // TODO: при выводе в последнем столбце лишний пробел
    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Matrix<T> &m)
    {
        if (m.getRows() == 0 || m.getColumns() == 0)
        {
            out << "{}" << std::endl;
            return out;
        }
        std::vector<size_t> maxLensInCols;
        for (size_t j = 0; j < m.getColumns(); ++j)
        {
            size_t maxLen = 0;
            for (size_t i = 0; i < m.getRows(); ++i)
            {
                std::stringstream ss;
                ss << m.getData()[j][i];
                maxLen = std::max(maxLen, ss.str().length());
            }
            maxLensInCols.push_back(maxLen);
        }
        out << "{";
        for (size_t i = 0; i < m.getRows(); ++i)
        {
            out << (i == 0 ? "{" : " {");
            for (size_t j = 0; j < m.getColumns(); ++j)
            {
                std::stringstream ss;
                ss << m.getData()[j][i]
                   << (j == m.getColumns() - 1 ? "" : ",");
                out << std::setw(maxLensInCols[j] + 2) << ss.str();
            }
            out << (i == m.getRows() - 1 ? "}}" : "},\n");
        }
        return out;
    }

    template <typename T>
    Matrix<T> operator-(const Matrix<T> &m1, const Matrix<T> &m2)
    {
        if (m1.getRows() != m2.getRows() || m1.getColumns() != m2.getColumns())
        {
            throw std::invalid_argument("Invalid matrix dimensions");
        }

        Matrix<T> result(m1.getColumns(), m1.getRows());

        for (size_t i = 0; i < m1.getColumns(); ++i)
        {
            for (size_t j = 0; j < m1.getRows(); ++j)
            {
                result.at(i, j) = m1.getData()[i][j] - m2.getData()[i][j];
            }
        }

        // move res to return
        return result;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator-=(const Matrix &m)
    {
        if (rows != m.rows || cols != m.cols)
        {
            throw std::invalid_argument("Invalid matrix dimensions");
        }

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                at(i, j) -= m.getData()[i][j];
            }
        }

        return *this;
    }

    template <typename T>
    Matrix<T> operator+(const Matrix<T> &m1, const Matrix<T> &m2)
    {
        if (m1.getRows() != m2.getRows() || m1.getColumns() != m2.getColumns())
        {
            throw std::invalid_argument("Invalid matrix dimensions");
        }

        Matrix<T> result(m1.getRows(), m1.getColumns());

        for (size_t i = 0; i < m1.getRows(); ++i)
        {
            for (size_t j = 0; j < m1.getColumns(); ++j)
            {
                result.at(i, j) = m1.getData()[i][j] + m2.getData()[i][j];
            }
        }

        return result;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator+=(const Matrix &m)
    {
        if (rows != m.rows || cols != m.cols)
        {
            throw std::invalid_argument("Invalid matrix dimensions");
        }

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                at(i, j) += m.getData()[i][j];
            }
        }

        return *this;
    }

    template <typename T>
    bool operator==(const Matrix<T> &m1, const Matrix<T> &m2)
    {
        if (m1.getRows() != m2.getRows() || m1.getColumns() != m2.getColumns())
        {
            return false;
        }

        for (size_t i = 0; i < m1.getRows(); ++i)
        {
            for (size_t j = 0; j < m1.getColumns(); ++j)
            {
                if (m1.getData()[j][i] != m2.getData()[j][i])
                {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename T>
    T &Matrix<T>::operator()(size_t col, size_t row)
    {
        return at(col, row);
    }

    template <typename T>
    void Matrix<T>::resize(size_t new_cols, size_t new_rows)
    {
        if (new_rows == rows && new_cols == cols)
        {
            return;
        }

        data.resize(new_rows);
        for (size_t i = 0; i < new_rows; ++i)
        {
            data[i].resize(new_cols);
        }

        rows = new_rows;
        cols = new_cols;
    }

    template <typename T>
    Matrix<T> Matrix<T>::transpose() const
    {
        Matrix<T> result(rows, cols);

        for (size_t i = 0; i < cols; ++i)
        {
            for (size_t j = 0; j < rows; ++j)
            {
                result.at(j, i) = data[i][j];
            }
        }

        return result;
    }

    template <typename T>
    bool Matrix<T>::isSquare() const
    {
        return rows == cols;
    }

    template <typename T>
    void Matrix<T>::swapRows(size_t row1, size_t row2)
    {
        if (row1 >= rows || row2 >= rows)
        {
            throw std::out_of_range("Invalid row index "
                                    "[swapRows(size_t row1, size_t row2)]");
        }

        for (size_t i = 0; i < cols; ++i)
        {
            std::swap(data[i][row1], data[i][row2]);
        }
    }

    template <typename T>
    void Matrix<T>::swapColumns(size_t col1, size_t col2)
    {
        if (col1 >= cols || col2 >= cols)
        {
            throw std::out_of_range("Invalid column index");
        }

        for (size_t i = 0; i < rows; ++i)
        {
            std::swap(data[col1][i], data[col2][i]);
        }
    }

    template <typename T>
    Matrix<T> Matrix<T>::inverse() const
    {
        if (!isSquare())
        {
            throw std::invalid_argument("Matrix must be square");
        }

        Matrix<T> result(rows, cols * 2);

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result(i, j) = data[i][j];
            }
        }

        for (size_t i = 0; i < rows; ++i)
        {
            result(i, i + cols) = 1;
        }

        for (size_t i = 0; i < rows; ++i)
        {
            if (result(i, i) == 0)
            {
                size_t j = i + 1;
                while (j < rows && result(j, i) == 0)
                {
                    ++j;
                }

                if (j == rows)
                {
                    throw std::invalid_argument("Matrix is not invertible");
                }

                result.swapRows(i, j);
            }

            T pivot = result(i, i);
            for (size_t j = 0; j < cols * 2; ++j)
            {
                result(i, j) /= pivot;
            }

            for (size_t j = 0; j < rows; ++j)
            {
                if (i == j)
                {
                    continue;
                }

                T multiplier = result(j, i);
                for (size_t k = 0; k < cols * 2; ++k)
                {
                    result(j, k) -= multiplier * result(i, k);
                }
            }
        }

        Matrix<T> inverse(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                inverse(i, j) = result(i, j + cols);
            }
        }

        return inverse;
    }

    template <typename T>
    T Matrix<T>::determinant() const
    {
        if (!isSquare())
        {
            throw std::invalid_argument("Matrix must be square");
        }

        Matrix<T> result(*this);
        size_t swaps = 0;

        for (size_t i = 0; i < rows; ++i)
        {
            if (result(i, i) == 0)
            {
                size_t j = i + 1;
                while (j < rows && result(j, i) == 0)
                {
                    ++j;
                }

                if (j == rows)
                {
                    return 0;
                }

                result.swapRows(i, j);
                ++swaps;
            }

            for (size_t j = i + 1; j < rows; ++j)
            {
                T coef = result(j, i) / result(i, i);
                for (size_t k = i; k < cols; ++k)
                {
                    result(j, k) -= coef * result(i, k);
                }
            }
        }

        T det = 1;
        for (size_t i = 0; i < rows; ++i)
        {
            det *= result(i, i);
        }

        det *= (swaps % 2 == 0 ? 1 : -1);
        return det;
    }

    template <typename T>
    Matrix<T> Matrix<T>::glueVectorColumn(const std::vector<T> &vec)
    {
        if (vec.size() != rows)
        {
            throw std::invalid_argument("Vector size must be equal to matrix "
                                        "rows");
        }

        data.push_back(vec);
        ++cols;

        return *this;
    }

    template <typename T>
    Matrix<T> Matrix<T>::glueVectorRow(const std::vector<T> &vec)
    {
        if (vec.size() != cols)
        {
            throw std::invalid_argument("Vector size must be equal to matrix "
                                        "cols");
        }

        for (size_t i = 0; i < cols; ++i)
        {
            data[i].push_back(vec[i]);
        }

        ++rows;

        return *this;
    }

    template <typename T>
    Matrix<T> Matrix<T>::insertColumn(const std::vector<T> &vec, size_t col)
    {
        if (vec.size() != rows)
        {
            throw std::invalid_argument("Vector size must be equal to matrix "
                                        "rows");
        }

        data.insert(data.begin() + col, vec);

        ++cols;

        return *this;
    }

    template <typename T>
    Matrix<T> Matrix<T>::insertRow(const std::vector<T> &vec, size_t row)
    {
        if (vec.size() != cols)
        {
            throw std::invalid_argument("Vector size must be equal to matrix "
                                        "cols");
        }

        for (size_t i = 0; i < cols; ++i)
        {
            data[i].insert(data[i].begin() + row, vec[i]);
        }

        ++rows;

        return *this;
    }

    template <typename T>
    Matrix<T> Matrix<T>::makeSquare()
    {
        if (rows == cols)
        {
            return *this;
        }

        auto startCols = cols;
        auto startRows = rows;

        if (startCols < startRows)
        {
            data.push_back(std::vector<T>(startRows, 0));
            ++cols;
        }
        else
        {
            for (size_t i = 0; i < startCols; ++i)
            {
                data[i].push_back(0);
            }
            ++rows;
        }

        return *this;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
    {
        if (v.empty())
        {
            return out << "{}";
        }
        out << "{";
        for (size_t i = 0; i < v.size(); ++i)
        {
            out << v[i] << (i == v.size() - 1 ? "}" : ",");
        }
        return out;
    }

    /**
     * @brief Решение системы линейных уравнений методом Гаусса.
     * @param m Матрица коэффициентов.
     * @param v Вектор свободных членов.
     * @return Вектор решений.
     */
    template <typename T>
    std::vector<T> solveSysLinEqGauss(const Matrix<T> &m,
                                      const std::vector<T> v)
    {
        if (m.getRows() != v.size())
        {
            throw std::invalid_argument("Matrix rows must be equal to vector "
                                        "size");
        }

        if (m.determinant() == 0 && v == std::vector<T>(v.size(), 0))
        {
            std::cout << "System has infinite solutions" << std::endl;
        }
        else if (m.determinant() == 0)
        {
            std::cout << "System has no solutions" << std::endl;
        }

        Matrix<T> mtr(m);
        mtr.glueVectorColumn(v);
        // Matrix store data as (column, row)
        // Прямой ход.

        for (size_t i = 0; i < mtr.getRows(); ++i)
        {
            if (mtr(i, i) == 0)
            {
                size_t j = i + 1;
                while (j < mtr.getRows() && mtr(j, i) == 0)
                {
                    ++j;
                }

                if (j == mtr.getRows())
                {
                    return std::vector<T>();
                }

                mtr.swapRows(i, j);
            }

            for (size_t j = i + 1; j < mtr.getRows(); ++j)
            {
                T coef = mtr(i, j) / mtr(i, i);
                for (size_t k = i; k < mtr.getColumns(); ++k)
                {
                    mtr(k, j) -= coef * mtr(k, i);
                }
            }
        }

        // Обратный ход.

        std::vector<T> result(mtr.getRows());

        for (size_t i = mtr.getRows() - 1; i < mtr.getRows(); --i)
        {
            T sum = 0;
            for (size_t j = i + 1; j < mtr.getColumns() - 1; ++j)
            {
                sum += mtr(j, i) * result[j];
            }
            result[i] = (mtr(mtr.getColumns() - 1, i) - sum) / mtr(i, i);
        }

        return result;
    }

    /**
     * @brief Возвращает строку с системой линейных уравнений.
     * @param mtr Матрица коэффициентов.
     * @param vec Вектор свободных членов.
     * @param vars Вектор переменных.
     * @return Строка с системой линейных уравнений.
     */
    template <typename T>
    std::string getSysLinEqString(const Matrix<T> &mtr,
                                  const std::vector<T> &vec,
                                  std::vector<std::string> vars =
                                      std::vector<std::string>())
    {
        Matrix<T> result(mtr);
        result = result.glueVectorColumn(vec);

        std::stringstream ss;
        if (vars.size() != result.getColumns() - 1)
        {
            vars.clear();
            for (size_t i = 0; i < result.getColumns() - 1; ++i)
            {
                vars.push_back("x" + std::to_string(i + 1));
            }
        }

        for (size_t i = 0; i < result.getRows(); ++i)
        {
            if (i == 0)
            {
                ss << "/ ";
            }
            else if (i == result.getRows() - 1)
            {
                ss << "\\ ";
            }
            else
            {
                ss << "| ";
            }
            for (size_t j = 0; j < result.getColumns() - 1; ++j)
            {
                if (result.getData()[j][i] == 0)
                {
                    continue;
                }
                ss << result.getData()[j][i] << "*" << vars[j]
                   << (j == result.getColumns() - 2 ? "" : " + ");
            }
            ss << " = "
               << result.getData()[result.getColumns() - 1][i] << std::endl;
        }
        return ss.str();
    }
}

#endif // __KSI_MATRIX_HPP
