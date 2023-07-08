#ifndef NUM___CLASS
#include"numClass.hpp"
#endif

num ::num()
{
    if(!PRECISION_SET){
        throw std::runtime_error("Precision not set");
    }
    digits.resize(nDIGITS, 0);
}

num ::num(const num& b){
    if(!PRECISION_SET){
        throw std::runtime_error("Precision not set");
    }
    digits.resize(nDIGITS, 0);
    for(int i =0; i<nDIGITS; i++){
        digits[i] = b.digits[i];
    }
}

num ::num(ll integer)
{
    if(!PRECISION_SET){
        throw std::runtime_error("Precision not set");
    }
    digits.resize( nDIGITS, 0);
    // if the number is negative take absolute value
    bool positive = integer >= 0;
    if (!positive)
        integer = -integer;

    // digits after the decimal = zero and before decimal are set one by one
    for (int i = 0; i < nDigits_Before_Decimal && integer>0; i++)
    {
        digits[nDigits_Before_Decimal - 1 - i] = integer % number_base;
        integer /= number_base;
    }

    if (!positive)
        this->negate(); // if number was negative then negate it
}

num ::num(std:: string number)
{
    if(!PRECISION_SET){
        throw std::runtime_error("Precision not set");
    }
    digits.resize(nDIGITS, 0);
    int totalLength = 0, charBeforeDecimal = 0; bool positive = number[0] != '-';
    if (!positive)
        number = number.substr(1); // to skip the '-' symbol

    totalLength = number.length(); 

    while (charBeforeDecimal < totalLength && number[charBeforeDecimal] != '.')
        charBeforeDecimal++;

    // first deal with the digits before decimal
    int i = nDigits_Before_Decimal - 1, j = charBeforeDecimal;
    while (i >= 0 && j > base_length) // break string into parts of length base_length and convert one by one
    {
        digits[i] = std::stoi(number.substr(j - base_length, base_length)) ;
        j -= base_length;
        i--;
    }
    if(i>=0) 
        digits[i] = strToDIGIT(number, j);
    
    if (totalLength == charBeforeDecimal){ // means there is no decimal point in the string
        if(!positive) this->negate();
        return;
    }
    int charAfterDecimal = totalLength - charBeforeDecimal - 1;

    i = nDigits_Before_Decimal;
    j = charBeforeDecimal+1;
    while (i < nDIGITS && charAfterDecimal > base_length)
    {
        digits[i] = std::stoi(number.substr(j, base_length));
        i++;
        charAfterDecimal -= base_length;
        j += base_length;
    }
    if(i<nDIGITS)
        digits[i] = strToDIGIT2(number.substr(j), charAfterDecimal);
    if (!positive)
        this->negate();
}
/* now we define assignment operator */

num& num::operator=(const num &b)
{
    for (int i = 0; i < nDIGITS; i++)
    {
        digits[i] = b.digits[i];
    }
    return *this;
}
