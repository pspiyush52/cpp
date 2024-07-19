#include "carr.h"

void cprod(int* A, int size_a, int i, int* B, int size_b){
	if (i >= size_a)
		return;
	for (int j{}; j < size_b; ++j)
		std::cout << '(' << A[i] << ", " << B[j] << ") ";
	cprod(A, size_a, i + 1, B, size_b);
}

int main(void)
{
	array<int> A{1, 2, 3}, B{100, 200};
	std::cout << "{ ";
	for (int a : A)
		for (int b : B)
			std::cout << '(' << a << ", " << b << ") ";
	std::cout << '}';
	int a[] = {23, 15, 48, 34};
	int b[] = {11, 20, 19};
	std::cout << '\n';
	cprod(a, 4, 0, b, 3);
	return 0;
}