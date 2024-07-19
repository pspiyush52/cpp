#include "person.h"
#include <iostream>

Person::Person(std::string_view first, std::string_view last):
    first_name(new std::string{first}), last_name(new std::string{last}){}

std::string* Person::get_first() const {
    return first_name;
}

std::string* Person::get_last() const {
    return last_name;
}

void Person::set_first(std::string_view first){
    delete first_name;
    first_name = new std::string{first};
}

void Person::set_last(std::string_view last){
    delete last_name;
    last_name = new std::string{last};
}

std::ostream& operator<<(std::ostream& output, const Person& p){
    output << "Person-{first_name: \"" << *(p.first_name) << "\", last_name: \""
    << *(p.last_name) << "\"}";
    return output;
}

Person::~Person(){
    delete first_name;
    delete last_name;
}