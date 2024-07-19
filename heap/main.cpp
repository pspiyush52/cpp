#include "heap.h"
#include <time.h>

int main(void)
{
    srand(time(NULL));
    Heap h(10);

    repeat(20)
        h.insert(rand() % 100);
    nl
    std::cout << "Unsorted heap : " << h << std::endl;
    h.sort();
    std::cout << "Heap after sorting : " << h << std::endl;
    return 0;
}