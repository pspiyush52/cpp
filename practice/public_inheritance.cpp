#include "quad.h"

int main(void)
{
    Rectangle r1{2.1, 1.48};
    double side{4.37};
    Square s1{side};
    Square s2{side};
    std::cout << "Area of a square of side " << side << ": " << s1.area() << '\n';
    std::cout << "Perimeter of a square of side " << side << ": " << s1.perimeter() << '\n';
    std::cout << std::boolalpha;
    std::cout << "s1 == s2 : " << (s1 == s2) << '\n';
    Square s3{2.49};
    std::cout << "s1 > s3 : " << (s1 > s3) << '\n';
    std::cout << (s3 <= r1);

    return 0;
}