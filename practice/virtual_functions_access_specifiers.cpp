/*
 * When we call a virtual function through a base class pointer, the access
 * specifier in the base class determines the accessibility of the function,
 * regardless of the access specifier in the derived class.
 * 
 * The most specialized function will still be called when using virtual
 * functions but the accessibility will be determined by where the virtual
 * function is declared in the base class.
 * 
 * In other words, when a function call is made through dynamic binding, the
 * access specifier of the base class applies and if the function call is made
 * through static binding then the access specifier of the derived class
 * applies.
 */
#include <iostream>
class base{
    public:
        virtual void print(){
            std::cout << "base::print()\n";
        }
};
class derived : public base{
    private:
        void print(){
            std::cout << "derived::print()\n";
        }
};

int main(void)
{
    derived d;
    derived* dptr = &d;
    base* bptr = &d;
    /*
     * Results in a compiler error since the access specifier for the print()
     * method in the derived class is private so it cannot be accessed using a
     * derived class pointer.
     * 
     *      dptr->print();
     *      d.print()  // cannot be used either since derived::print() is
     *                 // private in derived (Static Binding).
     */
    /*
     * However, when we try to access the print() method using a base pointer
     * the base pointer can access the print() method of the derived class but
     * with an access specifier of public since the print() method is defined
     * in the public scope in the base class.
     * 
     * So calling print() using the base pointer which stores the address of a
     * derived class object calls the derived::print() succesfully since the
     * access specifier is public when accessing using base class pointers.
     * 
     * The more specialized function is being called due to runtime
     * polymorphism but with the level of accessibility which is determined by
     * the access specifier of print() method in the base class.
     */
    bptr->print();

    return 0;
}