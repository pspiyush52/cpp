#include "print.h"

// Requires two modulo operations
bool isEquivalent_n(int a, int b, int n) {
    return ((a % n) == (b % n));
}

// Requires one modulo operation
bool isEquivalent(int a, int b, int n) {
    return (((a - b) % n) == 0);
}

int main(void)
{
    int a = 7;
    int b = 3;
    int n = 2;
    std::cout << std::boolalpha;
    print(isEquivalent(a, b, n));
    print(isEquivalent_n(a, b, n));
    return 0;
}
