module;

// Global Module Fragment
// All preprocessor directives must show up here
#include <iostream>
#include <string>

export module my_module;  // Module declaration

// Module Preamble

// Module Purview
export void say_hello(const char* name){
    std::cout << "Hello " << name << " from my module.\n";
}