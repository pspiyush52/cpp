#include <iostream>
#include "view.h"
#include "functors.h"
#include "frand.h"

int main(void)
{
    rng r;
    List<int> oddnums, rnums{r.integers(0, 100, 10)};
    for (auto val : rnums | odds())
        oddnums.append(val);
    std::cout << "Random odd numbers between 0 and 100: " << oddnums << '\n';
    return 0;
}