#include "square.h"
#include "circle.h"
#include <cmath>

class A {
    public:
        A(const char* str) : data(str){}
        const char* area() const {return data;}
    private:
        const char* data;
};

int main(void)
{
    Square s{std::sqrt(pi)};
    Circle c{1};

    std::cout << std::boolalpha;
    std::cout << "s: " << s << '\n';
    std::cout << "c: " << c << '\n';
    std::cout << "c < s : " << (c < s) << '\n';
    std::cout << "c == s : " << (c == s) << '\n';
    std::cout << "3 < c : " << (3 < c) << '\n';
    std::cout << "3 < c : " << (3 < c) << '\n';
    std::cout << "c > 2.4884 : " << (c >= 2.4884) << "\n\n";

    Square s2{1.2};
    
    std::cout << "s2: " << s2 << '\n';
    std::cout << "s < s2 : " << (s < s2) << '\n';
    std::cout << "s2 == 1.44 : " << (s2 == 1.44) << '\n';
    std::cout << "c == " << pi << " : " << (c == pi) << '\n';

    A obj{"random_string"};
    // (obj < s);  // compiler error due to constraints enforced by retval

    return 0;
}