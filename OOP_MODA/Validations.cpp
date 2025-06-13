#include "Validations.h"

bool Validations::isValidEGN(const MyString& EGN)
{
    if (EGN.getSize() == 10 && containsOnlyDigits(EGN))
    {
        return true;
    }
    return false;
}

bool Validations::containsOnlyDigits(const MyString& EGN) 
{
    for (size_t i = 0; i < EGN.getSize(); i++)
    {
        if (!isDigit(EGN[i]))
        {
            return false;
        }
    }
    return true;
}

bool Validations::isDigit(char ch) 
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    return false;
}
