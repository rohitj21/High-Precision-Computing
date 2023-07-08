#ifndef NUM___CLASS
#include"numClass.hpp"
#endif

/* now some useful math functions */

// square root function

num num:: sqrt(const num &x)
{

    num guess;
    if (x <= num()) /*edge case*/
        throw std::logic_error("Can't calculate the sqrt of a negative number");

    /*
        now how to find a good approximation to begin with?
        finding the exponent and halfing it looks like a good idea
        in our array indexing  the index (i) of the first non zero digit
        is related to the exponent (ex) as
            i = ex + M-1
    */
    int i = 0;
    /* find the first non zero digit's index i*/
    while (i < nDIGITS && !x.digits[i])
    {
        i++;
    }
    if ((i - nDigits_Before_Decimal + 1) % 2 == 0)
        /* case when the exponent is even */
        guess.digits[(i + nDigits_Before_Decimal - 1) / 2] = std::sqrt(x.digits[i]);
    else
        /* if the exponent is odd */
        guess.digits[(i + nDigits_Before_Decimal + 1) / 2] = std:: sqrt(x.digits[i] * number_base + x.digits[i + 1]);

    /*
        since we are starting with a very good approximation and the seq of guesses converges
        quadratically we only ever need to do log2(LK) iterations
    */
    int logLK = std:: log2(base_length * (nDIGITS)) + 2;
    for (i = 0; i < logLK; i++)
    {
        guess = (guess + (guess.reciprocal()) * x) / 2;
    }

    return guess;
}
num num:: int_reciprocal(ll x)
{
    if(x==0){
        throw std:: logic_error("divison by zero");
    }
    bool positive = x>0;
    if(!positive){
        x = -x;
    }
    num ans;
    ll remainder = 1;
    for (int i = nDigits_Before_Decimal; i < nDIGITS; i++){
        ans.digits[i] = (remainder * number_base) / x;
        remainder = (remainder * number_base) % x;
    }
    if(!positive){
        ans.negate();
    }
    return ans;
}

num num::arctan(const num &x)
{
    num xx = x * x;
    num ans;
    num zero;
    num term(x);

    for (int i = 1; term != zero; i += 2)
    {
        if (i & 2)
            ans = ans - term / i;
        else
            ans = ans + term / i;
        term = xx * term; /* this multiplication is O(n^2) */
    }
    return ans;
}

/* exploit the fact that we only need the arctan of the reciprocals of integers*/
num num:: arctanOfReciprocal(ll x)
{

    ll xx = x * x;
    num ans, zero;
    num term(int_reciprocal(x));

    for (int i = 1; term != zero; i += 2)
    {
        if (i & 2)
            ans = ans - term / i;
        else
            ans = ans + term / i;
        term = term / xx; /* this  is O(n) */
    }
    return ans;
}