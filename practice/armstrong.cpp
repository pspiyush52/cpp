#include "print.h"
#include "digits.h"

int main(void)
{
    const int UPTO{30000000};
    print("Armstrong numbers from 0 to ", UPTO);
    repeatu(UPTO)
        if (Digits::isArmstrong(i))
            std::cout << i << "  ";
    return 0;
}
