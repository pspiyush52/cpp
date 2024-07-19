#include "utils.h"

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3)
        return 1;
    
    int num = atoi(argv[1]);
    int upto;
    
    if (argc == 3)
        upto = atoi(argv[2]);
    else
        upto = 10;
    
    if (upto < 1)
        return 2;
    
    int multiplier_width = get_width(upto);
    int num_width = get_width(num);
    int max_prod_width = get_width(num * upto);
    int total_width = multiplier_width + num_width + max_prod_width + 14;

    nl
    draw_line(total_width);
    nl
    
    repeat (upto)
    {
        std::cout << "|   ";
        bin(num, num_width);
        std::cout << " x ";
        bin(i + 1, multiplier_width);
        std::cout << " = ";
        bin(num * (i + 1), max_prod_width);
        std::cout << "   |";
        nl
        draw_line(total_width);
        nl
    }
    return 0;
}