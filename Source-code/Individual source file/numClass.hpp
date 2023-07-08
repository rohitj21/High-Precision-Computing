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



