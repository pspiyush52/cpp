#include <iostream>
#include <functional>
#include "functors_stl.h"

// Custom comparison function
template<typename T>
bool comp(const T& a, const T& b) { return a > b; }

// Comparison functor
template<typename T>
struct Compare{
    bool operator()(const T& p1, const T& p2){
        return (p1 > p2);
    }
};

int main(void)
{
    string her{"Niharika Singh"};
    string me{"Piyush Singh"};
    string her_s{"Pratima"};
    string my_s{"Milan Singh"};
    
    arr::Array<string*> names{&her, &me, &her_s, &my_s};
    std::cout << "Max name: " << get_max(names, comp<string>) << '\n';

    arr::Array<int> nums{61, 54, 8, 21, 4, 87, 65, 98, 165, 65, 12};

    // Using a function pointer
    std::cout << "Max num: " << get_max(nums, comp<int>) << '\n';
    
    // Using a functor
    Compare<int> comp_functor;
    std::cout << "Max num: " << get_max(nums, comp_functor) << '\n';
    
    // Using built-in functor from the standard library
    std::greater<int> icomp;
    std::cout << "Max num: " << get_max(nums, icomp) << '\n';

    List<string*> Names;
    for (string* &name : names)
        Names.append(name);

    std::cout << "Max name: " << get_max(Names, comp<string>) << '\n';
    Compare<string> string_compare;
    std::cout << "Max name: " << get_max(Names, string_compare) << '\n';

    return 0;
}