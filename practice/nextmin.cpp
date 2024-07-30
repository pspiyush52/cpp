#include "print.h"
#include "frand.h"
#include "carr.h"
#include "minmaxtree.h"

void findMins(array<int>& nums) {
    int min{INT_MAX}, nextMin{INT_MAX};
    for (int& num : nums)
        if (num < min)
            min = num;
    for (int& num : nums)
        if ((num < nextMin) && (num != min))
            nextMin = num;
    print("Min:", min);
    print("Next min:", nextMin);
}

int main(void)
{
    array<int> nums(20);
    printer(rng().integers(0, 100, nums.size())) >> nums;
    // array<int> nums{1, 2, 80, 9, 7, 19};
    print(nums);
    findMins(nums);
    MinMaxTree<array<int>> T{nums};
    print("Min:", T.getMin());
    print("Next min:", T.getNextMin());
    return 0;
}
