#include <iostream>
#include <cmath>
#include <utility>
/*
    Using rel_ops namespace is convenient when we have to do comparisons b/w
    class objects. If we go by the regular method then we will have to write
    separate functions for each operator which is tedious.

    rel_ops namespace contains operator function templates which make it very
    easy to have the functionality of all logical comparisons by defining just
    two operator functions '==' and '<'.

    We just have to bring in the std::rel_ops namespace into our program and
    define operator functions for '==' and '<' operators and the rest will be
    taken care of by the template functions in rel_ops namespace.
*/
using namespace std::rel_ops;
class Point{
    public:
        Point(double X, double Y);
        double length() const;
        friend bool operator==(const Point& p1, const Point& p2);

        // can be defined either as a member function or a free standing one
        // friend bool operator<(const Point& p1, const Point& p2);
        bool operator<(const Point& p) const {
            return (length() < p.length());
        }
    private:
        double x;
        double y;
};

Point::Point(double X, double Y):
    x(X), y(Y){}

double Point::length() const {
    return std::sqrt(x*x + y*y);
}

bool operator==(const Point& p1, const Point& p2){
    return ((p1.x == p2.x) && (p1.y == p2.y));
}

// bool operator<(const Point& p1, const Point& p2){
//     return (p1.length() < p2.length());
// }

int main()
{
    Point p1{7, 2}, p2{3, -4};
    if (p1 != p2)
        std::cout << "p1 != p2\n";
    
    if (p1 >= p2)
        std::cout << "p1 >= p2\n";
    
    return 0;
}