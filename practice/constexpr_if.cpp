#include <iostream>
#include <type_traits>
#include <string>

void floating_point_fun(double d)
{
    std::cout << "floating_point_fun() called...\n";
}
void integral_fun(int n)
{
    std::cout << "integral_fun() called...\n";
}

template<typename T>
void fun(T num)
{
    // using constexpr ensures that only the statements which are needed make it to
    // the template instance. For example, if fun is called with an int, then the first
    // if condition will succeed and only that condition and the statement associated
    // with it will exist in the template instance and not the subsequent if's and their
    // statements
    if constexpr(std::is_integral<T>::value)
        integral_fun(num);
    else if constexpr(std::is_floating_point<T>::value)
        floating_point_fun(num);
    else
    {
        std::cerr << "Argument must be integral or floating point.\n";
        exit(1);
    }
}

int main(void)
{
    fun(54);
    std::string s{"string"};
    fun(s);
    return 0;
}