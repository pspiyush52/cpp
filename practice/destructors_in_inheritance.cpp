#include "utils.h"

struct base{
    base(){ std::cout << "base constructor called...\n";}
    ~base(){ std::cout << "base destructor called...\n"; }
};
struct level_1 : public base{
    level_1(){ std::cout << "level_1 constructor called...\n";}
    ~level_1(){ std::cout << "level_1 destructor called...\n"; }
};
struct level_2 : public level_1{
    level_2(){ std::cout << "level_2 constructor called...\n";}
    ~level_2(){ std::cout << "level_2 destructor called...\n"; }
};
struct level_3 : public level_2{
    level_3(){ std::cout << "level_3 constructor called...\n";}
    ~level_3(){ std::cout << "level_3 destructor called...\n"; }
};

int main(void)
{   
    level_3 obj;
    sep; 
    return 0;
}