#ifndef __ARR_H
#define __ARR_H

#include <iostream>
#include <initializer_list>
#include <type_traits>
#include <string>
#include <memory>

namespace arr {
    template<typename T>
    class Array {
        public:
            typedef T value_type;
            typedef value_type* iterator;
            explicit Array(size_t size = 16);
            Array(size_t size, const T& default_value);
            Array(T from, T to, T step);
            Array(std::initializer_list<T> args);
            Array(const T* array, size_t from, size_t to);
            Array(const T* array, size_t size);
            Array(const Array& src);
            Array(Array&& src);
            constexpr size_t size() const;
            double avg() const;
            T& operator[](size_t i);
            const T& operator[](size_t i) const;
            std::unique_ptr<Array<T>> slice(size_t i, size_t j) const;
            std::unique_ptr<Array<T>> operator()(size_t start, size_t end) const;
            std::unique_ptr<Array<T>> operator()(size_t end) const;
            void resize(size_t new_size);
            void resize(size_t new_size, const T& default_value);
            T* begin();
            const T* begin() const;
            T* end();
            const T* end() const;
            template<typename U>
            friend std::ostream& operator<<(std::ostream& output, const Array<U>& A);
            template<typename U>
            requires std::is_convertible_v<U, std::string_view>
            friend std::ostream& operator<<(std::ostream& output, const Array<U>& A);
            ~Array();
        
        protected:
            T* arr;
            size_t arr_size;
            static inline T error{};
            template<typename R, typename U>
            friend R _sum(const arr::Array<U>& A);
    };

    template<typename T>
    Array<T>::Array(size_t size){
        std::cout << "Array created at " << this << '\n';
        if (!size)
        {
            arr = nullptr;
            arr_size = 0;
        }
        else
        {
            arr = new T[size];
            arr_size = size;
        }
    }

    template<typename T>
    Array<T>::Array(size_t size, const T& default_value) : Array(size){
        for (size_t i{}; i < size; i++)
            arr[i] = default_value;
    }

    template<typename T>
    Array<T>::Array(T from, T to, T step) : Array((to - from) / step){
        for (size_t i{}; from < to; from += step)
            arr[i++] = from;
    }

    template<typename T>
    Array<T>::Array(std::initializer_list<T> args){
        std::cout << "Array created at " << this << '\n';
        arr_size = args.size();
        arr = new T[arr_size];
        const T* first = args.begin();
        for (size_t i{}; i < arr_size; i++)
            arr[i] = *(first + i);
    }

    template<typename T>
    Array<T>::Array(const T* array, size_t from, size_t to) : Array(to - from){
        for (size_t i{from}, j{}; i < to; i++, j++)
            arr[j] = array[i];
    }

    template<typename T>
    Array<T>::Array(const T* array, size_t size) : Array(array, 0, size){}

    template<typename T>
    Array<T>::Array(const Array<T>& src) : Array(src.arr, src.arr_size){
        std::cout << "Copied array from " << &src << " to " << this << '\n';
    }

    template<typename T>
    Array<T>::Array(Array<T>&& src){
        arr = src.arr;
        arr_size = src.arr_size;
        src.arr = nullptr;
        src.arr_size = 0;
        std::cout << "Array at " << &src << " moved to new Array at " << this << '\n';
    }

    template<typename T>
    constexpr size_t Array<T>::size() const {
        return arr_size;
    }

    template<typename T>
    double Array<T>::avg() const {
        size_t total{}, i{};
        for (; i < arr_size; i++)
            total += arr[i];
        return static_cast<double>(total) / arr_size;
    }

    template<>
    double Array<double>::avg() const {
        size_t i{};
        long double total{};
        for (; i < arr_size; i++)
            total += arr[i];
        return (total / arr_size);
    }

    template<typename T>
    T& Array<T>::operator[](size_t i){
        if (i > (arr_size - 1))
        {
            std::cerr << "ERROR: Array index out of bounds.\n";
            return error;
        }
        return arr[i];
    }

    template<typename T>
    const T& Array<T>::operator[](size_t i) const {
        if (i > (arr_size - 1))
        {
            std::cerr << "ERROR: Array index out of bounds.\n";
            return error;
        }
        return arr[i];
    }

