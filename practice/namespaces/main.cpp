#include "line.h"
#include <ctime>

int main(void)
{
    // Geom::Point p1{1.2, 10.64};
    // Geom::Point p2{5.49, 11.34};
    // Geom::Line line1{p1, p2};
    Geom::Line line1{{1.2, 10.64}, {5.49, 11.34}};
    std::cout << "line1 : " << line1 << '\n';
    std::cout << "Slope of line1 : " << line1.slope() << '\n';
    
    // this brings Point from the Geom namespace to the current namespace
    using Geom::Point;

    // this brings everything from the Geom namespace into the current namespace
    // using namespace Geom;

    Point p1{56.45, 12.48};  // will result in error without using Geom::Point

    std::cout << "Length of p1 : " << p1.length() << '\n';

    return 0;
}