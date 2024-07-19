#include "operator_overloading.h"

int main(void)
{
    Complex c1{2, 4}, c2{1, -3};
    std::cout << "c1: " << c1 << ", c2: " << c2 << '\n';
    std::cout << "c1 + c2 : " << c1 + c2 << '\n';

    // Does not work because operator+ is implemented as a member function
    // std::cout << (3 + c2) << '\n';

    // Works because the operator- is implemented as a free function
    std::cout << "2 - c2 : " << (2 - c2) << '\n';

    return 0;
}
/*
    When a binary operator is implemented as a member function, the
    left operand is never implicitly converted.

    When (Complex) a + (Complex) b is evaluated and + is implemented
    as a member function then the result is calculated by calling the
    operator function as,
        a.operator+(b);
    
    But if the first operand is not of type Complex then the function
    call a.operator+(b) will not make any sense, e.g.,
        2 + (Complex) will be evaluated as 2.operator+(a) which does
    not make any sense.
    Why not implicitly convert 2 to Complex type
    and then call the operator member function on it? It is because
    numerous other classes may have a constructor which can create an
    object with just one argument so the compiler won't know which one
    to choose therefore it is not allowed.

    The second operand however, can be of non-Complex type since it is
    an argument to the operator+ function and if the class definition
    allows it can be implicitly converted to a Complex number and then
    can be used as an argument for the operator+ function.

    But in the implementation of an operator as a free standing
    function there is no such restriction as the function is called
    with both the operands as arguments.
        (Complex) a + (Complex) b; translates to,
        operator+(a, b);
    In this case even if the first operator is not of type Complex
    then, if it is allowed by the class definition then it can be
    implicitly converted to a Complex number and passed to the
    function as an argument.
*/