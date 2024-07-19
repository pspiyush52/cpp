#include <iostream>

/*
    When namespaces are nested then inner namespaces have access to the items
    of the outer namespaces without using the scope resolution operator :: but
    the outer namespaces have to use the :: operator to access the items from
    the inner namespaces.
*/

namespace outer{
    int inner_count{};
    namespace inner{
        void inner_fun(){
            // no :: operator required to use an item from the enclosing namespace
            std::cout << "inner_fun() was called... call count : " << ++inner_count << '\n';
        }
        int outer_count{};
    }
    void outer_fun(){
        // :: operator required to use an item from the inner namespace
        std::cout << "outer_fun() was called... call count : " << ++inner::outer_count << '\n';
    }
}

int main(void)
{
    outer::inner::inner_fun();
    outer::inner::inner_fun();
    outer::inner::inner_fun();
    outer::outer_fun();
    outer::outer_fun();
    outer::outer_fun();
    outer::outer_fun();
    outer::outer_fun();
    outer::inner::inner_fun();
    outer::outer_fun();
    outer::inner::inner_fun();
    outer::outer_fun();
    return 0;
}