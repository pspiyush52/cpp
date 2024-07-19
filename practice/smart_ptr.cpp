#include <iostream>
#include "smart_ptr.h"
#include "point.h"


int main(void)
{
    sptr<Point> ptr(Point{1.2, 4.3});
    std::cout << "ptr->length() : " << ptr->length() << '\n';
    std::cout << "ptr->quadrant() : " << ptr->quadrant() << '\n';
    sptr<int> int_ptr(34);
    std::cout << "*int_ptr : " << *int_ptr << '\n';
    sptr<int> iptr{std::move(int_ptr)};
    if (!int_ptr.get())
        std::cout << "int_ptr is empty.\n";
    
    return 0;
}
