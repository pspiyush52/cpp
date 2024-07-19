#ifndef __STR_HELPERS_H
#define __STR_HELPERS_H

namespace hlp{
    struct tautology{
        template<typename T>
        bool operator()(T&& item){ return true; }

        template<typename T>
        bool operator()(const T& item){ return true; }
    };

    struct swapper{
        template<typename T>
        void operator()(T& __x, T& __y){
            T tmp = std::move(__x);
            __x = std::move(__y);
            __y = std::move(tmp);
        }
    };
    template<typename T>
    void swap(T& __x, T& __y){
        T tmp = std::move(__x);
        __x = std::move(__y);
        __y = std::move(tmp);
    }
}

#endif  // __STR_HELPERS_H