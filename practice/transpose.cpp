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
    matrix m, t_m;
    int rows, cols, i, j;
    printf("Enter the dimensions of the matrix: ");
    scanf("%d %d", &rows, &cols);
    printf("\nEnter the values of the matrix row-wise:\n");
    for (i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j){
            printf("M[%d][%d]: ", i + 1, j + 1);
            scanf("%d", *(m + i) + j);
        }
    
    printf("\nEntered matrix:\n");
    display(m, rows, cols);
    for (i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j)
            t_m[j][i] = m[i][j];
    
    printf("\nTranspose of the matrix:\n");
    display(t_m, cols, rows);
    return 0;
}
