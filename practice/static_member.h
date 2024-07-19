#ifndef __STATIC_MEMBER_H
#define __STATIC_MEMBER_H

#include <iostream>
#include <initializer_list>

class _arr_list;

class Array {
    public:
        Array();
        Array(size_t size);
        Array(std::initializer_list<int> args);
        Array(Array&& source_arr);  // move constructor
        bool is_full();
        bool is_empty();
        void append(int item);
        size_t capacity();
        size_t size();
        int& operator[](size_t i);
        void swap(size_t i, size_t j);
        void release();
        friend std::ostream& operator<<(std::ostream& output, Array& A);
        static const double PI {3.14};
    private:
        int* arr;
        size_t Size;
        size_t cur;
        static _arr_list _A_list;
        // inline static _arr_list _A_list{};  // initialization in the class
        // is allowed with inline
};

class _arr_node {
    public:
        _arr_node(Array* A);
    private:
        Array* A;
        _arr_node* next;
        friend class _arr_list;
};

class _arr_list {
    public:
        _arr_list();
        void _append(Array* A);
        void clear_list();
    private:
        _arr_node* head;
};

_arr_list Array::_A_list{};

#endif // __STATIC_MEMBER_H