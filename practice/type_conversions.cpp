#include "a.h"
#include "b.h"
#include "utils.h"

void fun(const A& obj){}

int main(void)
{
    A a{4}; B b{9};
    sep;

    // a = b;
    /*
        In assignments the compiler follows the following priority order
            1. Copy Assignment operator
            2. Cast
            3. Constructor with argument of type B
    */
    fun(b);
    /*
        In passing objects as function arguments the compiler follows the
        following order
            1. Cast
            2. Constructor with argument of type B
            3. 
    */
    return 0;
}

// g++ type_conversions.cpp a.cpp b.cpp -o type_conversions.exe