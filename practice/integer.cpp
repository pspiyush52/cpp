#include "print.h"
#include "integer.h"
#include "frand.h"

Integer rnum(int size) {
    rng r;
    CharList cl(size);
    for (int i{}; i < size; ++i) {
        cl.append(r.randint(48, 58));
    }
    return cl;
}

int main(void)
{
    Integer X{"457456745"};
    Integer mul{CharList('9', X.size())};
    print(X);
    print(mul);
    print(X * mul);
    return 0;
}
