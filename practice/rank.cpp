#include <iostream>
#include "qsort.h"
#include "range.h"
#include "carr.h"
typedef array<int> container;

int rank(container& arr, int key){
    int less_count{};
    for (auto& n : arr)
        if (n < key)
            ++less_count;
    return (less_count + 1);
}

int main(void)
{
    container arr = {10, 12, 42, 9, 17, 24, 11};
    std::cout << "The array: " << arr << '\n';
    std::cout << "\nRank of 12 in the array: " << rank(arr, 12) << '\n';
    std::cout << "\nSorted array: " << qsort(arr) << '\n';
    return 0;
}