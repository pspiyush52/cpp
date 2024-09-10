#include "print.h"
#include "matrix.h"
#include "tuples.h"

/**
 * Checks if the binary string contains the pattern "110" in it or not.
 * 
 * The matrix M corresponds to a transformation function,
 * 
 *               d : {q0, q1, q2, q3} X {0, 1} --> {0, 2}
 * 
 * of a finite automaton ({q0, q1, q2, q3}, {0, 1}, d, q0, {q3}) designed to
 * accept only those strings over the alphabet {0, 1} that contain the
 * substring "110".
 * 
 * The tabular representation of the transformation function is as follows:
 * 
 *                 ===========+=========+=========+
 *                 |          |    0    |    1    |
 *                 ===========+=========+=========+
 *                 |    q0    |   q0    |   q1    |
 *                 ===========+=========+=========+
 *                 |    q1    |   q0    |   q2    |
 *                 ===========+=========+=========+
 *                 |    q2    |   q3    |   q2    |
 *                 ===========+=========+=========+
 *                 |    q3    |   q3    |   q3    |
 *                 ===========+=========+=========+
 * 
 * Where q0 is the initial state where no character of the pattern has been
 * found and q3 is the accept state where the pattern has been found.
 */
Pair<bool, int> hasSubstring(const char* b_str) {
    Pair<bool, int> p;
    const Matrix M {4, 2,
        0, 1,
        0, 2,
        3, 2,
        3, 3
    };
    constexpr int acceptState{3};
    int currentState{}, count{1};
    for(; *b_str; ++b_str, ++count) {
        currentState = M[currentState][(*b_str - '0')];
        if (currentState == acceptState)
            return {true, count - 3};
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
