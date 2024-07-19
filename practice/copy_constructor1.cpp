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
        // ~Person();
    private:
        std::string first_name;
        std::string last_name;
        int* age;
        friend std::ostream& operator<<(std::ostream& output, const Person& p);
};

int main(void)
{
    Person p1("Niharika", "Joshi", 31);
    Person p2(p1);
    std::cout << "p1 : " << p1;
    std::cout << "\np2 : " << p2;
    p2.set_first_name("Piyush");
    p2.set_age(27);
    std::cout << "\n\nSetting p2\'s name to Piyush and age to 27...";
    std::cout << "\np2 : " << p2;
    std::cout << "\np1 : " << p1;
    /*
        Even though we change p2's age, p1's age was affected as well since we just copied the
        address contained in the age pointer and not the value of age, so both age pointers of
        p2 and p2 are pointing at the same integer in memory and so changing the age through one
        affects the other as well.

        Since we are releasing the memory used to store th age in the destructor this will also
        lead to our destructor trying to release the same memory more than once which wil result
        in a program crash.

        Even if we don't create our own copy constructor and use the default one still we will get
        the same problem because the default copy constructor just copies the values of member
        variables one by one and it will again copy just the address contained in age and not the
        age value contained at that address.

        Copied objects using this method are shallow copies.
    */
    return 0;
}

Person::Person(std::string_view First_Name, std::string_view Last_Name, int Age):
    first_name(First_Name), last_name(Last_Name), age(new int{Age}){}

Person::Person(const Person& source):
    first_name(source.get_first_name()),
    last_name(source.get_last_name()),
    age(source.get_age()){}  // copies the address contained in the age pointer

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
// Person::~Person(){
//     delete age;
// }

std::ostream& operator<<(std::ostream& output, const Person& p)
{
    output << "Person <First Name: " << std::quoted(p.first_name)
    << ", Last Name: " << std::quoted(p.last_name)
    << ", Age: " << *(p.age) << ">";
    return output;
}