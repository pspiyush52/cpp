#include <iostream>
#include <memory>
#include "point.h"
/*
    Smart pointers are a way to deal with the hassle of releasing heap memory
    which we have allocated after use.

    A unique pointer is a smart pointer which owns and manages another object
    through a pointer and disposes of that object (releases the memory used
    by that object) when the unique pointer goes out of scope or the unique
    pointer object is assigned another pointer via = operator or reset().

    Also at any given moment there can be only one unique pointer managing the
    memory.
*/
int main(void)
{
    // Point* ptr = new Point{4.5, 1.2};
    // std::unique_ptr<Point> p_ptr {ptr};  // initializing with another pointer
    // std::unique_ptr<Point> p_ptr {new Point{4.5, 1.2}};  // using new
    // std::unique_ptr<Point> p_ptr {nullptr};  // initializing with null

    // Available only on C++14 and above
    std::unique_ptr<Point> p_ptr = std::make_unique<Point>(4.5, 1.2);  // using make_unique function
    // make_unique<T> creates an object of type T and wraps it in a unique_ptr
    // by calling the constructor of type T and passing the arguments of
    // make_unique to the constructor.

    std::cout << "*p_ptr : " << *p_ptr << '\n';  // * and -> operators can be used on unique_ptr's
    std::cout << "Length : " << p_ptr->length() << '\n';
    
    // The object it was previously pointing is automatically released from
    // memory before making it point to a new object.
    p_ptr = std::make_unique<Point>(13.4, 65.14);
    std::cout << *p_ptr << '\n';

    // Copies and assignments are not allowed
    // Not allowed since at any point only one unique_ptr will point to a
    // memory location.
    // std::unique_ptr<Point> other_ptr = p_ptr;

    // Also not allowed for the same reason as above
    // std::unique_ptr<Point> other_ptr {p_ptr} // copy constructor deleted error

    // Moving ownership
    std::unique_ptr<Point> other_ptr = std::move(p_ptr); // now other_ptr
    // will manage the memory which was managed by p_ptr and p_ptr will now
    // point to nullptr

    auto check_ptr = [] <typename T> (std::unique_ptr<T>& ptr, const char* ptr_name){
        if (ptr)
            std::cout << ptr_name << " points to valid memory.\n";
        else
            std::cout << ptr_name << " is null.\n";
    };

    check_ptr(p_ptr, "p_ptr");

    std::cout << "*other_ptr : " << *other_ptr << '\n';

    // reset() method when called without any argument releases memory and
    // sets the unique_ptr to nullptr
    std::cout << "Calling reset() method on other_ptr... ";
    other_ptr.reset();
    check_ptr(other_ptr, "other_ptr");

    return 0;
}