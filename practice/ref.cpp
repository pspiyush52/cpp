#include "my.h"

int main(void)
{
    nl    
    int num = 45;
    int& ref = num;
    cout << "num : " << num << endl;
    cout << "ref : " << ref << endl;
    cout << "&num : " << &num << endl;
    cout << "&ref : " << &ref << endl;

    // Range based for loops cannot be used to modify arrays directly
    // We have to use references to do that
    nl
    int arr[] {21, 14, 2, 32, 51, 10};
    cout << "Array before modification : ";
    print_arr(arr, std::size(arr));

    for (int& num : arr)
        num *= 10;
    
    nl
    cout << "Array after modification : ";
    print_arr(arr, std::size(arr));
    nl

    return 0;
}