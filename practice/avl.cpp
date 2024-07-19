#include "avl.h"
#include "carr.h"
#include "range.h"

int main(void)
{
    Set t;
    array<int> arr(20);
    rand_range(-5, 10) >> arr;
    std::cout << "Array of numbers : " << arr << '\n';
    std::cout << "\nInserting the numbers into the tree...\n";
    for (auto num : arr)
        t.insert(num);
    std::cout << "\nThe tree : " << t << '\n';
    std::cout << "\nSize of the array: " << arr.size() << ", Size of the tree: " << t.size() << '\n';

    return 0;
}