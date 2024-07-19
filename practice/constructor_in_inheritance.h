#ifndef __CONST_IN_INHERITANCE_H
#define __CONST_IN_INHERITANCE_H

#include <iostream>

struct base{
    base(){ std::cout << "base constructor called...\n";}
};
struct level_1 : public base{
    level_1(){ std::cout << "level_1 constructor called...\n";}
};
struct level_2 : public level_1{
    level_2(){ std::cout << "level_2 constructor called...\n";}
};
struct level_3 : public level_2{
    level_3(){ std::cout << "level_3 constructor called...\n";}
};

#endif  //__CONST_IN_INHERITANCE_H