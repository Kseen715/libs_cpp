#include "fraction.hpp"

namespace KSI
{
    Fraction::Fraction() = default;

    Fraction::Fraction(int i)
    {
        this->numerator = i;
        this->denominator = 1;
    }

    Fraction::Fraction(double d)
    {
        this->numerator = (BaseTypes::fractionBaseType)(d * 1000000000);
        this->denominator = 1000000000;
        if (this->autoReduce)
        {
            this->reduce();
        }
    }

    Fraction::Fraction(BaseTypes::fractionBaseType numerator,
                       BaseTypes::fractionBaseType denominator)
    {
        this->numerator = numerator;
        this->denominator = denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
    }

    Fraction::Fraction(const Fraction &other)
    {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
    }

    Fraction::~Fraction() = default;

    Fraction &Fraction::operator=(const Fraction &other)
    {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }

    Fraction &Fraction::operator+=(const Fraction &other)
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

    Fraction &Fraction::operator-=(const Fraction &other)
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

    Fraction &Fraction::operator*=(const Fraction &other)
    {
        this->numerator = this->numerator * other.numerator;
        this->denominator = this->denominator * other.denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
        return *this;
    }

    Fraction &Fraction::operator/=(const Fraction &other)
    {
        this->numerator = this->numerator * other.denominator;
        this->denominator = this->denominator * other.numerator;
        if (this->autoReduce)
        {
            this->reduce();
        }
        return *this;
    }

    Fraction &Fraction::operator++()
    {
        this->numerator += this->denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
        return *this;
    }

    Fraction &Fraction::operator--()
    {
        this->numerator -= this->denominator;
        if (this->autoReduce)
        {
            this->reduce();
        }
        return *this;
    }

    Fraction Fraction::operator++(int)
    {
        Fraction tmp(*this);
        ++(*this);
        if (this->autoReduce)
        {
            this->reduce();
        }
        return tmp;
    }

    Fraction Fraction::operator--(int)
    {
        Fraction tmp(*this);
        --(*this);
        if (this->autoReduce)
        {
            this->reduce();
        }
        return tmp;
    }

    Fraction Fraction::operator-() const
    {
        return Fraction(-this->numerator, this->denominator);
    }

    Fraction Fraction::operator+() const
    {
        return Fraction(this->numerator, this->denominator);
    }

    Fraction Fraction::operator+(const Fraction &other) const
    {
        return Fraction(*this) += other;
    }

    Fraction Fraction::operator-(const Fraction &other) const
    {
        return Fraction(*this) -= other;
    }

    Fraction Fraction::operator*(const Fraction &other) const
    {
        return Fraction(*this) *= other;
    }

    Fraction Fraction::operator/(const Fraction &other) const
    {
        return Fraction(*this) /= other;
    }

    bool Fraction::operator==(const Fraction &other) const
    {
        return this->numerator == other.numerator &&
               this->denominator == other.denominator;
    }

    bool Fraction::operator!=(const Fraction &other) const
    {
        return !(*this == other);
    }

    bool Fraction::operator<(const Fraction &other) const
    {
        return this->numerator * other.denominator <
               other.numerator * this->denominator;
    }

    bool Fraction::operator>(const Fraction &other) const
    {
        return this->numerator * other.denominator >
               other.numerator * this->denominator;
    }

    bool Fraction::operator<=(const Fraction &other) const
    {
        return this->numerator * other.denominator <=
               other.numerator * this->denominator;
    }

    bool Fraction::operator>=(const Fraction &other) const
    {
        return this->numerator * other.denominator >=
               other.numerator * this->denominator;
    }

    BaseTypes::fractionBaseType Fraction::getNumerator() const
    {
        return this->numerator;
    }

    BaseTypes::fractionBaseType Fraction::getDenominator() const
    {
        return this->denominator;
    }

    void Fraction::setNumerator(BaseTypes::fractionBaseType numerator)
    {
        this->numerator = numerator;
    }

    void Fraction::setDenominator(BaseTypes::fractionBaseType denominator)
    {
        this->denominator = denominator;
    }

