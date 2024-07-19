#ifndef __FUNCTORS_WITH_PARAMS_H
#define __FUNCTORS_WITH_PARAMS_H

#include <iostream>
#include <concepts>
#include <ctime>
#include "lists.h"

template<typename T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
void rand_populate(List<T>& src, int num){
    std::srand(std::time(0));
    for (int i{}; i < num; i++)
        src.append(std::rand() % 100);
}

template<typename T, typename Comparator>
void range_extract(const List<T>& src, List<T>& target, Comparator&& comp_fun){
    T cur = src[0];
    for (size_t i{}; i < src.size(); i++)
        if (comp_fun(cur = src[i]))
            target.append(cur);
}

template<typename T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
size_t sum(const List<T>& l){
    size_t i{}, total{};
    for (; i < l.size(); i++)
        total += l[i];
    return total;
}
/*
 * Functors have the added advantage over callback functions that since
 * they can have member variables, they can store state. For example, in
 * the InRange class below, function objects of this class will already
 * contain the information about the range in which the values should
 * occur.
 * 
 * If we were to try and accomplish this using callback functions
 * then we would have to pass this extra information as additional
 * parameters to the higher order function.
 */
template<typename T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
bool check_range(const T& item, const T& min, const T& max){
    return (item >= min && item <= max);
}

template<typename T, typename Comparator>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T range_sum_fun(const List<T>& l, Comparator comp_fun, const T& min, const T& max){
    T total{};
    for (size_t i{}; i < l.size(); i++)
        if (check_range(l[i], min, max))
            total += l[i];
    
    return total;
}

/*
 * Using a functor we do not have to pass the minimum and maximum of the
 * range as function parameters as they are already stored in the functor
 * when it is created.
 */
template<typename T>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
class InRange{
    public:
        InRange(const T& min, const T& max) : range_min(min), range_max(max){}
        bool operator()(const T& item){
            return ((item >= range_min) && (item <= range_max));
        }
    private:
        T range_min;
        T range_max;
};

template<typename T, typename Comparator>
requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
T range_sum(const List<T>& l, Comparator&& comp_fun){
    T total{};
    for (size_t i{}; i < l.size(); i++)
        if (comp_fun(l[i]))
            total += l[i];
    
    return total;
}

#endif  // __FUNCTORS_WITH_PARAMS_H