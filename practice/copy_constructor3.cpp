#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>

class Person {
    public:
        Person(std::string_view First_Name, std::string_view Last_Name, int Age);
        Person(const Person& source);  // copy constructor
        const std::string& get_first_name() const;
        const std::string& get_last_name() const;
        int* get_age() const;
        void set_first_name(std::string_view first_name);
        void set_last_name(std::string_view last_name);
        void set_age(int age);
        void operator=(const Person& p);
        ~Person();
    private:
        std::string first_name;
        std::string last_name;
        int* age;
        friend std::ostream& operator<<(std::ostream& output, const Person& p);
};

int main(void)
{
    Person p1("Niharika", "Singh", 31);
    Person p2(p1);
    std::cout << "p1 : " << p1;
    std::cout << "\np2 : " << p2;
    p2.set_first_name("Piyush");
    p2.set_age(27);
    std::cout << "\n\nSetting p2\'s name to Piyush and age to 27...";
    std::cout << "\np2 : " << p2;
    std::cout << "\np1 : " << p1;
    p2 = p1;
    std::cout << "\n\np1 : " << p1;
    std::cout << "\np2 : " << p2 << '\n';
    
    return 0;
}

Person::Person(std::string_view First_Name, std::string_view Last_Name, int Age):
    first_name(First_Name), last_name(Last_Name), age(new int{Age}){}

// Delegating the task of creating the object to the constructor
Person::Person(const Person& source):
    Person(source.first_name, source.last_name, *(source.age)){}  // constructors can access private members directly

const std::string& Person::get_first_name() const {
    return first_name;
}
const std::string& Person::get_last_name() const {
    return last_name;
}
int* Person::get_age() const {
    return age;
}
void Person::set_first_name(std::string_view first_name){
    this->first_name = first_name;
}
void Person::set_last_name(std::string_view last_name){
    this->last_name = last_name;
}
void Person::set_age(int age){
    *(this->age) = age;
}
void Person::operator=(const Person& p)
{
    first_name = p.first_name;
    last_name = p.last_name;
    *age = *(p.age);
}
Person::~Person(){
    delete age;
}

std::ostream& operator<<(std::ostream& output, const Person& p)
{
    output << "Person <First Name: " << std::quoted(p.first_name)
    << ", Last Name: " << std::quoted(p.last_name)
    << ", Age: " << *(p.age) << ">";
    return output;
}