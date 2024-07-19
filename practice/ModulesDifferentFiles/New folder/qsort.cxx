module;

#include <cstddef>
#include <iostream>

export module qsort;

using ll = long long;

void aswap(int arr[], ll i, ll j);
void partition(int arr[], ll start, ll end, ll& mid);
int* _qsort(int arr[], ll start, ll end, ll& mid);
export int* qsort(int arr[], size_t size);

// Function template declaration an definition cannot be separated even
// in the case of modules.
export template<typename T>
void print_arr(T arr[], size_t size){
    std::cout << '[';
    size_t i{};
    for (; i < (size - 1); ++i)
        std::cout << arr[i] << ", ";
    std::cout << arr[i] << ']';
}