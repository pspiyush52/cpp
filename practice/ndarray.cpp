#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int arr1[] = {4, 14, 21, 6, 48, 9, 31, 11, 36}, i, j, k;
    cout << size(arr1) << endl;

    // only the leftmost dimension can be left blank
    int arr2[][3] = {
        {0, 1, 0},
        {11, 9, 8},
        {22, 84, 1},
        {45, 17, 8},
        {3, 12, 0},
        {2, 2, 6}
    };
    // Only the size of the outermost dimension is returned
    cout << size(arr2) << endl;
    // Now the size of the inner dimension is printed
    cout << size(arr2[0]) << endl;

    // traversing using for loops and std::size()
    for (i = 0; i < size(arr2); i++)
    {
        for (j = 0; j < size(arr2[0]); j++)
            cout << setw(3) << arr2[i][j] << " ";
        cout << endl;
    }

    cout << endl;
    // range based loop works only for the outermost dimension
    for (auto row : arr2)
    {
        for (int i = 0; i < size(arr2[0]); i++)
            cout << setw(3) << row[i] << " ";
        cout << endl;
    }

    int nums[][3][2] = {
        {{0, 1}, {7, 4}, {6, 11}},
        {{5, 9}, {4, 2}, {3, 0}},
        {{2, 2}, {1, 8}, {5, 9}},
        {{4, 5}, {5, 8}, {2, 7}},
        {{1, 3}, {8, 5}, {4, 9}},
        {{8, 0}, {9, 9}, {8, 2}},
    };

    cout << endl;
    for (i = 0; i < size(nums); i++)
    {
        for (j = 0; j < size(nums[0]); j++)
        {
            cout << "{";
            for (k = 0; k < size(nums[0][0]); k++)
                cout << setw(2) << nums[i][j][k] << " ";
            cout << "} ";
        }
        cout << endl;
    }

    int arr3[4][5];
    for (i = 0; i < 4; i++)
        for (j = 0; j < 5; j++)
            arr3[i][j] = i * j;
    
    int* ptr = &arr3[0][0];
    
    for (i = 0; i < 20; i++)
        cout << ptr[i] << " ";
    cout << endl;
    
    for (i = 0; i < 4; i++)
        for (j = 0; j < 5; j++)
            cout << arr3[i][j] << " ";

    return 0;
}