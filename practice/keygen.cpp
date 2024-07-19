#include <iostream>
#include "carr.h"
#include "random.h"

array<char> keygen(array<char>& enc){
    array<char> dec(enc.size());
    for (int i{}; i < enc.size(); ++i)
        dec[enc[i] - 'a'] = i + 'a';
    return dec;
}
void showkey(array<char>& key){
    for (char ch : key)
        std::cout << ch;
    std::cout << '\n';
}

int main(void)
{
    array<char> encrypt('a', 'z');
    shuffle(encrypt);
    showkey(encrypt);
    array<char> decrypt = keygen(encrypt);
    showkey(decrypt);
    return 0;
}