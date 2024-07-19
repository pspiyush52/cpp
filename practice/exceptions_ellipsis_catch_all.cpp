/*
 * The catch clause with ellipsis as the parameter can catch any type of
 * exception.
 */
#include "excepts_poly.h"
#include "utils.h"

void fun(size_t);
int main(int argc, char* argv[])
{
    for (size_t i{}; i < 15; i++)
        try{
            fun(i);
        }
        catch(ExceptionBase& ex){
            show_ex(ex, argv[0]);
        }
        catch(...){
            std::cout << "Something else went wrong.\n";
        }
    
    fmt::line();
    return 0;
}

void fun(size_t i){
    fmt::line();
    size_t n = i % 10;
    switch(n)
    {
        case 1:
            throw 1;
        case 3:
            throw 0;
        case 6:
            throw "Not Allowed.";
        case 2:
            throw CriticalError{"Multiple of 3", __LINE__};
        case 8:
            throw Warning{"Undefined behavior", __LINE__};
        default:
            printf("Iteration #%llu\n", i);
    }
}