#include <iostream>

// We can delete any constructor we do not want to use in our class by using
// the delete keyword as follows
class Point {
    public:
        Point() = delete; // marks the default constructor as deleted
        Point(double X, double Y);
        Point(const Point& p) = delete;  // deletes the copy constructor
        Point(Point&& p) = delete;  // deletes the move constructor
        double* get_x();
        double* get_y();
        Point operator+(const Point& p) const;
        ~Point();
    private:
        double* x;
        double* y;
        friend std::ostream& operator<<(std::ostream& output, const Point& p);
};

int main(void)
{
    // Point p; // compiler error
    Point p1(1.0, 15.2);

    // Point p2(p1); // compiler error
    std::cout << p1 << '\n';
    return 0;
}

Point::Point(double X, double Y):
    x(new double{X}), y(new double{Y}){}

double* Point::get_x(){
    return x;
}

double* Point::get_y(){
    return y;
}

Point Point::operator+(const Point& p) const
{
    return Point(*(p.x) + *x, *(p.y) + *y);
}

Point::~Point(){
    delete x;
    delete y;
}

std::ostream& operator<<(std::ostream& output, const Point& p)
{
    output << "Point at " << &p << " <x: " << *(p.x) << ", y: "
    << *(p.y) << ">";
    return output;
}