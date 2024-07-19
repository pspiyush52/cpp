#include <iostream>
#include "stream_insert.h"

int* bubble_sort(int arr[], size_t size){
    int tmp{};
    for (size_t i{}; i < (size - 1); ++i){
        for (size_t j = 1; j < size; ++j){
            if (arr[j - 1] > arr[j]){
                tmp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    return arr;
}

int main(void)
{
    int arr[] = {67, 48, 95, 12, 67, 19, 43, 77, 6, 34, 11, INT_MIN};
    using namespace delim_arr;
    std::cout << "Array before sorting : " << arr << '\n';
    std::cout << "Array after sorting : " << bubble_sort(arr, std::size(arr) - 1) << '\n';
    return 0;
}