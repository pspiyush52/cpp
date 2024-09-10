#ifndef __FUNCTORS_H
#define __FUNCTORS_H

#include <utility>

template<typename T>
const T& min(const T& x, const T& y){
    return (x < y) ? x : y;
}

template<typename T>
const T& max(const T& x, const T& y){
    return (x > y) ? x : y;
}

struct less {
    template<typename T, typename U>
    bool operator()(T&& x, U&& y) {
        return x < y;
    }
};

struct greater {
    template<typename T>
    bool operator()(T&& x, T&& y) {
        return x > y;
    }
};

struct less_eq{
    template<typename T>
    bool operator()(const T& lhs, const T& rhs){
        return (lhs <= rhs);
    }
};

struct greater_eq{
    template<typename T>
    bool operator()(const T& lhs, const T& rhs){
        return (lhs >= rhs);
    }
};

struct odds{
    template<typename T>
    bool operator()(const T& x) const { return (x % 2); }
};

struct evens{
    template<typename T>
    bool operator()(const T& x) const { return (!(x % 2)); }
};

struct identity {
    template<typename T>
    T&& operator()(T&& item){
        return std::forward<T&&>(item);
    }
    // template<typename T>
    // T& operator()(T& item){
    //     return std::forward<T&>(item);
    // }
    template<typename T>
    const T& operator()(T& item){
        return std::forward<const T&>(item);
    }
};

template<typename T>
class DivisibleBy{
    public:
        DivisibleBy(const T& num) : __num(num){}
        bool operator()(const T& num) const { return (!(num % __num)); }
    private:
        T __num;
};

template<typename T, T __num>
struct Divisible{
    bool operator()(const T& num) const {return ((num % __num) == 0); }
};

template<typename T>
void swap(T& x, T& y){
    T tmp = x;
    x = y;
    y = tmp;
}

template<typename T>
void swap(T&& x, T&& y){
    T tmp{std::move(x)};
    x = std::move(y);
    y = std::move(tmp);
}

template<typename T>
void swap(T* arr, int i, int j){
    auto tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

#endif  // __FUNCTORS_H