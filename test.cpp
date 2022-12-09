#include "test.h"

int testing() {
	std::cout << "Test #1: Reshaping." << "\n";
	if (!reshape_test()) {
		std::cout << " Fail." << "\n";
		return -1;
	}
	std::cout << "Test #1 - Passed!" << "\n";
	return 0;
}

int reshape_test() {
	try {
		linalg::Matrix<int> m1 = { {1, 2, 3}, {4, 5, 6} };
		linalg::Matrix<int> m2 = m1.reshape(3, 2);
		linalg::Matrix<int> answer = { {1, 2}, {3, 4}, {5, 6} };
		if (!(m2 == answer)) {
			return false;
		}
		linalg::Matrix<int> m3 = m1.reshape(3, 3);
		return true;
	}
	catch (linalg::InvalidSizesException& e) {
		std::cout << e.what() << std::endl; // cerr
		return false;
	}
};