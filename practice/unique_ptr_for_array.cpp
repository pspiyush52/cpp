#include <iostream>
#include <memory>
#include "point.h"

int main(void)
{
    /*
    std::unique_ptr<int[]> arr {new int[10]};

    // Declaring UP for use with array
    std::unique_ptr<Point[]> parr {new Point[5]{
        Point(0),
        Point(1),
        Point(2),
        Point(3),
        Point(4)
    }};
    std::cout << parr[2] << '\n';

    // use with auto
    auto parr2 = std::unique_ptr<Point[]>{new Point[4]{
        Point(0),
        Point(1),
        Point(2),
        Point(3)
    }};
    for (int i{}; i < 4; i++)
        std::cout << parr2[i] << '\n';
    */
    // Declaration using make_unique but initialization is not possible in
    // this case
    std::unique_ptr<Point[]> parr3 = std::make_unique<Point[]>(4);
    // with auto
    // auto parr3 = std::make_unique<Point[]>(4);
    parr3[2]['x'] = 4.79;
    for (int i{}; i < 4; i++)
        std::cout << parr3[i] << '\n';

    return 0;
}