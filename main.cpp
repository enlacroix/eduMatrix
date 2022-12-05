#include <iostream>
#include "matrix.h"

// main.cpp

int main() {
	setlocale(LC_ALL, "ru");
	linalg::Matrix<int> M(3, 3, 11);
	std::cout << M; 
	std::cout << "Успешно." << "\n";
	return 0;
}