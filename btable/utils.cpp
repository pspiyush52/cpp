#include "utils.h"

void bin(int num, int width)
{
    int i, flag, w;
    for (i = 31; i >= 0; i--)
        if ((1 << i) & num)
        {
            flag = 1;
            break;
        }
    
    w = i + 1;
    repeat(width - w)
        std::cout << "0";
    
    if (!flag)
        return;

    for (; i >= 0; i--)
        if ((1 << i) & num)
            std::cout << "1";
        else
            std::cout << "0";
}

int get_width(int num)
{
    for (int i = 31; i >= 0; i--)
        if ((1 << i) & num)
            return (i + 1);
    return 1;
}

void draw_line(int width)
{
    std::cout << "+";
    repeat(width - 2)
        std::cout << "-";
    std::cout << "+";
}