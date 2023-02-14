#include "fraction.hpp"

namespace KSI
{
    fraction::fraction() = default;

    fraction::fraction(int i)
    {
        this->numerator = i;
        this->denominator = 1;
    }

    fraction::fraction(double d)
    {
        this->numerator = d * 1000000000;
        this->denominator = 1000000000;
        if (this->autoReduce)
        {
            this->reduce();
        }
    }

    fraction::fraction(baseTypes::fractionBaseType numerator,
                       baseTypes::fractionBaseType denominator)
    {
        this->numerator = numerator;
        this->denominator = denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
    }

    fraction::fraction(const fraction &other)
    {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
    }

    fraction::~fraction() = default;

    fraction &fraction::operator=(const fraction &other)
    {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }

    fraction &fraction::operator+=(const fraction &other)
    {
        this->numerator = this->numerator * other.denominator +
                          other.numerator * this->denominator;
        this->denominator = this->denominator * other.denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
        return *this;
    }

    fraction &fraction::operator-=(const fraction &other)
    {
        this->numerator = this->numerator * other.denominator -
                          other.numerator * this->denominator;
        this->denominator = this->denominator * other.denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
        return *this;
    }

    fraction &fraction::operator*=(const fraction &other)
    {
        this->numerator = this->numerator * other.numerator;
        this->denominator = this->denominator * other.denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
        return *this;
    }

    fraction &fraction::operator/=(const fraction &other)
    {
        this->numerator = this->numerator * other.denominator;
        this->denominator = this->denominator * other.numerator;
        if (this->autoReduce)
        {
            this->reduce();
        }
        return *this;
    }

    fraction &fraction::operator++()
    {
        this->numerator += this->denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
        return *this;
    }

    fraction &fraction::operator--()
    {
        this->numerator -= this->denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
        return *this;
    }

    fraction fraction::operator++(int)
    {
        fraction tmp(*this);
        ++(*this);
        if (this->autoReduce)
        {
            this->reduce();
        }
        return tmp;
    }

    fraction fraction::operator--(int)
    {
        fraction tmp(*this);
        --(*this);
        if (this->autoReduce)
        {
            this->reduce();
        }
        return tmp;
    }

    fraction fraction::operator-() const
    {
        return fraction(-this->numerator, this->denominator);
    }

    fraction fraction::operator+() const
    {
        return fraction(this->numerator, this->denominator);
    }

    fraction fraction::operator+(const fraction &other) const
    {
        return fraction(*this) += other;
    }

    fraction fraction::operator-(const fraction &other) const
    {
        return fraction(*this) -= other;
    }

    fraction fraction::operator*(const fraction &other) const
    {
        return fraction(*this) *= other;
    }

    fraction fraction::operator/(const fraction &other) const
    {
        return fraction(*this) /= other;
    }

    bool fraction::operator==(const fraction &other) const
    {
        return this->numerator == other.numerator &&
               this->denominator == other.denominator;
    }

    bool fraction::operator!=(const fraction &other) const
    {
        return !(*this == other);
    }

    bool fraction::operator<(const fraction &other) const
    {
        return this->numerator * other.denominator <
               other.numerator * this->denominator;
    }

    bool fraction::operator>(const fraction &other) const
    {
        return this->numerator * other.denominator >
               other.numerator * this->denominator;
    }

    bool fraction::operator<=(const fraction &other) const
    {
        return this->numerator * other.denominator <=
               other.numerator * this->denominator;
    }

    bool fraction::operator>=(const fraction &other) const
    {
        return this->numerator * other.denominator >=
               other.numerator * this->denominator;
    }

    baseTypes::fractionBaseType fraction::getNumerator() const
    {
        return this->numerator;
    }

    baseTypes::fractionBaseType fraction::getDenominator() const
    {
        return this->denominator;
    }

    void fraction::setNumerator(baseTypes::fractionBaseType numerator)
    {
        this->numerator = numerator;
    }

    void fraction::setDenominator(baseTypes::fractionBaseType denominator)
    {
        this->denominator = denominator;
    }

