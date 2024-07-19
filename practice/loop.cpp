#include <iostream>

int main(void)
{
    int arr[] = {5, 12, 48, 79};
    int sum = 0, item, i, n = std::size(arr) - 1;

    std::cout << "\nThe array : [";
    for (i = 0; i < n; i++)
        std::cout << arr[i] << ", ";
    std::cout << arr[n] << "]" << std::endl;
    std::cout << "\nSize of array : " << std::size(arr) << "\n\n";
    for (int item : arr)
        std::cout << "Adding " << item  << " to " << sum << " gives " << (sum += item) << std::endl;
    return 0;
}

