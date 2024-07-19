#include "deque.h"
#include "random.h"
#include "frand.h"

const int TEST_SIZE{1000000};
const int LIST_SIZE{20};
const int FROM{0}, TO{20};

int num_of_comparisons(deque<int>& nums, int key){
    int count{};
    for (int n : nums){
        ++count;
        if (n == key)
            break;
    }
    return count;
}

int main(void)
{
    rng r;
    deque<int> nums;
    int key{}, comp{}, sum{};
    double avg{};
    for (int i{}; i < TEST_SIZE; ++i){
        for (int j{}; j < LIST_SIZE; ++j)
            nums.push_back(TO * r.rand());
        key = TO * r.rand();
        comp = num_of_comparisons(nums, key);
        sum += comp;
        nums.clear();
    }
    avg = 1.0 * sum / TEST_SIZE;
    std::cout << "The average number of comparisons for linear search: " << avg << '\n';
    return 0;
}