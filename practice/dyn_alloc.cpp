#include <iostream>

using namespace std;

int main(void)
{
    int len;
    cout << "\nEnter the size of array : ";
    cin >> len;
    if (len < 1)
    {
        cout << "Invalid Array length!\nTerminating...\n";
        return 1;
    }
    int* num = new(std::nothrow) int[len];
    if (num == nullptr)
    {
        cout << "Insufficient memory!\n";
        return -1;
    }
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        cout << "\nEnter number " << i + 1 << " : ";
        cin >> num[i];
        sum += num[i];
    }
    cout << "\nTotal : " << sum << '\n';
    delete[] num;
    return 0;
}