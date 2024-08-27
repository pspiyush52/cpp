// #define DEQUE_DEBUG
#include "deque.h"
#include "..\practice\stream_insertable.h"
#include "..\practice\defs.h"
#include "..\practice\print.h"
#include "..\practice\utils.h"
#include "..\practice\base_derived.h"
#include <vector>

deque<int>& insertionSort(deque<int>& A) {
    int key{}, i{}, j{};
    for (i = 1; i < A.size(); ++i) {
        key = A[i];
        for (j = i - 1; j >= 0 && A[j] > key; --j)
            A[j + 1] = A[j];
        A[j + 1] = key;
    }
    return A;
}

int main(void)
{
    int&& from{0};
    int&& to{100};
    deque<int> nums = rand_range(from, to, 10);
    deque<int> copy{nums, 4, 7};
    det(nums);
    nums.setValue(0);
    det(nums);
    det(copy);
    return 0;
}
