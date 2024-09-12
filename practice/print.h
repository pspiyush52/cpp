#ifndef __PRINT_H
#define __PRINT_H

#include <iostream>
#include "tuples.h"

#ifndef repeatu
#define repeatu(N) for (unsigned int i = 0; i < N; ++i)
#endif

#ifndef repeats
#define repeats(N) for (size_t i = 0; i < N; ++i)
#endif

#ifndef repeat
#define repeat(N) for (int i = 0; i < N; ++i)
#endif

#ifndef repeat_from
#define repeat_from(from, to, i) for (i = from; i < to; ++i)
#endif

#ifndef repeat_with
#define repeat_with(N, i) for (i = 0; i < N; ++i)
#endif

template<typename Container>
class printer{
    public:
        printer(const Container& c) : __c(c){}
        friend std::ostream& operator<<(std::ostream& output, const printer& d){
            auto iter = std::begin(d.__c);
            auto last = std::end(d.__c);
            if (iter == last) {
                output << "[]";
                return output;
            }
            --last;
            output.put('[');
            for (; iter != last; ++iter)
                output << *iter << ", ";
            output << *iter;
            output.put(']');
            return output;
        }
        template<typename cont>
        cont& operator>>(cont& c){
            auto iter = std::cbegin(this->__c);
            auto end = std::cend(this->__c);
            auto citer = std::begin(c);
            auto cend = std::end(c);
            for (; (iter != end) && (citer != cend); ++iter, ++citer)
                *citer = *iter;
            return c;
        }
    private:
        const Container& __c;
};

void print(){ std::cout << std::endl; }

template<typename arg, typename... args>
void print(arg&& first, args&&... rest){
    std::cout << first << ' ';
    print(rest...);
}

template<typename Container>
class _CountIteratorPair {
    public:
        _CountIteratorPair(typename Container::const_iterator it): p{1, it} {}
        size_t count() {
            return p.getFirst();
        }
        const typename Container::value_type& value() {
            return (*(p.getSecond()));
        }
        void operator++() {
            ++(p.getFirst());
            ++(p.getSecond());
        }
        bool operator==(_CountIteratorPair& rhs) {
            return this->p.getSecond() == rhs.p.getSecond();
        }
        bool operator!=(_CountIteratorPair& rhs) {
            return this->p.getSecond() != rhs.p.getSecond();
        }

    private:
        Pair<size_t, typename Container::const_iterator> p;
};

template<typename Container>
class enumerate {
    public:
        class iterator {
            typedef _CountIteratorPair<Container> CountIteratorPair;
            public:
                iterator(Container::const_iterator iter): p(iter) {}
                CountIteratorPair& operator*() {
                    return this->p;
                }
                iterator& operator++() {
                    ++(this->p);
                    return *this;
                }
                bool operator==(iterator& rhs) {
                    return (this->p == rhs.p);
                }
                bool operator==(iterator&& rhs) {
                    return (this->p == rhs.p);
                }
                bool operator!=(iterator& rhs) {
                    return (this->p != rhs.p);
                }
                bool operator!=(iterator&& rhs) {
                    return (this->p != rhs.p);
                }

            private:
                CountIteratorPair p{};
        };
        
        enumerate(const Container& cont): c{cont} {}
        enumerate(Container&& cont): c{cont} {}
        iterator begin() {
            return {c.begin()};
        }
        iterator end() {
            return {c.end()};
        }

    private:
        const Container& c;
};


#endif  // __PRINT_H
