#include <iostream>
#include <iomanip>
#define nl std::cout<<std::endl;

int main(void)
{
    nl
    
    /*
     * C-style
     * printf("%20s%20s", "First Name", "Last Name");
     * printf("%20s%20s", "----------", "---------");
     * printf("%20s%20s", "Piyush", "Singh");
     * printf("%20s%20s", "Niharika", "Joshi");
     */

    // Using setw
    std::cout << std::setw(20) << "First Name" << std::setw(20) << "Last Name" << std::endl;
    std::cout << std::setw(20) << "----------" << std::setw(20) << "---------" << std::endl;

    // To set the filler character
    // std::cout << std::setfill('-');

    // For alignment
    // std::cout << std::left;

    std::cout << std::setw(20) << "Piyush" << std::setw(20) << "Singh" << std::endl;
    std::cout << std::setw(20) << "Niharika" << std::setw(20) << "Joshi" << std::endl;
    nl

    // To show 'true' or 'false' for boolean values instead of 0 or 1
    std::cout << std::boolalpha;
    std::cout << "45 != 25 is " << (45 != 25);nl

    // To show + and - signs for positive and negative numbers
    std::cout << std::showpos;nl
    std::cout << "Using std::showpos : " << 27;nl

    // To turn off + and - signs
    std::cout << std::noshowpos;
    std::cout << "After std::noshowpos : " << 7;nl

    // To display numbers using different number systems
    nl
    std::cout << "457 in octal : " << std::oct << 457;nl
    std::cout << "457 in hexadecimal : " << std::hex << 457;nl
    std::cout << "decimal : "<< std::dec << 457;nl

    // To show the base of the number
    std::cout << std::showbase;nl
    std::cout << "Numbers with bases displayed : ";nl
    std::cout << "457 in octal : " << std::oct << 457;nl
    std::cout << "457 in hexadecimal : " << std::hex << 457;nl
    std::cout << "decimal : "<< std::dec << 457;nl

    // To use uppercase letters when denoting the base
    std::cout << std::uppercase;nl
    std::cout << "457 in uppercase hexadecimal : " << std::hex << 457;nl

    // Set the precision for floating point numbers
    std::cout << std::setprecision(3);nl
    std::cout << "4.57849 is displayed as : " << 4.57849 << " after using std::setprecision(3)";nl

    // Show the decimal point even when not required for floating point numbers
    std::cout << std::showpoint;nl
    std::cout << "45.0 is diplayed as : " << 45.0;nl

    // Hide the decimal point when not required
    std::cout << std::noshowpoint;nl
    std::cout << "After std::noshowpoint 45.0 is now displayed as : " << 45.0;nl
    return 0;
}