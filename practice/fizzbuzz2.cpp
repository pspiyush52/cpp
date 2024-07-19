#include <iostream>

void PrintNum(int n){ std::cout << n << "  "; }
void Fizz(int){ std::cout << "'Fizz'  "; }
void Buzz(int){ std::cout << "'Buzz'  "; }
void FizzBuzz(int){ std::cout << "'FizzBuzz'  "; }
void (*funs[])(int) = {
    &FizzBuzz, &PrintNum, &PrintNum, &Fizz, &PrintNum, &Buzz, &Fizz, &PrintNum,
    &PrintNum, &Fizz, &Buzz, &PrintNum, &Fizz, &PrintNum, &PrintNum
};

int main(int argc, char* argv[])
{
	int num{};
	std::cout << "Enter a number: ";  std::cin >> num;
	for (int i{1}; i <= num; ++i)
		funs[i % 15](i);
	return 0;
}