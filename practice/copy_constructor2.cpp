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
    /*
        Now since we are creating a new int while copying and storing the value at address contained
        in age, even if we modify one age the other won't be affected.

        Objects copies using this method are deep copies.
    */
    
    return 0;
}

Person::Person(std::string_view First_Name, std::string_view Last_Name, int Age):
    first_name(First_Name), last_name(Last_Name), age(new int{Age}){}

Person::Person(const Person& source):
    first_name(source.first_name),
    last_name(source.last_name),
    age(new int{*source.age}){}  // creating a new int variable to store the age of the new object

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