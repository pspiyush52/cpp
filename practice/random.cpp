#include <iostream>
#include <ctime>
#define COUNT 10
#define repeati(N, i) for (i = 0; i < N; i++)

void print_array(auto* arr);

int main(void)
{
    int arr[COUNT], i;

    // generating random numbers without the seed value
    repeati(COUNT, i)
        arr[i] = std::rand();
    std::cout << "\nFixed random numbers : " << std::endl;
    print_array(arr);
    // the numbers generated using this method will remain the same every time
    // the program is run.

    // giving a seed value using std::time() function
    std::srand(std::time(0));
    std::cout << "\nRandom numbers which change each time the program is run : " << std::endl;
    repeati(COUNT, i)
        arr[i] = std::rand();
    print_array(arr);
    // now the values will be different each time the program is run

    // we can restrict the range of random numbers using the % operator
    std::cout << "\nRandom numbers between 0 and 9 : " << std::endl;
    repeati(COUNT, i)
        arr[i] = std::rand() % 10;  // restricts the range from 0 to 9
    print_array(arr);

    std::cout << "\nRandom numbers between 50 and 100 : " << std::endl;
    repeati(COUNT, i)
        arr[i] = 50 + (std::rand() % 51);
    print_array(arr);

    double rand_val1, rand_val2, rarr[COUNT];
    int r;
    std::cout << "\nRandom numbers between 0 and 1 : " << std::endl;
    repeati(COUNT, i)
    {
        r = std::rand();
        rand_val1 = static_cast<double>(r);
        rand_val2 = static_cast<double>(std::rand() % (r+1));
        rand_val1 = (rand_val2 / rand_val1);
        rarr[i] = rand_val1;
    }
    print_array(rarr);
    
    return 0;
}

void print_array(auto* arr)
{
    unsigned int i;
    std::cout << "[";
    repeati(COUNT - 1, i)
        std::cout << arr[i] << ", ";
    std::cout << arr[i] << "]" << std::endl;
}