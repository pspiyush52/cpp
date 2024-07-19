#include <iostream>
#include "utils.h"

int main(void)
{
    int x{23};
    int y{82};
    std::cout << "max : " << max(x, y) << std::endl;
    return 0;
}