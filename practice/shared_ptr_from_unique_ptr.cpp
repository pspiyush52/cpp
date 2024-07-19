#include <memory>
#include "point.h"
#define make_u std::make_unique<Point>
#define make_s std::make_shared<Point>
#define sep std::cout << "----------------------------------------------------------------------------------------------------------------\n"

using point_uptr = std::unique_ptr<Point>;
using point_sptr = std::shared_ptr<Point>;
unsigned int counter{};
template<typename T> void show_point(T& ptr){
    std::cout << 'p' << ++counter << " : " << *ptr << '\n';
}

int main(void)
{
    point_uptr p1 = make_u(4, 5); sep;
    show_point(p1);
    sep;

    point_uptr p2{new Point(-2.5, -14.68)}; sep;
    show_point(p2);

    // point_sptr p3 = p1; // not allowed

    /*
        If we want a shared pointer to point to the object which the unique
        pointer is pointing to we have to move the ownership of that object
        from the unique pointer to the shared pointer using std::move().

        The SP p3 now points to the object which p1 was pointing to and p1
        will be reset to nullptr.
    */
    point_sptr p3 = std::move(p1); // moving the ownership of the object to p3
    show_point(p3);
    sep;

    if (!p1)
        std::cout << "p1 is now null.\n";

    point_sptr p4;
    p4 = std::move(p2);
    show_point(p4);
    sep;

    /*
        Initializing a unique pointer with a shared pointer does not work even
        with std::move.
        It does not make sense since a shared pointer can have many other
        shared pointers pointing to the same object in memory so assigning it
        to the unique pointer will result in a unique pointer pointing to
        memory pointed to by many other shared pointers which does not satisfy
        the condition of the unique pointer being the only owner of the object
        in memory.
    */
    // point_uptr p5 = p4;  // does not work
    // point_uptr p5 = std::move(p4)  // does not work either

    return 0;
}