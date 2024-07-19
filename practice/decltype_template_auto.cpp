#include <iostream>

/*
    Instead of having to type the entire expression in decltype we can use
    decltype(auto) as the return type in the function template.

    This however reintroduces the dependency of the compiler on the definition
    of the function to deduce the return type which means that the declaration
    and definition cannot be split in different places since the entire
    definition has to appear before the function is called.
*/
template<typename T, typename U>
decltype(auto) max(T a, U b)
{
    return (a > b) ? a : b;
}

int main(void)
{
    int a {56};
    double b {67.3};
    std::cout << "max(" << a << ", " << b << ") : " << max(a, b) << std::endl;
    return 0;
}