#include "utils.h"
#include "point.h"
/*
    Weak pointers are special in the sense that they don't own the data that
    they point to and if a weak pointer goes out of scope, the memory they
    point to will not be released.
    Also we cannot use the * or -> operators with weak pointers to read or
    modify data.

    To access data pointed to by the weak pointer we have to turn it into a
    shared pointer using the lock() method.

    The expired() method can be used to check if the object which was pointed
    to by the weak pointer has been destroyed or not.
*/

int main(void)
{
    s_ptr<Point> p1 = make_s<Point>({1.216, -9.14}); sep;
    s_ptr<Point> p2 = p1;
    
    std::weak_ptr<Point> weak_p1 = p2;

    std::cout << "*p2 : " << *p2 << ", use_count : " << p2.use_count() << '\n';
    sep;

    // std::cout << "*weak_p1 : " << *weak_p1 << '\n'; // compiler error

    // turning the WP to a SP using the lock() method
    s_ptr<Point> shared_from_weak = weak_p1.lock();

    std::cout << "*shared_from_weak : " << *shared_from_weak << '\n';
    std::cout << "shared_from_weak.use_count() : " << shared_from_weak.use_count() << '\n';
    sep;

    s_ptr<Point> p3 {make_s<Point>({-34.64, -15.4})}; sep;

    std::weak_ptr<Point> weak_p2 {p3};
    std::weak_ptr<Point> weak_p3 {p3};
    std::weak_ptr<Point> weak_p4 {weak_p2};

    // Reference count for weak pointers does not increase
    std::cout << "weak_p4.use_count() : " << weak_p4.use_count() << '\n';
    std::cout << "weak_p2.use_count() : " << weak_p2.use_count() << '\n';
    sep;

    std::cout << "p3.use_count() : " << p3.use_count() << '\n';
    std::cout << "Locking weak_p2 to shared_from_weak2...\n";
    s_ptr<Point> shared_from_weak2 {weak_p2.lock()};
    std::cout << "shared_from_weak2.use_count() : " << shared_from_weak2.use_count() << '\n';

    // use_count increases since there is one SP already pointing to the
    // memory that weak_p2 was pointing to
    std::cout << "p3.use_count() : " << p3.use_count() << '\n';
    sep;

    return 0;
}