#ifndef __RANGE_H
#define __RANGE_H

#include <cstdio>
#include "frand.h"
#include <climits>
#include <iterator>

class __range_gen_iterator{
    public:
        __range_gen_iterator(long long num) : __num(num){}
        long long& operator*(){ return __num; }
        __range_gen_iterator& operator++(){
            ++__num;
            return *this;
        }
        __range_gen_iterator operator++(int){
            __range_gen_iterator tmp(*this);
            ++__num;
            return tmp;
        }
        bool operator==(__range_gen_iterator& rhs){
            return (this->__num == rhs.__num);
        }
        bool operator==(__range_gen_iterator&& rhs){
            return (this->__num == rhs.__num);
        }
    private:
        long long __num;
};

class range{
    public:
        typedef __range_gen_iterator iterator;
        typedef long long value_type;
        explicit range(long long end) : __end(end){}
        range(long long start, long long end) : __start(start), __end(end){}
        iterator begin(){
            return iterator(__start);
        }
        iterator end(){
            return iterator(__end);
        }

    private:
        long long __start{};
        long long __end;
};

class __rand_range_iterator{
    public:
        __rand_range_iterator(const int& from, const int& to, const unsigned int& count):
            __from(from),
            __to(to),
            __count(count),
            __counter(0)
            {
                __cur = r.randint(from, to);
            }
        int& operator*(){
            return __cur;
        }
        __rand_range_iterator& operator++(){
            ++__counter;
            if (__counter >= __count)
                this->__from = INT_MIN;
            __cur = r.randint(__from, __to);
            return *this;
        }
        __rand_range_iterator operator++(int){
            __rand_range_iterator tmp(*this);
            ++__counter;
            if (__counter >= __count)
                this->__from = INT_MIN;
            __cur = r.randint(__from, __to);
            return tmp;
        }
        bool operator==(__rand_range_iterator& rhs){
            return (this->__from == rhs.__from);
        }
        bool operator==(__rand_range_iterator&& rhs){
            return (this->__from == rhs.__from);
        }
    
    private:
        int __from;
        int __to;
        unsigned int __count;
        unsigned int __counter;
        int __cur;
        rng r{};
};

class rand_range{
    public:
        typedef __rand_range_iterator iterator;
        typedef int value_type;
        rand_range(int from, int to) : __from(from), __to(to), __count(UINT_MAX){}
        rand_range(int from, int to, unsigned int count) : __from(from), __to(to), __count(count){}
        rand_range(unsigned int count) : __from(0), __to(INT_MAX), __count(count){}
        iterator begin(){
            return iterator(__from, __to, __count);
        }
        iterator end(){
            return iterator(INT_MIN, 0, 0);
        }

        template<typename Container>
        friend Container& operator>>(rand_range& r, Container& container);

        template<typename Container>
        friend Container& operator>>(rand_range&& r, Container& container);

    private:
        int __from{INT_MAX};
        int __to{INT_MAX};
        unsigned int __count;
};

template<typename Container>
Container& operator>>(rand_range& r, Container& container){
    rand_range::iterator riter = r.begin();
    auto citer = std::begin(container);
    auto cend = std::end(container);
    for (; citer != cend; ++citer, ++riter){
        if (riter == r.end())
            break;
        *citer = *riter;
    }
    return container;
}

template<typename Container>
Container& operator>>(rand_range&& r, Container& container){
    rand_range::iterator riter = r.begin();
    auto citer = std::begin(container);
    auto cend = std::end(container);
    for (; citer != cend; ++citer, ++riter){
        if (riter == r.end())
            break;
        *citer = *riter;
    }
    return container;
}

#endif  // __RANGE_H