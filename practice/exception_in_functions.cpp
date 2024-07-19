#include <iostream>
#include <type_traits>

template<typename T, typename U>
requires std::is_convertible_v<T, double>&&
std::is_convertible_v<U, double>
double res(T a, U b){
    if (b == 0)
        throw -1;
    return (static_cast<double>((a + b)/(a * b)));
}

int main(void)
{
    int x{12};
    double y{};
    /*
     * We can catch exceptions thrown by other functions in the try-catch
     * blocks. This enables us to wrap possibly problematic function calls
     * inside a try block and handle it accordingly if an exception is thrown.
     */
    try{
        auto result = res(x, y);
        std::cout << "result: " << result << '\n';
    }
    catch(int ex){
        std::cout << "Divide by zero error.\n";
    }
    return 0;
}