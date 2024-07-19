#include <iostream>
#include "triple.h"

int main(void)
{
    triple t1{1, 2, 3};
    triple t2{1, 2, 3};
    std::cout << std::boolalpha;
    std::cout << "t1 == t2 : " << (t1 == t2) << '\n';
    std::cout << "t1 != t2 : " << (t1 != t2) << '\n';
    std::cout << "t2 == 2 : " << (t1 == 2) << '\n';
    /*
        When we define the operators as member functions the left operand
        cannot be implicitly converted since the operator function is called
        on the left operand, but in the case of the '==' operator the compiler
        does some internal adjustments to make them work.
        (2 == t1) is equivalent to saying (t1 == 2) and the operator will work
        correctly since the left operand is an object.
    */
    std::cout << "2 == t1 : " << (2 == t1) << '\n';
    
    return 0;
}