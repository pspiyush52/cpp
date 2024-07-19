#include "constructor_in_inheritance.h"

int main(void)
{
    /*
     * Base constructor is called first then the constructor of the class next
     * in the hierarchy and so on. The constructor for the current class is
     * called last.
     */
    level_3 obj;
    return 0;
}