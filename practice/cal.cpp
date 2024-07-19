#include <iostream>
#include <iomanip>

unsigned char days_of_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char* weekdays[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
const char* months[] = {
    "January", "February", "March", "April",
    "May", "June", "July", "August", "September",
    "October", "November", "December"
};

int main(void)
{
    unsigned int year, first_day, i, j, k, date, day;
    const unsigned int COL_WIDTH = 5;
    std::cout << "Enter a year : ";
    std::cin >> year;
    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
        days_of_month[1] = 29;
    while (true)
    {
        std::cout << "Enter the first day of the year [1: Monday, 2: Tuesday, ...] : ";
        std::cin >> first_day;
        if (first_day < 1 || first_day > 7)
            std::cout << "Invalid day number. Please try again." << std::endl;
        else
            break;
    }
    day = --first_day;
    for(i = 0; i < 12; i++)
    {
        std::cout << "\n--" << months[i] << " " << year << "--\n" << std::endl;
        for(j = 0; j < 7; j++)
            std::cout << std::setw(COL_WIDTH) << weekdays[j];
        std::cout << std::endl;
        for(j = 0; j < day; j++)
            std::cout << std::setw(COL_WIDTH) << " ";
        for(k = 0; k < days_of_month[i]; k++)
        {
            if (day > 6)
            {
                day = 0;
                std::cout << std::endl;
            }
            date = (k % days_of_month[i]) + 1;
            std::cout << std::setw(COL_WIDTH) << date;
            day++;
        }
        std::cout << std::endl;
    }
    return 0;
}