#include <iostream>

// explicit requirement of ReturnType to be passed as a template parameter
template<typename ReturnType, typename T, typename U>
ReturnType max(T a, U b)
{
    return (a > b) ? a : b;
}

// a way around this is to use auto return type deduction
// the larger type will be returned
template<typename T, typename U>
auto maximum(T a, U b)
{
    return (a > b) ? a : b;
}
// for auto type deduction, the function definition has to come before the call

int main(void)
{
    std::cout << "max(\'c\', 12) : " << max<int> ('c', 12) << std::endl;
    /*
        can also be called as:
        max<int, char, int> ('c', 12)
        max<int, char> ('c', 12)
        
        The return type is mandatory as the compiler cannot deduce the return
        type by itself. The other two parameters can be left blank and the
        compiler will deduce them.
    */

    double x {45.32};
    int y {11};
    auto result = maximum(x, y); // double is larger so double will be returned
    std::cout << "max(" << x << ", " << ") : " << result << std::endl;
    std::cout << "sizeof(result) : " << sizeof(result) << std::endl;

    // If we explicitly specify the types, the largest from among them will be
    // returned. In this case, the types will not be deduced from the arguments
    auto result2 = maximum<char, double> ('X', 10); // double will be returned
    std::cout << "sizeof(result2) : " << sizeof(result2) << std::endl;

    return 0;
}