#include <iostream>

// structured bindings apply only to public member variables
/*
class Point {
    public:
        double x;
        double y;
};
*/
struct Point {
    double x;
    double y;
};

int main(void)
{
    Point p1 {1, 7};
    std::cout << "p1 : " << "[" << p1.x << ", " << p1.y << "]\n";
    auto [a, b] = p1;  // copies the values of x and y to a and b respectively
    std::cout << "a : " << a << std::endl;
    std::cout << "b : " << b << std::endl;
    p1.x = 11;
    p1.y = 3;
    std::cout << "Changed p1 : " << "[" << p1.x << ", " << p1.y << "]\n";

    // changing p1 does not affect a and b since they're just copies
    std::cout << "a : " << a << std::endl;
    std::cout << "b : " << b << std::endl;
    
    return 0;
}