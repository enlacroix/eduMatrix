#pragma once
namespace linalg {

	template <typename T = double>
	class Matrix {
	private: // а может не надо - одна из причин возможных в будущем ошибок.
		size_t m_rows;
		size_t m_cols;
	public:
		T* m_ptr;
		size_t m_capacity;
		Matrix();
		Matrix(size_t rows, size_t columns);
		Matrix(size_t rows, size_t columns, T defaultvalue);
		Matrix(const Matrix<T>& other);
		template <typename T1>
		Matrix(const Matrix<T1>& other);
		template <typename T1>
		Matrix(std::initializer_list<std::initializer_list<T1>> list);
		template <typename T1>
		Matrix(std::initializer_list<T1> list) noexcept;
		Matrix(Matrix&& m) noexcept;
		~Matrix() noexcept;
		size_t rows() const;
		size_t columns() const;
		bool empty() const;
		bool square() const;
		void swap(Matrix<T>& other);
		Matrix reshape(size_t new_rows, size_t new_cols);
		Matrix transpose();
		size_t capacity() const;
		void shrink_to_fit();
		void clear() noexcept;
		void reserve(size_t capacity);
		T& operator()(size_t i, size_t j);
		T operator()(size_t i, size_t j) const; // спасет от C3848, константным методам - константные значения! таков путь.
		template <typename T1>
		Matrix& operator=(const Matrix<T1>& m); // убрать &, ->decltype(*this)
		template <typename T1>
		auto& operator=(Matrix<T1>&& m) noexcept;
		template <typename T1>
		Matrix& operator+=(const Matrix<T1>& other);
		template <typename T1>
		auto& operator*=(T1 a);
		template <typename T1>
		auto& operator*=(const Matrix<T1>& A);
		Matrix operator-();
		template <typename T1>
		auto& operator-=(const Matrix<T1>& other);
		bool operator==(const Matrix<T>& other);
	};
template <typename T = double>
std::ostream& operator<<(std::ostream&, const Matrix<T>&);
template <typename T, typename T1>
auto operator*(const Matrix<T>& A, const Matrix<T1>& B);
template <typename T, typename T1>
auto operator*(const Matrix<T>& A, T1 b);
template <typename T, typename T1>
auto operator*(T1 b, const Matrix<T>& A);
template <typename T, typename T1>
auto operator+(const Matrix<T>& A, const Matrix<T1>& B);
template <typename T, typename T1>
auto operator-(const Matrix<T>& A, const Matrix<T1>& B);
 
// структуры, а не классы, потому что замучаешься вытаскивать сообщение из private.
struct MatrixException : public std::runtime_error {
	MatrixException(const char* message): runtime_error(message) {}
};
// делегирующие конструкторы, зовем родителя.
struct OutofBoundsException : public MatrixException {
	OutofBoundsException() : MatrixException("It is impossible to get a matrix cell with the specified indexes!") {}
};
struct EmptyMatrixException : public MatrixException {
	EmptyMatrixException() : MatrixException("It is impossible to perform this operation on an empty matrix") {}
};
struct InvalidSizesException : public MatrixException {
	InvalidSizesException() : MatrixException("Bad sizes of the matrix") {}
};
struct BadMultiSizesException : public MatrixException {
	BadMultiSizesException() : MatrixException("The sizes of the multiplied matrices do not correlate with each other") {}
};
}

#include "matrix.hpp"





