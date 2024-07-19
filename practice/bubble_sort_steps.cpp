#include "lists.h"
#include "random.h"

List<int>& bsort(List<int>& arr){
    if (arr.size() < 2)
        return arr;
    int tmp{};
    bool sorted{};
    for (size_t size{arr.size()}, i{size}, count{1}; i > 1; --i, ++count){
        std::cout << '\n';
        sorted = true;
        for (size_t j{1}; j < i; ++j){
            if (arr[j] < arr[j - 1]){
                sorted = false;
                tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
            }
        }
        if (sorted)
            return arr;
        std::cout << "After pass " << count << ": " << arr << '\n';
    }
    std::cout << '\n';
    return arr;
}

int main(int argc, char* argv[])
{
    List<int> nums;
    if (argc > 1)
        for (int i{1}; i < argc; ++i)
            nums.append(atoi(argv[i]));
    else
        append_random(nums, 0, 100, 10);
    std::cout << nums << '\n' << bsort(nums) << '\n';
    return 0;
}