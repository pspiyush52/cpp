#include "print.h"
#include "defs.h"
#include "frand.h"
#include "carr.h"

const char ALPHA_START{'a'};
const char ALPHA_END{'c'};
const int LENGTH{10};

begin_main

    rng r;
    array<char> alphabet(ALPHA_START, ALPHA_END);
    repeat(LENGTH)
        std::cout << alphabet[r.randint(alphabet.size())];
    return 0;

end_main
