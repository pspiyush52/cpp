#include <array>
#include "stream_insert.h"

int main(void)
{
    std::array<unsigned int, 15> nums{314, 15, 84, 74, 32, 10, 19, 67, 11};
    using namespace __array__;
    std::cout << nums << '\n';
    return 0;
}