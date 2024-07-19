#include <iostream>
#include <string>
#include <concepts>

template<typename T>
concept SizeLimit = requires (T a) {
    // sizeof(a) >= 4;  // only checks the correctness of syntax, will not check the value
    sizeof(a);  // checking for syntax validity
    
    // nested requirement
    requires sizeof(a) >= 4;  // this enforces that the size of a >= 4 must be true
};

template<typename T>
concept Addable = requires (T a, T b) {
    {a + b} -> std::convertible_to<int>; // enforces the correctness of a + b syntax
    // and that the return value of a + b is convertible to an int
};

template<Addable T> T add (T a, T b)
{
    return (a + b);
}

int main(void)
{
    std::string str1 {"string1"};
    std::string str2 {"string2"};
    // std::cout << "add(str1, str2) : " << add(str1, str2) << std::endl; // compiler error
    double x {6.022};
    double y {34};
    std::cout << "add(" << x << ", " << y << ") : " << add(x, y) << std::endl;
    return 0;
}