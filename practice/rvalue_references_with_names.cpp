/*
 * If an rvalue is assigned a name, it's treated by the compiler as if it
 * were an lvalue i.e., if it's used to initialize a class object then
 * the copy constructor will be called rather that the move constructor
 * and similarly if it is assigned to some other class object the copy
 * assignment operator will be called rather than the move assignment
 * operator.
 */
#include <iostream>
#include "person.h"

void fun(Person& p);
void fun(const Person& p);
void fun(Person&& p);

int main(void)
{
    Person me{"Piyush Singh", "Student", 27};
    fun(me);
    std::cout << '\n';
    fun(Person{"Piyush Singh", "Student", 27});

    Person&& tmp = Person{"Temp", "NA", 0};
    fun(tmp);  // Calls fun(&) because named rvalues are treated as lvalues
    std::cout << '\n';
    // If we want fun(&&) to be called, we can wrap tmp in std::move
    fun(std::move(tmp));

    // Copy constructor invoked
    Person copy_tmp{tmp};

    return 0;
}

void fun(Person& p){
    std::cout << "fun(&) called with " << p << '\n';
}

void fun(const Person& p){
    std::cout << "const fun(&) called with " << p << '\n';
}

void fun(Person&& p){
    std::cout << "fun(&&) called with " << p << '\n';
    Person copy{p};  // copy constructor will be used
    Person tmp;
    tmp = p;  // copy assignment operator will be called
    std::cout << "fun(&&) end...\n\n";
}