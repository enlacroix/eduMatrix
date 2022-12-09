#include <iostream>
#include "matrix_utility.h"
#include "test.h"


int main() {
	setlocale(LC_ALL, "ru");
	bool IWantTests = false;
	linalg::Matrix<int> A(3, 3, 1);
	//linalg::Matrix<int> E = ext_linalg::eye<int>(3);
	linalg::Matrix<int> B = {{1, 2, 4}, {3, 4, 6}, {5, 6, 0} };
	//linalg::Matrix<int> F = B.transpose();
	linalg::Matrix<int> m_i = { {-1, 26}, {3, 405}, {0, 1} };
	linalg::Matrix<int> f_i = { {-1, 26}, {3, 4}};
	linalg::Matrix<double> m_d = { {1.1, 2.2}, {4.4, 5.5}};
	B = f_i * 5.14;
	std::cout << B;
	if (IWantTests) {
		testing();
	}
	
	/*
	* Подогнал присваивание под auto, но все равно не работает.
	* + не работает умножение интовой матрицы на дробное число, остается интовым. 
	* linalg::Matrix<short> m_s = m_d;
	m_s = m_i;
	*/
	return 0;
}