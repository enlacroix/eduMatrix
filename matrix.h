#pragma once
namespace linalg {

	template <typename T = double>
	class Matrix {
	public:
		T* m_ptr;
		int m_rows;
		int m_cols;
		Matrix();
		Matrix<T>(int rows, int columns);
		Matrix<T>(int rows, int columns, T defaultvalue);
		Matrix<T>(const Matrix<T>& other);
		int rows() const;
		int columns() const;
		bool empty() const;
	};
template <typename T = double>
std::ostream& operator<<(std::ostream&, const Matrix<T>&);
}
#include "matrix.hpp"





