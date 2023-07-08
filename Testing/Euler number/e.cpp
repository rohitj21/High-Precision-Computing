#include"../../Source-code/Combined source file/num.hpp"
#include<string>
#include<fstream>
int main(){
    // set precision
    int N = 5, M = 12500, K= 8;
    num:: setPrecision(N, M, K);
    // start the clock
    clock_t tStart = clock();
    // calculate e
    num e(0);
    num term(1);
    num zero(0);
    long long r = 1;
    while(term != zero){
        e = e + term;
        term = term/r;
        r++;
    }

    
    std:: string calculated_e = num::NumToString(e);

    // read the true value of e from e.txt
    std:: string true_e;
    std:: ifstream e_txt("e.txt");
    std:: getline(e_txt, true_e);
    
    // compare digits, and report the first unequal digit
    int i = 0;
    while(i<true_e.length() && i<calculated_e.length() &&  true_e[i] == calculated_e[i]){
        i++;
    }
    std::cout<<"First wrong digit is " << i<<std::endl;
    
    // report the time taken
    std:: cout<< "Time taken:" << (double)(clock() - tStart) / CLOCKS_PER_SEC << std:: endl;
    return 0;
}