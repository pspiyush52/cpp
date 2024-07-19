#ifndef __PERSON_H
#define __PERSON_H

#include <string>
#include <string_view>

class Player;

class Person {
    public:
        Person() = default;
        Person(std::string_view first, std::string_view last);
        std::string* get_first() const;
        std::string* get_last() const;
        void set_first(std::string_view first);
        void set_last(std::string_view last);
        ~Person();
        friend std::ostream& operator<<(std::ostream& output, const Person& p);
        friend std::ostream& operator<<(std::ostream& output, const Player& p);
    /*
     * Protected members of the base class can be accessed in any derived
     * class but cannot be accessed by objects of it's own class. So, except
     * when it comes to derived classes, the protected members behave like
     * private members.
     */
    protected:
        std::string* first_name{};
        std::string* last_name{};
};

#endif  // __PERSON_H