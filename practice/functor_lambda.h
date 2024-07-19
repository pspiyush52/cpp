#ifndef __FUNCTOR_LAMBDA_H
#define __FUNCTOR_LAMBDA_H

#include <cstdio>
#include <ctime>
#include <concepts>

template<std::integral T>
T* populate(T* arr, size_t size, int factor = 100){
    std::srand(std::time(0));
    for (size_t i{}; i < size; i++)
        arr[i] = std::rand() % factor;
    return arr;
}

template<typename T>
using valfun = bool (*)(const T&);

template<typename T>
class InRange{
    public:
        InRange(T min, T max){
            range_min = min;
            range_max = max;
        }
        bool operator()(const T& item) const{
            return ((item >= range_min) && (item <= range_max));
        }
        
        using ret_type = bool (*)(const T&);
        /*
         * Defining this operator enables conversion of the function
         * objects of this class to a function pointer type.
         * The same mechanism exists in lambdas which enable them to be
         * passed directly even where a function pointer is required.
         */
        operator ret_type() const{
            return __internal;
        }
    private:
        static bool __internal(const int& x){
            return InRange{range_min, range_max}.operator()(x);
        }
        /*
         * Have to be declared static since the static function
         * __internal does not have any access to the member variables
         * of the class and we need the min and max values to set up an
         * object inside __internal so we can invoke the operator()
         * method on it.
         */
        static inline T range_min{};
        static inline T range_max{};
};

#endif  // __FUNCTOR_LAMBDA_H