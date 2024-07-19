#ifndef __STR_CONT_H
#define __STR_CONT_H

#include <iostream>
#include "reverse_iterator.h"

class deque{
    
    private:
    static const int SIZE{16};
    class __deque_iterator{
        
        public:
            typedef       char         value_type;
            typedef       char*        pointer;
            typedef       char&        reference;
            typedef const char&        const_reference;
        
        public:
            __deque_iterator(size_t pos, deque* d);
            __deque_iterator& operator++();
            __deque_iterator operator++(int);
            __deque_iterator& operator--();
            __deque_iterator operator--(int);
            char& operator*();
            __deque_iterator operator+(size_t i);
            __deque_iterator operator-(size_t i);
            bool operator==(const __deque_iterator& rhs) const;
            bool operator!=(const __deque_iterator& rhs) const;
            size_t __get_pos();
        
        private:
            size_t __pos{};
            deque* __parent{};

            size_t __rel_pos();
    };
    class __const_deque_iterator{

        public:
            typedef       char         value_type;
            typedef       char*        pointer;
            typedef       char&        reference;
            typedef const char&        const_reference;
        
        public:
            __const_deque_iterator(size_t pos, const deque* d);
            __const_deque_iterator& operator++();
            __const_deque_iterator operator++(int);
            __const_deque_iterator& operator--();
            __const_deque_iterator operator--(int);
            const char& operator*() const;
            __const_deque_iterator operator+(size_t i);
            __const_deque_iterator operator-(size_t i);
            bool operator==(const __const_deque_iterator& rhs) const;
            bool operator!=(const __const_deque_iterator& rhs) const;
            size_t __get_pos() const;
        
        private:
            size_t __pos{};
            const deque* __parent{};

            size_t __rel_pos();
    };

    public:
        typedef                                                        char                   value_type;
        typedef                                                        char*                  pointer;
        typedef                                                        char&                  reference;
        typedef                                                  const char&                  const_reference;
        typedef                                             __deque_iterator                  iterator;
        typedef                                       __const_deque_iterator                  const_iterator;
        typedef             __reverse_iterator<__deque_iterator, value_type>                  reverse_iterator;
        typedef __const_reverse_iterator<__const_deque_iterator, value_type>                  const_reverse_iterator;
    
    public:
        deque();
        deque(const deque& src);
        deque(deque&& src);
        deque& operator=(const deque& src);
        deque& operator=(deque&& src);
        bool is_empty() const;
        bool is_full() const;
        size_t capacity() const;
        size_t size() const;
        deque& push_front(const char& item);
        deque& push_front(char&& item);
        deque& push_back(const char& item);
        deque& push_back(char&& item);
        deque& pop_front();
        deque& pop_back();
        deque& pop_frontn(int n);
        deque& pop_backn(int n);
        deque& shrink_to_fit();
        const deque& shrink_to_fit() const;
        void clear();
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;
        const_reverse_iterator crbegin() const;
        const_reverse_iterator crend() const;
        char& operator[](long long i);
        const char& operator[](long long i) const;
        ~deque();
        friend std::ostream& operator<<(std::ostream& output, const deque& d);
        void __contents();

    protected:
        mutable char* __arr{};
        mutable size_t __size{};
        mutable size_t __front{};
        mutable size_t __rear{};

        deque(long long size);
        void __make(size_t size);
        void __expand();
        void __invalidate();
        void __incr(size_t& val) const;
        void __set_front(iterator iter);
        void __set_front(const_iterator iter) const;
        void __set_rear(iterator iter);
        void __set_rear(const_iterator iter) const;
        size_t __rel_pos(size_t i) const;
        void __shrink() const;
};

#endif  // __STR_CONT_H