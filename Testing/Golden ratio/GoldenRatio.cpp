#include"../../Source-code/Combined source file/num.hpp"
#include<string>
#include<fstream>
int main(){
    // set precision
    int N = 125, M = 125, K= 8;
    num:: setPrecision(N, M, K);
    // start the clock
    clock_t tStart = clock();
    // calculate phi
    num phi = (num::sqrt(num(5))+num(1))/2;
    
    std:: string calculated_phi = num::NumToString(phi);

    // read the true value of phi from GoldenRatio.txt
    std:: string true_phi;
    std:: ifstream phi_txt("GoldenRatio.txt");
    std:: getline(phi_txt, true_phi);
    
    // compare digits, and report the first unequal digit
    int i = 0;
    while(i<true_phi.length() && i<calculated_phi.length() &&  true_phi[i] == calculated_phi[i]){
        i++;
    }
    std::cout<<"First wrong digit is " << i<<std::endl;
    
    // report the time taken
    std:: cout<< "Time taken:" << (double)(clock() - tStart) / CLOCKS_PER_SEC << std:: endl;
}