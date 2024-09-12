#include "..\deque\deque.h"
#include <vector>
#include <list>
#include <deque>
#include "print.h"
#include "carr.h"

template<typename T>
using Container = std::deque<T>;

int main(void)
{
    array<int> nums{34, 23, 65, 834, 23, 43, 265, 8, 23};
    for (auto& e : enumerate(nums))
        print(e.count(), ":", e.value());
    return 0;
}
