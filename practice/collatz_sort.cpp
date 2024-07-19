#include "print.h"
#include "heap.h"
#include "cpair.h"

struct cless{
    bool operator()(const cpair& x, const cpair& y){
        return (x.c_x < y.c_x);
    }
};

int main(void)
{
    cpair A[] = {31, 48, 97, 61, 43, 12, 94, 17};
    int n = std::size(A);
    Heap<cpair, cless> H;
    repeat(n) H.insert(A[i]);
    print("Array of (x, collatz(x)) pairs:\n ", printer(A));
    print("\nValues of x sorted in a non-decreasing order according to the c(x) values");
    while (!H.isEmpty())
        std::cout << "  " << H.extract().x;
    return 0;
}