    template<typename T>
    std::unique_ptr<Array<T>> Array<T>::slice(size_t i, size_t j) const {
        if (j <= i)
            return nullptr;
        std::unique_ptr<Array<T>> ptr = std::make_unique<Array<T>>(arr, i, j);
        return ptr;
    }

    template<typename T>
    std::unique_ptr<Array<T>> Array<T>::operator()(size_t start, size_t end) const {
        return slice(start, end);
    }

    template<typename T>
    std::unique_ptr<Array<T>> Array<T>::operator()(size_t end) const {
        return slice(0, end);
    }

    template<typename T>
    void Array<T>::resize(size_t new_size){
        if (new_size <= arr_size)
        {
            std::cerr << "ERROR: Resizing array to a size less than data size.\n";
            return;
        }
        T* new_arr = new T[new_size];
        memcpy(new_arr, arr, arr_size * sizeof(T));
        delete[] arr;
        arr = new_arr;
        arr_size = new_size;
    }

    template<typename T>
    void Array<T>::resize(size_t new_size, const T& default_value){
        if (new_size <= arr_size)
        {
            std::cerr << "ERROR: Resizing array to a size less than data size.\n";
            return;
        }
        T* new_arr = new T[new_size];
        memcpy(new_arr, arr, arr_size * sizeof(T));
        for (size_t i{arr_size}; i < new_size; i++)
            new_arr[i] = default_value;
        delete[] arr;
        arr = new_arr;
        arr_size = new_size;
    }

    template<typename T>
    T* Array<T>::begin(){
        return arr;
    }

    template<typename T>
    const T* Array<T>::begin() const {
        return arr;
    }

    template<typename T>
    T* Array<T>::end(){
        return (arr + arr_size);
    }

    template<typename T>
    const T* Array<T>::end() const {
        return (arr + arr_size);
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& output, const Array<T>& A){
        if (A.arr_size == 0)
            output << "[]";
        else
        {
            size_t i{}, upto{A.arr_size - 1};
            T* arr = A.arr;
            output << '[';
            for (; i < upto; i++)
                output << arr[i] << ", ";
            output << arr[i] << ']';
        }
        return output;
    }

    template<>
    std::ostream& operator<<(std::ostream& output, const Array<char>& A){
        if (A.arr_size == 0)
            output << "[]";
        else
        {
            size_t i{}, upto{A.arr_size - 1};
            char* arr = A.arr;
            output << '[';
            for (; i < upto; i++)
                output << '\'' << arr[i] << "\', ";
            output << '\'' << arr[i] << "\']";
        }
        return output;
    }

    template<typename T>
    requires std::is_convertible_v<T, std::string_view>
    std::ostream& operator<<(std::ostream& output, const Array<T>& A){
        if (A.arr_size == 0)
            output << "[]";
        else
        {
            size_t i{}, upto{A.arr_size - 1};
            const T* arr = A.arr;
            output << '[';
            for (; i < upto; i++)
                output << '\"' << arr[i] << "\", ";
            output << '\"' << arr[i] << "\"]";
        }
        return output;
    }

    template<typename T>
    Array<T>::~Array(){
        std::cout << "Array at " << this << " destroyed...\n";
        delete[] arr;
        arr_size = 0;
    }

    Array<size_t> range(size_t from, size_t to, size_t step = 1){
        if (from >= to)
        {
            std::cerr << "ERROR: Invalid range arguments.\n";
            return arr::Array<size_t>(0);
        }
        return arr::Array<size_t>(from, to, step);
    }

    Array<size_t> range(size_t to, size_t step = 1){
        return arr::range(0, to, step);
    }

    template<typename R, typename T>
    R _sum(const arr::Array<T>& A){
        size_t i{}, size{A.arr_size};
        R total{};
        T* arr = A.arr;
        for (; i < size; i++)
            total += arr[i];
        return total;
    }

    template<typename T>
    auto sum(const arr::Array<T>& A){
        if constexpr (std::is_integral_v<T>)
            return _sum<size_t, T>(A);
        else if constexpr (std::is_convertible_v<T, double>)
            return _sum<long double, T>(A);
        else
            return 0;
    }

    template<typename T>
    requires std::is_convertible_v<T, double>
    void transform(Array<T>& A, void (*fun)(T&)){
        for (size_t i{}; i < A.size(); i++)
            fun(A[i]);
    }

    template<typename T>
    using uptr = std::unique_ptr<Array<T>>;
}

#endif  // __ARR_H