    std::ostream &operator<<(std::ostream &os, const fraction &f)
    {
        if (f.getDenominator() == 1)
        {
            os << f.getNumerator();
            return os;
        }
        os << f.getNumerator() << "/" << f.getDenominator();
        return os;
    }

    std::istream &operator>>(std::istream &is, fraction &f)
    {
        baseTypes::fractionBaseType numerator, denominator;
        is >> numerator >> denominator;
        f.setNumerator(numerator);
        f.setDenominator(denominator);
        if (f.autoReduce)
        {
            f.reduce();
        }
        return is;
    }

    fraction operator+(const fraction &f1, const fraction &f2)
    {
        return fraction(f1) += f2;
    }

    fraction operator-(const fraction &f1, const fraction &f2)
    {
        return fraction(f1) -= f2;
    }

    fraction operator*(const fraction &f1, const fraction &f2)
    {
        return fraction(f1) *= f2;
    }

    fraction operator/(const fraction &f1, const fraction &f2)
    {
        return fraction(f1) /= f2;
    }

    fraction::operator double() const
    {
        return static_cast<double>(this->numerator) /
               static_cast<double>(this->denominator);
    }

    baseTypes::fractionBaseType fraction::gcd(baseTypes::fractionBaseType a,
                                              baseTypes::fractionBaseType b)
        const
    {
        if (a == 0)
            return b;
        return gcd(b % a, a);
    }

    baseTypes::fractionBaseType fraction::lcm(baseTypes::fractionBaseType a,
                                              baseTypes::fractionBaseType b)
        const
    {
        return (a * b) / gcd(a, b);
    }

    void fraction::reduce()
    {
        baseTypes::fractionBaseType g = gcd(this->numerator, this->denominator);
        this->numerator /= g;
        this->denominator /= g;
    }

    void fraction::invert()
    {
        baseTypes::fractionBaseType tmp = this->numerator;
        this->numerator = this->denominator;
        this->denominator = tmp;
        if (this->autoReduce)
        {
            this->reduce();
        }
    }

    void fraction::abs()
    {
        this->numerator = std::abs(this->numerator);
        this->denominator = std::abs(this->denominator);
    }

    void fraction::negate()
    {
        this->numerator = -this->numerator;
    }

    bool fraction::isAutoReduce() const
    {
        return this->autoReduce;
    }

    void fraction::setAutoReduce(bool autoReduce)
    {
        this->autoReduce = autoReduce;
    }

    fraction &fraction::operator=(int i)
    {
        this->numerator = i;
        this->denominator = 1;
        return *this;
    }

    fraction &fraction::operator+=(int i)
    {
        throw std::runtime_error("Not implemented");
    }
    fraction &fraction::operator-=(int i)
    {
        throw std::runtime_error("Not implemented");
    }
    fraction &fraction::operator*=(int i)
    {
        return *this *= fraction(i);
    }
    fraction &fraction::operator/=(int i)
    {
        throw std::runtime_error("Not implemented");
    }

    fraction fraction::operator+(int i) const
    {
        throw std::runtime_error("Not implemented");
    }
    fraction fraction::operator-(int i) const
    {
        throw std::runtime_error("Not implemented");
    }
    fraction fraction::operator*(int i) const
    {
        auto tmp = *this;
        tmp *= i;
        return tmp;
    }
    fraction fraction::operator/(int i) const
    {
        throw std::runtime_error("Not implemented");
    }

    bool fraction::operator==(int i) const
    {
        return this->numerator == i && this->denominator == 1;
    }
    bool fraction::operator!=(int i) const
    {
        throw std::runtime_error("Not implemented");
    }
    bool fraction::operator<(int i) const
    {
        throw std::runtime_error("Not implemented");
    }
    bool fraction::operator>(int i) const
    {
        throw std::runtime_error("Not implemented");
    }
    bool fraction::operator<=(int i) const
    {
        throw std::runtime_error("Not implemented");
    }
    bool fraction::operator>=(int i) const
    {
        throw std::runtime_error("Not implemented");
    }
}