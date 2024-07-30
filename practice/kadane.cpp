#include "carr.h"
#include "frand.h"
#include "print.h"

struct Kpair {
    Kpair(int m, int s, int e): max_sub_sum(m), start_index(s), end_index(e) {}
    int max_sub_sum;
    int start_index;
    int end_index;
};
std::ostream& operator<<(std::ostream& out, const Kpair& k);
Kpair maxSum(const array<int>& A);

int main(void)
{
    rng r;
    array<int> nums(15);
    printer(r.integers(-30, 20, nums.size())) >> nums;
    print("The array:", nums);
    print(maxSum(nums));
    return 0;
}

std::ostream& operator<<(std::ostream& out, const Kpair& k) {
    out << "Maximum sub-array sum: " << k.max_sub_sum << '\n';
    out << "Max sum range indices: [" << k.start_index << ", " << k.end_index << "]\n";
    return out;
}
Kpair maxSum(const array<int>& A) {
    int cur_max{}, max_ends_here{}, start{}, possible_start{}, end{};
    for (size_t i{}; i < A.size(); ++i) {
        max_ends_here += A[i];
        if (max_ends_here > cur_max) {
            cur_max = max_ends_here;
            end = i;
            start = possible_start;
        }
        if (max_ends_here < 0) {
            max_ends_here = {};
            possible_start = i + 1;
        }
    }
    return {cur_max, start, end};
}
