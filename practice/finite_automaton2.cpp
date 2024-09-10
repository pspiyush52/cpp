#include "print.h"
#include "matrix.h"
#include "tuples.h"

Pair<bool, int> hasSubstring(const char* b_str) {
    Pair<bool, int> p;
    const Matrix M {8, 2,
        0, 1,
        0, 2,
        3, 2,
        0, 4,
        0, 5,
        6, 2,
        7, 4,
        7, 7
    };
    constexpr int acceptState{7};
    int currentState{}, count{1};
    for(; *b_str; ++b_str, ++count) {
        currentState = M[currentState][static_cast<int>(*b_str - '0')];
        if (currentState == acceptState)
            return {true, count - 7};
    }
    return {false, -1};
}

int main(void)
{
    Pair p = hasSubstring("1001000101001010100101010101000010101010100100101010011");
    auto found = [](const Pair<bool, int>& p) {
        if(p.getFirst())
            print("Substring found within the main string from index", p.getSecond());
        else
            print("Substring not found within the main string.");
    };
    found(p);
    found(hasSubstring("01101100010100101011"));
    found(hasSubstring("010010100000011100"));
    return 0;
}
