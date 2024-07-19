#include "utils.h"

int main(void)
{
    // Both methods work
    s_ptr<int[]> arr{new int[5]};
    // s_ptr<int[]> arr = std::make_shared<int[]>(5);

    repeat(5)
        arr[i] = i*i;

    repeat(5)
        std::cout << "arr[" << i << ']' << " : " << arr[i] << '\n';
    
    return 0;
}