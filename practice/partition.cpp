#include "carr.h"
#include "functors.h"

array<int>& partition(array<int>& arr);
array<int>& partition_r(array<int>& arr);
int partition(int* arr, int start, int end);

int main(void)
{
    array<int> arr{45, 84, 97, 64, 415, 34, 14, 48};
    array<int> arr_cpy{arr};
    std::cout << "Array before partition: " << arr << '\n';
    std::cout << "Partitioned array:\n";
    std::cout << "First element as pivot: " << partition(arr) << '\n';
    std::cout << "Last element as pivot:  " << partition_r(arr_cpy) << '\n';
    return 0;
}

// Pivot position = 0, start from the end
array<int>& partition(array<int>& arr){
    int low{}, high = arr.size() - 1, pivot = arr[low], k = high;
    for (int i = high; i > low; i--)
        if (arr[i] > pivot)
            swap(arr, i, k--);
    swap(arr, low, k);
    return arr;
}
// Pivot position = end, start from the start
array<int>& partition_r(array<int>& arr){
    int low{}, high = arr.size() - 1, pivot = arr[high], j = low, i = low;
    for (; i < high; ++i)
        if (arr[i] <= pivot)
            swap(arr, i, j++);
    swap(arr, high, j);
    return arr;
}
// Pivot position = 0, start from the start
int partition(int* arr, int start, int end){
    int pivot{arr[start]}, i{start + 1}, j{start};
    for (; i <= end; ++i)
        if (arr[i] <= pivot)
            swap(arr, i, ++j);
    swap(arr, start, j);
    return j;
}