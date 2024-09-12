#include "deque.h"
#include "..\practice\print.h"
#include "..\practice\heap.h"
#include "..\practice\range.h"

int main(void)
{
    int&& from{0};
    int&& to{100};
    deque<int> nums = rand_range(from, to, rng().randint(30));
    deque<int> copy(4, 0);
    copy += nums;
    print(copy);
    return 0;
}
