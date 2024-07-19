#include <iostream>
#include <iomanip>
#include <cmath>

class Point {
    public:
        Point() = default;  // tells the compiler to make a default constructor
        Point(double x, double y);
        double distance(Point p) const;
        double slope() const;
        double get_x() const;
        double get_y() const;
        unsigned int quadrant() const;
        bool operator==(Point& p) const;
        Point operator+(Point& p) const;
        Point operator-(Point& p) const;
        void operator+=(Point& p);
        void operator-=(Point& p);
        double operator[](char axis) const;
    private:
        double m_x;
        double m_y;
        friend std::ostream& operator<<(std::ostream& output, const Point& p);
};

int main(void)
{
    Point p1(4, 7);
    Point p2(1, 3);
    std::cout << "p1 : " << p1 << std::endl;
    std::cout << "Quadrant of p1 : " << p1.quadrant() << std::endl;
    std::cout << "p2 : " << p2 << std::endl;
    std::cout << "p1 == p2 : " << std::boolalpha << (p1 == p2) << std::endl;
    std::cout << "p1 + p2 : " << p1 + p2 << std::endl;
    std::cout << "p2 - p1 : " << p2 - p1 << std::endl;
    std::cout << "Quadrant of p2 - p1 : " << (p2 - p1).quadrant() << std::endl;
    std::cout << "slope of p1 : " << p1.slope() << std::endl;
    std::cout << "slope of p2 : " << p2.slope() << std::endl;
    std::cout << "Distance of p1 from p2 : " << p1.distance(p2) << std::endl;
    Point p3;
    std::cout << "p3: " << p3 << '\n';
    p1 += p2;
    std::cout << "\np1 after p1 += p2 : " << p1 << std::endl;
    p2 -= p1;
    std::cout << "p2 after p2 -= p1 : " << p2 << std::endl;
    std::cout << "\np1[\'x\'] : " << p1['x'] << std::endl;
    std::cout << "p2[\'Y\'] : " << p2['Y'] << std::endl;

    const Point p4(0, 11);
    std::cout << "p4 : " << p4 << std::endl;
    std::cout << "p4[\'x\'] : " << p4['x'] << std::endl;
    std::cout << "Distance from p2 : " << p4.distance(p2) << std::endl;
    std::cout << "p4 == p1 : " << (p4 == p1) << std::endl;
    std::cout << "Distance from (p4 - p1) : " << p4.distance(p4 - p1) << std::endl;
    return 0;
}

Point::Point(double x, double y)
{
    m_x = x;
    m_y = y;
}

double Point::distance (Point p) const
{
    return std::sqrt(std::pow(m_x - p.m_x, 2) + std::pow(m_y - p.m_y, 2));
}

double Point::slope() const
{
    return (m_y / m_x);
}

double Point::get_x() const{
    return m_x;
}

double Point::get_y() const{
    return m_y;
}

unsigned int Point::quadrant() const
{
    if (m_x > 0 && m_y > 0)
        return 1;
    else if (m_x < 0 && m_y > 0)
        return 2;
    else if (m_x < 0 && m_y < 0)
        return 3;
    else if (m_x > 0 && m_y < 0)
        return 4;
    else
        return 0;
}

std::ostream& operator<<(std::ostream& output, const Point& p)
{
    output << "Point [x : " << p.m_x << ", y : " << p.m_y << "]";
    return output;
}

bool Point::operator==(Point& p) const
{
    return ((m_x == p.m_x) && (m_y == p.m_y));
}

Point Point::operator+(Point& p) const
{
    Point new_point;
    new_point.m_x = m_x + p.m_x;
    new_point.m_y = m_y + p.m_y;
    return new_point;
}

Point Point::operator-(Point& p) const
{
    Point new_point;
    new_point.m_x = m_x - p.m_x;
    new_point.m_y = m_y - p.m_y;
    return new_point;
}

void Point::operator+=(Point& p)
{
    m_x += p.m_x;
    m_y += p.m_y;
}

void Point::operator-=(Point& p)
{
    m_x -= p.m_x;
    m_y -= p.m_y;
}

double Point::operator[](char axis) const
{
    switch (axis)
    {
        case 'X':
        case 'x':
            return m_x;
        case 'Y':
        case 'y':
            return m_y;
        default:
            std::cerr << "ERROR: Invalid axis : \'" << axis << "\'\n";
            exit(1);
    }
}