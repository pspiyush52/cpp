#include <iostream>

void swap(int* arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void merge(int* arr, int* tmp, int start, int mid, int end){
    int i = start, j = mid + 1, k = 0;
    while((i <= mid) && (j <= end))
        tmp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    
    if (i > mid)
        while (j <= end)
            tmp[k++] = arr[j++];
    else if (j > end)
        while (i <= mid)
            tmp[k++] = arr[i++];
    for (i = start, j = 0; i <= end;)
        arr[i++] = tmp[j++];
}

void msort(int* arr, int* tmp, int start, int end){
    if (start >= end)
        return;
    int mid = (start + end) / 2;
    msort(arr, tmp, start, mid);
    msort(arr, tmp, mid + 1, end);
    merge(arr, tmp, start, mid, end);
}

void mergesort(int* arr, size_t size){
    int* tmp = new int[size];
    msort(arr, tmp, 0, size - 1);
    delete[] tmp;
}

int main(void)
{
    int arr[] = {32, 15, 24, -15, 2, 61, 94, 84, 21, 63, 48, 31, 18}, i{}, n{std::size(arr)};
    mergesort(arr, n);
    std::cout << '[';
    for (; i < n - 1; i++)
        std::cout << arr[i] << ", ";
    std::cout << arr[i] << "]\n";
    return 0;
}