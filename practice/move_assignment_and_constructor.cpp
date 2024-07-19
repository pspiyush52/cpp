#include"person.h"
#include "utils.h"
#define spacing newline;fmt::line();newline

Person make_person(const char* name, const char* profession, unsigned int age){
    return Person{name, profession, age};
}

namespace rv{
    void fun(Person&& p){
        std::cout << "fun(Person&&) called with " << p << '\n';
    }
}

namespace lv{
    void fun(Person p){
        std::cout << "fun(Person) called with " << p << '\n';
    }
}

int main(void)
{
    fmt::start(); newline;
    Person me{"Piyush Singh", "Student", 27};
    std::cout << me << '\n';
    spacing;
    
    Person she;
    // Copying from a temporary object, will invoke the move assignment
    // operator
    she = Person{"Niharika Joshi", "HR Consultant", 31};
    spacing;

    // The function returns an rvalue so the move assignment operator
    // will be called
    she = make_person("Niharika Joshi", "HR Consultant", 31);
    std::cout << she << '\n';
    spacing;

    /*
     * Copy/Move constructors are bypassed due to copy/move elision while
     * initializing a class object with a temporary object. This is an
     * internal optimization where the object is directly created in the
     * location where it would otherwise be moved to.
     * 
     * Here the make_person will return a temporary object and then the
     * object will be moved to the location of the newly created object
     * _friend.
     * Instead of moving the created object, the compiler bypasses the
     * move constructor and the object is directly created in the memory
     * location of _friend. This is referred to as copy/move elision.
     */
    // 
    Person _friend = make_person("Pranjai Bhatt", "Architect Sometimes", 27);
    std::cout << _friend << '\n';
    spacing;

    rv::fun(Person{"Temporary", "NA", 0}); spacing;
    /*
     * Copy constructor is elided since we are passing a temporary object
     * by value. The local Person object in fun() will have to be created
     * and if we were passing an lvalue, it would have been created using
     * the copy constructor. But since we are passing a temporary object
     * the copy constructor will be elided and the temporary object we
     * are creating here will be directly created where the local object
     * is required in fun().
     */
    lv::fun(Person{"Temporary", "NA", 0}); spacing;

    /*
     * std::move does not move data, it just casts its parameter to an
     * rvalue so it can be passed to functions with rvalue reference
     * parameters.
     * 
     * This is the reason why when we create class objects using other
     * objects wrapped in std::move we invoke the move constructor since
     * the parameter of a move constructor is an rvalue reference to a
     * class object.
     * 
     * Also when we want to move data from one object to the other we use
     * the move assignment operator(again which has an rvalue reference
     * as its parameter) and wrap the source object in std::move to cast
     * it to an rvalue reference so that the move assignment operator is
     * called and not the copy assignment operator.
     */
    rv::fun(std::move(_friend));
    std::cout << "After call to fun() " << _friend << '\n';
    spacing;

    lv::fun(std::move(_friend));
    std::cout << "After call to fun() " << _friend << '\n';
    newline;
    fmt::end();
    
    return 0;
}