#include <iostream>
#include "set.h"

int main(void)
{
	int arr[] = {65, 3, 54, 8, 74, 1, 65, 21, 3, 4, 12};
	Set<int> b;
	std::cout << "Empty set : " << b << '\n';
	for (int i{}; i < std::size(arr); ++i)
		b.insert(arr[i]);
    std::cout << "Set after insertion of elements : " << b << '\n';
	
    auto insert_into_set = [&](int&& num){
        std::cout << "\nTrying to insert " << num << " into the set...\n";
        if (b.contains(num))
            std::cout << "  " << num << " already exists in the set.\n";
        else
            std::cout << "  Inserted " << num << " into the set " << b.insert(num) << '\n';
    };

	insert_into_set(20);
    insert_into_set(21);
    insert_into_set(2);
    insert_into_set(4);

    std::cout << "\nSize of a set object : " << sizeof(Set<int>) << '\n';

    Set<int>::iterator iter = b.begin();
    ++iter;
    for (; iter != b.end(); ++iter)
        std::cout << '{' << *iter << "}  ";
    std::cout << '\n';

    Set<int> a{1, 12, 5, 65};

    std::cout << "Set a : " << a << '\n';
    std::cout << "Difference of sets (b - a) = " << (b - a) << '\n';
    std::cout << "Difference of sets (a - b) = " << (a - b) << '\n';
    std::cout << "Union of sets (a U b) = " << (a + b) << '\n';
    std::cout << sizeof(_bintree_node<int>) << '\n';

	return 0;
}