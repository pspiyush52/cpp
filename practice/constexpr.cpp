#include <iostream>
/*
 * constant expressions are used to define constants which are evaluated at 
 * compile time and the result of the expression is stored in the binary
 * executable and reused whenever the binary file is executed.
 * 
 * This is beneficial in case of heavy computations. The heavy computation is
 * performed once by the developer while generating the executable and then
 * any user of the application can benefit from the results of the computation
 * done at compile time.
 */
int main(void)
{
    const int x = 34;
    std::cout << std::showbase;
    // std::cout << std::hex << 0x3f4;
    std::cout << -0x7fff;
    return 0;
}