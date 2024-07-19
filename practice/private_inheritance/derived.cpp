#include "derived.h"

Derived::Derived(int x) : d_public(x), d_protected(x), d_private(x), Base{x}{}
Derived::Derived(int x, int y, int z) : d_public(x), d_protected(y), d_private(z), Base{y, z, x}{}

void Derived::print_base_info() const {
    std::cout << "b_public: " << this->b_public << '\n';
    std::cout << "b_protected: " << this->b_protected << '\n';
    /*
     * In private inheritance the public and protected members of the base
     * class are private in the derived class.
     * The private members of the base class are inaccessible in the derived
     * class.
     * 
     * When another class derives from the derived class it will not have
     * access to any member of the base class. So, in a way private
     * inheritance stops further inheritance of the base class members down
     * the line.
     * The derived class inherits from the base class and keeps all
     * the inherited members to itself and does not allow them to be inherited
     * further down the line
     * 
     * Objects of the derived class cannot access the public members of the
     * base class but they are still accessible from inside the derived class
     * like the other private members of the derived class.
     * 
     * Public members of the base class can be accessed by the objects of the
     * base class but not by objects of the derived class.
     */

    // std::cout << "b_private: " << this->b_private; // private member of base class
    std::cout << "b_private: " << this->get_base_private() << '\n';
}

void Derived::set_base(int x, int y, int z){
    b_public = x;  // allowed because public members of base class become
    // protected in derived class
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