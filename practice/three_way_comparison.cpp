#include <iostream>

int main(void)
{
    int x{36}, y{87};
    if ((x <=> y) < 0)
        std::cout << "x < y\n";
    else
        std::cout << "x >= y\n";
    
    /*
        The three way comparison operator '<=>' returns a type whose value is
        comparable to the literal 0. It cannot be compared with an int of
        value 0 and works only with the literal 0.
        Specifically it returns an object of either std::strong_ordering,
        std::weak_ordering or std::partial_ordering type.
    */
    auto result = x <=> y;
    if (result < 0)
        std::cout << "x < y\n";
    else if (result == 0)
        std::cout << "x == y\n";
    else
        std::cout << "x > y\n";

    std::cout << "Size of the object returned by the <=> operator = " << sizeof(result) << '\n';

    return 0;
}