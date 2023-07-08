#ifndef NUM__CLASS
#define NUM__CLASS
#include<iostream>
#include<vector>
#include<math.h>
typedef long long ll;
class num{
    private:
    static ll nDigits_Before_Decimal, nDigits_After_Decimal, number_base, base_length, nDIGITS;
    static bool PRECISION_SET;
    std::vector<ll> digits;
    public:

    //  useful constructors and assignment operators
    num();                                      // a default constrctor to instantiate numbers (to zero)
    num(const num& b);                          // copy constructor
    num(std:: string arr);                            // first to  create numbers with a large number of digits , using  char input
    num(ll integer);                            // another one to make numbes from int
    num& operator=(const num &b);               // assignment operator : O(nDIGITS)
    ~num(){}
    
    // Declare some helper functions
    private:
    static ll strToDIGIT(std:: string str/*length <= baselength*/, int length);
    static ll strToDIGIT2(std:: string str/*length <= baselength*/, int length);
    static std:: string DIGITtoString(ll number);
    void negate();
    public:
    bool signum() const;                                            // returns 1 if the number is positive, 0 if neg : O(1) 
    static void shiftnum(num &x, ll s);
    static std:: string NumToString(const num &x);
    static void setPrecision(ll DigitsBeforeDecimal, ll DigitsAfterDecimal, ll baseLength); // functions for changing precision
    

    // Comparision operators
    bool operator==(const num &b) const;        // O(nDIGITS)
    bool operator!=(const num &b) const;        // O(nDIGITS)

    bool operator>(const num &b) const;         // O(nDIGITS)
    bool operator>=(const num &b) const;        // O(nDIGITS)
    bool operator<(const num &b) const;         // O(nDIGITS)
    bool operator<=(const num &b) const;        // O(nDIGITS)


    // Arithematic Operators
    num operator+(const num &b) const;          // O(nDIGITS)
    num operator-(const num &b) const;          // O(nDIGITS)
    num operator-() const;                      // O(nDIGITS)
    num operator*(const num &b) const;          // O(nDIGITS^2)
    num operator*(ll b) const;                  // O(nDIGITS)                 for efficient multiplication with small integers
    num reciprocal() const;                     // O(nDIGITS*nDIGITS*log(nDIGITS))
    num operator/(const num &b) const;          // O(nDIGITS*nDIGITS*log(nDIGITS))
    num operator/(ll b) const;                  // O(nDIGITS);                for efficient division with small integers

    
    // Declare math functions
    public:
    static num int_reciprocal(ll x);                                // O(nDIGITS)
    static num sqrt(const num &x);                                  // O(nDIGITS*log(nDIGITS))                                     
    static num arctan(const num &x);
    static num arctanOfReciprocal(ll x);                            // O(nDIGITS*nDIGITS)


};

std:: ostream& operator<<(std:: ostream& os, num number);


// initialising static variables
ll num:: base_length;
ll num:: number_base;
ll num:: nDigits_Before_Decimal;
ll num:: nDigits_After_Decimal;
ll num:: nDIGITS;
bool num::PRECISION_SET= false;

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
#endif