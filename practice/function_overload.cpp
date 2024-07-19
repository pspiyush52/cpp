#include <iostream>

int max(int& a, int& b);
int max(const int& a, const int& b);

int main(void)
{
    int x{4};
    int y{2};
    std::cout << "For max(x, y) : ";
    max(x, y); // max(int&, int&) will be called

    const int a{45};
    const int b{23};
    std::cout << "For max(a, b) : ";
    max(a, b); // max(const int&, const int&) will be called

    int& ref_x{x};
    int& ref_y{y};
    std::cout << "For max(ref_x, ref_y) : ";
    max(ref_x, ref_y); // max(int&, int&) will be called

    const int& cref_x{x};
    const int& cref_y{y};
    std::cout << "For max(cref_x, cref_y) : ";
    max(cref_x, cref_y); // max(const int&, const int&) will be called

    const int& cref_a{a};
    const int& cref_b{b};
    std::cout << "For max(cref_a, cref_b) : ";
    max(cref_a, cref_b); // max(const int&, const int&) will be called

    return 0;
}

int max(int& a, int& b)
{
    std::cout << "max(int&, int&) called\n";
    return (a > b) ? a : b;
}

int max(const int& a, const int& b)
{
    std::cout << "max(const int&, const int&) called\n";
    return (a > b) ? a : b;
}