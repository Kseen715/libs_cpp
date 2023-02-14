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
     * @tparam T Тип данных.
     */
    template <typename T = float>
    struct matrix
    {
    protected:
        std::vector<std::vector<T>> data;
        size_t rows;
        size_t cols;

    public:
        matrix() = default;

        /**
         * @brief Функция создания матрицы.
         * Функция создает матрицу размером size_t rows на size_t cols.
         * @param rows Количество строк.
         * @param cols Количество столбцов.
         * @return Двумерный вектор (матрица).
         */
        matrix(size_t cols_, size_t rows_)
        {
            this->rows = rows_;
            this->cols = cols_;
            data.resize(rows);
            for (auto &row : data)
            {
                row.resize(cols);
            }
            for (auto &row : data)
            {
                for (auto &col : row)
                {
                    col = 0;
                }
            }
        }

        /**
         * @brief Конструктор копирования матрицы с параметрами.
         * @param other Копируемая матрица.
         * @return Новый экземпляр матрицы.
         */
        matrix(const matrix &other)
            : rows(other.rows), cols(other.cols), data(other.data)
        {
        }

        /**
         * @param matrix &&other Конструктор копирования с перемещением для
         * класса Matrix
         * @return Создание нового экземпляра класс Matrix
         */
        matrix(matrix &&other)
            : rows(other.rows), cols(other.cols), data(std::move(other.data))
        {
        }

        /**
         * @brief Функция приравнивает текущий массив к заданному массиву
         * @param other массив, к которому приравнивается текущий
         * @return текущий массив
         */
        matrix &operator=(const matrix &other)
        {
            rows = other.rows;
            cols = other.cols;
            data = other.data;
            return *this;
        }

        /**
         * @brief Оператор присваивания для матрицы
         * @param other ссылка на другую матрицу
         * @return *this
         */
        matrix &operator=(matrix &&other)
        {
            rows = other.rows;
            cols = other.cols;
            data = std::move(other.data);
            return *this;
        }

        /**
         * @brief Создает матрицу и инициалзирует ее определенными значениями.
         * @param list Список для инициализации матрицы.
         */
        matrix(std::initializer_list<std::initializer_list<T>> list)
        {
            rows = list.size();
            cols = list.begin()->size();
            data.resize(rows);
            for (auto &row : data)
            {
                row.resize(cols);
            }
            size_t i = 0;
            for (auto &row : list)
            {
                size_t j = 0;
                for (auto &col : row)
                {
                    data[i][j] = col;
                    j++;
                }
                i++;
            }
        }

        /**
         * @brief Функция возвращает количество строк в матрице.
         * @return Количество строк.
         */
        size_t getRows() const
        {
            return rows;
        }

        /**
         * @brief Функция возвращает количество столбцов в матрице.
         * @return Количество столбцов.
         */
        size_t getColumns() const
        {
            return cols;
        }

        /**
         * @brief Функция возвращает двумерный вектор (матрицу).
         * @return Двумерный вектор (матрица).
         */
        std::vector<std::vector<T>> getData() const
        {
            return data;
        }

        /**
         * @brief Функция возвращает элемент матрицы по индексу.
         * @param row Индекс строки.
         * @param col Индекс столбца.
         * @return Элемент матрицы.
         */
        T &at(size_t row, size_t col)
        {
            return data.at(row).at(col);
        }

        /**
         * @brief Функция возвращает элемент матрицы по индексу.
         * @param row Индекс строки.
         * @param col Индекс столбца.
         * @return Элемент матрицы.
         */
        std::vector<T> &operator[](size_t row)
        {
            return data[row];
        }

        /**
         * @brief Операция умножения матрицы на другую матрицу.
         * @param other Матрица, на которую будет производиться операция
         * умножения
         * @return Новая матрица результат произведённой операции
         */
        matrix operator*(const matrix &other) const
        {
            if (cols != other.rows)
            {
                throw std::invalid_argument("Invalid matrix dimensions");
            }

            matrix result(rows, other.cols);

            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < other.cols; ++j)
                {
                    for (size_t k = 0; k < cols; ++k)
                    {
                        result.at(i, j) += this->getData()[i][k] *
                                           other.getData()[k][j];
                    }
                }
            }

            return result;
        }

        /**
         * @brief Умножает матрицу на константу
         * @param scalar Константа
         * @return  Матрица, представляющая умноженную матрицу
         */
        matrix operator*(const T &scalar) const
        {
            matrix result(rows, cols);

            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < cols; ++j)
                {
                    result.at(i, j) = getData()[i][j] * scalar;
                }
            }

            return result;
        }

        /**
         * @brief Переопределение оператора умножения для матрицы и скаляра
         * @param scalar Скаляр типа T
         * @param m Матрица типа matrix
         * @return Новая матрица с применением оператора умножения
         */
        friend matrix operator*(const T &scalar, const matrix &m)
        {
            return m * scalar;
        }

        /**
         * @brief Оператор для перемножения матрицы размера
         * NxM с вектором длины M
         * @param vec Вектор, к которому применяется оператор, размера M
         * @return Вектор размера N
         */
        std::vector<T> operator*(const std::vector<T> &vec) const
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
                    result[i] += getData()[i][j] * vec[j];
                }
            }

            return result;
        }

        /**
         * @brief Переопределение оператора умножения для матрицы и вектора
         * @param vec Вектор типа std::vector<T>
         * @param m Матрица типа matrix
         * @return Новый вектор с применением оператора умножения
         */
        friend std::vector<T> operator*(const std::vector<T> &vec,
                                        const matrix &m)
        {
            return m * vec;
        }

        /**
         * @brief Функция ввода данных типа matrix из потока ввода
         * @param in Поток ввода
         * @param m Объект матрицы
         * @return Ссылка на поток ввода
         */
        friend std::istream &operator>>(std::istream &in, matrix &m)
        {
            for (size_t i = 0; i < m.rows; ++i)
            {
                for (size_t j = 0; j < m.cols; ++j)
                {
                    std::cout << "[" << i << "][" << j << "] = ";
                    in >> m.at(i, j);
                }
            }
            return in;
        }

        /**
         * @brief Функция, использующаяся для вывода матрицы на экран
         * @param out Выходной поток
         * @param m Объект-матрица
         * @return Выходной поток
         */
        friend std::ostream &operator<<(std::ostream &out, const matrix<T> &m)
        {
            if (m.rows == 0 || m.cols == 0)
            {
                out << "{}" << std::endl;
                return out;
            }
            // get the max length of the elements
            std::vector<size_t> maxLensInCols;
            for (size_t j = 0; j < m.cols; ++j)
            {
                size_t maxLen = 0;
                for (size_t i = 0; i < m.rows; ++i)
                {
                    std::stringstream ss;
                    ss << m.getData()[i][j];
                    maxLen = std::max(maxLen, ss.str().length());
                }
                maxLensInCols.push_back(maxLen);
            }
            // print the matrix
            out << "{";
            for (size_t i = 0; i < m.rows; ++i)
            {
                out << (i == 0 ? "{" : " {");
                for (size_t j = 0; j < m.cols; ++j)
                {
                    out << std::setw(maxLensInCols[j]) << m.getData()[i][j]
                        << (j == m.cols - 1 ? "" : ",");
                }
                out << (i == m.rows - 1 ? "}}" : "},\n");
            }
            return out;
        }

        /**
         * @brief Оператор вычитания матриц
         * @param m1 Матрица типа matrix
         * @param m2 Матрица типа matrix
         * @return Новая матрица с применением оператора вычитания
         */
        friend matrix operator-(const matrix &m1, const matrix &m2)
        {
            if (m1.rows != m2.rows || m1.cols != m2.cols)
            {
                throw std::invalid_argument("Invalid matrix dimensions");
            }

            matrix result(m1.rows, m1.cols);

            for (size_t i = 0; i < m1.rows; ++i)
            {
                for (size_t j = 0; j < m1.cols; ++j)
                {
                    result.at(i, j) = m1.getData()[i][j] - m2.getData()[i][j];
                }
            }

            return result;
        }

        /**
         * @brief Неявное вычитание матрицы m из матрицы this
         * @param m вычитаемая матрица
         * @return Возвращает измененную матрицу this
         */
        matrix &operator-=(const matrix &m)
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

        /**
         * @brief Оператор сложения матриц
         * @param m1 Матрица типа matrix
         * @param m2 Матрица типа matrix
         * @return Новая матрица с применением оператора сложения
         */
        friend matrix operator+(const matrix &m1, const matrix &m2)
        {
            if (m1.rows != m2.rows || m1.cols != m2.cols)
            {
                throw std::invalid_argument("Invalid matrix dimensions");
            }

            matrix result(m1.rows, m1.cols);

            for (size_t i = 0; i < m1.rows; ++i)
            {
                for (size_t j = 0; j < m1.cols; ++j)
                {
                    result.at(i, j) = m1.getData()[i][j] + m2.getData()[i][j];
                }
            }

            return result;
        }

        /**
         * @brief Оператор присваивания сложения для двух матриц
         * @param m объект класса matrix, на который указывает аргумент
         * @return ссылку на объект *this
         * Функция используется для прибавления к текущему матричному объекту
         * другого матричного аргумента m. После этого элементы первого объекта
         * прибавляются к соответствующим элементам второго объекта. В случае,
         * если размеры двух матриц не совпадают, выбрасывается
         * исключение std::invalid_argument.
         */
        matrix &operator+=(const matrix &m)
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

        /**
         * @brief Оператор сравнения двух матриц
         *
         * @param m1 Первая матрица
         * @param m2 Вторая матрица
         *
         * @return Возвращает true, если матрицы равны по значеиям и false в
         * противном случае.
         */
        friend bool operator==(const matrix &m1, const matrix &m2)
        {
            if (m1.rows != m2.rows || m1.cols != m2.cols)
            {
                return false;
            }

            for (size_t i = 0; i < m1.rows; ++i)
            {
                for (size_t j = 0; j < m1.cols; ++j)
                {
                    if (m1.getData()[i][j] != m2.getData()[i][j])
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        /**
         * @brief Оператор доступа к элементу матрицы
         * @param row Номер строки
         * @param col Номер столбца
         * @return Ссылку на элемент матрицы
         * Функция используется для доступа к элементу матрицы по индексам
         * row и col. В случае, если индексы выходят за границы матрицы,
         * выбрасывается исключение std::out_of_range.
         */
        T &operator()(size_t row, size_t col)
        {
            if (row >= rows || col >= cols)
            {
                throw std::out_of_range("Invalid matrix index");
            }

            return data[row][col];
        }

        /**
         * @brief Функция изменяет размеры таблицы до заданного new_rows и
         * new_cols,
         * и присаивает новые значения rows и cols.
         * @param new_rows Новое количество строк
         * @param new_cols Новое количество столбцов
         */
        void resize(size_t new_rows, size_t new_cols)
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

        /**
         * @brief Функция возвращает транспонированную матрицу.
         * Для каждого элемента столбца входной матрицы присваивается
         * соответствующий элемент строки в выходной матрице.
         * @return транспонированная матрица
         */
        matrix transpose() const
        {
            matrix result(cols, rows);

            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < cols; ++j)
                {
                    result.at(j, i) = data[i][j];
                }
            }

            return result;
        }

        /**
         * @brief Функция проверяющая, является ли матрица квадратной
         * @return true, если матрица квадратная, иначе возвращается false
         */
        bool isSquare() const
        {
            return rows == cols;
        }

        /**
         * @brief Обменивает две строки матрицы
         *
         * @param row1 Индекс первой строки
         * @param row2 Индекс второй строки
         *
         * @return void
         */
        void swapRows(size_t row1, size_t row2)
        {
            if (row1 >= rows || row2 >= rows)
            {
                throw std::out_of_range("Invalid matrix index");
            }
            std::swap(data[row1], data[row2]);
        }

        /**
         * @brief Вычисляет обратную матрицу.
         * Эта функция использует Гаусс-Жорданов метод для
         * нахождения обратной матрицы. В первую очередь, исходная
         * матрица дополняется единичной матрицей. Затем следует
         * применять операцию вычитания и деления применять для
         * нахождения единичных элементов в диагонали.
         * После применения этих операций, входная матрица будет
         * трансформирована в единичную матрицу. Таким образом,
         * обратная матрица станет расположена на правой стороне
         * исходной матрицы.
         * @param  Нет
         * @return Обратная матрица
         */
        matrix inverse() const
        {
            if (!isSquare())
            {
                throw std::invalid_argument("Matrix must be square");
            }

            matrix result(rows, cols * 2);

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

                for (size_t j = i + 1; j < rows; ++j)
                {
                    T coef = result(j, i) / result(i, i);
                    for (size_t k = i; k < cols * 2; ++k)
                    {
                        result(j, k) -= coef * result(i, k);
                    }
                }
            }

            for (size_t i = rows - 1; i > 0; --i)
            {
                for (size_t j = i - 1; j < rows; --j)
                {
                    T coef = result(j, i) / result(i, i);
                    for (size_t k = i; k < cols * 2; ++k)
                    {
                        result(j, k) -= coef * result(i, k);
                    }
                }
            }

            for (size_t i = 0; i < rows; ++i)
            {
                T coef = result(i, i);
                for (size_t j = i; j < cols * 2; ++j)
                {
                    result(i, j) /= coef;
                }
            }

            matrix inv(rows, cols);

            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < cols; ++j)
                {
                    inv(i, j) = result(i, j + cols);
                }
            }

            return inv;
        }

        // use empty vector as default argument
        std::string getSysLinearEquationsString(
            std::vector<std::string> vars = std::vector<std::string>()) const
        {
            std::stringstream ss;
            if (vars.size() != cols - 1)
            {
                vars.clear();
                for (size_t i = 0; i < cols - 1; ++i)
                {
                    vars.push_back("x" + std::to_string(i + 1));
                }
            }

            for (size_t i = 0; i < rows; ++i)
            {
                if (i == 0)
                {
                    ss << "/ ";
                }
                else if (i == rows - 1)
                {
                    ss << "\\ ";
                }
                else
                {
                    ss << "| ";
                }
                for (size_t j = 0; j < cols - 1; ++j)
                {
                    if (data[i][j] == 0)
                    {
                        continue;
                    }
                    ss << data[i][j] << "*" << vars[j]
                       << (j == cols - 2 ? "" : " + ");
                }
                ss << " = " << data[i][cols - 1] << std::endl;
            }
            return ss.str();
        }

        // determinant using Gauss method, count of swaps used to get sign
        T determinant() const
        {
            if (!isSquare())
            {
                throw std::invalid_argument("Matrix must be square");
            }

            matrix result(*this);
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

        // solve system of linear equations using Gauss-Jordan elimination
        std::vector<T> solveSysLinearEquations() const
        {
            matrix result(*this);

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

                for (size_t j = i + 1; j < rows; ++j)
                {
                    T coef = result(j, i) / result(i, i);
                    for (size_t k = i; k < cols; ++k)
                    {
                        result(j, k) -= coef * result(i, k);
                    }
                }
            }

            for (size_t i = rows - 1; i > 0; --i)
            {
                for (size_t j = i - 1; j < rows; --j)
                {
                    T coef = result(j, i) / result(i, i);
                    for (size_t k = i; k < cols; ++k)
                    {
                        result(j, k) -= coef * result(i, k);
                    }
                }
            }

            for (size_t i = 0; i < rows; ++i)
            {
                T coef = result(i, i);
                for (size_t j = i; j < cols; ++j)
                {
                    result(i, j) /= coef;
                }
            }

            std::vector<T> x(rows);
            for (size_t i = 0; i < rows; ++i)
            {
                x[i] = result(i, cols - 1);
            }

            return x;
        }
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
    {
        out << "{";
        for (size_t i = 0; i < v.size(); ++i)
        {
            out << v[i] << (i == v.size() - 1 ? "}" : ",");
        }
        return out;
    }
}

#endif // __KSI_MATRIX_HPP
