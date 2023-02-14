/*
RUS: Структура fraction представляет собой дробь, которая может быть
представлена в виде числителя и знаменателя.

Я не тестировал этот код, но он должен работать. Для написания исходного кода
были использованы технологии Copilot и ChatGPT.

ENG: The fraction structure represents a fraction that can be
represented as a numerator and denominator.

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

#ifndef __KSI_FRACTION_HPP
#define __KSI_FRACTION_HPP

#include <iostream>
#include <cstdlib>

namespace baseTypes
{
        typedef long long fractionBaseType;
}

namespace KSI
{
        struct fraction
        {
                baseTypes::fractionBaseType numerator;
                baseTypes::fractionBaseType denominator;
                bool autoReduce = true;

                fraction();
                fraction(int i);
                fraction(double d);
                fraction(baseTypes::fractionBaseType numerator,
                         baseTypes::fractionBaseType denominator);
                fraction(const fraction &f);

                ~fraction();

                fraction &operator=(const fraction &f);
                fraction &operator+=(const fraction &f);
                fraction &operator-=(const fraction &f);
                fraction &operator*=(const fraction &f);
                fraction &operator/=(const fraction &f);
                fraction &operator++();
                fraction &operator--();
                fraction operator++(int);
                fraction operator--(int);
                fraction operator-() const;
                fraction operator+() const;

                fraction operator+(const fraction &f) const;
                fraction operator-(const fraction &f) const;
                fraction operator*(const fraction &f) const;
                fraction operator/(const fraction &f) const;

                bool operator==(const fraction &f) const;
                bool operator!=(const fraction &f) const;
                bool operator<(const fraction &f) const;
                bool operator>(const fraction &f) const;
                bool operator<=(const fraction &f) const;
                bool operator>=(const fraction &f) const;

                operator double() const;

                baseTypes::fractionBaseType gcd(baseTypes::fractionBaseType a,
                                                baseTypes::fractionBaseType b)
                    const;
                baseTypes::fractionBaseType lcm(baseTypes::fractionBaseType a,
                                                baseTypes::fractionBaseType b)
                    const;

                friend std::ostream &operator<<(std::ostream &os,
                                                const fraction &f);
                friend std::istream &operator>>(std::istream &is,
                                                fraction &f);

                baseTypes::fractionBaseType getNumerator() const;
                baseTypes::fractionBaseType getDenominator() const;

                void setNumerator(baseTypes::fractionBaseType numerator);
                void setDenominator(baseTypes::fractionBaseType denominator);

                void reduce();

                bool isAutoReduce() const;
                void setAutoReduce(bool autoReduce);

                void abs();

                void invert();
                void negate();

                // cast int to fraction
                fraction &operator=(int i);

        };
}

#endif // __KSI_FRACTION_HPP
