#include "print.h"
#include <cstdlib>

typedef unsigned long long Num;

Num fib(Num n) {
	Num first{}, second{1}, third{1}, i{}, fib_n{};
	for (; i < n; ++i) {
		fib_n = first;
		std::cout << fib_n << "  ";
		first = second;
		second = third;
		third = first + second;
	}
	std::cout << "\n\n";
	return fib_n;
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		print("Missing num arg");
		std::exit(EXIT_FAILURE);
	}
	Num n{std::stoull(argv[1])};
	printf("Fib(%llu) = %llu\n", n, fib(n));
	return 0;
}
