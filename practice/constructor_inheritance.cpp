#include <iostream>
#include "utils.h"

class base{
    public:
        base() { std::cout << "base default constructor...\n"; }
        base(int X, int Y) : b_x(X), b_y(Y) {}
        base(int x_y) : b_x(x_y), b_y(x_y) {}
        void print() const { std::cout << "b_x: " << b_x << ", b_y: " << b_y; }
    
    protected:
        int b_x{};
        int b_y{};
};
class derived : public base{
    public:
        /*
         * Inheriting the base constructor. All the constructors from the base
         * class will be inherited by this class except for copy constructors,
         * they cannot be inherited.
         * In this case both the single and the double param constructors will
         * be inherited.
         * 
         * The constructors will be inherited with a level of access which
         * will depend on the access specifier under which the using statement
         * appears.
         */
        using base::base;
        derived(int b_x, int b_y, int protected_data) : base{b_x, b_y}, d_protected(protected_data){}
        int get() const { return d_protected; }
    
    protected:
        int d_protected{12};
};
class derived2 : public derived{
    public:
        using derived::derived;
        /*
         * Inheriting all the constructors from the derived class which will
         * include the constructors of the base class as well.
         * One constructor of the derived class has the same signature as the
         * constructor of this class, so the one which is closer will be
         * chosen while creating objects of the derived2 class.
         */
        derived2(int b_x, int b_y, int derived_num) : derived(b_x, b_y), d2_data(derived_num){}
        derived2(int b_x, int b_y, int d_protected, int derived2_data):
            derived{b_x, b_y, d_protected}, d2_data{derived2_data}{}
        void print(){ std::cout << d_protected; }
        int d2_data;
};

int main(void)
{
    /*
     * Objects of class derived can be constructed using any one out of the
     * four constructors with the following signatures:
     * 
     *      1. (void)                     // base class constructor
     *      2. (int, int)                 // base class constructor
     *      3. (int)                      // base class constructor
     *      4. (int, int, int)            // derived class constructor
     */
    derived D1{12, 25}, D2{78}, e;
    D1.print(); newline;
    sep;
    D2.print(); newline;
    sep;

    /*
     * Objects of derived2 class can be constructed using any one out of five
     * constructors with the following signatures:
     * 
     *      1. (void)                      // base class constructor
     *      2. (int, int)                  // base class constructor
     *      3. (int)                       // base class constructor
     *      4. (int, int, int)             // derived2 class constructor
     *      5. (int, int, int, int)        // derived2 class constructor
     * 
     * In 4 above, the constructor from the class derived will not be used
     * even when it has the exact same signature since the derived2 class
     * constructor is the one closest for derived2 objects.
     */
    derived2 d{1, 2, 4, 29}, p;
    d.print();
    return 0;
}