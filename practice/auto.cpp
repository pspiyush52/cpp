#include <iostream>

int main(void)
{
    int x{4};
    auto& ref_x = x;
    ref_x++;
    std::cout << "x : " << &x << std::endl;
    std::cout << "ref_x : " << &ref_x << std::endl;
    // reference can be further used to initialize another reference
    int& ref_x2 = ref_x;
    ref_x2++;

    std::cout << "ref_x : " << &ref_x2 << std::endl;
    std::cout << "x : " << x << std::endl;

    return 0;
}