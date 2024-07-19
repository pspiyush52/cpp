#include "matrix.h"
#include "lists.h"

int main(void)
{
    unsigned int num_of_vars{}, i{}, j{};
    double num{};
    List<double> data, rhs;

    std::cout << "Number of variables? : ";
    std::cin >> num_of_vars;

    for (; i < num_of_vars; ++i){
        std::cout << "Enter the coefficients of equation no. " << (i + 1) << " one by one:\n";
        for (j = 0; j < num_of_vars; ++j){
            std::cin >> num;
            data.append(num);
        }
    }
    std::cout << "Enter the RHS values for all the equations one by one:\n";
    for (i = 0; i < num_of_vars; ++i){
        std::cin >> num;
        rhs.append(num);
    }

    Matrix A{num_of_vars, data};
    Matrix B{num_of_vars, 1, rhs};

    try{
        Matrix res = A.inverse() * B;
        std::cout << "\nResult matrix:" << res << '\n';
    }
    catch(UndefinedError& ex){
        std::cout << "The system of equations is unsolvable.\n";
    }
    
    return 0;
}