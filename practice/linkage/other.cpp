#include <iostream>

const double DISTANCE{47.3};

/*
    The non-const global variable like the one below have external linkage
    which means that they can be accessed from any TU.

    Functions have external linkage by default as they can be defined in some
    TU and used in other TU's.
*/
int global_var{};

/*
    To declare a constant global variable which can be accessed from other
    files we have to prefix the definition of the global const with extern.
*/
extern const double SOME_CONSTANT{2.4187962};

void func();  // declaration

namespace other{
    void print_const(){
        std::cout << "distance : " << DISTANCE << ", at : " << &DISTANCE << '\n';
    }
    void print_global(){
        std::cout << "global_var : " << ++global_var << ", at : " << &global_var << '\n';
    }
    void print_extern_const(){
        std::cout << "SOME_CONSTANT : " << SOME_CONSTANT << ", at : " << &SOME_CONSTANT << '\n';
    }
    void call_func(){
        func();
    }
}

/*
    The above call to func() inside other::call_func() will call the func()
    defined in main.cpp and not the one defined in cur.cpp because the one
    defined in cur.cpp has internal linkage and can be used only in the same
    file i.e., cur.cpp so if we call func() from the current file the linker
    will look for the definition of a func() with external linkage in all the
    TU's.
*/