    std::ostream &operator<<(std::ostream &os, const Fraction &f)
    {
        if (f.getDenominator() == 1)
        {
            os << f.getNumerator();
            return os;
        }
        os << f.getNumerator() << "/" << f.getDenominator();
        return os;
    }

    std::istream &operator>>(std::istream &is, Fraction &f)
    {
        BaseTypes::fractionBaseType numerator, denominator;
        is >> numerator >> denominator;
        f.setNumerator(numerator);
        f.setDenominator(denominator);
        if (f.autoReduce)
        {
            f.reduce();
        }
        return is;
    }

    Fraction operator+(const Fraction &f1, const Fraction &f2)
    {
        return Fraction(f1) += f2;
    }

    Fraction operator-(const Fraction &f1, const Fraction &f2)
    {
        return Fraction(f1) -= f2;
    }

    Fraction operator*(const Fraction &f1, const Fraction &f2)
    {
        return Fraction(f1) *= f2;
    }

    Fraction operator/(const Fraction &f1, const Fraction &f2)
    {
        return Fraction(f1) /= f2;
    }

    Fraction::operator double() const
    {
        return static_cast<double>(this->numerator) /
               static_cast<double>(this->denominator);
    }

    BaseTypes::fractionBaseType Fraction::gcd(BaseTypes::fractionBaseType a,
                                              BaseTypes::fractionBaseType b)
        const
    {
        if (a == 0)
            return b;
        return gcd(b % a, a);
    }

    BaseTypes::fractionBaseType Fraction::lcm(BaseTypes::fractionBaseType a,
                                              BaseTypes::fractionBaseType b)
        const
    {
        return (a * b) / gcd(a, b);
    }

    void Fraction::reduce()
    {
        BaseTypes::fractionBaseType g = gcd(this->numerator, this->denominator);
        this->numerator /= g;
        this->denominator /= g;
        if (this->denominator < 0)
        {
            this->numerator = -this->numerator;
            this->denominator = -this->denominator;
        }
    }

    void Fraction::invert()
    {
        BaseTypes::fractionBaseType tmp = this->numerator;
        this->numerator = this->denominator;
        this->denominator = tmp;
        if (this->autoReduce)
        {
            this->reduce();
        }
    }

    void Fraction::abs()
    {
        this->numerator = std::abs(this->numerator);
        this->denominator = std::abs(this->denominator);
    }

    void Fraction::negate()
    {
        this->numerator = -this->numerator;
    }

    bool Fraction::isAutoReduce() const
    {
        return this->autoReduce;
    }

    void Fraction::setAutoReduce(bool autoReduce)
    {
        this->autoReduce = autoReduce;
    }

    Fraction &Fraction::operator=(int i)
    {
        this->numerator = i;
        this->denominator = 1;
        return *this;
    }

    Fraction &Fraction::operator+=(int i)
    {
        return *this += Fraction(i);
    }
    Fraction &Fraction::operator-=(int i)
    {
        return *this -= Fraction(i);
    }
    Fraction &Fraction::operator*=(int i)
    {
        return *this *= Fraction(i);
    }
    Fraction &Fraction::operator/=(int i)
    {
        return *this /= Fraction(i);
    }

    Fraction Fraction::operator+(int i) const
    {
        auto tmp = *this;
        tmp += i;
        return tmp;
    }
    Fraction Fraction::operator-(int i) const
    {
        auto tmp = *this;
        tmp -= i;
        return tmp;
    }
    Fraction Fraction::operator*(int i) const
    {
        auto tmp = *this;
        tmp *= i;
        return tmp;
    }
    Fraction Fraction::operator/(int i) const
    {
        auto tmp = *this;
        tmp /= i;
        return tmp;
    }

    bool Fraction::operator==(int i) const
    {
        return this->numerator == i && this->denominator == 1;
    }
    bool Fraction::operator!=(int i) const
    {
        return !(*this == i);
    }
    bool Fraction::operator<(int i) const
    {
        return this->numerator < i * this->denominator;
    }
    bool Fraction::operator>(int i) const
    {
        return this->numerator > i * this->denominator;
    }
    bool Fraction::operator<=(int i) const
    {
        return this->numerator <= i * this->denominator;
    }
    bool Fraction::operator>=(int i) const
    {
        return this->numerator >= i * this->denominator;
    }
}