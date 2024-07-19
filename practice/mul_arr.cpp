#include <iostream>

int main(void)
{
    int a1[] = {0, 1, INT_MIN};
    int a2[] = {2, 4, 1, 5, 7, INT_MIN};
    int a3[] = {5, 1, 4, 8, 9, 8, 7, 4, 1, 0, 3, 6, INT_MIN};
    int* arr[] = {a1, a2, a3};
    int* cur;

    for (int i = 0, j; i < 3; i++)
    {
        cur = arr[i];
        std::cout << "[";
        for (j = 0; cur[j + 1] != INT_MIN; j++)
            std::cout << cur[j] << ", ";
        std::cout << cur[j] << "]";
        std::cout << std::endl;
    }
    
    return 0;
}