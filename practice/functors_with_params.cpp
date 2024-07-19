#include "functors_with_params.h"

int main(void)
{
    std::srand(std::time(0));
    int i{};
    List<int> nums;
    List<int> in_range;

    // Populating the list with 20 random values
    rand_populate(nums, 20);
    
    // Functor to check if a value is in range or not
    InRange<int> range_functor(25, 75);
    
    range_extract(nums, in_range, range_functor);
    
    std::cout << "Numbers: " << nums << '\n';
    std::cout << "Numbers which are in range: " << in_range << '\n';

    std::cout << "Sum of numbers: " << sum(nums) << '\n';

    // Using a callback function to calculate the sum of numbers in range
    // We have to pass min and max as parameters
    std::cout << "Sum of numbers in range(using function): " << range_sum_fun(nums, check_range<int>, 25, 75) << '\n';
    
    // A bit more convenient than using the function method
    std::cout << "Sum of numbers in range(using named functor): " << range_sum(nums, range_functor) << '\n';
    
    // This syntax can be used as well instead of passing a named object
    std::cout << "Sum of numbers in range(using anonymous functor): " << range_sum(nums, InRange<int>{25, 75}) << '\n';
    return 0;
}