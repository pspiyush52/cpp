/*
 * The typeid operator is used when the dynamic type of a polymorphic object
 * must be known or for static type identification.
 * <typeinfo> header must be included before using typeid or the program is
 * ill-formed.
 */
#include <iostream>
#include <typeinfo>

class base {
    public: void print() { std::cout << "base\n"; }
};
class derived : public base {
    public: void print() { std::cout << "derived\n"; }
};

int main(void)
{
    auto z{0};
    if (typeid(z) == typeid(int))
        std::cout << "z is an int.\n";

    // The typeid operator refers to a std::type_info object representing the
    // type of the expression in parantheses.
    // We can store a reference to the std::type_info object and use it later
    // to compare with other std::type_info references
    const std::type_info& z_info = typeid(z + 1.0);
    
    // The name method returns the type name
    std::cout << z_info.name() << '\n';

    if (z_info == typeid(int))
        std::cout << "(z + 1.0) results in an int.\n";
    else if (z_info == typeid(double))
        std::cout << "(z + 1.0) results in a double.\n";
    
    base b; derived d;
    base* bptr = &b;
    std::cout << "\ntypeid(*bptr): " << typeid(*bptr).name() << '\n';
    bptr = &d;
    // Since the class hierarchy is non-polymorphic, the typeid operator gives
    // us the static type of the expression inside the parantheses.
    std::cout << "\ntypeid(*bptr): " << typeid(*bptr).name() << '\n';
    
    return 0;
}