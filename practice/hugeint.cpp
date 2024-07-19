#include <iostream>
#include "hugeint.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
        return 1;
    
    h_int num1{argv[1]};
    h_int num2{argv[2]};
    std::cout << num1 << " + " << num2 << " = " << num1 + num2 << '\n';
    return 0;
}