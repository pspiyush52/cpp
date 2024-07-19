#include "utils.h"
#include "point.h"
#include "arr.h"

int main(void)
{
    u_ptr<int> uptr = make_u<int>(5);
    std::cout << "*uptr : " << *uptr;

    s_ptr<int> sptr = std::move(uptr);
    std::cout << "\n*sptr : " << *sptr;
    if (!uptr)
        std::cout << "\nuptr is now null.\n";
    sep;
    
    u_ptr<Point> p1 = make_u<Point>(Point{4, 5}); sep;
    std::cout << "p1 : " << *p1 << '\n';
    sep;
    
    s_ptr<Point> p2 = std::move(p1);
    s_ptr<Point> p3 = p2;
    s_ptr<Point> p4{p2};
    s_ptr<Point> p5{p3};
    
    std::cout << "sptr.use_count() : " << sptr.use_count() << '\n';
    std::cout << "p2.use_count() : " << p2.use_count() << '\n';
    std::cout << "p3.use_count() : " << p3.use_count() << '\n';
    std::cout << "p4.use_count() : " << p4.use_count() << '\n';
    std::cout << "p5.use_count() : " << p5.use_count() << '\n';
    sep;

    s_ptr<Point> p6 = make_s<Point>(Point{3.15, -12.49}); sep;
    // u_ptr<Point> p7{p6};  // not allowed

    return 0;
}