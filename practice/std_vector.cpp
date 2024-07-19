#include <iostream>
#include <vector>
#include "stream_insert.h"

int main(void)
{
    std::vector<int> nums{12, 1, 3, 48, 19, 30, 4, 37, 66};
    using namespace __vec__;
    std::cout << nums << '\n';
    return 0;
}