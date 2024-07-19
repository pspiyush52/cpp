/*
 * We can use polymorphism to avoid writing catch clauses for each type of
 * exception in our exception classes hierarchy.
 * For example, we can declare the what() method in the base class as virtual
 * so that every deriving exception class can override it and have its own
 * version of the what() method which can be desirable since the every
 * exception may need a different description.
 * 
 * We can do this by using a reference to the base exception class as the
 * parameter of a single catch clause and since the what() method is virtual,
 * whenever we call the what() method on the base reference the most specific
 * what() method will be called according to the type of the exception object
 * the base reference refers to.
 */
#include "excepts_poly.h"

void do_something();
int main(void)
{
    fmt::start('-', 127);
    try{
        throw SmallError{"Main function failed to execute.", __LINE__};
    }catch(ExceptionBase& ex){    // A single catch clause is enough to deal
        show_ex(ex, __FILE__);     // any exceptions in the entire hierarchy.
    }
    
    try{
        std::cout << "Retrying...\n";
        throw CriticalError{"Memory address corrupted.", __LINE__};
    }
    catch(ExceptionBase& ex){
        show_ex(ex, __FILE__);
    }
    fmt::line();
    do_something();
    fmt::end('-', 127);
    
    return 0;
}

void fun(size_t);
void do_something(){
    for (size_t i{}; i < 10; i++)
    {
        try{
            fun(i);
        }catch(ExceptionBase& ex){
            show_ex(ex, __FILE__);
            newline;
        }
    }
}

void fun(size_t num){
    switch(num)
    {
        case 0:
            throw Warning{"Passing 0 will give indeterminate results.", __LINE__};
        case 1:
        case 7:
        case 9:
            std::cout << "Iteration #" << num << '\n';
            break;
        case 3:
            throw CriticalError{"Uninitialized memory access.", __LINE__};
        case 5:
            throw ExceptionBase{"Multiples of 5.", __LINE__};
        default:
            throw SmallError{"Even Numbers not allowed", __LINE__};
    }
}