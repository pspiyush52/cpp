#ifndef __LISTS_H
#define __LISTS_H

#include <iostream>
#include "exceptions.h"
#include <initializer_list>
#include <string.h>
#include <concepts>
#include <string_view>

template<typename T>
class List{
    public:
        typedef             T       value_type;
        typedef             T*      iterator;
        typedef       const T*      const_iterator;

    public:    
        explicit List(size_t size = 16);
        List(std::initializer_list<T> args);
        List(const List& src);
        List(List&& src);
        bool is_full() const;
        bool is_empty() const;
        void append(const T& item);
        void append(T&& item);
        void pop();
        size_t size() const;
        size_t capacity() const;
        std::ostream& stream_insert(std::ostream& output) const;
        std::ostream& stream_insert_s(std::ostream& output) const;
        T* begin();
        const T* begin() const;
        const T* end() const;
        T* end();
        T& operator[](long long i);
        const T& operator[](long long i) const;
        List& operator=(const List& rhs);
        List& operator=(List&& rhs);
        ~List();

        template<typename U>
        friend std::ostream& operator<<(std::ostream& output, const List<U>& L);

    protected:
        T* arr;
        size_t list_size;
        size_t cur;
};

template<typename T>
List<T>::List(size_t size) : arr(new T[size]), list_size(size), cur(0){}

template<typename T>
List<T>::List(std::initializer_list<T> args) : List(args.size()){
    cur = args.size();
    T* _arr = arr;
    const T* start = args.begin();
    const T* end = args.end();
    while (start != end)
        (*(_arr++) = *(start++));
}

template<typename T>
List<T>::List(const List<T>& src) : List(src.list_size){
    memcpy(arr, src.arr, list_size * sizeof(T));
    cur = src.cur;
}

template<typename T>
List<T>::List(List<T>&& src) : List(src.list_size){
    memcpy(arr, src.arr, list_size * sizeof(T));
    cur = src.cur;
    delete[] src.arr;
    src.arr = nullptr;
    src.list_size = 0;
    src.cur = 0;
}

template<typename T>
bool List<T>::is_full() const {
    return (cur == list_size);
}

template<typename T>
bool List<T>::is_empty() const {
    return (!cur);
}

template<typename T>
void List<T>::append(const T& item){
    if (is_full())
    {
        T* new_arr = new T[2 * list_size], *iter = this->begin(), *end = this->end();
        for (size_t i{}; iter != end; ++iter)
            new_arr[i++] = std::move(*iter);
        delete[] arr;
        arr = new_arr;
        list_size *= 2;
    }
    arr[cur++] = item;
}

template<typename T>
void List<T>::append(T&& item){
    if (is_full())
    {
        T* new_arr = new T[2 * list_size], *iter = this->begin(), *end = this->end();
        for (size_t i{}; iter != end; ++iter)
            new_arr[i++] = std::move(*iter);
        delete[] arr;
        arr = new_arr;
        list_size *= 2;
    }
    arr[cur++] = std::move(item);
}

template<typename T>
void List<T>::pop(){
    if (is_empty())
        throw IndexError("List empty");
    else
        cur--;
}

template<typename T>
size_t List<T>::size() const { return cur; }

template<typename T>
size_t List<T>::capacity() const { return list_size; }

template<typename T>
T& List<T>::operator[](long long i){
    if (i < 0)
        i = this->cur + i;
    if (i >= cur || (i < 0))
        throw IndexError();
    return arr[i];
}

template<typename T>
const T& List<T>::operator[](long long i) const{
    if (i < 0)
        i = this->cur + i;
    if (i >= cur || (i < 0))
        throw IndexError();
    return arr[i];
}

template<typename T>
std::ostream& List<T>::stream_insert(std::ostream& output) const {
    if (cur == 0)
        output << "[]";
    else
    {
        size_t i{}, upto{cur - 1};
        output << '[';
        for (; i < upto; i++)
            output << arr[i] << ", ";
        output << arr[i] << ']';
    }
    return output;
}

template<typename T>
std::ostream& List<T>::stream_insert_s(std::ostream& output) const{
    if (cur == 0)
        output << "[]";
    else
    {
        size_t i{}, upto{cur - 1};
        output << '[';
        for (; i < upto; i++)
            output << '\"' << arr[i] << "\", ";
        output << '\"' << arr[i] << "\"]";
    }
    return output;
}

template<typename T>
T* List<T>::begin(){
    return arr;
}

template<typename T>
const T* List<T>::begin() const{
    return arr;
}

template<typename T>
T* List<T>::end(){
    return (arr + cur);
}

template<typename T>
const T* List<T>::end() const{
    return (arr + cur);
}

template<typename T>
List<T>& List<T>::operator=(const List& rhs){
    if (this == &rhs)
        return *this;
    delete[] arr;
    arr = new T[rhs.list_size];
    list_size = rhs.list_size;
    cur = rhs.cur;
    memcpy(arr, rhs.arr, list_size * sizeof(T));
    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List&& rhs){
    if (this == &rhs)
        return *this;
    delete[] arr;
    arr = rhs.arr;
    list_size = rhs.list_size;
    cur = rhs.cur;
    rhs.arr = nullptr;
    rhs.list_size = 0;
    rhs.cur = 0;
    return *this;
}

template<typename T>
List<T>::~List(){
    delete[] arr;
    arr = nullptr;
    list_size = 0;
}

template<typename U>
std::ostream& operator<<(std::ostream& output, const List<U>& L){
    return L.stream_insert(output);
}

template<typename U>
requires std::is_convertible_v<U, std::string_view>
std::ostream& operator<<(std::ostream& output, const List<U>& L){
    return L.stream_insert_s(output);
}

#endif  // __LISTS_H