#include "string.h"

int main(void)
{
    string in;
    std::cout << "Enter numbers separated by newlines (Ctrl+D - Enter to stop):\n";
    get(in);
    deque<int> nums = to_int(in.collapse().split('\n'));
    long long sum{};
    for (int n : nums)
        sum += n;
    std::cout << "Sum: " << sum << ", Average: " << (1.0 * sum / nums.size()) << '\n';
    return 0;
}