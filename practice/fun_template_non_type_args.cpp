#include <iostream>
#include <iomanip>

template<int threshold, typename T>
bool is_valid(T collection[], size_t size)
{
    double sum{};
    size_t i{};
    for (; i < size; i++)
        sum += collection[i];
    double avg = sum / size;
    std::cout << "avg : " << avg << std::endl;
    return (avg <= threshold);
}

int main(void)
{
    // double temps[] = {32.4, 34.8, 45, 18.7, 60.7, 39.4, 48.5};
    int temps[] = {32, 35, 45, 19, 61, 40, 49};
    constexpr int threshold {40};
    bool result = is_valid<threshold>(temps, std::size(temps));
    std::cout << "is_valid(temps) : " << std::boolalpha << result << std::endl;
    return 0;
}