#include <iostream>
#include "utils.h"
/*
    If we have a shared pointer for each Person object in our program then if
    two Person objects are friends then when the SP's of both of them go out
    of scope then the objects should be destroyed, but in this case the other
    Person object which is a friend of the current object also has a shared
    pointer pointing to the current object so the reference count of the SP of
    current object will not go to zero and so the current object will not be
    released from memory. Same will apply for the other person object, it will
    not be released from the memory as well.

    This is a cyclic dependency problem and can be solved using weak pointers.
    Since using a weak pointer will not change the reference count of the SP's
    so there will no longer be a cyclic dependency problem and the objects
    will be properly released from memory.
*/
class Person{
    public:
        explicit Person(const char* name);
        explicit Person(const std::string& name);
        void add_friend(s_ptr<Person> P);
        ~Person();
        friend std::ostream& operator<<(std::ostream& output, const Person& P);
    private:
        std::string* name;
        // s_ptr<Person> _friend; // creates a cyclic dependency
        w_ptr<Person> _friend;
};

int main(void)
{
    s_ptr<Person> her = std::make_shared<Person>("Niharika");
    s_ptr<Person> me = std::make_shared<Person>("Piyush"); sep;

    // Creating a cyclic dependency
    her->add_friend(me);
    me->add_friend(her);

    std::cout << *her << '\n';
    std::cout << *me << '\n';
    sep;

    // The destructors will not be called for the two objects if they use SP

    // Destructors will be called if they use weak pointers

    return 0;
}

Person::Person(const char* Name):
    name(new std::string{Name}){
        std::cout << "Person " << Name << " created at " << this << '\n';
    }


Person::Person(const std::string& Name):
    Person(Name.c_str()){}

Person::~Person(){
    std::cout << "Person " << *name << " destroyed at " << this << '\n';
    delete name;
}

void Person::add_friend(s_ptr<Person> P){
    _friend = P;
}

std::ostream& operator<<(std::ostream& output, const Person& P){
    s_ptr f = P._friend.lock();
    output << "Person [name: \"" << *(P.name) << "\", friend: \"";
    if (f)
        output << *(f->name) << "\"]";
    else
        output << "none\"]";
    return output;
}