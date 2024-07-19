// #define __MATRIX_H_DEBUG
#include "matrix.h"

int main(void)
{
	const Matrix I2{Matrix::identity_matrix(2)};
	const Matrix I3{Matrix::identity_matrix(3)};
	const Matrix I4{Matrix::identity_matrix(4)};
	std::cout << "Identity matrix of order 4: " << I4 << '\n';
	Matrix m1(2);
	m1 = {3, 4, -2, -2};
	Matrix m2(3);
	std::cout << "\nMatrix m1:" << m1 << '\n';
	m2 = {2, 0, -1, 5, 1, 0, 0, 1, 3};
	std::cout << "\nMatrix m2: " << m2 << '\n';
	std::cout << "\nm2 x m2: " << (m2 * m2) << '\n';
	m2 *= m2;
	std::cout << "\nm2 = m2 x m2: " << m2 << '\n';

	Matrix m3(2, 4);
	m3 = {1, 0, -1, 1, 0, -1, 0, 1};
	std::cout << "\nMatrix m3: " << m3 << '\n';
	std::cout << "\nm1 x m3: " << (m1 * m3) << '\n';

	SMatrix<3> m{
		2, 4, -6,
		7, 3, 5,
		1, -2, 4
	};
	// std::cout << m * m.inverse() << '\n';
	std::cout << "|m| = " << m() << '\n';

	// SMatrix<2> n{2, 1, 7, 2};
	// std::cout << n.inverse() << '\n';

	SMatrix<3> o{
		1, 2, 3,
		2, 4, 5,
		3, 5, 6
	};
	std::cout << o.swap_rows(0, 2) << '\n';

	Matrix M{3, 7, {
		3, 1, 5, 0, 0, 1, -1,
		5, 0, 0, 1, 6, 4, 8,
		-2, -4, 1, 3, 1, 5, 4
	}};
	
	std::cout << -M.get_transpose() << '\n';
	
	return 0;
}