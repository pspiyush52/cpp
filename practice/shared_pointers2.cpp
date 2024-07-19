#include <memory>
#include "point.h"
#define make_u std::make_unique<Point>

using point_sptr = std::shared_ptr<Point>;

int main(void)
{
    point_sptr p1 = make_u(-11.48, 32.63);
    point_sptr p2 = p1;
    std::cout << "\np1 : " << *p1 << '\n';
    std::cout << "\nUsing p2 to modify the object...\n";
    p2->set_x(40.32);
    p2->set_y(17.8);
    std::cout << "p2 : " << *p2 << '\n';
    std::cout << "The changes are reflected in p1 as well...\n";
    std::cout << "p1 : " << *p1 << "\n\n";
    std::cout << "p2.length() : " << p2->length() << '\n';
    std::cout << "p1.length() : " << p1->length() << "\n\n";
    return 0;
}