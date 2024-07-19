/*
 * If we have regular destructors in our class hierarchy and then use base
 * class pointers to manage dynamically allocated derived class objects then
 * when we use delete on the base pointer only the base destructor gets called
 * which is really bad because if any dynamic memory was allocated in any of
 * the derived classes it will be leaked.
 * 
 * This problem arises due to the fact that the call to the destructors is
 * resolved using static binding. The compiler only looks at the type of the
 * pointer and calls the destructor for that type.
 * 
 * To solve this problem we have to call our destructors using polymorphism by
 * marking them virtual. This will call the most specific destructor i.e., if
 * a base class pointer is managing a derived class object then using delete
 * on the pointer will call the destructor of the derived class which in turn
 * will call the destructor of the base class and so on.
 * This will release the allocated memory properly and prevent any leaks.
 * 
 * If a base class declares its destructor virtual, the derived destructor
 * always overrides it. This makes it possible to delete dynamically allocated
 * objects of polymorphic type through pointers to base.
 */
#include "utils.h"

class Base {
    public:
        virtual ~Base(){ std::cout << "Base destructor called.\n"; }
};

class One : public Base {
    public:
        ~One(){ std::cout << "One destructor called.\n"; }
};

class Two : public One {
    public:
        ~Two(){ std::cout << "Two destructor called.\n"; }
};

int main(void)
{
    // Two t;
    sep;
    Base* b = new Two;
    delete b;
    sep;
    return 0;
}