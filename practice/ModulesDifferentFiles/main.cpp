#include <iostream>

import qsort;

int main(void)
{
    int nums[] = {67, 18, 98, 43, 94, 73, 16, 27, 64, 91, 33, 56};
    size_t size = std::size(nums);
    std::cout << "Array before sorting: ";
    print_arr(nums, size);
    qsort(nums, size);
    std::cout << "\nArray after sorting: ";
    print_arr(nums, size);
    return 0;
}