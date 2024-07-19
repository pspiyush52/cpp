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
    Person p2("Piyush", "Singh", 27);
    Person p3("Pratima", "Punj", 36);
    /*
        If we create an array of Person objects like this the objects will all be copied
        and we will see the copy constructor being called for each object.
        The objects inside the array will be copies of the actual objects inside the
        array.
    */
    Person p_arr[] = {p1, p2, p3, Person(p2)};
    std::cout << "\n---------------------------------------------------------------------------------------------------------------\n\n";
    // The addresses of p1, p2 and p3 will be different from the addresses of arr_p[0], arr_p[1]
    // and arr_p[2]
    
    // If we use the reference syntax in the range based for loop then copies
    // will not be created as the original objects will be referenced
    for (Person& p : p_arr)
        std::cout << "p : " << p << '\n';
    
    std::cout << '\n';

    // In the usual for loops there will be no copies created as the objects
    // are accessed directly using the array access operator [].
    for (int i{}; i < 4; i++)
        std::cout << "p : " << p_arr[i] << '\n';

    return 0;
}

Person::Person(std::string_view First_Name, std::string_view Last_Name, int Age):
    first_name(First_Name), last_name(Last_Name), age(new int{Age}){}

// Delegating the task of creating the object to the constructor
Person::Person(const Person& source):
    Person(source.first_name, source.last_name, *(source.age)){
        std::cout << "Copy constructor called for " << source << std::endl;
    }

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
    output << "Person object at " << &p << " <First Name: "
    << std::quoted(p.first_name)
    << ", Last Name: " << std::quoted(p.last_name)
    << ", Age: " << *(p.age) << ">";
    return output;
}