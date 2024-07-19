#ifndef __CALLBACK_ENCRYPT_H
#define __CALLBACK_ENCRYPT_H

#include <string>

const int SHIFT = 2;

void encrypt(char& ch){ ch += SHIFT; }
void decrypt(char& ch){ ch -= SHIFT; }

std::string& modify(std::string& s, void (*modifier)(char&)){
    for (char& ch : s)
        modifier(ch);
    return s;
}

namespace typ{
    
    // We can setup a type alias for a function pointer using typedef
    typedef void (*modifier_function)(char&);

    std::string& modify(std::string& s, modifier_function modifier){
        for (char& ch : s)
            modifier(ch);
        return s;
    }

}

namespace usi{

    // Setting up a type alias for the function pointer via the 'using' keyword
    using modifier_function = void (*)(char&);
    
    std::string& modify(std::string& s, modifier_function modifier){
        for (char& ch : s)
            modifier(ch);
        return s;
    }
}

#endif  // __CALLBACK_ENCRYPT_H