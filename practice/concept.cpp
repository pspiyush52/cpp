#include <iostream>
#include <concepts>

// Concepts in C++ are used to restrict the type of arguments that can be passed
// to a function template.

// Syntax #1
template<typename T>
requires std::integral<T>
// requires std::is_integral<T>::value // using type traits also works
T add (T a, T b)
{
    return a + b;
}
// any expression that can be evaluated at compile time and which results in a
// boolean can be used with the requires keyword

// Syntax #2
template<std::integral T>
T min (T a, T b)
{
    return (a < b) ? a : b;
}

// Syntax #3
template<typename T>
double avg(T a, T b) requires std::integral<T> // requires std::is_integral<T>::value can be used as well
{
    return static_cast<double>(a + b) / 2;
}

// using concepts with auto
std::integral auto diff (std::integral auto x, std::integral auto y)
{
    return x - y;
}

int main(void)
{
    int a{27};
    int b{14};
    std::cout << "add(" << a << ", " << b << ") : " << add(a, b) << std::endl;
    std::cout << "min(" << a << ", " << b << ") : " << min(a, b) << std::endl;

    // can also be used with lambda functions
    auto max = [] <std::integral T> (T a, T b) {
        return (a > b) ? a : b;
    };
    std::cout << "max(" << a << ", " << b << ") : " << max(a, b) << std::endl;

    // using the requires keyword
    auto fun = [] <typename T> requires std::floating_point<T> (T num) {
        std::cout << "floating point num : " << num << std::endl;
    };
    fun(4.5);

    std::cout << "avg(" << a << ", " << b << ") : " << avg(a, b) << std::endl;

    // Syntax #3 with a lambda function
    auto prod = [] <typename T> (T a, T b) -> T requires std::integral<T> {
        return a * b;
    };

    std::cout << "prod(" << a << ", " << b << ") : " << prod(a, b) << std::endl;

    return 0;
}