module;

#include <cstddef>

module qsort;

void aswap(int arr[], ll i, ll j){
    int tmp = arr[i];
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