#include <iostream>

class Point {
    public:
        Point(double X, double Y);
    private:
        double x;
        double y;
        // Point origin_point; // compiler error: incomplete type

        // one solution can be to declare pointer variables
        Point* origin_point1;  // this is allowed

        // another can be to declare them as static
        static Point origin_point2;  // allowed because initialization is done later

        static const Point origin_point3;
};

Point Point::origin_point2 {1.0, 1.0};
const Point Point::origin_point3 {2.0, 2.0};

int main(void)
{
    std::cout << sizeof(Point) << '\n';
    return 0;
}

Point::Point(double X, double Y):
    x(X), y(Y), origin_point1(nullptr){}