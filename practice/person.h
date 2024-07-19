#ifndef __PERSON_H
#define __PERSON_H

#include <iostream>
#include <string>
#include "stream_insertable.h"

class Person : public StreamInsertable{
    public:
        Person() = default;
        Person(const char* name, const char* profession, unsigned int age):
            _name(new std::string{name}),
            _profession(new std::string{profession}),
            _age(age){}
        // Copy constructor
        Person(const Person& src){
            std::cout << "Copy constructing a new object at " << this
                << " from an object at " << &src << '\n';
            this->_name = (src._name) ? new std::string{*src._name} : nullptr;
            this->_profession = (src._profession) ? new std::string{*src._profession} : nullptr;
            this->_age = src._age;
        }
        // Move constructor
        Person(Person&& src){
            if (this == &src)
                return;
            std::cout << "Move constructing a new object at " << this
                << ", moving an existing object from " << &src << '\n';
            this->_name = src._name;
            this->_profession = src._profession;
            this->_age = src._age;
            src.invalidate();
        }
        // Copy assignment
        Person& operator=(const Person& rhs){
            if (this == &rhs)
                return *this;
            std::cout << "Copy assignment, copying from " << &rhs << " to " << this << '\n';
            delete this->_name;
            delete this->_profession;
            this->_name = (rhs._name) ? new std::string{*rhs._name} : nullptr;
            this->_profession = (rhs._profession) ? new std::string{*rhs._profession} : nullptr;
            this->_age = rhs._age;
            return *this;
        }
        // Move assignment
        Person& operator=(Person&& rhs){
            if (this == &rhs)
                return *this;
            std::cout << "Move assignment, moving from " << &rhs << " to " << this << '\n';
            delete this->_name;
            delete this->_profession;
            this->_name = rhs._name;
            this->_profession = rhs._profession;
            this->_age = rhs._age;
            rhs.invalidate();
            return *this;
        }
        void stream_insert(std::ostream& output) const override{
            if (!_name){
                output << "'Person object at " << this << " [Name: NULL, Profession: NULL, Age: NULL]'";
            }
            else
                output << "'Person object at " << this << " [Name: " << *_name
                    << ", Profession: " << *_profession << ", Age: " << _age
                        << "]'";
        }
        ~Person(){
            delete _name;
            delete _profession;
        }
    
    private:
        std::string* _name{};
        std::string* _profession{};
        unsigned int _age{};
        void invalidate(){
            _name = _profession = nullptr;
        }
};

#endif  // __PERSON_H