#include <iostream>
#include <vector>
#include "lists.h"
#include "random.h"
#include "views.h"

template<typename T>
class DivisibleBy{
	public:
		DivisibleBy(T num) : __num(num){}
		bool operator()(T& x){ return ((x % __num) == 0); }
	private:
		T __num;
};

int main(void)
{
	List<int> nums;
	append_random(nums, 0, 50, 50);
	for (int i = 2; i < 10; ++i)
		// std::cout << "Numbers in the list divisible by " << i << " : " << Views(nums, DivisibleBy(i)) << '\n';
		std::cout << "Numbers in the list divisible by " << i << " : " << (nums | DivisibleBy(i)) << '\n';
	return 0;
}