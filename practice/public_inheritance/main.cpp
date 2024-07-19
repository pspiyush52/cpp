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
     * Accessible since public members of the base class are accessible in the
     * public scope of the derived class.
     */
    std::cout << "D.b_public: " << D.b_public << '\n';
    // std::cout << D.d_protected;  // not allowed since for objects protected
    // and private behave the same
    std::cout << "D.d_public: " << D.d_public << '\n';
    // std::cout << D.b_protected; // cannot be accessed here but from inside derived class
    sep;
    D.print_base_info(); // protected member accessed from inside a member function
    sep;
    std::cout << "D.Base.b_public: " << D.get_public() << '\n';
    std::cout << "D.Base.b_protected: " << D.get_protected() << '\n';
    std::cout << "D.Base.b_private: " << D.get_private() << '\n';
    sep;

    return 0;
}