#include <iostream>
#include <iomanip>

int main (void)
{
    using real = long double;
    real e {2.71828182845};
    std::cout << std::setprecision(15);
    std::cout << e << std::endl;

    using ull = unsigned long long int;
    ull num {21474836448878745};
    std::cout << num << std::endl;
    
    return 0;
}