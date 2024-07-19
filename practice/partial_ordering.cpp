#include <iostream>
#include <cmath>
/*
 * Partial ordering is useful when we have contraints on the range of values
 * on which we can perform comparisons. For example let's assume that for the
 * Point class, only the points with X co-ordinates b/w -100 and 100 and Y co-
 * ordinated b/w -100 and 100 are valid then, the points which lie beyond this
 * range cannot be compared and we can simulate this using partial_ordering.
 */
class Point {
    public:
        Point() = default;
        Point(double X, double Y) : x(X), y(Y){}
        explicit Point(double x_y) : Point(x_y, x_y){}
        double length() const { return std::sqrt(x*x + y*y); }
        bool in_range() const { return ((std::abs(x) <= 100) && (std::abs(y) <= 100)); }
        std::partial_ordering operator<=>(const Point& p) const;
        std::partial_ordering operator<=>(double p) const;
        bool operator==(const Point& p) const;
        bool operator==(double p) const;
        friend std::ostream& operator<<(std::ostream& output, const Point& p);

    private:
        double x{};
        double y{};  
};

int main(void)
{
    Point p1{80.49, -99.34}, p2{32.18, 98.45};
    std::cout << std::boolalpha;
    std::cout << "p1: " << p1 << ", p2: " << p2 << '\n';
    std::cout << "p1 > p2 : " << (p1 > p2) << '\n';
    std::cout << "p1 > 120 : " << (p1 > 120) << '\n';
    std::cout << "110 < p1 : " << (110 < p1) << '\n';

    Point p3{110};
    std::cout << "p3: " << p3 << '\n';

    // Since p3 is out of range every comparison will return false
    std::cout << "p2 < p3 : " << (p2 < p3) << '\n';
    std::cout << "p2 <= p3 : " << (p2 <= p3) << '\n';
    std::cout << "p2 > p3 : " << (p2 > p3) << '\n';
    std::cout << "p2 >= p3 : " << (p2 >= p3) << '\n';
    std::cout << "p2 == p3 : " << (p2 == p3) << '\n';
    std::cout << "p2 != p3 : " << (p2 != p3) << '\n';
    std::cout << "p3 == 110 : " << (p2 == 110) << '\n';
    std::cout << "p3 == 110 : " << (110 == p2) << '\n';
    
    return 0;
}

std::partial_ordering Point::operator<=>(const Point& p) const{
    using po = std::partial_ordering;
    if (this->in_range() && p.in_range())
    {
        if (this->length() < p.length())
            return po::less;
        else if (this->length() > p.length())
            return po::greater;
        else
            return po::equivalent;
    }
    return std::partial_ordering::unordered;
}

std::partial_ordering Point::operator<=>(double p) const {
    using po = std::partial_ordering;
    if (this->in_range() && (p <= std::sqrt(20000)))
    {
        if (this->length() < p)
            return po::less;
        else if (this->length() > p)
            return po::greater;
        else
            return po::equivalent;
    }
    return std::partial_ordering::unordered;
}

bool Point::operator==(const Point& p) const {
    return (this->length() == p.length());
}

bool Point::operator==(double p) const {
    return (this->length() == p);
}

std::ostream& operator<<(std::ostream& output, const Point& p){
    output << "Point[x: " << p.x << ", y: " << p.y << ", length: "
    << p.length() << ']';
    return output;
}