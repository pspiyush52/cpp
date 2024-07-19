#ifndef __TMPSPEC_H
#define __TMPSPEC_H

#include <cstring>

template<typename T>
class Adder{
    public:
        T add(T a, T b);
};

template<typename T>
T Adder<T>::add(T a, T b){ return a + b; }

template<>
inline char* Adder<char*>::add(char* lhs, char* rhs){
    return std::strcat(lhs, rhs);
}

#endif  // __TMPSPEC_H