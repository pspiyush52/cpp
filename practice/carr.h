#ifndef __CARR_H
#define __CARR_H

#include <iostream>
#include <cmath>
#include <initializer_list>
#include <string.h>
#include <type_traits>
#ifdef CARR_BCHECK
#include "exceptions.h"
#endif

template<typename T>
class array{
    public:
        typedef T value_type;
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef std::size_t size_type;
        array() = delete;
        array(size_t size) : __arr(new T[size]), __size(size){}
        array(std::initializer_list<T> args){
            this->__size = args.size();
            this->__arr = new T[this->__size];
            size_t i{};
            for (const T* iter = args.begin(); iter != args.end(); ++iter, ++i)
                this->__arr[i] = *iter;
        }
        array(T from, T to){
            if (from <= to){
                this->__size = to - from + 1;
                this->__arr = new T[this->__size];
                T* iter = this->begin();
                for (; from <= to; ++from, ++iter)
                    *iter = from;
            }
        }
        array(T from, T to, T step){
            if (from <= to){
                this->__size = std::floor(1.0 * (to - from) / step) + 1;
                this->__arr = new T[this->__size];
                T* iter = this->begin();
                T* end = this->end();
                for (; iter != end; ++iter, from += step)
                    *iter = from;
            }
        }
        array(const char* str){
            static_assert(std::is_same_v<T, char>);
            this->__size = strlen(str);
            this->__arr = new char[this->__size];
            memcpy(this->__arr, str, this->__size);
        }
        array(const array& src){
            this->__size = src.__size;
            this->__arr = new T[this->__size];
            memcpy(this->__arr, src.__arr, src.__size * sizeof(T));
        }
        array(array&& src){
            this->__arr = src.__arr;
            this->__size = src.__size;
            src.__arr = nullptr;
            src.__size = 0;
        }
        void operator=(const array& rhs) = delete;
        void operator=(array&& rhs){
            delete[] this->__arr;
            this->__arr = rhs.__arr;
            this->__size = rhs.__size;
            rhs.__arr = nullptr;
            rhs.__size = 0;
        }

        T* begin(){
            return this->__arr;
        }
        T* end(){
            return (this->__arr + this->__size);
        }
        const T* begin() const{
            return this->__arr;
        }
        const T* end() const{
            return (this->__arr + this->__size);
        }
        
        const T* cbegin() const {
            return this->__arr;
        }
        const T* cend() const {
            return (this->__arr + this->__size);
        }
        
        size_t size() const { return this->__size; }
        T& operator[](size_t i){
#ifdef CARR_BCHECK
            if (i >= this->__size)
                throw IndexError();
#endif
            return this->__arr[i];
        }
        const T& operator[](size_t i) const {
#ifdef CARR_BCHECK
            if (i >= this->__size)
                throw IndexError();
#endif
            return this->__arr[i];
        }
        
        ~array(){
            delete[] this->__arr;
            this->__arr = nullptr;
            this->__size = 0;
        }
        
        array& reverse(){
            T* left = this->begin();
            T* right = this->end() - 1;
            T tmp{};
            for (; left < right; ++left, --right){
                tmp = *left;
                *left = *right;
                *right = tmp;
            }
            return *this;
        }
        array& set(const T& val){
            T* iter = this->begin();
            T* end = this->end();
            for (; iter != end; ++iter)
                *iter = val;
            return *this;
        }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& output, const array<U>& arr);
    
    private:
        T* __arr{nullptr};
        size_t __size{};
};

array<double> linspace(double from, double to, size_t size){
    array<double> nums(size);
    double* iter = nums.begin(), *end = nums.end();
    double step = (to - from) / (size - 1);
    for (; iter != end; ++iter, from += step)
        *iter = from;
    return nums;
}

template<typename T>
std::ostream& operator<<(std::ostream& output, const array<T>& arr){
    output << '[';
    if (arr.__size){
        const T* iter = arr.cbegin();
        for (; iter != (arr.cend() - 1); ++iter)
            output << *iter << ", ";
        output << *iter;
    }
    output << ']';
    return output;
}

#endif  // __CARR_H