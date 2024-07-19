#ifndef __ARRAY_H
#define __ARRAY_H

#include <iostream>
#include <iomanip>
#include <string>
#define newline printf("\n")

template<typename T> class _arr_list;

template <typename T>
class Array {
    public:
        Array(size_t Size = 16);
        Array(T array[], size_t Size);
        bool is_empty();
        bool is_full();
        template<typename U = T> void append(U item);
        size_t size();
        size_t capacity();
        T& operator[](size_t i);
        void swap(size_t i, size_t j);
        void release();
        ~Array();
    private:
        T* arr;
        size_t s;
        size_t cur;
        template<typename U> friend std::ostream& operator<<(std::ostream& output, Array<U>& A);
};

template <typename T> Array<T>::Array(size_t Size)
{
    arr = new T[Size];
    s = Size;
    cur = 0;
}

template<typename T>
Array<T>::Array(T array[], size_t Size)
{
    arr = new T[Size];
    s = Size;
    cur = 0;
    for (size_t i{}; i < Size; i++)
        append(array[i]);
}

template<typename T>
bool Array<T>::is_empty()
{
    return (cur == 0);
}

template<typename T>
bool Array<T>::is_full()
{
    return (cur == s);
}

template<typename T>
template<typename U>
void Array<T>::append(U item)
{
    if (is_full())
    {
        T* new_arr = new T[2 * s];
        for (size_t i{}; i < s; i++)
            new_arr[i] = arr[i];
        s *= 2;
        delete[] arr;
        arr = new_arr;
    }
    arr[cur++] = item;
}

template<>
template<>
void Array<std::string>::append(const char* item)
{
    if (is_full())
    {
        std::string* new_arr = new std::string[2 * s];
        for (size_t i{}; i < s; i++)
            new_arr[i] = arr[i];
        s *= 2;
        delete[] arr;
        arr = new_arr;
    }
    arr[cur++] = std::string(item);
}


template<typename T>
size_t Array<T>::size()
{
    return cur;
}

template<typename T>
size_t Array<T>::capacity()
{
    return s;
}

template<typename T>
T& Array<T>::operator[](size_t i)
{
    if (i >= cur)
    {
        std::cerr << "\nERROR: Array index out of range.\n";
        exit(0);
    }
    return arr[i];
}

template<typename T>
void Array<T>::swap(size_t i, size_t j)
{
    if (i >= cur || j >= cur)
    {
        std::cerr << "ERROR: Array index out of range.\n";
        return;
    }
    T tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

template<typename T>
void Array<T>::release(){
    delete[] arr;
    arr = nullptr;
    std::cout << "Array cleared.\n";
}

template <typename T>
Array<T>::~Array()
{
    delete[] arr;
}

template<typename T>
std::ostream& operator<<(std::ostream& output, Array<T>& A)
{
    if (A.is_empty())   
        output << "[]";
    else
    {
        size_t i{}, upto{A.cur - 1};
        T* array = A.arr;
        output << "[";
        for (; i < upto; i++)
            output << array[i] << ", ";
        output << array[i] << "]";
    }
    return output;
}

template<>
std::ostream& operator<<(std::ostream& output, Array<const char*>& A)
{
    if (A.is_empty())   
        output << "[]";
    else
    {
        size_t i{}, upto{A.cur - 1};
        const char** array = A.arr;
        output << "[";
        for (; i < upto; i++)
            output << std::quoted(array[i]) << ", ";
        output << std::quoted(array[i]) << "]";
    }
    return output;
}

template<>
std::ostream& operator<<(std::ostream& output, Array<std::string>& A)
{
    if (A.is_empty())   
        output << "[]";
    else
    {
        size_t i{}, upto{A.cur - 1};
        std::string* array = A.arr;
        output << "[";
        for (; i < upto; i++)
            output << std::quoted(array[i]) << ", ";
        output << std::quoted(array[i]) << "]";
    }
    return output;
}

#endif // __ARRAY_H