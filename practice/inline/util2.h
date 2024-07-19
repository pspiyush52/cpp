#ifndef __UTIL2_H
#define __UTIL2_H

#include <iostream>

/*
    If we define a non-inline variable here then we will get a multiple
    definition linker error as the definition will show up in main.cpp as
    well as util2.cpp which will violate the ODR (One Definition Rule).
*/
inline double DISTANCE{67.82};

namespace util2{
    void print_distance();
    void print_shift();
}

#endif  // __UTIL2_H