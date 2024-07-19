#include <iostream>
/*
// we can use decltype to deduce the return type of a function template
template<typename T, typename U>
auto max(T a, U b) -> decltype((a > b) ? a : b)
{
    return (a > b) ? a : b;
}
*/

/*
    we can also split the declaration and definition in this case because
    the compiler can deduce the type from decltype and does not need to see
    the complete definition of the function to deduce its return type
*/
// Declaration
template<typename T, typename U>
auto max(T a, U b) -> decltype((a > b) ? a : b);

int main(void)
{
    int a {37};
    double b {68.2};
    std::cout << "max(" << a << ", " << b << ") : " << max(a, b) << std::endl;
    return 0;
}

// Definition
template<typename T, typename U>
auto max(T a, U b) -> decltype((a > b) ? a : b)
{
    return (a > b) ? a : b;
}