#ifndef __UTIL1_H
#define __UTIL1_H

#include <iostream>

/*
    If we define a non-inline variable here then we will get a multiple
    definition linker error as the definition will show up in main.cpp as
    well as util2.cpp which will violate the ODR (One Definition Rule).
*/
inline int SHIFT{2147};

namespace util1{
    void print_shift();
    void print_distance();
}

#endif  // __UTIL1_H