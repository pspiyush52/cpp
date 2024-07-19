/*
 * Any class with at least one pure virtual function is known as an abstract
 * class. Abstract classes cannot be used to create objects of their own.
 * Any class deriving from an abstract class has to override all of the pure
 * virtual methods of the abstract class otherwise it will become abstract
 * itself.
 */
/*
 * Makes sense to make area and perimeter methods pure virtual since we cannot
 * calculate the area and perimeter of the polygon without further
 * information.
 */
#include <iostream>
#include <cmath>
#include <typeinfo>
class polygon{
    public:
        polygon(unsigned int sides) : num_of_sides(sides){}
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
    
    protected:
        unsigned int num_of_sides;
};

class triangle : public polygon{
    public:
        triangle(double A, double B, double C) : polygon(3), a(A), b(B), c(C){}
        double area() const {
            double S = (a + b + c) / 2;
            return (std::sqrt(S*(S - a) * (S - b) * (S - c)));
        }
        double perimeter() const { return (a + b + c); }
        unsigned int get_sides() const { return num_of_sides; }
    
    protected:
        double a;
        double b;
        double c;
};

class rectangle : public polygon{
    public:
        rectangle(double length, double breadth) : polygon(4), l(length), b(breadth){}
        double area() const { return (l * b); }
        double perimeter() const { return (2*(l + b)); }

    protected:
        double l;
        double b;
};

class square : public rectangle{
    public:
        square(double Side) : rectangle(Side, Side){}
};

void print_areas(polygon* polygons[], size_t size);

int main(void)
{
    square s{4.16};
    std::cout << "Area of square: " << s.area() << '\n';
    std::cout << "Perimeter: " << s.perimeter() << '\n';
    rectangle r1{14.1, 5.48};
    rectangle r2{3.8, 6};
    triangle t1{3, 3, 2};
    triangle t2{3.45, 12.5, 14.1};
    std::cout << "Num of sides in t1: " << t1.get_sides() << '\n';

    polygon* polygons[] = {&r1, &r2, &t1, &s, &t2};
    print_areas(polygons, 5);

    return 0;
}

void print_areas(polygon* polygons[], size_t size){
    const std::type_info& tt = typeid(triangle);
    const std::type_info& tr = typeid(rectangle);
    const std::type_info& ts = typeid(square);
    const std::type_info* tp;
    std::cout << "\nAreas of all polygons:\n";
    for (size_t i{}; i < size; i++)
    {
        tp = &(typeid(*polygons[i]));
        std::cout << "  ";
        if (*tp == tt)
            std::cout << "Area of triangle: ";
        else if (*tp == tr)
            std::cout << "Area of rectangle: ";
        else if (*tp == ts)
            std::cout << "Area of square: ";
        std::cout << polygons[i]->area() << '\n';
    }
}