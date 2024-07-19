#include <iostream>

class Point {
    public:
        Point();
        Point(double X, double Y);
        Point(const Point& p);
        Point(Point&& p);
        double* get_x();
        double* get_y();
        void invalidate();
        Point operator+(const Point& p) const;
        ~Point();
    private:
        double* x;
        double* y;
        friend std::ostream& operator<<(std::ostream& output, const Point& p);
};

int main(void)
{
    // using std::move forces the compiler to create a temporary Point variable
    Point p1(std::move(Point(1.4, 3.7)));
    std::cout << '\n' << p1 << '\n';
    Point p2(15.74, 3.21);
    return 0;
}

Point::Point(){
    std::cout << "Default object constructed at " << this << '\n';
    x = new double;
    y = new double;
}

Point::Point(double X, double Y):
    x(new double{X}), y(new double{Y}){
        std::cout << "Object constructed at " << this << " with x: " << X << ", y: " << Y << '\n';
    }

/*
    The copy constructor does a deep copy and allocates two new double variables
    and stores the values from Point p in them. This introduces extra overhead
    when constructing objects from temporary objects.

    If the object is temporary and will anyways be thrown away, why not use the
    double variables already allocated inside the temporary variable and make
    the new objects' pointers point to them instead of allocating two new
    double variables?
    To achieve this we make use of the move constructor. It makes the pointers
    of the new variables point to the variables already allocated on the heap
    and makes the temporary objects members variables point to nullptr.

    This way we only have to allocate memory for 2 double variables whereas if
    we use the copy constructor, memory will be allocated 4 times, 2 times for
    x and y of the temporary object and another 2 times for the x and y of the
    neew object to be created.
*/
Point::Point(const Point& p):
    x(new double{*(p.x)}), y(new double{*(p.y)}){
        std::cout << "Copy constructor called for " << p << '\n';
    }

/*
    When the move constructor is called with the temporary object, the temp
    object's x and y are already pointing to double variables allocated on the
    heap.
    The move constructor makes the x and y pointers of the new object point to
    the already allocated double variables on the heap whose addresses are
    stored in temp.x and temp.y and in doing so it saves the extra overhead of
    allocating memory for two new double variables on the heap.

    temp.x and temp.y are made to point to nullptr afterwards because temp
    will be deleted immediately and if temp.x and temp.y are still pointing
    to the same location as new.x and new.y then the destructor will release
    those memory locations and the new object will be rendered useless.
*/
Point::Point(Point&& temp):
    x(temp.x), y(temp.y){
        std::cout << "Move constructor called for " << temp << '\n';
        temp.invalidate();  // make p.x and p.y point to nullptr
    }

double* Point::get_x(){
    return x;
}
double* Point::get_y(){
    return y;
}

void Point::invalidate(){
    x = nullptr;
    y = nullptr;
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