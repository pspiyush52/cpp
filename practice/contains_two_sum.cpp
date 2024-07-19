#include <iostream>
#include "range.h"
#include "carr.h"
#include "set.h"

template<typename T>
bool contains_two_sum(array<T>& arr, T target){
	Set<T> visited;
	T complement{};
	for (size_t i{}; i < arr.size(); ++i){
		complement = target - arr[i];
		if (visited.contains(complement))
			return true;
		visited.insert(arr[i]);
	}
	return false;
}

int main(void)
{
	array<int> nums(100);
	rand_range(-1000, 1000) >> nums;
	std::cout << "List:  " << nums << '\n';
	int target = 1024;
	std::cout << std::boolalpha << "The list contains " << target
		<< " sum: " << contains_two_sum(nums, target);

	return 0;
}