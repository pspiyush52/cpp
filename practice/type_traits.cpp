#include <iostream>
#include <type_traits>

template<typename T> void print_num(T num)
{
    static_assert(std::is_integral<T>::value, "print_num called with a non-integral type.");
    std::cout << num << std::endl;
}

int main(void)
{
    int num{67};
    int a{8};
    print_num(num);
    double x{45.12};
    // print_num(x); // compilation will fail because x is not of integral type

    auto add = [] <typename T> (T a, T b) -> T {
        static_assert(std::is_integral<T>::value, "add called with a non-integral type.");
        return a + b;
    };
    std::cout << "add(" << num << ", " << a << ") : " << add(num, a) << std::endl;
    // add(x, x); // compilation will fail because x is not integral
    return 0;
}