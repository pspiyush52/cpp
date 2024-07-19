#ifndef __FUNCTORS_STL_H
#define __FUNCTORS_STL_H

#include "arr_strings.h"
#include "lists.h"

template<typename T, typename Comparator>
T get_max(const arr::Array<T*>& arr, Comparator comp_fun){
    T cur_max = *(arr[0]);
    for (size_t i{}; i < arr.size(); i++)
        if (comp_fun(*(arr[i]), cur_max))
            cur_max = *(arr[i]);
    
    return cur_max;
}

template<typename T, typename Comparator>
T get_max(const List<T*>& arr, Comparator comp_fun){
    T cur_max = *(arr[0]);
    for (size_t i{}; i < arr.size(); i++)
        if (comp_fun(*(arr[i]), cur_max))
            cur_max = *(arr[i]);
    
    return cur_max;
}

template<typename T, typename Comparator>
T get_max(const arr::Array<T>& arr, Comparator comp_fun){
    T cur_max = arr[0];
    for (size_t i{}; i < arr.size(); i++)
        if (comp_fun(arr[i], cur_max))
            cur_max = arr[i];
    
    return cur_max;
}

#endif  //  __FUNCTORS_STL_H