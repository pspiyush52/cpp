#include "print.h"
#include "frand.h"

void insertKey(int A[], int n, int key);
void insertionSort(int A[], int n) {
	int i{1};
	for (; i < n; ++i)
		insertKey(A, i, A[i]);
}

int main(int argc, char* argv[])
{
	int arr[15];
	printer(rng().integers(-20, 100, std::size(arr))) >> arr;
	printer arr_printer(arr);
	print("   The array: ", arr_printer);
	insertionSort(arr, std::size(arr));
	print("Sorted array: ", arr_printer);
	return 0;
}

void insertKey(int A[], int n, int key) {
	int i{n - 1};
	for (; i >= 0 && key < A[i]; --i)
		A[i + 1] = A[i];
	A[i + 1] = key;
}
