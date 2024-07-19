#include <iostream>
#include <string>
#include <string_view>

class Person {
    public:
        Person(std::string_view Name, unsigned int Age);
        std::string_view get_name() const;
        std::string& get_name();
        unsigned int get_count() const;
    private:
        std::string name;
        unsigned int age;
        mutable unsigned int count;  // makes it able to be modified inside const member functions
};

Person::Person(std::string_view name, unsigned int age)
{
    this->name = name;
    this->age = age;
    this->count = 0;
}
std::string_view Person::get_name() const
{
    count++;
    return name;
}
std::string& Person::get_name()
{
    return name;
}
unsigned int Person::get_count() const
{
    return count;
}

int main(void)
{
    const Person p1("Niharika", 30);
    p1.get_name();
    std::cout << "p1.get_name() : " << p1.get_name() << std::endl;
    std::cout << "get_name() was called " << p1.get_count() << " times.\n";
    Person p2("Piyush", 27);
    p2.get_name() = "Hunny";
    std::cout << "p2.get_name() : " << p2.get_name() << std::endl;
    return 0;
}