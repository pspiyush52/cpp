#include <iostream>
#include <memory>
#include "point.h"
using std::unique_ptr, std::make_unique, std::move;
using point_uptr = unique_ptr<Point>;
/*
    When passing the unique_ptr as function parameters, we cannot use call by
    value since it involves making copies of the parameter and unique_ptr
    cannot be copied.
    
    If we want to use unique_ptr as a function parameter then we have to
    either use call by reference or use std::move() to move the ownership of
    the memory to the parameter.
    
    The second approach will render the pointer passed as the argument useless
    since it will be reset to null and the memory which the unique_ptr was
    pointing to will be released after the function call is over and the
    unique_ptr parameter goes out of scope.
*/

// Call by reference
void show_point_ref(unique_ptr<Point>& p){
    std::cout << "<" << (p->get_x()) << ", " << (*p)['y'] << ">\n";
}
// Call by value using std::move
void show_point(unique_ptr<Point> p){
    std::cout << "<" << (p->get_x()) << ", " << (*p)['y'] << ">\n";
}

/*
    If we want to return a unique_ptr from a function we have to keep the same
    things in mind. We should not return a unique_ptr by value although it is
    allowed in some compilers and it does some optimizations in the background
    to make this possible.
    The compiler actually makes it so that the function returns something like
    a reference to the newly created unique_ptr. This can be proved by looking
    at the addresses of the UP(unique_ptr) inside the function and in main.
    In the usual return by value the two addresses will be different because a
    copy is returned, but in this case the two addresses will be the same
    because something like a reference is being returned.
*/

// Function returning unique_ptr to Point by value
point_uptr get_point(double x, double y){
    point_uptr ptr = make_unique<Point>(x, y);
    // std::cout << "&ptr (get_point) : " << &ptr << '\n';  // this address will
    // be the same as in main

    return ptr;
}

// Function returning unique_ptr to unique_ptr to Point
unique_ptr<point_uptr> get_point_ptr(double x, double y){
    // creating a unique pointer to a unique pointer to Point
    // initializing with a pointer to Point
    unique_ptr<point_uptr> ptr = make_unique<point_uptr>(make_unique<Point>(x, y));
    return ptr;
}

// Function returning a reference to unique_ptr to point
point_uptr& get_point_ref(double x, double y){
    // This does not work as expected
    unique_ptr<point_uptr> ptr = make_unique<point_uptr>(make_unique<Point>(x, y));
    return *ptr;
}

int main(void)
{
    point_uptr p1 = make_unique<Point>(17.4, 12);
    show_point_ref(p1);

    point_uptr p2 = make_unique<Point>(-11.23, 16.78);
    show_point(move(p2));

    // After pasing p2 using std::move, p2 is reset to null and the memory is
    // released when the function show_point is done executing and the
    // unique_ptr parameter goes out of scope.
    if (!p2)
        std::cout << "p2 is now null.\n";

    point_uptr p3 = get_point(59.4, -13.24);
    std::cout << "p3 : " << *p3 << '\n';
    std::cout << "&ptr (main) : " << &p3 << '\n';

    // The unique_ptr to unique_ptr to Point will be deleted automatically
    // when it goes out of scope and so will the Point object by chain calls
    unique_ptr<point_uptr> p4 = get_point_ptr(40.12, -17.84);
    std::cout << "p4 : " << **p4 << '\n';
    
    point_uptr& p5 = get_point_ref(-12.45, 9.67);
    std::cout << "p5 : " << *p5 << '\n';
    
    // If the pointer is used directly and not stored in any variable then it
    // is used and deleted right after.
    get_point(3, 1)->length();

    std::cout << "Done.\n";

    return 0;
}