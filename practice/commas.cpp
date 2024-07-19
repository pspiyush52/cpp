#include <iostream>
#include "defs.h"

template<typename T>
void print_commas(T num){
    if (num < 1000)
        std::cout << num;
    else{
        print_commas(num / 1000);
        std::cout << ',' << (num % 1000);
    }
}

int main(void)
{
    print_commas(6546547894); newline;
    print_commas(123);
    return 0;
}