/*
 * If we are managing a derived class object using a base class pointer then
 * we cannot use a non-polymorphic(non-virtual) function using the base class
 * pointer because the base class has no knowledge of the non-virtual derived
 * class methods.
 * 
 * We can however, transform the base pointer/reference to a derived class
 * pointer/reference at run time and then use it to access derived class
 * methods using dynamic cast. This makes it possible to call non polymorphic
 * methods.
 */
#include <iostream>
#include "utils.h"

class base {
    public:
        virtual void do_nothing(){}
        void print(){
            std::cout << "base::print\n";
        }
        virtual ~base(){}
};

class one : public base {
    public:
        void do_nothing(){}
        void print(){
            std::cout << "one::print\n";
        }
        void show() {
            std::cout << "one::show\n";
        }
};

class two : public one {
    public:
        two() = delete;
        explicit two(int x) : _two(x){}
        void do_nothing(){}
        void print(){
            std::cout << "two::print " << _two << '\n';
        }
    protected:
        int _two;
};

int main(void)
{
    base* bptr = new two{9};
    bptr->print();
    (dynamic_cast<two*>(bptr))->print();
    (dynamic_cast<two*>(bptr))->show();
    delete bptr;
    fmt::line();

    two t{12};
    base& bref{t};
    bref.print();
    (dynamic_cast<two&>(bref)).print();
    fmt::line();

    two& tref{dynamic_cast<two&>(bref)};
    tref.print();
    fmt::line();

    bptr = new one;
    bptr->print();
    (dynamic_cast<one*>(bptr))->print();
    /*
     * We cannot cast the base pointer to two* since bptr is pointing to a one
     * object and to convert it into a two* would require additional
     * information for the two object which is the parameter of the
     * constructor of class two.
     * 
     * When the dynamic cast fails it returns a nullptr so we can use it to
     * check if the cast succeeded or not.
     * No nullptr is returned in case of dynamic casting with references.
     */
    two* tp = dynamic_cast<two*>(bptr);
    if (!tp)
        std::cout << "Cast failed\n";
    else
        tp->print();
    
    delete bptr;

    return 0;
}