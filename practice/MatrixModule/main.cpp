#include <iostream>

import Matrix;

int main(void)
{
    Matrix m{3, 3, 3, 4, 5, 1, 5, 8, 4, 6, 1};
    try{
        std::cout << m() << '\n';
    }
    catch(SizeError& ex){
        ex.desc();
    }
    std::cout << Matrix::diagonal_matrix(3, 1) << '\n';
    std::cout << m.inverse() << '\n';
    std::cout << m.get_transpose().inverse() << '\n';
    return 0;
}