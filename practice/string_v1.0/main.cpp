#include "arr_string.h"

int main()
{
    string text{"this      is some     text"};
    string str{"A string"};
    std::cout << (text + str).collapse();
    std::cout << (text <= str) << '\n';
    long double num{234.23434};
    int x{2342323};
    std::cout << to_string(num) + " " + to_string(x) << '\n';
    std::cout << bstring(x) + "  " + bstring(x) << '\n';
    string n{"255"};
    std::cout << n.bstring() << '\n';
    return 0;
}