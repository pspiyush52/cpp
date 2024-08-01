#include "heap.h"
#include "print.h"
#include "cpair.h"

int main(void)
{
    int arr[] = {77, 5, 17, -12, 56, -7, 9, 0, 12, -75, 98, 23, 72, -45};
    Heap<decltype(arr), Greater> maxHeap(arr);
    maxHeap.sort();
    print(printer(arr));
    print(collatz(19));
    return 0;
}
