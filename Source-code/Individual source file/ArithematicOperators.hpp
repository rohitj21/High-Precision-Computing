#ifndef NUM___CLASS
#include"numClass.hpp"
#endif

num num::operator-() const
{
    num ans(*this);
    ans.negate();
    return ans;
}

num num::operator+(const num &b) const
{
    num ans;
    ll carry = 0;
    for (int i = nDIGITS - 1; i >= 0; i--)
    {
        ll temp = carry + b.digits[i] + digits[i];
        ans.digits[i] = temp % number_base;
        carry = temp >= number_base;
    }
    return ans;
}
num num::operator-(const num &b) const
{
    num ans;
    ll carry = 0;
    for (int i = nDIGITS - 1; i >= 0; i--)
    {
        ll temp = digits[i] - b.digits[i] - carry ;
        ans.digits[i] = (temp + number_base) % number_base;
        carry = temp < 0;
    }
    return ans;
}

num num::operator*(const num &c) const
{
    /* for multiplication we  multiply every pair and then group according to exponent */
    // multiplication is the most used operation so it must be as fast as possible

    //  to deal with negative numbers just convert all number to be positive
    num b(c);
    num a(*this);
    bool sameSign = a.signum() == b.signum(); // variable to store the sign of the final ans

    if (!a.signum())
        a.negate();
    if (!b.signum())
        b.negate();

    // creating an empty array to hold the temporary result

    std:: vector<ll> ans(2*nDIGITS,0);

    for (int i = 0; i < nDIGITS; i++)
    {
        // no need to waste time multipying with zeros
        if (!b.digits[i])
            continue;

        for (int j = 0; j < nDIGITS; j++)
        {
            ans[i + j + 1] += a.digits[j] * b.digits[i];
        }
    }

    // now  modify the digits of ans appropriately
    for (int i = 2 * (nDIGITS) - 1; i > 0; i--)
    {
        ans[i - 1] += ans[i] / number_base;
        ans[i] = ans[i] % number_base;
    }
    // now set the answer variable
    num prod;
    for (int i = 0; i < nDIGITS; i++)
    {
        prod.digits[i] = ans[nDigits_Before_Decimal + i];
    }
    if (!sameSign)
        prod.negate();
    return prod;
}

// for division we first need reciprocal
num num::reciprocal() const
{
    num guess;
    if(this->operator== (guess)){
        throw std::logic_error("division by 0 ocurred");
    }
    // take care of negative numbers
    bool positive = this->signum();
    num a(*this);
    if (!positive)
        a.negate();
    // if (a.digits[0] > number_base / 4) 
    //     // for very large number return 0
    //     return num();

    // after handling the edge cases the real chalenge is to make a smart guess for the reciprocal
    // the exponent of the ans is the negative of the exponent of the given number
    int r = 0;
    while (!a.digits[r])
        r++;
    
    guess.digits[nDIGITS - 1 - r] = number_base / a.digits[r];
    num two(2); // we use this number quite often so better to store it than to generate it everytime
    // the approximation converges quadratically so we only need to do at most log2(LK) iterations
    int logLK = (int)std:: log2(base_length * nDIGITS) + 2;
    for (int k = 0; k < logLK; k++)
    {
        //std::cout<<guess<<std::endl;
        guess = guess * (two - a * guess);
    }
    if (!positive)
        guess.negate();
    return guess;
}

// now we can finally impliment the division
num num::operator/(const num &b) const
{
    num  y;
    if(b == y){
        throw std:: logic_error("Division by 0");
    }
    num x(*this);
    y = b;
    bool sameSign = x.signum() == y.signum();
    if(!x.signum()){
        x = -x;
    }
    if(!y.signum()){
        y = -y;
    }
    int i = 0;
    num p, q;
    while(y.digits[i] == 0){
        i++;
    }
    int shift = nDigits_Before_Decimal - i - 1;
    shiftnum(x, shift);
    shiftnum(y, shift);
    if(sameSign)
        return x*y.reciprocal();
    return -x*y.reciprocal();
}

num num::operator*(ll x) const
{
    num ans;
    num y(*this);
    bool sameSign = y.signum() == (x>0);
    if(!y.signum()){
        y = -y;
    }
    if(x<0){
        x = -x;
    }

    ll carry = 0;
    for (int i = nDIGITS - 1; i >= 0; i--){
        ll temp = y.digits[i] * x + carry;
        ans.digits[i] = temp % number_base;
        carry = temp / number_base;
    }
    if(!sameSign){
        ans.negate();
    }
    return ans;
}

num num::operator/(ll x) const
{
    if(x==0){
        throw std::logic_error("Division by zero");
    }
    num ans;
    num y(*this);
    bool sameSign = y.signum() == (x>0);
    if(!y.signum()){
        y = -y;
    }
    if(x<0){
        x = -x;
    }
    ll remainder = 0;
    for (int i = 0; i < nDIGITS; i++){
        ll temp = remainder * number_base + y.digits[i];
        ans.digits[i] = temp / x;
        remainder = temp % x;
    }
    if(!sameSign){
        ans.negate();
    }
    return ans;

}
