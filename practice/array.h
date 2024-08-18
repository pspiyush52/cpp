#ifndef __ARRAY_H
#define __ARRAY_H

#include <iostream>
#include "reverse_iterator.h"

template<typename arr_tp, size_t size>
class Array {
    public:
        typedef                               PointerIterator<arr_tp>                                 iterator;
        typedef                               ConstIterator<iterator>                                 const_iterator;
        typedef                BidirectionalReverseIterator<iterator>                                 reverse_iterator;
        typedef                       ConstIterator<reverse_iterator>                                 const_reverse_iterator;

        Array() = default;
        Array(std::initializer_list<arr_tp> args) {
            size_t i{};
            auto it = args.begin();
            for (; i < size && it != args.end(); ++i, ++it)
                this->arr[i] = *it;
        }
        template<typename Container>
        Array(const Container& c) {
            auto it = std::cbegin(c);
            size_t i{};
            for (; i < size && it != std::cend(c); ++it, ++i)
                this->arr[i] = *it;
        }
        template<typename Iterator>
        Array(Iterator&& begin, Iterator&& end) {
            size_t i{};
            for (; i < size && begin != end; ++i, ++begin)
                this->arr[i] = *begin;
        }
        arr_tp& operator[](size_t i) {
            return this->arr[i];
        }
        iterator begin() {
            return {this->arr};
        }
        iterator end() {
            return {this->arr + size};
        }
        reverse_iterator rbegin() {
            return {iterator(this->arr + size - 1)};
        }
        reverse_iterator rend() {
            return {iterator(this->arr - 1)};
        }
        friend std::ostream& operator<<(std::ostream& out, const Array& A) {
            size_t i{};
            out << '[';
            for (; i < size - 1; ++i)
                out << A.arr[i] << ", ";
            out << A.arr[i] << ']';
            return out;
        }

    private:
        arr_tp arr[size];
};

#endif  // __ARRAY_H
