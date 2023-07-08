#ifndef NUM___CLASS
#include"numClass.hpp"
#endif

bool num::operator==(const num &b) const
{
    for (int i = nDIGITS - 1; i >= 0; i--)
    {
        if (digits[i] != b.digits[i])
        {
            return false;
        }
    }
    return true;
}
bool num::operator!=(const num &b) const
{
    return !this->operator==(b);
}

bool num::operator<(const num &b) const
{
    if (this->signum() == b.signum())
    {
        for (int i = 0; i < nDIGITS; i++)
        {
            if (digits[i] != b.digits[i])
            {
                return digits[i] < b.digits[i];
            }
        }
        return false;
    }

    return b.signum();
}
bool num::operator>=(const num &b) const
{
    return !this->operator<(b);
}
bool num::operator>(const num &b) const
{
    // same logic follows is both of them have same sign
    if (this->signum() == b.signum())
    {
        for (int i = 0; i < nDIGITS; i++)
        {
            if (digits[i] != b.digits[i])
            {
                return digits[i] > b.digits[i];
            }
        }
        return false;
    }

    return this->signum();
}

bool num::operator<=(const num &b) const
{
    return !this->operator>(b);
}

