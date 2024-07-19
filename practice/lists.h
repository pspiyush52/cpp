#ifndef __LISTS_H
#define __LISTS_H

#include <iostream>
#include <exception>
#include <initializer_list>
#include <cstring>
#include <concepts>
#include <string_view>
#include <cassert>

class ListIndexError : public std::out_of_range{
    public:
        ListIndexError():
            std::out_of_range(""){}
        const char* what() const noexcept {
            return "ListIndexError: List index out of bounds.";
        }
};

namespace arr{
    template<typename T>
    class List{
        public:
            typedef                            T              value_type;
            typedef                   value_type*             pointer;
            typedef             const value_type*             const_pointer;
            typedef                   value_type&             reference;
            typedef             const value_type&             const_reference;
            typedef                   value_type*             iterator;
            typedef                      const T*             const_iterator;
            typedef                  std::size_t              size_type;
        
        public:
            explicit List(size_t size = 16);
            List(std::initializer_list<T> args);
            template<typename Iterator>
            List(Iterator begin, Iterator end);
            List(const char* str);
            List(const List& src);
            List(List&& src);
            bool is_full() const;
            bool is_empty() const;
            List& append(const T& item);
            List& append(T&& item);
            void pop();
            size_t size() const;
            size_t capacity() const;
            std::ostream& stream_insert(std::ostream& output) const;
            std::ostream& stream_insert_s(std::ostream& output) const;
            iterator begin();
            iterator end();
            const_iterator begin() const;
            const_iterator end() const;
            const_iterator cbegin() const;
            const_iterator cend() const;
            reference operator[](long long i);
            const_reference operator[](long long i) const;
            List& operator=(const List& rhs);
            List& operator=(List&& rhs);
            ~List();

            template<typename U>
            friend std::ostream& operator<<(std::ostream& output, const List<U>& L);

        protected:
            T* arr;
            size_t list_size;
            size_t cur;

            void __expand(){
                pointer new_arr = new value_type[2 * this->list_size], ptr = new_arr;
                iterator iter = this->begin(), end = this->end();
                for (; iter != end; ++iter, ++ptr)
                    *ptr = std::move(*iter);
                delete[] this->arr;
                this->arr = new_arr;
                this->list_size *= 2;
            }
    };

    template<typename T>
    List<T>::List(size_t size) : arr(new T[size]), list_size(size), cur(0){}

    template<typename T>
    List<T>::List(std::initializer_list<T> args) : List(2 * args.size()){
        cur = args.size();
        iterator _arr = this->begin();
        auto start = args.begin();
        auto end = args.end();
        while (start != end)
            (*(_arr++) = *(start++));
    }

    template<typename T>
    template<typename Iterator>
    List<T>::List(Iterator begin, Iterator end) : List(){
        if (begin >= end)
            return;
        size_t i{};
        for (; begin != end; ++begin, ++i)
            this->arr[i] = *begin;
        cur = i;
    }

    template<typename T>
    List<T>::List(const char* str){
        static_assert(std::is_same_v<T, char>);
        size_t s{std::strlen(str)};
        if (s == 0){
            this->arr = new char[16];
            this->list_size = 16;
            this->cur = 0;
        }
        else{
            this->arr = new char[s + 10];
            this->list_size = s + 10;
            this->cur = s;
            memcpy(this->arr, str, s);
        }
    }

    template<typename T>
    List<T>::List(const List<T>& src) : List(src.list_size){
        memcpy(arr, src.arr, list_size * sizeof(T));
        cur = src.cur;
    }

    template<typename T>
    List<T>::List(List<T>&& src){
        this->arr = src.arr;
        this->cur = src.cur;
        this->list_size = src.list_size;
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
    List<T>& List<T>::append(const T& item){
        if (is_full())
            this->__expand();
        arr[cur++] = item;
        return *this;
    }

    template<typename T>
    List<T>& List<T>::append(T&& item){
        if (is_full())
            this->__expand();
        arr[cur++] = std::move(item);
        return *this;
    }

    template<typename T>
    void List<T>::pop(){
        if (is_empty())
            std::cerr << "ERROR: List empty.\n";
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
            throw ListIndexError();
        return arr[i];
    }

    template<typename T>
    const T& List<T>::operator[](long long i) const{
        if (i < 0)
            i = this->cur + i;
        if (i >= cur || (i < 0))
            throw ListIndexError();
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

    template<>
    std::ostream& List<char>::stream_insert(std::ostream& output) const {
        if (cur == 0)
            output << "[]";
        else
        {
            size_t i{}, upto{cur - 1};
            output << '[';
            for (; i < upto; i++)
                output << '\'' << arr[i] << "\', ";
            output << '\'' << arr[i] << "\']";
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
    List<T>::iterator List<T>::begin(){
        return arr;
    }

    template<typename T>
    List<T>::const_iterator List<T>::begin() const{
        return arr;
    }

    template<typename T>
    List<T>::iterator List<T>::end(){
        return (arr + cur);
    }

    template<typename T>
    List<T>::const_iterator List<T>::end() const{
        return (arr + cur);
    }

    template<typename T>
    List<T>::const_iterator List<T>::cbegin() const {
        return this->arr;
    }

    template<typename T>
    List<T>::const_iterator List<T>::cend() const {
        return this->arr + this->list_size;
    }
    
    template<typename T>
    List<T>& List<T>::operator=(const List& rhs){
        delete[] arr;
        arr = new T[rhs.list_size];
        list_size = rhs.list_size;
        cur = rhs.cur;
        memcpy(arr, rhs.arr, list_size * sizeof(T));
        return *this;
    }

    template<typename T>
    List<T>& List<T>::operator=(List&& rhs){
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
}

namespace arr{
    template<typename T>
    requires std::is_move_assignable_v<T> && std::is_move_constructible_v<T>
    void swap(T& lhs, T& rhs){
        T tmp = std::move(lhs);
        lhs = std::move(rhs);
        rhs = std::move(tmp);
    }
}

template<typename U>
std::ostream& arr::operator<<(std::ostream& output, const arr::List<U>& L){
    return L.stream_insert(output);
}

template<typename U>
requires std::is_convertible_v<U, std::string_view>
std::ostream& arr::operator<<(std::ostream& output, const arr::List<U>& L){
    return L.stream_insert_s(output);
}

#endif  // __LISTS_H