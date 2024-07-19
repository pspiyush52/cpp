#include "print.h"
#include "hugeint.h"
#include "exceptions.h"

void fib(int n){
    if (n < 1)
        throw ArgError("Invalid value for n");
    h_int tmp{"0"};
    h_int prev{"0"};
    h_int fib{1};
    while (--n){
        tmp = fib;
        h_int res = fib + prev;
        fib = res;
        prev = tmp;
    }
    print(fib);
}

int main(int argc, char* argv[])
{
    if (argc == 2){
        int n{atoi(argv[1])};
        print("The", n, "Fibonacci number is:");
        fib(n);
    }
    return 0;
}