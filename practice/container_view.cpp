/**
 * Creating a view enables lazy calculations in our programs i.e., at the time
 * of creating the view no calculation is performed. Calculations are
 * performed only when the data from the view is accessed.
*/
#include <iostream>
#include <vector>
#include "view.h"
#include "stream_insert.h"

template<typename __predicate>
void modify(View<std::vector<int>, __predicate>& cv){
	if (cv.begin() != cv.end()){
		for (auto& item : cv)
			item *= 2;
	}
}

int main(void)
{
	std::vector<int> nums = {98, 48, 64, 37, 12, 1, 94, 84, 11, 37, 4, 72};
	
	View nums_all(nums);
	std::cout << "Printing the data from the view using a for loop :\n  ";
	auto iter_all = nums_all.begin();
	for (; iter_all != nums_all.end(); ++iter_all)
		std::cout << *iter_all << ' ';
	std::cout << '\n';

	struct odds{
		bool operator()(int& n){ return ((n % 2) != 0); }
	};

	View<std::vector<int>, odds> oddnums(nums);
	auto iter = oddnums.begin();
	std::cout << "\nGenerating a view which views only the odd numbers from the above data...\n";
	std::cout << "Printing the data from the view using a for loop :\n  ";
	for (; iter != oddnums.end(); ++iter)
		std::cout << *iter << ' ';
	std::cout << '\n';

	std::cout << "\nPrinting the data from the view using the stream insertion operator :\n  "
		<< nums_all << '\n';

	modify(oddnums);
	using namespace __vec__;
	std::cout << "\nVector after modifying only the odd values :\n" << nums << '\n';

	return 0;
}