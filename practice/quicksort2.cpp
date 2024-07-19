#include "carr.h"
#include "range.h"

typedef array<int> container;
void swap(container& arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
int partition(container& arr, int start, int end){
    int pivot{arr[start]}, i{start + 1}, j{start};
    for (; i <= end; ++i)
        if (arr[i] <= pivot)
            swap(arr, i, ++j);
    swap(arr, start, j);
    return j;
}
container& _qsort(container& arr, int start, int end){
    if (start < end){
        int mid = partition(arr, start, end);
        _qsort(arr, start, mid - 1);
        _qsort(arr, mid + 1, end);
    }
    return arr;
}
container& qsort(container& arr){ return _qsort(arr, 0, std::size(arr) - 1); }

int main(void)
{
    container arr(10);
    rand_range(0, 100) >> arr;
    std::cout << "Original array: " << arr << '\n';
    std::cout << "After sorting:  " << qsort(arr) << '\n';
    return 0;
}