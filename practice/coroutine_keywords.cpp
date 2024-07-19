/**
 * A coroutine is a function that can suspend execution to be resumed
 * later. Coroutines are stackless; they suspend execution by returning
 * to the caller and the data that is required to resume execution is
 * stored separately from the stack.
 * 
 * A function is a coroutine if its definition contains any of the
 * following keywords:
 * 
 *      co_yield : suspends the execution of the function and returns a
 *                 value.
 * 
 *      co_return : completes execution and optionally returns a value.
 * 
 *      co_await : suspends the execution until resumed.
 * 
 * If a function contains one of these three keywords, it becomes a
 * coroutine. There is no other special syntax for coroutines.
**/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <coroutine>

class __rand_iterator{
    public:
        __rand_iterator(int from, int to) : __from(from), __to(to){}
        int operator*() const{
            return (__from + (std::rand() % (__to - __from)));
        }
        __rand_iterator& operator++(){ return *this; }
        __rand_iterator operator++(int){ return *this; }
        bool operator==(const __rand_iterator& rhs) const = default;
        bool operator!=(const __rand_iterator& rhs) const{ return !(*this == rhs); }

    private:
        int __from;
        int __to;
};

class rand{
    public:
        typedef __rand_iterator iterator;
        rand(int from, int to) : __from(from), __to(to){}
        iterator begin(){
            std::srand(std::time(0));
            return __rand_iterator(__from, __to);
        }
        iterator end(){ return __rand_iterator(INT_MAX, INT_MAX); }

    private:
        int __from;
        int __to;
};