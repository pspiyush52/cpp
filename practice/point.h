#ifndef __POINT_H
#define __POINT_H

#include <iostream>
#include <cmath>
#include <type_traits>

class Point {
    public:
        Point();
        explicit Point(double xy);
        Point(double x, double y);
        Point(const Point& p);  // copy
        Point(Point&& src);  // move
        double distance(const Point& p) const;
        double length() const;
        double slope() const;
        double get_x() const;
        void set_x(double x);
        double get_y() const;
        void set_y(double y);
        unsigned int quadrant() const;
        Point& operator=(const Point& p);  // only implemented as a member function
        Point& operator=(double num);  // assignment from other types
        bool operator==(const Point& p) const = default;
        Point operator+(const Point& p) const;
        Point operator-(const Point& p) const;
        Point& operator+=(const Point& p);
        Point& operator-=(const Point& p);
        const double& operator[](char axis) const;  // getter for const objects
        double& operator[](char axis);  // getter and setter for non-const objects
        Point& operator++();  // prefix
        Point operator++(int);  // postfix
        Point& operator--();  // prefix
        Point operator--(int);  // postfix
        operator bool();
        /*
            If we do not mark it as explicit then the compiler will insert
            implicit conversions wherever required and we may get unexpected
            results.
            If we mark it as explicit then the conversion will work only when
            we explicitly use the conversion operator (static_cast<T>).
        */
        explicit operator double();

        template<typename T>
        requires std::is_convertible_v<T, double>
        Point operator*(T a) const;

        template<typename T>
        requires std::is_convertible_v<T, double>
        friend inline Point operator*(T a, const Point& p);

        template<typename T>
        requires std::is_convertible_v<T, double>
        Point& operator*=(T a);

        template<typename T>
        requires std::is_convertible_v<T, double>
        Point operator/(T a);

        template<typename T>
        requires std::is_convertible_v<T, double>
        Point& operator/=(T a);

        friend inline std::ostream& operator<<(std::ostream& output, const Point& p);
        friend inline std::istream& operator>>(std::istream& input, Point& p);
        static unsigned int get_point_count();
        static double line_slope(const Point& p1, const Point& p2);
        static bool collinear(const Point& p1, const Point& p2, const Point& p3);
        ~Point();
    private:
        double m_x{};
        double m_y{};
        static inline unsigned int point_count{};
};

Point::Point():
    Point{0.0, 0.0}{}

Point::Point(double xy):
    Point{xy, xy}{}

Point::Point(double x, double y):
    m_x(x), m_y(y){
        point_count++;  std::cout << "Point created at " << this << '\n';
    }

Point::Point(const Point& p):
    Point(p.m_x, p.m_y){}

Point::Point(Point&& src):
    Point(src.m_x, src.m_y){}

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

void Point::set_x(double x){
    m_x = x;
}

double Point::get_y() const{
    return m_y;
}

void Point::set_y(double y){
    m_y = y;
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

Point& Point::operator=(const Point& p){
    // checking if the object is being copied/assigned to itelf or not
    if (this != &p)
    {
        m_x = p.m_x;
        m_y = p.m_y;
    }
    return *this;
}

Point& Point::operator=(double num){
    m_x = m_y = num;
    return *this;
}

inline std::ostream& operator<<(std::ostream& output, const Point& p)
{
    output << "Point(x: " << p.m_x << ", y: " << p.m_y << ")";
    return output;
}

inline std::istream& operator>>(std::istream& input, Point& p){
    std::cout << "Enter the co-ordinates of the point,\n";
    std::cout << "Enter x and y separated by spaces: ";
    input >> p.m_x >> p.m_y;
    return input;
}

Point Point::operator+(const Point& p) const {
    return Point{m_x + p.m_x, m_y + p.m_y};
    // return Point{*this} += p;  // using another operator to do the job
}

Point Point::operator-(const Point& p) const {
    return Point{m_x - p.m_x, m_y - p.m_y};
}

Point& Point::operator+=(const Point& p)
{
    m_x += p.m_x;
    m_y += p.m_y;
    return *this;
}

Point& Point::operator-=(const Point& p)
{
    m_x -= p.m_x;
    m_y -= p.m_y;
    return *this;
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

Point::operator bool(){
    return ((m_x != 0) && (m_y != 0));
}

Point::operator double(){
    return (m_x + m_y) / 2;
}

template<typename T>
requires std::is_convertible_v<T, double>
inline Point Point::operator*(T a) const {
    return Point{m_x * a, m_y * a};
}

template<typename T>
requires std::is_convertible_v<T, double>
Point operator*(T a, const Point& p){
    return Point{p.m_x * a, p.m_y * a};
}

template<typename T>
requires std::is_convertible_v<T, double>
Point& Point::operator*=(T a){
    m_x *= a;
    m_y *= a;
    return *this;
}

template<typename T>
requires std::is_convertible_v<T, double>
Point Point::operator/(T a){
    return Point{m_x / a, m_y / a};
}

template<typename T>
requires std::is_convertible_v<T, double>
Point& Point::operator/=(T a){
    m_x /= a;
    m_y /= a;
    return *this;
}

unsigned int Point::get_point_count(){
    return point_count;
}

double Point::line_slope(const Point& p1, const Point& p2){
    return ((p2.m_y - p1.m_y) / (p2.m_x - p1.m_x));
}

bool Point::collinear(const Point& p1, const Point& p2, const Point& p3){
    return (line_slope(p1, p2) == line_slope(p1, p3));
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

Point::~Point(){
    point_count--;
    std::cout << "Point destroyed at " << this << "\n";
}

#endif // __POINT_H