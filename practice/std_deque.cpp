#include <iostream>
#include <deque>
#include "stream_insert.h"

int main(void)
{
    std::deque<int> nums_d{22, 15, 67, 49, 3, 18, 5, 94};
    using namespace __deque__;
    std::cout << nums_d << '\n';
    return 0;
}