#include <iostream>
#include "range.h"
#include "print.h"

const int SIZE{20};
int count{};
void maxMin(int* arr, int size);

int main(void)
{
    int arr[SIZE];
    rand_range(0, 1000) >> arr;
    std::cout << "Array of size " << SIZE << " : " << printer(arr) << '\n';
    maxMin(arr, std::size(arr));
    std::cout << "Number of comparisons: " << count << '\n';
    return 0;
}

void maxMin(int* arr, int size){
    int* minarr = new int[size / 2 + 1], *minit = minarr, *minptr = minarr;
    int* maxarr = new int[size / 2 + 1], *maxit = maxarr, *maxptr = maxarr;
    int max, min, i{1};
    for (; i < size; i += 2){
        ++count;
        if (arr[i - 1] < arr[i]){
            *minptr++ = arr[i - 1];
            *maxptr++ = arr[i];
        } else {
            *minptr++ = arr[i];
            *maxptr++ = arr[i - 1];
        }
    }
    if (i == size){
        *maxptr++ = arr[size - 1];
        *minptr++ = arr[size - 1];
    }
    for (min = *minit++; minit != minptr; ++minit){
        ++count;
        if (min > *minit)
            min = *minit;
    }
    for (max = *maxit++; maxit != maxptr; ++maxit){
        ++count;
        if (max < *maxit)
            max = *maxit;
    }
    delete[] minarr;
    delete[] maxarr;
    std::cout << "Min: " << min << '\n';
    std::cout << "Max: " << max << '\n';
}
