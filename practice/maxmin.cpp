#include <iostream>
#include "range.h"
#include "print.h"

void maxMin(int* arr, int start, int end, int& min, int& max){
    if (start == end)
        min = max = arr[start];
    else if (end - start == 2){
        if (arr[start] < arr[end]){
            min = arr[start];
            max = arr[end];
        } else {
            min = arr[end];
            max = arr[start];
        }
    } else {
        int _minl, _maxl, _minr, _maxr, mid{(start + end) / 2};
        maxMin(arr, start, mid, _minl, _maxl);
        maxMin(arr, mid + 1, end, _minr, _maxr);
        if (_minl < _minr)
            min = _minl;
        else
            min = _minr;
        if (_maxl > _maxr)
            max = _maxl;
        else
            max = _maxr;
    }
}

int main(void)
{
    int arr[20];
    rand_range(0, 10000) >> arr;
    int min, max;
    maxMin(arr, 0, std::size(arr) - 1, min, max);
    std::cout << printer(arr) << '\n';
    std::cout << "Max: " << max << '\n';
    std::cout << "Min: " << min << '\n';
    return 0;
}