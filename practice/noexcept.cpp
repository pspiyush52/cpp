/*
 * The noexcept specifier is a way to specify that we don't want
 * exceptions to propagate out of a given function.
 * This means that if an exception is thrown in the body of a function,
 * then it cannot propagate out of the function and if it is not handled
 * in the function then we will not be able to handle it from the calling
 * scope of the function.
 * 
 * In other words it specifies that a function cannot throw any
 * exceptions. If we allow any exception to remain unhandled inside the
 * function then the program will terminate as the function will not
 * throw the exception.
 */
#include <iostream>
#include "noexcept.h"

void fun() noexcept;
int main(void)
{
    /*
     * The exception thrown in fun() cannot propagate to main so we can't
     * catch it here in this try-catch block.
     */
    try{
        // fun();
    }catch(...){
        std::cout << "Something went wrong.\n";
    }

    try{
        ex::NoExcept obj;
        /*
         * Same applies to class methods too. If a method has a noexcept
         * specifier then it is not allowed to throw exceptions and if it
         * does then std::terminate is called immediately.
         */
        obj.some_method();
    }
    catch(int ex){
        std::cout << "Exception occurred at line " << __LINE__ << '\n';
    }

    return 0;
}

void do_something(){
    throw "Something is wrong.";
}

// This function is not allowed to throw exceptions so if any exception
// occurs inside it, the program will terminate immediately.
void fun() noexcept {
    std::cout << "Calling do_something()\n";
    do_something();
}