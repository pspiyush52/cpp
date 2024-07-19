#include <stdio.h>
#define MAX_SIZE 10
typedef int matrix[MAX_SIZE][MAX_SIZE];

void display(matrix m, int rows, int cols){
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j)
            printf("%10d", m[i][j]);
        putchar('\n');
    }
}

int main(void)
{
    matrix m;
    int rows, cols, i = 0, j = 0, input, non_zero_count = 0;
    printf("Enter the dimensions of the matrix: ");
    scanf("%d %d", &rows, &cols);
    printf("Enter the elements of the matrix:\n");
    for (; i < rows; ++i)
        for (j = 0; j < cols; ++j){
            printf("M[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &input);
            m[i][j] = input;
            if (input)
                ++non_zero_count;
        }
    printf("\nThe matrix:\n");
    display(m, rows, cols);
    printf("\nIn sparse matrix representation:\n");
    printf("%d, %d, %d\n", rows, cols, non_zero_count);
    for (i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j)
            if (m[i][j])
                printf("(%d, %d, %d)\n", i, j, m[i][j]);
    return 0;
}
