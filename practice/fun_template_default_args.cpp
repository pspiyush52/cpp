#include <iostream>

// specifying a default for the ReturnType template argument
template<typename ReturnType = double, typename T, typename U>
ReturnType max(T a, U b)
{
    return (a > b) ? a : b;
}

template<typename ReturnType = int, typename T> ReturnType min(T a, T b)
{
    return (a > b) ? b : a;
}

int main(void)
{
    int a {20};
    double b {31.149};

    // the default value i.e., 'double' will be used as the return type
    std::cout << "max(" << a << ", " << b << ") : " << max(a, b) << std::endl;

    // if we specify a type explicitly, it will be the return type of the generated function
    std::cout << "max(" << a << ", " << b << ") : " << max<int> (a, b) << std::endl;

    double x {3.141};
    double y {3.745};
    std::cout << "min(" << x << ", " << y << ") : " << min(x, y) << std::endl;
    std::cout << "min<double> (" << x << ", " << y << ") : " << min<double>(x, y) << std::endl;
    return 0;
}