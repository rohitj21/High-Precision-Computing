#include"../../Source-code/Combined source file/num.hpp"
#include<string>
#include<fstream>
int main(){
    // set precision
    int N = 2, M = 1250, K= 8;
    num:: setPrecision(N, M, K);
    // start the clock
    clock_t tStart = clock();
    // calculate pi
    num pi = num::arctanOfReciprocal(5) * 16 - num::arctanOfReciprocal(239) * 4;
    std:: string calculated_pi = num::NumToString(pi);

    // read the true value of pi from pi.txt
    std:: string true_pi;
    std:: ifstream pi_txt("pi.txt");
    std:: getline(pi_txt, true_pi);

    // compare digits, and report the first unequal digit
    int i = 0;
    while(i<true_pi.length() && i<calculated_pi.length() &&  true_pi[i] == calculated_pi[i]){
        i++;
    }
    std::cout<<"First wrong digit is " << i<<std::endl;
    
    // report the time taken
    std:: cout<< "Time taken:" << (double)(clock() - tStart) / CLOCKS_PER_SEC << std:: endl;
}