#ifndef __ISORT_H
#define __ISORT_H

#include "functors.h"
#include <stddef.h>

template<typename Container, typename Comparator, typename Projection>
int bsearch(Container& arr, Comparator& compare, Projection& proj, int left, int right, typename Container::value_type key){
    if (left >= right)
        return right;
    int mid{(left + right) / 2};
    if (key == proj(arr[mid]))
        return mid;
    else if (compare(key, proj(arr[mid])))
        return bsearch(arr, compare, proj, left, mid - 1, key);
    else
        return bsearch(arr, compare, proj, mid + 1, right, key);
}

template<typename Container, typename Comparator = less, typename Projection = identity>
Container& isort_b(Container& arr, Comparator compare = {}, Projection proj = {}){
    size_t size = arr.size(), i = 1, j = 0;
    for (; i < arr.size(); ++i){
        int pos = bsearch(arr, compare, proj, 0, i - 1, arr[i]);
        std::cout << '-' << pos << "-\n";
        for (j = i; j > pos; --j)
            swap(arr[j], arr[j - 1]);
    }
    return arr;
}

template<typename Container, typename Comparator = less, typename Projection = identity>
Container& isort(Container& arr, Comparator compare = {}, Projection proj = {}){
    size_t size = arr.size(), i = 1, j = 0;
    for (; i < arr.size(); ++i)
        for (j = i; (j > 0) && compare(proj(arr[j]), proj(arr[j - 1])); --j)
            swap(arr[j], arr[j - 1]);
    return arr;
}

template<typename Container, typename Comparator = less, typename Projection = identity>
Container& isort(Container&& arr, Comparator compare = {}, Projection proj = {}){
    return isort(arr, compare, proj);
}

template<typename arr_tp, size_t size, typename Comparator = less, typename Projection = identity>
arr_tp* isort(arr_tp (&arr)[size], Comparator compare = {}, Projection proj = {}){
    size_t i{1}, j{};
    for (; i < size; ++i)
        for (j = i; (j > 0) && compare(proj(arr[j]), proj(arr[j - 1])); --j)
            swap(arr, j, j - 1);
    return arr;
}

#endif  // __ISORT_H