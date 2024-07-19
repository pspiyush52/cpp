const char* note = R"(
/*
 * When a virtual method of the base class which is overridden in the derived
 * class has default arguments in both the base and derived classes and a base
 * pointer is used to access the overridden method the most specific method
 * will be called depending on the type of the object the base pointer is
 * pointing to but the default argument used in the function call will not be
 * the default argument specified in that function but rather the default
 * argument specified in the base class definition of the virtual function.
 * 
 * This is because the default arguments are handled at compile time whereas
 * the virtual functions are called at run time with polymorphism.
 * Static binding is used to decide which argument will be passed to the
 * function.
 */
)";
#include <iostream>
#include "utils.h"

class Base {
    public:
        virtual void show_num(int num = 15){
            std::cout << "Base::show_num(): " << num << '\n';
        }
};
class Derived : public Base {
    public:
        void show_num(int num = 5) override {
            std::cout << "Derived::show_num(): " << num << '\n';
        }
};

int main(void)
{
    sep;
    std::cout << note;
    Base b; Derived d;
    std::cout << "\nBase method: \n\tvoid show_num(int num = 15);\n";
    std::cout << "\nDerived method: \n\tvoid show_num(int num = 5);\n";
    std::cout << "\nBase b; Derived d;\n\n";
    Base* ptr = &b;
    sep;
    std::cout << "\nCalling show_num() method using the Base pointer:\n";
    std::cout << "\n\tBase* ptr = &b;\n\tptr->show_num(): ";

    // Base::show_num() is called with the default arg in base i.e., 15
    ptr->show_num();

    ptr = &d;
    std::cout << "\n\tBase* ptr = &d;\n\tptr->show_num(): ";

    // Derived::show_num() is called with the default arg in base i.e., 15
    ptr->show_num(); newline;
    sep;

    // Calling show_num() directly will work as expected.
    std::cout << "\nCalling show_num() method directly using objects:\n";

    // Calls Base::show_num() with the default arg in Base i.e., 15
    std::cout << "\n\tb.show_num(): ";  b.show_num();
    // Calls Derived::show_num() with the default arg in Derived i.e., 5
    std::cout << "\n\td.show_num(): ";  d.show_num();
    newline; sep;
    
    return 0;
}