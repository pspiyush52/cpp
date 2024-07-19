#include <iostream>
#include <memory>
#include "arr.h"

using namespace arr;
using iarr_uptr = std::unique_ptr<Array<int>>;

// Returning UP(unique pointer) to UP to Array<int> works well as expected
std::unique_ptr<iarr_uptr> func(){
    std::unique_ptr<iarr_uptr> ptr = 
    std::make_unique<iarr_uptr>(std::make_unique<Array<int>>(Array<int>{2, 3, 41, 54, 1, 0, 7}));
    return ptr;
}

int main(void)
{
    std::unique_ptr<iarr_uptr> arr2 = func();
    std::cout << (**arr2) << '\n';
    
    return 0;
}