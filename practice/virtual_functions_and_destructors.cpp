/*
 * If we call a virtual function from a constructor or a destructor the most
 * specific overridden method will not be called which is what we usually
 * expect in polymorphism.
 * 
 * This happens because when the constructor is called for the derived class,
 * it first constructs the base part and then the derived part.
 * If a virtual method is being called in the base constructor then since the
 * derived part hasn't been constructed yet we cannot call the most specific
 * method which is the derived class method. This is the reason due to which
 * the call to a virtual method from a constructor gives static binding
 * results.
 * 
 * Same goes for destructors, when a derived object is destroyed the derived
 * part is destroyed first and then the base part. So after the derived part
 * has been destroyed the virtual method which was overridden in the derived
 * class will cease to exist which is why if we call a virtual method inside a
 * destructor we will not be able to call the most specific method and the
 * call will be resolved using static binding.
 * 
 * Due to the above reasons we should refrain from calling virtual methods
 * from inside constructors or destructors.
 */
#include "utils.h"
class base {
    public:
        base(){
            cout << "base constructor\n";
            this->print();
        }
        virtual void print(){
            cout << "base::print\n";
        }
        ~base(){
            cout << "base destructor\n";
            this->print();
        }
};
class derived : public base {
    public:
        derived(){
            cout << "derived constructor\n";
            this->print();
        }
        void print(){
            cout << "derived::print\n";
        }
        ~derived(){
            cout << "derived destructor\n";
            this->print();
        }
};

int main(void)
{
    base* b = new derived;
    delete b;

    return 0;
}