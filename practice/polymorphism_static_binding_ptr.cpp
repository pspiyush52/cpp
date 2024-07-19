#include <iostream>
#include "shape.h"
#include "utils.h"

int main(void)
{
    Shape shape1{"shape1"};
    Oval oval1{1.2, 5.8, "oval1"};
    Circle circle1{4.8, "circle1"};
    sep;
    // auto& cout = std::cout;

    cout << "Calling methods through pointers : Static Binding.\n";
    sep;
    Shape* sptr = &shape1;

    // We would like to call Shape::draw()
    sptr->draw(); newline;

    sptr = &oval1;
    // We would like to call Oval::draw()
    sptr->draw(); newline;

    sptr = &circle1;
    // We would like to call Circle::draw()
    sptr->draw(); sep;

    /*
     * Contrary to what we wanted to accomplish, the above calls to draw()
     * will only call the draw() method defined in the base class Shape.
     * This is known as static binding in C++, the compiler just looks at the
     * pointer type to decide which draw method to call.
     * 
     * Binding: Binding refers to the process of converting identifiers (such
     * as variable and performance names) into addresses. Binding is done for
     * each variable and function. For functions, it that matching the call
     * with the right function definition by the compiler. It takes place
     * either at compile time or at runtime.
     * 
     * Static/Early Binding: By default, C++ matches a function call with the
     * correct function definition at compile time. This is called static
     * binding.
     * 
     * Dynamic/Late Binding: We can specify that the compiler match a function
     * call with the correct function definition at runtime; this is called
     * dynamic binding.
     * 
     * We have used Shape* above so the compiler calls the Shape::draw()
     * method whenever a pointer is used to call the draw() method.
     */

    return 0;
}