#include <iostream>
#include "rotator.h"

const char* Days[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

int main(void)
{
    int day{}, shift{};
    std::cout << "Enter the day number today: ";
    std::cin >> day;
    if ((day > 7) || (day < 1)) {
        std::cerr << "Invalid day of the week\n";
        return EXIT_FAILURE;
    }
    --day;
    std::cout << "Enter the amount of shift: ";
    std::cin >> shift;
    Rotator d(Days, -shift);
    std::cout << "Today is " << Days[day] << ", ";
    std::cout
        << abs(shift) << " days "
        << ((shift < 0) ? ("before it would have been a ") : ("later it would be a "))
        << d[day];
    return 0;
}
