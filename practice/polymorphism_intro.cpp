/*
 * The word Polymorphism literally means having different forms. A basic
 * example is function overloading. Multiple functions with the same name can
 * exist simultaneously in a program performing seemingly similar tasks.
 * This is an example of compile-time polymorphism or early binding.
 * Another example of early binding is operator overloading.
 * 
 * Polymorphism in classes occurs when we have multiple classes related to
 * each other by inheritance.
 * 
 * A pointer or a reference of the base class can manage derived class objects
 * so at any point of time it can take the form of any of the multiple classes
 * which derive from it and hence it has multiple forms.
 * As a consequence of this all the base class objects can be stored in one
 * collection of base class pointers.
 */
#include "quad.h"
#define nl '\n'

int main(void)
{
    Rectangle r = Square{1.172};
    std::cout << "r: " << r << nl;
    std::cout << "r.area : " << r.area() << nl;

    Square s1{1.172};
    Rectangle r1{2.4, 13.1};
    Rectangle r2{30.41, 12.18};
    Square s2{3.34};
    Square s3{12.4};
    Square s4{33.7};
    Rectangle r3{0.74, 3.303};

    // A base class reference can be initialized with a derived class object.
    Rectangle& r_ref{s1};
    std::cout << "r_ref: " << r_ref << nl;
    std::cout << "r_ref.area() : " << r_ref.area() << nl;

    // Storing pointers to all objects in one array of type pointer to base.
    Rectangle* quadrilaterals[] = {&s1, &r1, &r2, &s2, &s3, &s4, &r3};

    std::cout << "=====================================================================\n";
    for (Rectangle* r : quadrilaterals)
    {
        std::cout << " Current quadrilateral: " << *r << ", ";
        std::cout << "Area: " << r->area();
        std::cout << "\n=====================================================================\n";
    }

    return 0;
}