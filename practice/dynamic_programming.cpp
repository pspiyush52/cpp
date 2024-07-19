#include <iostream>

int* calculated{};

int fibonacci(int num){
    switch(num){
        case 0:
            return 0;
        case 1:
        case 2:
            return 1;
        default:
            return fibonacci(num - 1) + fibonacci(num - 2);
    }
}

int __fibonacci_d(int num){
    int c1 = ((calculated[num - 1] != -1) ? (calculated[num - 1]) : __fibonacci_d(num - 1));
    int c2 = ((calculated[num - 2] != -1) ? (calculated[num - 2]) : __fibonacci_d(num - 2));
    calculated[num] = c1 + c2;
    return calculated[num];
}

int fibonacci_d(int num){
    if (num < 2)
        return num;
    calculated = new int[num];
    for (int i{}; i < num; ++i)
        calculated[i] = -1;
    calculated[0] = 0;
    calculated[1] = 1;
    return __fibonacci_d(num);
}

int main(void)
{
    int num{22};
    std::cout << fibonacci_d(num);
    delete[] calculated;
    return 0;
}