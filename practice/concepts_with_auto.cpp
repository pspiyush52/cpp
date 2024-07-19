#include <iostream>
#include <concepts>

template<typename T>
requires std::is_convertible_v<T, double>
auto adjust(T a)
{
    return (a + 3.498) / 2;
}

int main(void)
{
    // std::integral auto x = adjust(45); // will generate a compiler error
    // because adjust returns double which is not integral

    std::floating_point auto y = adjust(47); // succeeds because adjust returns double
    std::cout << "y : " << y << std::endl;
    
    return 0;
}