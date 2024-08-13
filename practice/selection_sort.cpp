#include "print.h"
#include "frand.h"
const int SIZE{7};

template<typename arr_tp, size_t size>
void selectionSort(arr_tp (&A)[size]);

int main(void)
{
    int A[SIZE];
    printer(rng().integers(-10, 100, SIZE)) >> A;
    print("The array: ", printer(A));
    selectionSort(A);
    print("Sorted: ", printer(A));
    return 0;
}

template<typename T>
size_t findMinIndex(T* A, size_t begin, size_t size) {
    size_t minIndex{begin}, i{begin};
    T min{A[minIndex]};
    for (; i < size; ++i) {
        if (A[i] < min) {
            min = A[i];
            minIndex = i;
        }
    }
    return minIndex;
}
template<typename T>
void arraySwap(T* A, int i, int j) {
    T tmp{A[i]};
    A[i] = A[j];
    A[j] = tmp;
}
template<typename arr_tp, size_t size>
void selectionSort(arr_tp (&A)[size]) {
    for (size_t i = 0; i < size - 1; ++i)
        arraySwap(A, i, findMinIndex(A, i, size));
}
