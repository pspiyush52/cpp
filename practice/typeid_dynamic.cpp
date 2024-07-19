/*
 * The typeid operator is used when the dynamic type of a polymorphic object
 * must be known or for static type identification.
 * <typeinfo> header must be included before using typeid or the program is
 * ill-formed.
 */
#include "utils.h"
#include <typeinfo>

class base {
    public: virtual void print() { std::cout << "base\n"; }
};
class derived : public base {
    public: void print() { std::cout << "derived\n"; }
};

void fun(base* ptr);

int main(void)
{
    fmt::line('-');
    base b; derived d;
    base* bptr = &b;
    std::cout << "typeid(*bptr): " << typeid(*bptr).name() << '\n';
    fun(bptr);
    bptr = &d;
    // When the expression inside the parantheses is a polymorphic type(i.e.,
    // a class that declares or inherits at least one virtual function), the
    // typeid operator gives us the dynamic type of the expression.
    // Now since the hierarchy is polymorphic(virtual functions involved), if
    // the base pointer stores the address of a derived object then using
    // typeid will give us the derived type and not the base type.
    std::cout << "\ntypeid(*bptr): " << typeid(*bptr).name() << '\n';
    fun(bptr);
    fmt::line('-');
    
    return 0;
}

void fun(base* ptr){
    const std::type_info& ptr_info = typeid(*ptr);
    std::cout << "fun(bptr):\n\t";
    if (ptr_info == typeid(base))
        std::cout << "The pointer stores the address of a base class object.\n";
    else
        std::cout << "The pointer stores the address of a derived class object.\n";
}