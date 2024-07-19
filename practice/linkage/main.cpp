#include <iostream>
#include "other.h"
#include "cur.h"
/*
    Linkage is a property associated with a name which determines how wide or
    narrow is the visibility of the name across translation units.

    The age variable defined in the function below has no linkage because it
    is not accessible anywhere in the global scope of the file where it is
    defined or any other translation unit.
*/
void fun(){
    int age{26};  std::cout << "age : " << age << '\n';
}

void func(){
    std::cout << "main func()\n";
}

int main(void)
{
    // will print the DISTANCE const variable from the current TU
    cur::print_const();

    // will print the DISTANCE const variable from the 'other' TU
    other::print_const();

    std::cout << '\n';

    // will print the global_var defined in other.cpp
    other::print_global();

    // will print the same global_var defined in other.cpp
    cur::print_global();

    extern int global_var;
    std::cout << "global_var : " << global_var << ", at : " << &global_var << '\n';
    std::cout << "\nprint_global() has been called " << global_var << " times.\n\n";
    
    // will calll the func() with internal linkage defined in cur.cpp
    cur::call_func();

    // will call the func() with external linkage defined in main.cpp
    other::call_func();

    std::cout << '\n';

    // will print the global constant defined in other.cpp
    other::print_extern_const();

    // will print the same global constant defined in other.cpp
    cur::print_extern_const();

    return 0;
}