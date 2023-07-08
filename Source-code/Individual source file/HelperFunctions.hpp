#ifndef NUM___CLASS
#include"numClass.hpp"
#endif

ll num:: strToDIGIT(std:: string str/*length <= baselength*/, int length)
{
    ll ans = 0;
    ll exponent = 1;
    // converts an baselength char array to a single long long integer.
    for (int i = length - 1; i >= 0; i--)
    {
        ans += (str[i] - '0') * exponent;
        exponent *= 10;
    }
    return ans;
}
ll num:: strToDIGIT2(std::string str/*length <= baselength*/, int length)
{
    ll ans = 0;
    ll exponent = 1;
    // converts an baselength string to a single long long integer.
    int i = length - 1;
    for (; i >= 0; i--)
    {
        ans += (str[i] - '0') * exponent;
        exponent *= 10;
    }
    while (exponent != number_base)
    {
        ans *= 10;
        exponent *= 10;
    }
    return ans;
}
std:: string num:: DIGITtoString(ll number)
{
    // this function prints the digits properly . say the digit is 123 then we print 00000123
    std:: string result;
    char arr[base_length];
    for (int i = base_length - 1; i >= 0; i--)
    {
        arr[i] = number % 10;
        number /= 10;
    }
    for (int i = 0; i < base_length; i++)
        result.push_back('0' + arr[i]);
    return result;
}
void num::shiftnum(num& x, ll s){
    // this function is meant to be used on non-negative numbers only
    if(!x.signum()){
        throw std:: logic_error("tried shifting a negative number");
    }
    if(s>0){
        // right shift
        int i= nDIGITS-1;
        while(i>=s){
            x.digits[i] = x.digits[i-s];
            i--;
        }
        while(i>=0){
            x.digits[i] = 0;
            i--;
        }
    }
    else if(s<0){
        // left shift
        s =  -s;
        int i = 0;
        while(i+s<nDIGITS){
            x.digits[i]= x.digits[i+s];
            i++;
        }
        while(i<nDIGITS){
            x.digits[i] = 0;
            i++;
        }
    }
}
bool num::signum() const
{
    return digits[0] < number_base / 2;
}
void num ::negate()
{
    //  convert the input to  the mybase compliment of itself

    int i = nDIGITS - 1;
    while (!digits[i] && i >= 0) // skip last zeroes
        i--;
    digits[i] = number_base - digits[i];
    i--;
    while (i >= 0)
    {
        digits[i] = number_base - digits[i] - 1;
        i--;
    }
}

std:: string num ::NumToString(const num& x)
{
    std:: string result;
    num y(x); // using the default copy constructor
    // deal with the negative case
    if (!y.signum())
    {
        result.push_back('-');
        y.negate(); // nagates the value inside the variable
    }

    // skip leading zeros
    int i = 0;
    while (y.digits[i] == 0 && i < nDigits_Before_Decimal - 1)
        i++;
    // print first non zero digits
    result.append(std::to_string(y.digits[i]));
    i++;
    // print rest of the digits before decimal
    while (i < nDigits_Before_Decimal)
    {
        result.append(DIGITtoString(y.digits[i]));
        i++;
    }
    // avoid trailing zeroes
    int t = nDIGITS;
    while (y.digits[t - 1] == 0 && t >= nDigits_Before_Decimal)
        t--;

    // if t == nDigits_After_Decimal there is no need to print the decimal point
    if (t != nDigits_After_Decimal)
    {
        result.push_back('.');
        while (i < t)
        {
            result.append(DIGITtoString(y.digits[i]));
            i++;
        }
    }
    return result;
}
    
std:: ostream& operator<<(std::ostream& os, num x) {
    std:: cout << num::NumToString(x);
    return os;
}

void num::setPrecision(ll DigitsBeforeDecimal, ll DigitsAfterDecimal, ll baseLength){
    // *** CHANGING THE PRECISION IN THE MIDDLE OF A CALCULATION WILL RESULT IN UNDEFINED BEHAVIOR *** //
    // *** SET THE PRECISION IN THE BEGING OF A PROGRAMME BEFORE DECLARING ANY NUM OBJECTS *** //
    if(PRECISION_SET){
        throw std::logic_error( "Failed to set precision\nprecision was already set");
        return;
    } 
    if(base_length > 9){
        throw std::invalid_argument("Failed to set precision\nBase Length too large\nSpecify a base length less than 10 ");
        return;
    }
    if(DigitsAfterDecimal <= 0 || baseLength <= 0 || DigitsBeforeDecimal <= 0 ||
        DigitsAfterDecimal + DigitsBeforeDecimal > 1024*1024*1024){
            throw std::invalid_argument("Failed to set precision\nInvalid Input");
            return;
        }
        
    PRECISION_SET = true;
    base_length = baseLength;
    number_base = 1;
    for(ll i =0; i<baseLength; i++){
        number_base *= 10;
    }
    nDigits_After_Decimal = DigitsAfterDecimal;
    nDigits_Before_Decimal = DigitsBeforeDecimal;
    nDIGITS = nDigits_After_Decimal+nDigits_Before_Decimal;
}