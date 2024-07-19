#include <iostream>

const char* days[] {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

int main(void)
{
    int day, days_passed;
    std::cout << "Which day is today [1 : Monday, ..., 7 : Sunday] : ";
    std::cin >> day; day--;
    if (day < 0 || day > 6)
    {
        std::cout << day << " is not a valid day. Bye!" << std::endl;
        return 1;
    }
    std::cout << "How many days have passed upto today : ";
    std::cin >> days_passed;
    std::cout << "Today is " << days[day] << std::endl;
    std::cout << "If we went " <<  days_passed
              << " days in the past, we would hit a "
              << days[((7 - (days_passed % 7) + day) % 7)] << std::endl;
    return 0;
}