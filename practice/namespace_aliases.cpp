#include <iostream>

namespace level1{
    namespace level2{
        namespace level3{
            const double PI{3.14159265358979};
        }
    }
}
/*
    To access the PI variable we will have to go through all the namespaces
    from outer to inner like level1::level2::level3::PI.

    To avoid this hassle we can use namespace aliases to assign an alias to
    the namespace level1::level2::level3 using the syntax:
    
        namespace data = level1::level2::level3;

    Now data is an alias for the namespace level1::level2::level3 and we can
    access PI using this alias as data::PI.
*/

int main(void)
{
    std::cout << "Pi : " << level1::level2::level3::PI << '\n';
    
    // setting up the namespace alias
    namespace data = level1::level2::level3;
    
    // using the alias to access PI
    std::cout << "Pi : " << data::PI << '\n';

    return 0;
}