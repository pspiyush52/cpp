#include "util1.h"
#include "util2.h"
/*
    Marking stuff as inline unifies multiple definitions of that item across
    multiple translation units. Without inline, multiple definitions will
    result in a linker error.

    Inlining stuff is particularly useful if we are designing a library of
    only header files. Since the header files will contain the definitions
    including them in different TU's can result in a linker error because
    those definitions will appear more than once.
    
    We can resolve this by prefixing the declarations with the inline keyword.
*/
int main(void)
{
    /*
        The addresses of SHIFT and DISTANCE variables will be the same because
        all the definitions have been combined into one.
    */
    util1::print_shift();
    util2::print_distance();

    util1::print_distance();
    util2::print_shift();

    return 0;
}