#include <iostream>
#include <bitset>
#include <iomanip>

#define newline std::cout << std::endl;

int main(int argc, char* argv[])
{
    unsigned short int num { 0xffff }, tmp;
    if (argc == 2)
        num = static_cast<unsigned short int>(atoi(argv[1]));
    
    // unsigned short int val { 0xff0u };
    unsigned short int val { 0xf };

    newline
    std::cout << "val : " << val << std::endl;
    std::cout << "Binary representation : " << std::bitset<16>(val) << std::endl;
    
    std::cout << "Shifted 4 bits to the left : " << (val << 4) << std::endl;
    std::cout << "Binary representation : " << std::bitset<16>(val << 4) << std::endl;

    newline
    for (tmp = num; tmp; tmp <<= 1)
        std::cout << std::bitset<16>(tmp) << std::endl;
    
    if (num)
        while (!((1 << 15) & num))
            num <<= 1;
    
    newline
    for (; num; num >>= 1)
        std::cout << std::bitset<16>(num) << std::endl;

    newline
    // Demonstrating two's complement being used to store negative integers
    std::cout << (~10) + 1 << std::endl;

    // Flipping all the bits to 1 results in the largest unsigned int value
    std::cout << static_cast<unsigned int>(~0) << std::endl;
    std::cout << UINT_MAX << std::endl;

    std::cout << std::boolalpha;

    unsigned char x = 45;
    // if two numbers are the same XOR'ing them results in a zero
    std::cout << "Is x equal to 45 : " << ((x ^ 45) == 0) << std::endl;

    // shifting the bits back right to get only 1 or zero as the final result
    for (int i = 7; i >= 0; i--)
        std::cout << (((1 << i) & x) >> i);
    newline

    return 0;
}