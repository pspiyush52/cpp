#include <iostream>
#include <string>
#include <memory>
#include "point.h"
#define separator std::cout << LINE << '\n'

const std::string LINE(110, '-');
/*
    Shared Pointers(SP) are another tye of smart pointers in C++. Unlike UP we
    can have multiple SP's pointing to the same object but the ownership of
    the object belongs to only one SP.

    Any number of SP's can be made to point to the object and the object can
    be accessed via any of them.

    The object is destroyed from memory only when the last remaining SP owning
    the object is destroyed(goes out of scope) or, the last remaining SP
    owning the object is assigned another pointer via assignment(=) operator
    or reset().

    The reset() method when called without any argument decrements the
    reference count and sets the SP to nullptr.

    The use_count() method returns the number of shared pointers pointing
    towards the same object in memory.
*/
void fun(std::shared_ptr<Point> ptr){
    std::cout << "Point" << '<' << ptr->get_x() << ", " << ptr->get_y() << ">\n";
    std::cout << "num(fun) : " << ptr.use_count() << '\n';
    /*
        After the function terminates the shared pointer ptr goes out of scope
        and is destroyed but the object remains intact as the owner SP, i.e.,
        p1 is still in scope in main().
        The object will not be destroyed until p1 remains in scope.
    */
}

int main(void)
{
    std::shared_ptr<Point> p1 = std::make_shared<Point>(-2.31, 21.6); separator;
    std::cout << "p1 : " << *p1 << '\n';
    std::cout << "num(main) before fun() call : " << p1.use_count() << '\n';
    fun(p1);
    std::cout << "num(main) after fun() call : " << p1.use_count() << '\n';
    separator;

    /*
        p2 = p1 makes the SP p2 point to the same object as p1 and the
        use_count() method will now return 2 since there are two SP's pointing
        towards the same object.
    */
    std::shared_ptr<Point> p2 = p1;
    std::cout << "p2 : " << *p2 << '\n';

    // Addresses of both shared_ptr's will be different
    std::cout << "&p1 : " << &p1 << ", &p2 : " << &p2 << '\n';
    // Adress to which they are pointing to will be the same
    std::cout << "p1.get() : " << p1.get() << ", p2.get() : " << p2.get() << '\n';
    separator;

    {
        std::shared_ptr<Point> p3 = p2;
        std::cout << "p3.get() : " << p3.get() << '\n';
        std::cout << "p3 : " << *p3 << '\n';
        separator;
        // Only p3 will be destroyed when it goes out of scope, not the object
        // it is pointing to because p3 is not the last remaining SP pointing
        // to the object. p1 and p2 are still left and they point towards the
        // object.
    }

    std::shared_ptr<Point> p4{};
    {
        std::shared_ptr<Point> p5 = std::make_shared<Point>(4.2, 63.15); separator;
        p4 = p5;
    }
    std::cout << "p4 : " << *p4 << '\n';
    separator;

    using point_sptr = std::shared_ptr<Point>;
    point_sptr p6{p2};  // reference count goes up each time a new SP is made
    point_sptr p7{p1};  // to point to he same object in memory
    point_sptr p8{p6};

    auto show_use_count = [&](){
        std::cout << "p6.use_count() : " << p6.use_count() << '\n';
        std::cout << "p7.use_count() : " << p7.use_count() << '\n';
        std::cout << "p8.use_count() : " << p8.use_count() << '\n';    
    };
    show_use_count();
    std::cout << "After resetting p7...\n";
    p7.reset();
    show_use_count();
    separator;
    std::cout << "After assigning a new Point object to p7...\n";
    p7 = std::make_shared<Point>(12);
    separator;
    show_use_count();
    separator;

    return 0;
}