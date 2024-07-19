#ifndef __FRAND_H
#define __FRAND_H

#include <ctime>
#include "functors.h"
#include "lists.h"

class rng{
    typedef arr::List<int> list;
    public:
        rng() = default;
        list integers(int from, int to, size_t size);
        arr::List<double> random(size_t size);
        double rand();
        int randint(int to);
        int randint(int from, int to);
        
        template<typename arr_tp, size_t size>
        arr_tp* shuffle(arr_tp (&arr)[size]);

        template<typename container_tp>
        container_tp& shuffle(container_tp& arr);
        
        template<typename container_tp, typename value_tp>
        container_tp randoms(value_tp from, value_tp to, size_t size);
        
        template<typename container_tp>
        container_tp rnums(int from, int to, size_t size);

    private:
        int __seed{static_cast<int>(std::time(0))};
        inline static int __mul{165874657};
        inline static double A{0.79127988146021};
};

rng::list rng::integers(int from, int to, size_t size){
    list l(size);
    for (size_t i{}; i < size; ++i)
        l.append(from + this->rand() * (to - from));
    return l;
}
arr::List<double> rng::random(size_t size){
    arr::List<double> l(size);
    double p{};
    for (size_t i{}; i < size; ++i){
        p = this->__seed * A;
        p -= static_cast<int>(p);
        l.append(p);
        this->__seed = static_cast<int>(p * this->__mul);
    }
    return l;
}
double rng::rand(){
    double p{this->__seed * A};
    p -= static_cast<int>(p);
    this->__seed = static_cast<int>(p * this->__mul);
    return p;
}
int rng::randint(int to){
    return (this->rand() * to);
}
int rng::randint(int from, int to){
    return (from + this->rand() * (to - from));
}
template<typename arr_tp, size_t size>
arr_tp* rng::shuffle(arr_tp (&arr)[size]){
    for (size_t i{}; i < size; ++i)
        swap(arr, i, this->randint(0, size - 1));
    return arr;
}
template<typename container_tp>
container_tp& rng::shuffle(container_tp& arr){
    int rnum{};
    for (size_t i{}, size{arr.size()}; i < size; ++i){
        rnum = this->randint(0, size - 1);
        swap(arr[i], arr[rnum]);
    }
    return arr;
}
template<typename container_tp, typename value_tp>
container_tp rng::randoms(value_tp from, value_tp to, size_t size){
    container_tp c;
    value_tp delta{to - from};
    while (size--)
        c.push_back(static_cast<value_tp>(from + this->rand() * delta));
    return c;
}
template<typename container_tp>
container_tp rng::rnums(int from, int to, size_t size){
    container_tp cont(size);
    int delta{to - from};
    for (auto& item : cont)
        item = from + this->rand() * delta;
    return cont;
}

#endif  // __FRAND_H
