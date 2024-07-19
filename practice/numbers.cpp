#include "utils.h"

int main(void)
{
    using namespace fmt;
    // Initializes all the values in the array with zero
    int var[100]{};
    var[99] = INT_MIN;
    newline;
    cout << "Initialized array :\n";
    std::cout << var << "\n\n";

    // Does not initialize the array so it will contain garbage values
    int garbage[21];
    garbage[20] = INT_MIN;
    cout << "Uninitialized array :\n";
    std::cout << garbage << "\n\n";
    cout << std::size(var) << '\n';

    return 0;
}