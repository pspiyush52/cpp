#include <iostream>
#include "arr.h"
#include "defs.h"

class i_arr : public arr::Array<int> {
    public:
        using arr::Array<int>::Array;
        i_arr(const arr::Array<int>& src) : Array(src){}
        i_arr(Array<int>&& src) : Array(std::move(src)){}
        size_t sum(){
            size_t total{}, i{};
            for (; i < arr_size; i++)
                total += arr[i];
            return total;
        }
};

int main(void)
{
    i_arr arr{5, 21, 4, 8, 9, 6, 3, 1, 23, 18, 45, 21, 36, 94, 84, 32, 10, 21}; sep;
    std::cout << arr << '\n'; sep;
    i_arr sliced = std::move(*arr(4, 10)); sep;
    std::cout << "sliced from 4 to 9: " << sliced << '\n';
    std::cout << "Total of sliced: " << sliced.sum() << '\n'; sep;

    return 0;
}