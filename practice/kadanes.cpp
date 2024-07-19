#include <iostream>
#include "carr.h"
#include "range.h"

template<typename container>
int max_contiguous_sum(container con){
    size_t size{con.size()};
    int max{INT_MIN}, total{}, begin{}, tmp{}, end{};
    for (size_t i{}; i < size; ++i){
        total += con[i];
        if (total < 0)
            total = 0;
        if (max < total)
            max = total;
    }
    return max;
}

int main(void)
{
    array<int> arr(10);
    rand_range(-10, 10) >> arr;
    std::cout << "arr: " << arr << '\n';
    std::cout << max_contiguous_sum(arr);
    return 0;
}