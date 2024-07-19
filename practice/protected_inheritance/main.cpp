#include "base.h"
#include "derived.h"
#define sep std::cout << "--------------------------------------------------------------------------------------------------------\n"

int main(void)
{
    sep;
    Base B{1, 0, 9};
    std::cout << "Base object B: " << B << '\n';

    Derived D{5, 4, 2};
    D.set_base(-12, 54, 13);
    std::cout << "Derived object D: " << D << '\n';
    sep;

    /* 
     * Inaccessible since public members of the base class are protected in
     * the derived class and cannot be accessed using objects of the class
     */
    // std::cout << "D.b_public: " << D.b_public << '\n';

    // std::cout << D.d_protected;  // not allowed since for objects protected
    // and private behave the same
    
    std::cout << "D.d_public: " << D.d_public << '\n';
    // std::cout << D.b_protected; // cannot be accessed here but from inside derived class
    sep;
    D.print_base_info(); // protected member accessed from inside a member function
    sep;
    /*
     * Not allowed since in protected inheritance the public members of the
     * base become protected in the derived class. And for objects of the
     * derived class, protected members behave the same as private members,
     * that is, they are inaccessible.
     *  
     *      std::cout << "D.Base.b_public: " << D.get_base_public() << '\n';
     *      std::cout << "D.Base.b_protected: " << D.get_base_protected() << '\n';
     *      std::cout << "D.Base.b_private: " << D.get_base_private() << '\n';
     */

    return 0;
}