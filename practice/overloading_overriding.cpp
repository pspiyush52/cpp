#include <iostream>
class base {
    public:
        void fun(){ std::cout << "Base fun() called.\n"; }
        void fun(const char* str){
            std::cout << "Base fun(const char*) called with \"" << str << "\".\n";
        }
        void fun(const char* str, size_t num){
            std::cout << "Base fun(const char*, size_t) called with \"" << str
            << "\", " << num << ".\n";
        }
    protected:
        int base_var{};
};
class derived : public base {
    public:
        /*
         * If we override any base class methods which are overloaded in the
         * base class then all the base class overloads are hidden in the
         * derived class and only the ones defined in the derived class can
         * be accessed from within it.
         */
        void fun(){ std::cout << "Derived fun() called.\n"; }
};
int main(void)
{
    derived d;

    // Derived class has a fun() method which hides all the overloads from the
    // base class.
    d.fun();
    // d.fun("there", 24);  // does not work

    base* b{&d};
    b->fun("asdas");
    b->fun();

    return 0;
}