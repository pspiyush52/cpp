#include <iostream>
#include "arr_string.h"

unsigned int count_vowels(string& str){
	unsigned int count{};
	str.to_lower();
	for (char ch : str){
		if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
			++count;
	}
	return count;
}

int main(void)
{
	string name;
	string dob;
	std::cout << "Enter name : " ;
	std::cin >> name;
	std::cout << "DOB(ddmmyyyy) : " ;
	std::cin >> dob;
	std::cout << "Number of vowels in your name : " << count_vowels(name.strip()) << '\n';
	std::cout << "Possible password : " << name(4).to_upper() + dob.strip().nlast(4) << '\n';

    string Name{"                         "};
    std::cout << Name.last_word() << '\n';
	
	return 0;
}