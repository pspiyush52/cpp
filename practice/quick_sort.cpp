#include <iostream>
#include "stream_insert.h"

using ll = long long;
template<typename T>
void aswap(T arr[], ll i, ll j){
    T tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void partition(int arr[], ll start, ll end, ll& mid){
    int pivot = arr[start];
    ll i{start + 1}, j{end};
    while(1){
        while ((i <= j) && (arr[i] <= pivot))
            ++i;
        while ((i <= j) && (arr[j] > pivot))
            --j;
        if (i >= j)
            break;
        aswap(arr, i++, j--);
    }
    mid = i - 1;
    aswap(arr, start, mid);
}

int* _qsort(int arr[], ll start, ll end, ll& mid){
    if (start >= end)
        return arr;
    partition(arr, start, end, mid);
    _qsort(arr, start, mid - 1, mid);
    _qsort(arr, mid + 1, end, mid);
    return arr;
}

int* qsort(int arr[], size_t size){
    ll mid{};
    return _qsort(arr, 0, static_cast<ll>(size - 1), mid);
}

int main(void)
{
    // int arr[] = {98, 48, 64, 37, 12, 1, 94, 84, 11, 37, 4, 72, INT_MIN};
    int arr[] = {98, 48, 64, 37, 12, 1, 94, 84, 11, 37, 4, 72};
    // using namespace delim_arr;
    // std::cout << "Unsorted array : " << arr << '\n';
    // std::cout << "Array after sorting : " << qsort(arr, std::size(arr) - 2) << '\n';
    qsort(arr, std::size(arr));
    for (int n : arr)
        std::cout << n << ' ';
    std::cout << '\n';
    return 0;
}