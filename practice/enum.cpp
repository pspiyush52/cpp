#include <iostream>
#include <string_view>
#include <stdint.h>

enum class month : uint8_t {
    Jan = 1, 
    Feb, Mar, Apr,
    May, Jun, Jul,
    Aug, Sep, Oct,
    Nov, Dec
};
std::string_view print_month(month m);

int main(void)
{
    month birthday_month {month::Oct};
    uint8_t m;
    std::cout << static_cast<int>(birthday_month);
    std::cout << "\nsizeof(birthday_month) : " << sizeof(birthday_month) << std::endl;
    std::cout << "\nEnter month number : ";
    scanf("%d", &m);
    if (month(m) == month::Oct)
        std::cout << "It's the birthday month!\n";
    else
        std::cout << "Not the birthday month.\n";
    std::cout << "You entered : " << print_month(month(m)) << std::endl;
    return 0;
}

std::string_view print_month(month m)
{
    /* Old method
    switch (m)
    {
        case month::Jan : return "January";
        case month::Feb : return "February";
        case month::Mar : return "March";
        case month::Apr : return "April";
        case month::May : return "May";
        case month::Jun : return "June";
        case month::Jul : return "July";
        case month::Aug : return "August";
        case month::Sep : return "September";
        case month::Oct : return "October";
        case month::Nov : return "November";
        case month::Dec : return "December";
        default : return "No month";
    }
    */
    switch (m)
    {
        // we do not have to use the scope resolution operator for every case using this method
        using enum month;
        case Jan : return "January";
        case Feb : return "February";
        case Mar : return "March";
        case Apr : return "April";
        case May : return "May";
        case Jun : return "June";
        case Jul : return "July";
        case Aug : return "August";
        case Sep : return "September";
        case Oct : return "October";
        case Nov : return "November";
        case Dec : return "December";
        default : return "Invalid month";
    }
}