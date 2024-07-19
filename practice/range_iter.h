#ifndef __RANGE_ITER_H
#define __RANGE_ITER_H

#include <iostream>

template<typename T>
struct __allof{
    bool operator()(T&){ return true; }
};

template<typename Container, typename Predicate = __allof<typename Container::value_type>>
class range{
    public:
        range(Container& C) : __iter(std::begin(C)), __end(std::end(C)){
            while ((__iter != __end) && !__pred(*__iter))
                ++__iter;
        }
        range(Container& C, Predicate pred) : range(C){}
        typename Container::value_type& operator*(){
            return *__iter;
        }
        range& operator++(){
            ++__iter;
            while ((__iter != __end) && !__pred(*__iter))
                ++__iter;
            return *this;
        }
        bool operator==(range& rhs){
            return (this->__iter == rhs.__iter);
        }
        bool operator==(range&& rhs){
            return (this->__iter == rhs.__iter);
        }
        bool at_end(){
            return (this->__iter == this->__end);
        }
        template<typename __container, typename __predicate>
        friend std::ostream& operator<<(std::ostream& output, range<__container, __predicate> R);

    private:
        typename Container::iterator __iter;
        typename Container::iterator __end;
        static inline Predicate __pred;
};

template<typename __container, typename __predicate>
std::ostream& operator<<(std::ostream& output, range<__container, __predicate> iter){
    if (!iter.at_end()){
        range<__container, __predicate> leading = iter;
        ++leading;
        output << '[';
        for (; !leading.at_end(); ++iter, ++leading)
            output << *iter << ", ";
        output << *iter << ']';
    }
    return output;
}

#endif  // __RANGE_ITER_H