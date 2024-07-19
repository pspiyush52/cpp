#include <iostream>
#include "frand.h"

typedef arr::List<int> container;
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
int partition(container& arr, int low, int high) {
    int pivot = arr[high], i = low;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot)
            swap(arr[i++], arr[j]);
    swap(arr[i], arr[high]);
    return i;
}
container& quicksort(container& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
    return arr;
}
container& qsort(container& arr){ return quicksort(arr, 0, arr.size() - 1); }

int main()
{
    container arr = rng().integers(0, 100, 10);
    std::cout << "Original array: " << arr << '\n';
    std::cout << "After sorting:   " << qsort(arr) << '\n';
    return 0;
}
