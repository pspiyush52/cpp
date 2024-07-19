#ifndef __QSORT_H
#define __QSORT_H

#include "functors.h"
#include <iterator>

using ll = long long;

template<typename Container, typename Comparator, typename Projection>
ll __partition__(Container& con, ll start, ll end, Comparator comp, Projection proj){
	auto pivot{proj(con[start])};
    ll i{end}, j{end};
    for (; i > start; --i)
        if (comp(pivot, proj(con[i])))
            swap(con[i], con[j--]);
    swap(con[start], con[j]);
    return j;
}
template<typename Container, typename Comparator, typename Projection>
void __qsort__(Container& con, ll start, ll end, Comparator comp, Projection proj)
{
	if (start < end){
        ll mid = __partition__(con, start, end, comp, proj);
        __qsort__(con, start, mid - 1, comp, proj);
        __qsort__(con, mid + 1, end, comp, proj);
    }
}
template<typename Collection, typename Comparator = less, typename Projection = identity>
Collection& qsort(Collection& col, Comparator compare = {}, Projection proj = {})
{
	__qsort__(col, 0, col.size() - 1, compare, proj);
	return col;
}

template<typename T, typename Comparator, typename Projection>
ll __partition_array__(T* arr, ll start, ll end, Comparator& comp, Projection& proj){
    auto pivot{proj(arr[start])};
    ll i{end}, j{end};
    for (; i > start; --i)
        if (comp(pivot, proj(arr[i])))
            swap(arr, i, j--);
    swap(arr, start, j);
    return j;
}
template<typename T, typename Comparator, typename Projection>
void _qsort(T* arr, int start, int end, Comparator& comp, Projection& proj){
    if (start < end){
        ll mid = __partition_array__(arr, start, end, comp, proj);
        _qsort(arr, start, mid - 1, comp, proj);
        _qsort(arr, mid + 1, end, comp, proj);
    }
}
template<typename arr_tp, size_t size, typename Comparator = less, typename Projection = identity>
arr_tp* qsort(arr_tp (&arr)[size], Comparator comp = {}, Projection proj = {}){
    _qsort(arr, 0, size - 1, comp, proj);
    return arr;
}

template<typename T>
T* qsort(T* arr, size_t size){
	if (size < 2)
		return arr;
	__qsort__array__(arr, 0, size - 1);
	return arr;
}

#endif  // __QSORT_H