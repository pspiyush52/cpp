#include "print.h"
#include "functors.h"
#include "frand.h"
const int ARR_SIZE{7};
int findMin(int A[], int n, int start);

void selectionSort(int A[], int n) {
	for (int i{}; i < n - 1; ++i)
		swap(A, i, findMin(A, n, i));
}

int main(void)
{
	int arr[ARR_SIZE];
	printer(rng().integers(-10, 100, ARR_SIZE)) >> arr;
	printer arr_print(arr);
	print("The array: ", arr_print);
	selectionSort(arr, ARR_SIZE);
	print("Sorted array:", arr_print);
	return 0;
}

int findMin(int A[], int n, int start) {
	int min{INT_MAX}, pos;
	for (int i{start}; i < n; ++i) {
		if (A[i] < min) {
			min = A[i];
			pos = i;
		}
	}
	return pos;
}
