#include <iostream>
#include <cmath>

class Point {
    public:
        Point();
        explicit Point(double xy);
        Point(double x, double y);
        double distance(const Point& p) const;
        double length() const;
        double slope() const;
        double get_x() const;
        double get_y() const;
        unsigned int quadrant() const;
        bool operator==(const Point& p) const;
        Point operator+(const Point& p) const;
        Point operator-(const Point& p) const;
        void operator+=(const Point& p);
        void operator-=(const Point& p);
        const double& operator[](char axis) const;
        double& operator[](char axis);
        Point& operator++();
        Point operator++(int);
        Point& operator--();
        Point operator--(int);
        friend std::ostream& operator<<(std::ostream& output, const Point& p);
        /*
            Static function belongs to the class itself and not to any object.
            It does not have access to the this pointer.

            Static member functions do not have access to non-static member
            variables but they can access static member variables even if they
            are private;
        */
        static unsigned int get_point_count();
        /*
            We can access member variables from a static function if we pass
            the object as a parameter to the function like,

            static void show(Point& p){
                std::cout << "<" << p.m_x << ", " << p.m_y << ">\n";
            }

            We are able to access the private non-static member variables as
            the function is defined inside the class itself.
            If we define the function outside the class then we will not have
            access to the private non-static member variables directly.
        */
       static void show(const Point& p);
    private:
        double m_x;
        double m_y;
        static inline unsigned int point_count{};
};

/*
    Here we do not have direct access to the private non-static member
    variables of the class as the static function is defined outside the class
    body.
*/
void Point::show(const Point& p){
    std::cout << "<" << p['x'] << ", " << p['y'] << ">\n";
}

int main(void)
{
    const Point origin;
    Point p1(4.5, 13.78);
    std::cout << "p1 : " << p1 << '\n';
    std::cout << "Distance of p1 from origin : " << p1.distance(origin) << '\n';
    std::cout << "Length of line from origin to p1 : " << p1.length() << '\n';
    const Point center{3, -7};
    p1 += center;
    std::cout << "New length of p1 : " << p1.length() << '\n';
    std::cout << "Distance of center from origin : " << center.length() << '\n';
    std::cout << "center is in quadrant " << center.quadrant() << '\n';

    Point p2(2.3, 9.65);
    std::cout << "\np2 : " << p2 << '\n';
    p2++;
    std::cout << "p2 : " << p2 << '\n';
    Point::show(p1);

    std::cout << "\nTotal number of points : " << Point::get_point_count() << '\n';
    return 0;
}

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