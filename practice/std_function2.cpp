#include "std_function.h"  // This header has come before the second
#include "lists.h"

int main(void)
{
    using int_printer = std::function<void(int)>;
    /*
     * Using std::function emables us to store different function like
     * entities in one collection which would otherwise be impossible.
     */
    List<int_printer> printers;
    Printer print_functor;
    printers.append(printer_fun);      // function
    printers.append(print_functor);    // functor
    printers.append(printer_lambda);   // lambda function

    int num{42};
    for (int i{}; i < 3; i++){
        std::cout << "Iteration #" << (i + 1) << "\n  ";
        printers[i](num);
        std::cout << '\n';
    }

    std::cout << "List of printers: " << printers << '\n';
    return 0;
}