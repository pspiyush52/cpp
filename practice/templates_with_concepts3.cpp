#include <iostream>
#include <concepts>

template<typename T>
concept Number = (std::integral<T>||std::floating_point<T>)&&
                 (!std::same_as<T, char>)&&
                 (!std::same_as<T, bool>);

template<Number T, Number U>
auto add(T a, U b) { return a + b; }

int main(void)
{
    std::cout << add(3.4, 17) << '\n';
    return 0;
}