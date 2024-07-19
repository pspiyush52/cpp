#include <iostream>
#include "points.h"

// Setting up a templated function pointer alias
template<typename T>
using comparator_fun =  bool (*)(const T&, const T&);

template<typename T>
bool l_max(const T& a, const T& b){
    return (a.length() > b.length());
}

template<typename T>
// T get_max(T* arr, T (*comparator)(const T&, const T&), size_t size)
T get_max(T* arr, comparator_fun<T> comparator, size_t size){
    T& cur_max = arr[0];
    for (size_t i{}; i < size; i++)
        if (comparator(arr[i], cur_max))
            cur_max = arr[i];
    
    return cur_max;
}

int main(void)
{
    Point p[5]{
        {1.2, 3.4}, {15.1, 31}, {3.72, 54.1}, {0.768, 1.047}, {0.322, 1.28}
    };

    std::cout << "Max point: "  << get_max(p, l_max, 5) << '\n';
    return 0;
}