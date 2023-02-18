/*
RUS: Структура Fraction представляет собой дробь, которая может быть
представлена в виде числителя и знаменателя.

Я не тестировал этот код, но он должен работать. Для написания исходного кода
были использованы технологии Copilot и ChatGPT.

ENG: The Fraction structure represents a Fraction that can be
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

namespace BaseTypes
{
        typedef long long fractionBaseType;
}

namespace KSI
{
        struct Fraction
        {
                BaseTypes::fractionBaseType numerator;
                BaseTypes::fractionBaseType denominator;
                bool autoReduce = true;

                Fraction();
                Fraction(int i);
                Fraction(double d);
                Fraction(BaseTypes::fractionBaseType numerator,
                         BaseTypes::fractionBaseType denominator);
                Fraction(const Fraction &f);

                ~Fraction();

                Fraction &operator=(const Fraction &f);
                Fraction &operator+=(const Fraction &f);
                Fraction &operator-=(const Fraction &f);
                Fraction &operator*=(const Fraction &f);
                Fraction &operator/=(const Fraction &f);
                Fraction &operator++();
                Fraction &operator--();
                Fraction operator++(int);
                Fraction operator--(int);
                Fraction operator-() const;
                Fraction operator+() const;

                Fraction operator+(const Fraction &f) const;
                Fraction operator-(const Fraction &f) const;
                Fraction operator*(const Fraction &f) const;
                Fraction operator/(const Fraction &f) const;

                bool operator==(const Fraction &f) const;
                bool operator!=(const Fraction &f) const;
                bool operator<(const Fraction &f) const;
                bool operator>(const Fraction &f) const;
                bool operator<=(const Fraction &f) const;
                bool operator>=(const Fraction &f) const;

                operator double() const;

                BaseTypes::fractionBaseType gcd(BaseTypes::fractionBaseType a,
                                                BaseTypes::fractionBaseType b)
                    const;
                BaseTypes::fractionBaseType lcm(BaseTypes::fractionBaseType a,
                                                BaseTypes::fractionBaseType b)
                    const;

                friend std::ostream &operator<<(std::ostream &os,
                                                const Fraction &f);
                friend std::istream &operator>>(std::istream &is,
                                                Fraction &f);

                BaseTypes::fractionBaseType getNumerator() const;
                BaseTypes::fractionBaseType getDenominator() const;

                void setNumerator(BaseTypes::fractionBaseType numerator);
                void setDenominator(BaseTypes::fractionBaseType denominator);

                void reduce();

                bool isAutoReduce() const;
                void setAutoReduce(bool autoReduce);

                void abs();

                void invert();
                void negate();

                // cast int to fraction
                Fraction &operator=(int i);
                Fraction &operator+=(int i);
                Fraction &operator-=(int i);
                Fraction &operator*=(int i);
                Fraction &operator/=(int i);

                Fraction operator+(int i) const;
                Fraction operator-(int i) const;
                Fraction operator*(int i) const;
                Fraction operator/(int i) const;

                bool operator==(int i) const;
                bool operator!=(int i) const;
                bool operator<(int i) const;
                bool operator>(int i) const;
                bool operator<=(int i) const;
                bool operator>=(int i) const;
        };
}

#endif // __KSI_FRACTION_HPP
