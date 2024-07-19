#include <iostream>
#include <string>

/*
    Anonymous namespace is limited to the current Translation Unit only.
    Behind the scenes, the compiler assigns a random name to the anonymous
    namespace. Which is why the namespace can be used in the current
    Translation Unit only.
    
    So the declaration and definition of functions/classes in the anonymous
    namespace cannot be split apart in different files.
*/

namespace {
    void say_hello(const std::string& name);
}

int main(void)
{
    /*
        Items of anonymous namespaces can be accessed directly without using
        the scope resolution operator :: in the same translation unit where
        the item is declared and defined.
    */
    say_hello("Piyush");
    return 0;
}

namespace {
    void say_hello(const std::string& name){
        std::cout << "Hello there " << name << '\n';
    }
}