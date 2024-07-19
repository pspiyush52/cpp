#include <iostream>
/*
    The const variable DISTANCE has internal linkage meaning that it is
    visible in the translation unit where it is defined. If we try to declare
    it in another translation unit, we will be creating a completely separate
    new definition.
*/
const double DISTANCE{22.458};

// Specifying that global_var is a variable defined in some other file
extern int global_var;  // Declaration of a variable defined in some other
                        // translation unit.

/*
    The constant global variable which is defined in some other file has to be
    declared as follows to be usable in the current file.
*/
extern const double SOME_CONSTANT;  // declaration

static void func();

namespace cur{
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
    Functions by default have external linkage which means that they can be
    accessed from TU other than the one where they are defined. To restrict
    this and make a function have internal linkage we can prefix the function
    with the static keyword.
    Now if this function is called from another TU, it will result in a linker
    error.
*/
static void func(){
    std::cout << "static void func()\n";
}
/*
    If we remove the definition of func() from this file and remove the static
    keyword from the func() declaration above then the func() defined in
    main.cppp will be used inside call_func().
*/

/*
    Another method is to wrap the said function in an anonymous namespace and
    this will limit the access of the function to the current TU and it will
    not be accessible from any other TU.

    namespace {
        void func(){
            std::cout << "static void func()\n";
        }
    }
*/