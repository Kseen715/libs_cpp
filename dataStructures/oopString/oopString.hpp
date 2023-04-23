#ifndef C7C74F3A_948D_4128_A234_F32FE88B665C
#define C7C74F3A_948D_4128_A234_F32FE88B665C

#include <cstring>
#include <iostream>

class oopString
{
    char *str;
    int n;

public:
    oopString();
    ~oopString();

    oopString(const char *s);

    size_t spacesCount() const;

    oopString lowerCase();

    oopString deletePunctuation();

    oopString operator/(const oopString &other) const;

    friend std::istream &operator>>(std::istream &in, oopString &s);

    friend std::ostream &operator<<(std::ostream &out, const oopString &s);
};

#endif /* C7C74F3A_948D_4128_A234_F32FE88B665C */
