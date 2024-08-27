#ifndef __RANGE_H
#define __RANGE_H

#include <cstdio>
#include "frand.h"
#include <climits>
#include "reverse_iterator.h"

class range {
    public:
    class iterator {
            public:
                typedef              const int             value_type;
                iterator(int from): cur{from} {}
                value_type& operator*() {
                    return this->cur;
                }
                iterator& operator++() {
                    ++(this->cur);
                    return *this;
                }
                iterator operator++(int) {
                    iterator tmp{*this};
                    ++(this->cur);
                    return tmp;
                }
                iterator& operator--() {
                    --(this->cur);
                    return *this;
                }
                iterator operator--(int) {
                    iterator tmp{*this};
                    --(this->cur);
                    return tmp;
                }
                bool operator==(const iterator& rhs) {
                    return (this->cur == rhs.cur);
                }
                bool operator!=(const iterator& rhs) {
                    return (this->cur != rhs.cur);
                }
            private:
                int cur;
        };
        typedef                                                 int               value_type;
        typedef              BidirectionalReverseIterator<iterator>               reverse_iterator;
        range(int from, int to): m_from{from}, m_to{to} {}
        range(int to): range(0, to) {}
        int size() const {
            return (this->m_to - this->m_from);
        }
        iterator begin() const {
            return {this->m_from};
        }
        iterator end() const {
            return {this->m_to};
        }
        reverse_iterator rbegin() const {
            return {iterator(this->m_to - 1)};
        }
        reverse_iterator rend() const {
            return {iterator(this->m_from - 1)};
        }
    private:
        int m_from;
        int m_to;
};

class rand_range {
    public:
        class iterator {
            public:
                typedef             const int             value_type;
                iterator(const rand_range* ptr, int cur): p{ptr}, cur_count{cur} {}
                value_type& operator*() {
                    this->cur = p->r.randint(p->m_from, p->m_to);
                    return this->cur;
                }
                iterator& operator++() {
                    ++(this->cur_count);
                    return *this;
                }
                iterator operator++(int) {
                    iterator tmp{*this};
                    ++(this->cur_count);
                    return tmp;
                }
                iterator& operator--() {
                    --(this->cur_count);
                    return *this;
                }
                iterator operator--(int) {
                    iterator tmp{*this};
                    --(this->cur_count);
                    return tmp;
                }
                bool operator==(const iterator& rhs) {
                    return (this->cur_count == rhs.cur_count);
                }
                bool operator!=(const iterator& rhs) {
                    return (this->cur_count != rhs.cur_count);
                }
            private:
                int cur{};
                const rand_range* p;
                int cur_count{};
        };
        typedef                                                      int             value_type;
        typedef                   BidirectionalReverseIterator<iterator>             reverse_iterator;
        rand_range(int from, int to, int count): m_from{from}, m_to{to}, m_count{count} {}
        constexpr int size() const {
            return this->m_count;
        }
        iterator begin() const {
            return {this, 0};
        }
        iterator end() const {
            return {this, m_count};
        }
        reverse_iterator rbegin() const {
            return {iterator{this, m_count}};
        }
        reverse_iterator rend() const {
            return {iterator{this, 0}};
        }
        
    private:
        int m_from;
        int m_to;
        int m_count;
        inline static rng r{};
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