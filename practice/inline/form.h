#ifndef __FORM_H
#define __FORM_H

#include <iostream>

/*
    If the function is not marked inline then it will be defined in util1.cpp
    and util2.cpp and also in main.cpp if we include form.h there.
    This will result in a multiple definition linker error.
*/
inline void newline(){
    std::cout << '\n';
}

#endif  // __FORM_H