#include "matrix.h"
#include "print.h"
#include "frand.h"

int main(void)
{
    rng r;
    const int SIZE{15};
    Matrix A(SIZE), B(SIZE);
    double *ptr_A = A[0], *ptr_B = B[0];
    repeatu(A.get_cols() * A.get_rows()) {
        (*(ptr_A++)) = r.randint(10);
        (*(ptr_B++)) = r.randint(10);
    }
    print(A);
    print(B);
    print(A * B);
    print((long long)(B)());
    repeat(5) {
        A.add_row(0).add_col(0);
        B.add_row(0).add_col(0);
    }
    print(A * B);
    return 0;
}
