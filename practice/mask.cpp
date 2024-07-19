#include <cstdio>
#include <iostream>
#include <iomanip>
#include <bitset>

#define repeat(N) for(i = 0; i < N; i++)
#define endl std::endl;
#define setw std::setw(WIDTH)
#define bin(N) std::bitset<8>(N)
#define WIDTH 40

int main(void)
{
    int i;
    unsigned char mask[8];

    // creating masks
    repeat(8)
        mask[i] = (1 << i);

    unsigned char num = 25;
    printf("The number : \n%*d\n", WIDTH, num);
    std::cout << "Binary representation : " << endl;
    std::cout << setw << bin(num) << endl;

    std::cout << "\nSetting the bit at position 2" << endl;

    // using bitwise OR to set the bit at position 2
    num |= mask[2];
    printf("The number now : \n%*d\n", WIDTH, num);
    std::cout << "Binary representation : " << endl;
    std::cout << setw << bin(num) << endl;

    std::cout << "\nResetting the bit at position 4" << endl;
    
    // using bitwise AND with negation to reset the bit
    num &= (~mask[4]);
    printf("The number now : \n%*d\n", WIDTH, num);
    std::cout << "Binary representation : " << endl;
    std::cout << setw << bin(num) << endl;

    std::cout << "\nToggling the bit at position 6" << endl;

    // using bitwise XOR to toggle the bit
    num ^= mask[6];
    printf("The number now : \n%*d\n", WIDTH, num);
    std::cout << "Binary representation : " << endl;
    std::cout << setw << bin(num) << endl;

    std::cout << "\nToggling the bit again : " << endl;

    num ^= mask[6];
    printf("The number now : \n%*d\n", WIDTH, num);
    std::cout << "Binary representation : " << endl;
    std::cout << setw << bin(num) << endl;

    std::cout << "\nSetting 7th, 6th, 5th and 4th bits in one go," << endl;

    // bitwise OR'ing multiple masks sets the bits at all the mask positions
    num |= (mask[7] | mask[6] | mask[5] | mask[4]);
    printf("The number now : \n%*d\n", WIDTH, num);
    std::cout << "Binary representation : " << endl;
    std::cout << setw << bin(num) << endl;

    std::cout << "\nResetting bits at 6th, 4th, 2nd and 1st position," << endl;

    num &= (~(mask[6] | mask[4] | mask[2] | mask[1]));
    printf("The number now : \n%*d\n", WIDTH, num);
    std::cout << "Binary representation : " << endl;
    std::cout << setw << bin(num) << endl;

    std::cout << "\nResetting all the bits, " << endl;

    num &= 0;
    printf("The number now : \n%*d\n", WIDTH, num);
    std::cout << "Binary representation : " << endl;
    std::cout << setw << bin(num) << endl;

    return 0;
}