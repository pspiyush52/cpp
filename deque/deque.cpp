#include "deque.h"
#include "..\practice\defs.h"

int main(void)
{
    deque<int> nums;

    repeat(5) nums.push_back(i);
    repeat(12) nums.push_front(i);
    nums.pop_front();

    nums.status();
    std::cout << "\n ";
    
    deque<int>::iterator iter = nums.begin();
    for (; iter != nums.end(); ++iter)
        std::cout << *iter << "  ";
    
    std::cout << '\n' << nums << '\n';
    printf("\nSize: %d, Capacity: %d\n", nums.size(), nums.capacity());
    
    return 0;
}
