#include <iostream>

int main(void)
{
    int x{21};
    double y{17.32};

    // decltype can be used to deduce the type of an expression and then that
    // can be further used to declare other variables of the same type
    decltype((x > y) ? x : y) z{};  // declaring a variable of type deduced by decltype
    std::cout << "sizeof(z) : " << sizeof(z) << std::endl;
    
    return 0;
}