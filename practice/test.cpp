#include "print.h"
#include "frand.h"
#include "llist.h"

int main(void)
{
    LList<int> nums;
    rng r;
    repeat(12) nums.append(r.randint(100));
    print(nums);
    print(nums.sort());
    return 0;
}
