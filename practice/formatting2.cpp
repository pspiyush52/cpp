#include <iostream>
#include <iomanip>

#define nl std::cout << std::endl;
#define repeatn(N) for(int i = 0; i < N; i++)

int main(void)
{
    nl
    char names[][20]{"Niharika Joshi", "Piyush Singh", "Pratima", "Milan Singh", "Ankit Singh"};
    unsigned int n = std::size(names);
    unsigned int age[]{31, 27, 37, 33, 24};
    char sex[]{'F', 'M', 'F', 'F', 'M'};
    std::cout << "+";
    repeatn(32)
        std::cout << "-";
    std::cout << "+";
    nl
    std::cout << std::left;
    std::cout << "|";
    std::cout << std::setw(4);
    std::cout << "#" ;
    std::cout << std::setw(20);
    std::cout << "Name";
    std::cout << std::setw(5);
    std::cout << "Age";
    std::cout << std::setw(3);
    std::cout << "Sex";
    std::cout << "|";
    nl
    std::cout << "+";
    repeatn(32)
        std::cout << "-";
    std::cout << "+";
    nl
    for (int i = 0; i < n; i++)
    {
        std::cout << "|";
        std::cout << std::setw(4) << i+1;
        std::cout << std::setw(20) << names[i];
        std::cout << std::setw(5) << age[i];
        std::cout << std::setw(3) << sex[i] << "|";
        nl
    }
    std::cout << "+";
    repeatn(32)
        std::cout << "-";
    std::cout << "+";
    nl
    return 0;
}