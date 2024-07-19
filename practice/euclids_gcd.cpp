#include "string.h"

int gcd(int, int);

int main(int argc, char* argv[])
{
    if (argc != 3){
        std::cout << "The number of inputs must be 2\n";
        return 1;
    }
    string arg1{argv[1]}, arg2{argv[2]};
    try{
        int a{arg1.stoi()}, b{arg2.stoi()};
        std::cout << "The GCD of " << a << " and " << b << " is " << gcd(a, b) << '\n';
    }
    catch(ValueError&){
        std::cout << "Invalid input\n";
    }
    return 0;
}

int gcd(int m, int n){
    if (!m)
        return n;
    return gcd(n % m, m);
}