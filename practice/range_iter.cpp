#include <iostream>
#include <vector>
#include "range_iter.h"
#include "stream_insert.h"

template<typename Collection, typename Predicate, typename Modifier>
void modify(range<Collection, Predicate> r, Modifier mod_fun){
	if (!r.at_end()){
		for (; !r.at_end(); ++r)
			mod_fun(*r);
	}
}

int main(void)
{
	std::vector<int> nums = {98, 48, 64, 37, 12, 1, 94, 84, 11, 37, 4, 72};
	struct odds{
		bool operator()(int& n){ return ((n % 2) != 0); }
	};
	using namespace __vec__;
	range numview(nums);

    std::cout << "Printing the values in the view using a for loop:\n  ";
	for (; !numview.at_end(); ++numview)
		std::cout << *numview << ' ';
	std::cout << '\n';

	range oddnums(nums, odds());
	std::cout << "\nViewing only the odd numbers from the above data :\n  " << oddnums << '\n';
	modify(oddnums, [](int& n){ n = -n; });
	std::cout << "\nThe view after modifying only the odd numbers:\n  " << oddnums << '\n';
	std::cout << "\nThe vector after modifying only the odd numbers:\n  " << nums << '\n';

	return 0;
}