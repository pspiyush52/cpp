#include "derived.h"

Derived::Derived(int x) : d_public(x), d_protected(x), d_private(x), Base{x}{}
Derived::Derived(int x, int y, int z) : d_public(x), d_protected(y), d_private(z), Base{y, z, x}{}

void Derived::print_base_info() const {
    std::cout << "b_public: " << this->b_public << '\n';
    std::cout << "b_protected: " << this->b_protected << '\n';
    /*
     * The protected members of the Base class are protected in the Derived
     * class and they can be accessed from within the Derived class.
     * The private members of the Base class are private in context of the
     * derived class so b_private cannot be accessed here.
     * 
     * So making any member protected ensures that any classes derived from
     * the current class using the public base class access specifier can
     * access that member. If we do not want a member to be accessed by any
     * derived class we make it private in the base class.
     * 
     * Public members can be accessed anywhere, by derived classes and by
     * objects of the base as well as the derived classes.
     */

    // std::cout << "b_private: " << this->b_private; // private member of base class
    std::cout << "b_private: " << this->get_private() << '\n';
}

void Derived::set_base(int x, int y, int z){
    b_public = x;
    b_protected = y;
    // b_private = z; // not allowed
    
    // set_private() is a protected setter so can be accessed from inside a
    // member function of the Derived class.
    set_private(z);
}

std::ostream& operator<<(std::ostream& output, const Derived& obj){
    output << "Derived[" << obj.d_public << ", " << obj.d_protected
    << ", " << obj.d_private << ']';
    return output;
}