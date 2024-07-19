#include <iostream>

int main(void)
{
    int num = 3;
    int x = 14;
    switch (num)
    {
        case 0:
            int x;
            std::cout << "case 0" << std::endl;
            break;
        case 1:
            x = 22;
            std::cout << "case 1, x : " << x << std::endl;
            break;
        case 2:
            x = 10;
            int y;
            x++;
            std::cout << "case 2, x : " << x << std::endl;
            break;
        default:
            x = 2;
            y = 101;
            x *= y;
            int z = 64;
            std::cout << z << " Default : " << x << std::endl;
    }
    return 0;
}