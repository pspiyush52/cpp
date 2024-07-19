#include <iostream>

int main(void)
{
	const char* strings[] = {
		"FizzBuzz", nullptr, nullptr, "Fizz", nullptr, "Buzz", "Fizz",
		nullptr, nullptr, "Fizz", "Buzz", nullptr, "Fizz", nullptr, nullptr
	};
	const char* cur = nullptr;
	size_t num{};
	std::cout << "Enter a number: ";
	std::cin >> num;
	for (size_t j{1}; j <= num ; ++j){
		if ((cur = strings[j % 15]))
			std::cout << '\'' << cur << "'  ";
		else
			std::cout << j << "  ";
	}
	return 0;
}