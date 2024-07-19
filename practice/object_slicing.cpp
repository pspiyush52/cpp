/*
 * Since derived classes contain all the attributes of the base class plus
 * some additional attributes they define for themselves, their objects are
 * mostly larger in size as compared to base class objects.
 * 
 * When a derived class object is assigned to a base class object, the derived
 * class object's extra attributes are sliced off(not considered) to generate
 * the base class object. This process is termed object slicing.
 * 
 * In other words the extra attributes which come from the derived class are
 * sliced off when the derived class object is assigned to a base class
 * object.
 * 
 * Objects of classes which use dynamic binding for runtime polymorphism have
 * a larger size than the objects of the same classes if dynamic binding isn't
 * used since each class has to keep track of the vtable to resolve the
 * virtual function calls.
 */
#include "shape.h" // contains Shape class without virtual function

int main(void)
{
    Circle c{4, "circle"};
    Shape s{c};  // No compiler error due to object slicing. Only relevant
    // data is picked up to initialize s.

    std::cout << sizeof(Shape) << '\n';
    std::cout << sizeof(Oval) << '\n';
    std::cout << sizeof(Circle) << '\n';

    return 0;
}