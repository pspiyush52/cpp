#ifndef __PLAYER_H
#define __PLAYER_H

#include <string>
#include "person.h"
/*
 * In public inheritance, derived classes can access and use public members of
 * the base class, but cannot directly access the private members.
 * The same applies to friends of the derived class. They have access to
 * private members of derived, but don't have access to the base class.
 * 
 * Here public is the base class access specifier and it controls how
 * accessible base class members are from the derived class.
 * 
 * In public inheritance, all members of the base class retain their member
 * access specifiers i.e., public members remain public, protected remain
 * protected and private remain private.
 */
class Player : public Person {
    public:
        Player() = default;
        Player(std::string_view game);
        Player(const Person& p, std::string_view Game);
        ~Player();
        friend std::ostream& operator<<(std::ostream& output, const Player& p);
    
    private:
        std::string* game{};
};
/*
 * When we specify the base class access specifier as protected then public
 * and protected members of the base class become protected in the derived
 * class and private members remain Private.
 * 
 * With the private access specifier, all members of the base class become
 * private in the derived class.
 */
#endif  // __PLAYER_H