#include <iostream>
#include "shape.h"
#include "utils.h"

int main(void)
{
    Shape shape{"shape1"};
    Oval oval{1.2, 5.8, "oval1"};
    Circle circle{4.8, "circle1"};
    sep;

    cout << "Calling methods through references : Static Binding.\n";
    sep;
    Shape& sptr1{shape};

    // We would like to call Shape::draw()
    sptr1.draw(); newline;

    Shape& sptr2{oval};
    // We would like to call Oval::draw()
    sptr2.draw(); newline;

    Shape& sptr3{circle};
    // We would like to call Circle::draw()
    sptr3.draw(); sep;

    /*
     * In this case, the compiler just looks at the reference type to decide
     * which draw method to call. We have used Shape& above so the compiler
     * calls the Shape::draw() method whenever a pointer is used to call the
     * draw() method.
     * This again, is the result of static binding.
     */

    return 0;
}