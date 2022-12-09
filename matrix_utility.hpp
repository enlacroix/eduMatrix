#pragma once
namespace ext_linalg {
	template <typename T>
	linalg::Matrix<T> eye(int size) {
		linalg::Matrix<T> A(size, size, 0);
		for (int i = 0; i < size; i++) { A.m_ptr[i * A.m_cols + i] = 1; }
		return A;
	}
	
}