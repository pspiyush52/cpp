/*
 * If an exception occurs in the program and it is not handled then the
 * program is terminated by calling std::terminate which in turn calls
 * std::abort() to kill the program.
 * 
 * We can set our own custom terminate function which will be called when
 * an unhandled exception occurs in our program using std::set_terminate
 * which takes in a pointer to a function which takes no arguments and
 * returns void.
 * 
 * It can also take a lambda function directly as its argument.
 * 
 * The pointer to a function which takes no arguments and returns void is
 * given an alias std::terminate_handler using a typedef statement,
 * 
 *      typedef void (*std::terminate_handler)();
 */
#include <iostream>
#include <typeinfo>
#include <exception>
#include "excepts_poly.h"

void custom_terminate();

int main(int argc, char* argv[])
{
    typedef void (*void_fun)();
    void_fun vf = &custom_terminate;
    /*
     * std::terminate_handler is a pointer to function type which takes no
     * arguments and returns void.
     * It is defined as,
     * 
     *      typedef void (*std::terminate_handler)();
     */
    std::terminate_handler th = &custom_terminate;

    // Using a lambda function
    // std::set_terminate([](){
    //     std::cout << "Terminate: Program crashed due to unhandled exception.\n";
    //     std::abort();
    // });

    // Using a function pointer
    std::set_terminate(th);
    
    std::cout << "Running main...\n";
    try{
        throw CriticalError{"Insufficient memory.", __LINE__};
    }
    catch(ExceptionBase& ex){
        show_ex(ex, argv[0]);
        if (typeid(ex) == typeid(CriticalError))
            throw ex;
    }

    return 0;
}

void custom_terminate(){
    std::cout << "Terminate: Program crashed due to unhandled exception.\n";
    std::abort();
}