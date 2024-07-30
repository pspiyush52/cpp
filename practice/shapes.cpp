#include "lists.h"
#include "print.h"
#include "shapes.h"
#include <memory>

template<typename T>
using uptr = std::unique_ptr<T>;

template<typename T, typename... Args>
uptr<T> makeShape(const Args& ...args) {
    return std::make_unique<T>(args...);
}

int main(void)
{
    arr::List<uptr<Shape>> Shapes;
    Shapes
        .append(makeShape<Circle>(1.732))
        .append(makeShape<Rectangle>(12, 14))
        .append(makeShape<Square>(9.8))
        .append(makeShape<Triangle>(3, 4, 5));
    
    for (auto& shape : Shapes) {
        print();
        print("For", *shape);
        Circle* cp = dynamic_cast<Circle*>(shape.get());
        if (cp)
            print("  Diameter:", cp->diameter());
        print("  Area:", shape->area());
        print("  Perimeter:", shape->perimeter());
    }

    return 0;
}
