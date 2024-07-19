#include "ctwo.h"
#include "utils.h"
/* 
 * When we define a custom '<=>' operator, the compiler automatically
 * generates the '<', '<=', '>', '>=' operators but the '==' operator has to
 * be defined separately and if it is define the compiler further generates
 * the '!=' operator on its own.
 * 
 * The type double supports partial ordering by default so we use
 * partial_ordering as the return type for our spaceship operator function.
 * 
 * We can define the '<=>' operator as a member function or as a free standing
 * function, both will support implicit type conversions. 
 */
int main(void)
{
    fmt::line();
    const Point p1{-2.47, 5.63}, p2{9.82, 0.14};
    std::cout << "p1: " << p1 << '\n';
    std::cout << "p2: " << p2 << '\n';
    fmt::line();
    std::cout << std::boolalpha;
    std::cout << "p1 < p2 : " << (p1 < p2) << '\n';
    // supports implicit conversions
    std::cout << "5 <= p1 : " << (5 <= p1) << '\n';
    std::cout << "p2 > 7 : " << (p2 > 7) << '\n';
    std::cout << "p2 != p1 : " << (p2 != p1) << '\n';
    fmt::line();
    Point p3{3, 4};
    std::cout << "p3: " << p3 << '\n';
    std::cout << "p3 == 5 : " << (p3 == 5) << '\n';
    std::cout << "9.821 == p2 : " << (9.820997912635965 == p2) << '\n';
    std::cout << "p3 != 4 : " << (p3 != 4) << '\n';
    fmt::line();
    Point p4{5, 12};
    unsigned char ch{13};
    std::cout << "p4: " << p4 << '\n';
    std::cout << "p4 == ch : " << (p4 == ch) << '\n';
    fmt::line();

    return 0;
}