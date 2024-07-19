#include <iostream>
#include <cmath>

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
template<typename T> bool operator<=(const T& lhs, const T& rhs);
template<typename T> bool operator>(const T& lhs, const T& rhs);
template<typename T> bool operator>=(const T& lhs, const T& rhs);
template<typename T> bool operator!=(const T& lhs, const T& rhs);
int main()
{
    Point p1{7, 2}, p2{3, -4};
    if (p1 != p2)
        std::cout << "p1 > p2\n";
    return 0;
}

Point::Point(double X, double Y):
    x(X), y(Y){}

double Point::length() const {
    return std::sqrt(x*x + y*y);
}

bool operator==(const Point& p1, const Point& p2){
    return ((p1.x == p2.x) && (p1.y == p2.y));
}

/*
    The rel_ops namespace contains templates like below which implement the
    rest of the logical operators using '<' and '=='.
*/
template<typename T>
bool operator<=(const T& lhs, const T& rhs){
    std::cout << "template <= called...\n";
    return !(rhs < lhs);
}

template<typename T>
bool operator>(const T& lhs, const T& rhs){
    std::cout << "template > called...\n";
    return (rhs < lhs);
}

template<typename T>
bool operator>=(const T& lhs, const T& rhs){
    std::cout << "template >= called...\n";
    return !(lhs < rhs);
}

template<typename T>
bool operator!=(const T& lhs, const T& rhs){
    std::cout << "template != called...\n";
    return !(lhs == rhs);
}