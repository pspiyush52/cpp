#include <iostream>
#include <iomanip>
#include "arr_string.h"
#include "defs.h"

unsigned int get_max_width(unsigned int* counter){
    unsigned int max{}, width{};
    repeat(26)
        if (counter[i] > max)
            max = counter[i];
    for (; max /= 10; ++width);
    return width;
}

int main(int argc, char* argv[])
{
    string text;
    const char* alphabets = "abcdefghijklmnopqrstuvwxyz";
    
    if (argc == 2)
        text = argv[1];
    else
        text = R"(Computing efficiency: The hash function should compute the hash value 
        quickly and efficiently even for large key values
        Uniform distribution: The hash function should be able to distribute the keys
        evenly in the hash table.
        Deterministic: The hash function should consistently create the same key for a
        given value.
        Minimal Collisions: The hash function should minimize the key collisions in the
        hash table.)";
    
    text.to_lower();
    unsigned int counter[26]{};
    for (char ch : text)
        ++counter[ch - 'a'];
    repeat(26)
        std::cout << alphabets[i] << " : " << std::setw(get_max_width(counter) + 6)
            << std::left << counter[i] << (((i + 1) % 4 == 0) ? "\n" : "");
    return 0;
}