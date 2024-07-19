#include "ex_cls.h"

void fun(){
    /*
     * When we throw an unnamed temporary class object the compiler optimizes
     * this and there are no copies made and we can reference this object
     * directly in our catch block.
     */
    // throw MyExcept("ERROR: This function cannot be called directly.");

    /*
     * When we throw a class object like below, the copy or move constructor
     * is called and the object is used to copy or move initialize an
     * exception object.
     * 
     * The exception object is a temporary object in unspecified storage that
     * is constructed by the throw expression.
     * The type of the expression object is same as the type of expression.
     * Unlike other temporary objects the exception object can be bound to a
     * reference.
     * 
     * The exception object persists until the last catch clause exits.
     */
    MyExcept mex{"ERROR: This function cannot be called directly."};
    throw mex;
}

int main(void)
{
    fmt::start();
    try{
        std::cout << "Trying to get the program to run...\n";
        // throw MyExcept("ERROR");
        fun();
        std::cout << "Program finished\n";
    }catch(MyExcept& ex){
        std::cout << "Exception caught in main(), what: " << ex.what() << '\n';
        std::cout << "Program finished with error(s).\n";
    }
    fmt::end();

    return 0;
}