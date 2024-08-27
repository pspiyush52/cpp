#include "utils.h"
#include "functors.h"

template<typename T>
int partition(T* A, int p, int r) {
    T pivot{A[p]};
    int i{r}, j{r};
    for (; i > p; --i) {
        if (A[i] > pivot)
            swap(A, i, j--);
    }
    swap(A, p, j);
    return j;
}
template<typename T>
void qsort(T* A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        qsort(A, p, q - 1);
        qsort(A, q + 1, r);
    }
}
template<typename arr_tp, int size>
auto quickSort(arr_tp (&A)[size]) -> decltype(A)
{
    qsort(A, 0, size - 1);
    return A;
}
int main(void)
{
    int A[] = {23, 76, 32, 56, 67, 34, 12, 54, 2};
    quickSort(A);
    print(printer(A));
    quickSort(A);
    print(printer(A));
    return 0;
}
