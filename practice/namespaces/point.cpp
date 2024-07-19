#include "point.h"

namespace Geom{
    Point::Point():
    Point{0.0, 0.0}{}

    Point::Point(double xy):
        Point{xy, xy}{}

    Point::Point(double x, double y):
        m_x(x), m_y(y){point_count++;}

    double Point::distance (const Point& p) const
    {
        return std::sqrt(std::pow(m_x - p.m_x, 2) + std::pow(m_y - p.m_y, 2));
    }

    double Point::length() const{
        return std::sqrt(m_x * m_x + m_y * m_y);
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
        output << "Point <x : " << p.m_x << ", y : " << p.m_y << ">";
        return output;
    }

    bool Point::operator==(const Point& p) const
    {
        return ((m_x == p.m_x) && (m_y == p.m_y));
    }

    Point Point::operator+(const Point& p) const
    {
        Point new_point;
        new_point.m_x = m_x + p.m_x;
        new_point.m_y = m_y + p.m_y;
        return new_point;
    }

    Point Point::operator-(const Point& p) const
    {
        Point new_point;
        new_point.m_x = m_x - p.m_x;
        new_point.m_y = m_y - p.m_y;
        return new_point;
    }

    void Point::operator+=(const Point& p)
    {
        m_x += p.m_x;
        m_y += p.m_y;
    }

    void Point::operator-=(const Point& p)
    {
        m_x -= p.m_x;
        m_y -= p.m_y;
    }

    Point& Point::operator++(){
        m_x++; m_y++;
        return *this;
    }

    Point Point::operator++(int){
        Point tmp {*this};
        m_x++; m_y++;
        return tmp;
    }

    Point& Point::operator--(){
        m_x--; m_y--;
        return *this;
    }

    Point Point::operator--(int){
        Point tmp {*this};
        m_x--; m_y--;
        return tmp;
    }

    unsigned int Point::get_point_count(){
        return point_count;
    }

    const double& Point::operator[](char axis) const
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

    double& Point::operator[](char axis)
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
}