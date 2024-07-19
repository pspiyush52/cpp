#include <iostream>
#include "callback_encrypt.h"

void _enc(char& ch){ ch += 4; }
void _dec(char& ch){ ch -= 4; }

int main(void)
{
    std::string name{"Niharika"};
    std::cout << "Name encrypted: " << modify(name, encrypt) << '\n';
    std::cout << "Name decrypted: " << modify(name, decrypt) << '\n';

    typ::modifier_function enc = _enc;
    typ::modifier_function dec = _dec;

    std::cout << "Name encrypted: " << modify(name, enc) << '\n';
    std::cout << "Name decrypted: " << modify(name, dec) << '\n';
    return 0;
}