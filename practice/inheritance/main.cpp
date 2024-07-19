#include <iostream>
#include "person.h"
#include "player.h"

int main(void)
{
    Person her{"Niharika", "Joshi"};
    // Player niharika{her, "Basketball"};
    Player niharika{{"Niharika", "Joshi"}, "Basketball"};
    std::cout << niharika << '\n';

    return 0;
}