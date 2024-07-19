#include "stream_insert.h"
#include "defs.h"
#include "utils.h"

int main(void)
{
    int arr[] = {87, 45, 12, 54, 2, INT_MIN};
    {
        fmt::print_u("Display the array arr :");
        using namespace delim_arr;
        std::cout << arr << newl;
    }
    return 0;
}