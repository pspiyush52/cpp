#include <iostream>
#include "print.h"
#include "range.h"
#include "functors.h"

int findMin(int* arr, int size){
    if (size < 2)
        return arr[0];
    int left_min{findMin(arr, size - 1)};
    return min(left_min, arr[size - 1]);
}
int findMin_i(int* arr, int size){
    if (size < 1)
        return INT_MIN;
    int min{INT_MAX};
    while (size--)
        if (arr[size] < min)
            min = arr[size];
    return min;
}

int main(void)
{
    int arr[10];
    rand_range(0, 100) >> arr;
    std::cout << "The array: " << printer(arr) << '\n';
    std::cout << "Minimum found recursively: " << findMin(arr, std::size(arr)) << '\n';
    std::cout << "Minimum found iteratively: " << findMin_i(arr, std::size(arr)) << '\n';
    return 0;
}