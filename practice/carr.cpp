#include "carr.h"
#include "range.h"
#include "views.h"

int main(void)
{
    array<int> nums = {65, 15, 48, 3, 64, 73, 9};
    std::cout << nums << '\n';
    array<int> randnums(20);
    rand_range(-100, 100) >> randnums;
    std::cout << (randnums | [](int& n){ return (n < 0); }) << '\n';
    return 0;
}