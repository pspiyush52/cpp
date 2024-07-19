#include <iostream>
#include "carr.h"

int __bsearch__(array<int>& nums, int key, int left, int right){
    if (left > right)
        return -1;
    int mid = (left + right) / 2;
    if (key < nums[mid])
        return __bsearch__(nums, key, left, mid - 1);
    else if (key > nums[mid])
        return __bsearch__(nums, key, mid + 1, right);
    else
        return mid;
}

int bsearch_r(array<int>& nums, int key){
    return __bsearch__(std::forward<array<int>&>(nums), key, 0, nums.size() - 1);
}

int bsearch_i(array<int>& nums, int key){
    int left{}, right{static_cast<int>(nums.size()) - 1}, mid{(left + right) / 2};
    for (; left <= right; mid = (left + right) / 2){
        if (key < nums[mid])
            right = mid - 1;
        else if (key > nums[mid])
            left = mid + 1;
        else
            return mid;
    }
    return -1;
}

int main(void)
{
    array<int> nums{5, 12, 17, 19, 24, 35, 40, 42, 43, 57, 68, 77};
    std::cout << bsearch_r(nums, 40) << '\n';
    std::cout << bsearch_r(nums, 41) << '\n';
    return 0;
}