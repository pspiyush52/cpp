#ifndef __PRINT_H
#define __PRINT_H

#include <iostream>

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
void print(const arg& first, const args&... rest){
    std::cout << first << ' ';
    print(rest...);
}

#endif  // __PRINT_H
