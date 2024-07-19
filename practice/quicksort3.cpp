#include "print.h"
#include "functors.h"

template<typename T, typename Comparator>
int partition(T* arr, int start, int end, Comparator& comp){
    T pivot{arr[start]};
    int i{end}, j{end};
    for (; i > start; --i)
        if (comp(pivot, arr[i]))
            swap(arr, i, j--);
    swap(arr, start, j);
    return j;
}
template<typename T, typename Comparator>
void _qsort(T* arr, int start, int end, Comparator& comp){
    if (start < end){
        int mid = partition(arr, start, end, comp);
        _qsort(arr, start, mid - 1, comp);
        _qsort(arr, mid + 1, end, comp);
    }
}
template<typename arr_tp, size_t size, typename Comparator = less>
arr_tp* qsort(arr_tp (&arr)[size], Comparator comp = {}){
    _qsort(arr, 0, size - 1, comp);
    return arr;
}

int main(void)
{
    int arr[] = {44, 12, 39, 48, 67, 1, 21};
    std::cout << printer(arr) << '\n';
    qsort(arr, greater());
    std::cout << printer(arr) << '\n';
    return 0;
}
