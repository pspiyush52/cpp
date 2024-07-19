#include <iostream>
#include <string>
#include "encrypt.h"
#include "decrypt.h"

void enc(char& ch){ ch += 3; }
void dec(char& ch){ ch -= 3; }

/*
 * Templating the higher order function(function which takes another
 * function as a parameter) and using a template parameter to specify the
 * type of the callback function we would like to use gives us the
 * flexibility to use either direct function pointers while calling the
 * function or use a functor instead.
 */
template<typename Modifier>
std::string& modify(std::string& s, Modifier mod_fun){
    for (char& ch : s)
        mod_fun(ch);
    return s;
}

int main(void)
{
    std::string name{"Niharika"};

    // Using function pointers to call the modify function
    std::cout << "Encrypted: " << modify(name, enc) << '\n';
    std::cout << "Decrypted: " << modify(name, dec) << '\n';

    Encrypt encrypt_functor;
    Decrypt decrypt_functor;
    
    // Using functors to call the modify function
    std::cout << "Encrypted: " << modify(name, encrypt_functor) << '\n';
    std::cout << "Decrypted: " << modify(name, decrypt_functor) << '\n';

    return 0;
}