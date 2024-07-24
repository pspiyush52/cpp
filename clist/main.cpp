#include "clist.h"
#include "utils.h"
#include <ctime>

int main(void)
{
    nl
    std::srand(std::time(0));
    List l;  int i;
    repeat(10, i)
        l.append(std::rand() % 100);
    std::cout << l << std::endl;
    std::cout << l[-4] << std::endl;

    if (!error(l.find(45)))
        std::cout << "45 found at index " << l.find(45) << " in the list.\n";
    return 0;
}