#include "oopString.hpp"

oopString::oopString()
{
    str = new char[1];
    str[0] = '\0';
    n = 0;
}

oopString::~oopString()
{
    delete[] str;
}

oopString::oopString(const char *s)
{
    n = strlen(s);
    str = new char[n + 1];
    strcpy(str, s);
}

size_t oopString::spacesCount() const
{
    size_t count = 0;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

oopString oopString::lowerCase()
{
    oopString result;
    result.n = n;
    result.str = new char[result.n + 1];
    strcpy(result.str, str);
    for (int i = 0; i < result.n; i++)
    {
        if (result.str[i] >= 'A' && result.str[i] <= 'Z')
        {
            result.str[i] += 32;
        }
    }
    return result;
}

oopString oopString::deletePunctuation()
{
    oopString result;
    result.n = n;
    result.str = new char[result.n + 1];
    strcpy(result.str, str);
    for (int i = 0; i < result.n; i++)
    {
        if (result.str[i] == '.' || result.str[i] == ',' ||
            result.str[i] == '!' || result.str[i] == '?')
        {
            for (int j = i; j < result.n; j++)
            {
                result.str[j] = result.str[j + 1];
            }
            result.n--;
            i--;
        }
    }
    return result;
}

oopString oopString::operator/(const oopString &other) const
{
    oopString result;
    result.n = n + other.n;
    result.str = new char[result.n + 1];
    strcpy(result.str, str);
    strcat(result.str, other.str);
    return result;
}

std::istream &operator>>(std::istream &in, oopString &s)
{
    char buffer[1000];
    in.getline(buffer, 1000);
    s.n = strlen(buffer);
    s.str = new char[s.n + 1];
    strcpy(s.str, buffer);
    return in;
}

std::ostream &operator<<(std::ostream &out, const oopString &s)
{
    out << s.str;
    return out;
}