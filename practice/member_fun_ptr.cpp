#include "print.h"

class Pair {
    public:
        Pair(int first, int second): m_first{first}, m_second{second} {}
        int getFirst() {
            return this->m_first;
        }
        int getSecond() {
            return this->m_second;
        }
        int m_first;
        int m_second;
};

typedef int (Pair::*member_fun)();

void show(Pair& p, member_fun fun) {
    print("show():", (p.*fun)());
}

int main(void)
{
    Pair p(3, 12);
    show(p, &Pair::getFirst);

    // Pointer to data member
    int Pair::*first_ptr = &Pair::m_first;

    // Pointer to data member can be dereferenced using the ".*" operator
    std::cout << p.*first_ptr << '\n';

    // Pointer to member function
    int (Pair::*fun)() = &Pair::getSecond;

    // Can be dereferenced using the ".*" operator but with parentheses
    std::cout << (p.*fun)() << '\n';

    Pair* ptr = &p;

    // Pointers to data members and member functions can be dereferenced using
    // object pointers as well with the "->*" operator
    std::cout << ptr->*first_ptr << '\n';

    // Member function pointers still require parantheses while dereferencing
    std::cout << (ptr->*fun)() << '\n';
    return 0;
}
