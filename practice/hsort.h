#ifndef __HSORT_H
#define __HSORT_H

#include <stddef.h>
#include "defs.h"
#include "functors.h"

namespace hlp{
    template<typename Container>
    void swap(Container& arr, int i, int j){
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    template<typename Container>
    void heapify(Container& arr, int size, int root){
        int l{2*root + 1}, r{l + 1}, largest{root};
        if (l < size && arr[l] > arr[largest])
            largest = l;
        if (r < size && arr[r] > arr[largest])
            largest = r;
        if (root != largest){
            swap(arr, root, largest);
            heapify(arr, size, largest);
        }
    }
}
template<typename Container>
Container& make_heap(Container& c){
    int size = std::size(c), i{size / 2 - 1};
    for (; i; --i)
        hlp::heapify(c, size, i);
    hlp::heapify(c, size, 0);
    return c;
}
// template<typename arr_tp, size_t size>
// arr_tp* hsort(arr_tp (&arr)[size]){
//     if (size < 2)
//         return arr;
//     make_heap(arr);
//     for (int arr_size = size; arr_size; --arr_size){
//         swap(arr[0], arr[arr_size - 1]);
//         hlp::heapify(arr, arr_size - 1, 0);
//     }
//     return arr;
// }
template<typename Container>
Container& hsort(Container& c){
    int size = std::size(c);
    if (size < 2)
        return c;
    make_heap(c);
    for (; size; --size){
        swap(c[0], c[size - 1]);
        hlp::heapify(c, size - 1, 0);
    }
    return c;
}

#endif  // __HSORT_H