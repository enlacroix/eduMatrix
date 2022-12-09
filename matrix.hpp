#pragma once
#include <iomanip>
#include <sstream>
#include <iostream>
namespace linalg {
// ������� ��������� ������ (�� ���� ������ inline-������� � ��������), ����� ��������� ���� ����� � ����������.
#define index(i, j) ((m_cols * (i)) + (j))
#define double_cycle(x, y) for (size_t i = 0; i < (x); i++) for (size_t j = 0; j < (y); j++)

template <typename T>
Matrix<T>::Matrix()
{
	m_rows = 0;
	m_cols = 0;
	m_ptr = nullptr;
	m_capacity = 0;
}
// 
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns)
{
	m_rows = rows;
	m_cols = columns;
	m_capacity = rows * columns;
	m_ptr = new T[m_rows * m_cols];
}
// ��������� ��� ������ ������� �������� ��������� defaultvalue. ������ numpy.zeroes((row, col))
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, T defaultvalue)
{
	m_rows = rows;
	m_cols = columns;
	m_ptr = new T[m_rows * m_cols];
	m_capacity = rows * columns;

	for (size_t i = 0; i < m_rows * m_cols; i++)
	{
		m_ptr[i] = defaultvalue;
	}
}
// ����������� �����������
template <typename T>
Matrix<T>::Matrix(const Matrix& other)
{
	m_rows = other.rows();
	m_cols = other.columns();
	m_capacity = m_rows * m_cols;
	m_ptr = new T[m_rows * m_cols];
	for (size_t i = 0; i < m_rows * m_cols; i++)
	{
		m_ptr[i] = other.m_ptr[i];
	}
}
template <typename T>
template <typename T1>
Matrix<T>::Matrix(const Matrix<T1>& other)
{
	m_rows = other.rows();
	m_cols = other.columns();
	m_capacity = m_rows * m_cols;
	m_ptr = new T[m_rows * m_cols];
	for (size_t i = 0; i < m_rows * m_cols; i++)
	{
		m_ptr[i] = other.m_ptr[i];
	}
}
template <typename T>
template <typename T1>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T1>> list) {
	// ��������� ���������� �� size_t, .size() ���������� ������ ���
	size_t max_cols = 0;
	for (auto sub_list : list) {
		if (max_cols < sub_list.size())
			max_cols = sub_list.size();
	}
	// ����������� �� ��������� �������, ����� ����� ��� ������������ ������. 
	m_rows = list.size();
	m_cols = max_cols;
	m_capacity = m_rows * m_cols;
	m_ptr = new T[m_rows * m_cols];
	
	int i = 0;
	for (auto sub_list : list) {
		size_t j = 0;
		for (auto elem : sub_list) {
			m_ptr[i * m_cols + j++] = elem;
		}
		// ��������� ��������
		for (; j < m_cols; ++j) {
			m_ptr[i * m_cols + j] = T(); // �� ��������� double(), ������� ��������.  
		}
		++i;
	}
}
template <typename T>
template <typename T1>
Matrix<T>::Matrix(std::initializer_list<T1> list) noexcept
{
	m_rows = list.size();
	m_cols = 1;
	m_ptr = new T[m_rows * m_cols];
	std::copy(list.begin(), list.end(), m_ptr);
}

template <typename T>
// linalg::Matrix<int> m2(std::move(C))
Matrix<T>::Matrix(Matrix<T>&& m) noexcept {
	this->swap(m);
}
/*����������*/
template<typename T>
Matrix<T>::~Matrix() noexcept {
	for (T* ptr = m_ptr; ptr != m_ptr + m_rows * m_cols; ++ptr)
		ptr->~T();
	delete[] m_ptr;
}

// ������ ������� ������ � �������
template<typename T>
void Matrix<T>::shrink_to_fit() {
	if (m_capacity == m_rows * m_cols) return;
	*this = Matrix(*this);
}
template<typename T>
void Matrix<T>::clear() noexcept {
	for (T* ptr = m_ptr; ptr != m_ptr + m_rows * m_cols; ++ptr)
		ptr->~T();
	m_rows = 0;
	m_cols = 0;
}
template <typename T>
size_t Matrix<T>::capacity() const
{
	return m_capacity;
}
template<typename T>
void Matrix<T>::reserve(size_t capacity) {
	if (m_capacity >= capacity) return;
	T* tmp_ptr = new T[capacity];
	for (size_t i = 0; i < m_rows * m_cols; i++)
	{
		tmp_ptr[i] = m_ptr[i];
	}
	delete[] m_ptr;
	m_ptr = tmp_ptr;
	m_capacity = capacity;
}
// ������ ����� �������
template <typename T>
size_t Matrix<T>::rows() const
{
	return m_rows;
}
template <typename T>
size_t Matrix<T>::columns() const
{
	return m_cols;
}
template <typename T> 
bool Matrix<T>::empty() const
{
	return (m_cols == 0 || m_rows == 0);
}
template <typename T>
bool Matrix<T>::square() const {
	return m_rows == m_cols;
}
template <typename T>
Matrix<T> Matrix<T>::transpose() {
	Matrix<T> m(m_cols, m_rows);
	for (size_t i = 0; i < (m_rows); i++) for (size_t j = 0; j < (m_cols); j++)
		m(j, i) = (*this)(i, j);
	return m;
}
template <typename T>
Matrix<T> Matrix<T>::reshape(size_t new_rows, size_t new_cols) {
	if (this->m_cols*this->m_rows != new_cols*new_rows) throw InvalidSizesException();
	m_rows = new_rows;
	m_cols = new_cols;
	return *this;
}
template <typename T>
void Matrix<T>::swap(Matrix<T>& other) {
	std::swap(m_rows, other.m_rows);
	std::swap(m_cols, other.m_cols);
	std::swap(m_ptr, other.m_ptr);
}

// ���������

constexpr int nmax{ 100 };
template <typename T>
int number_of_digits(T n) {
	std::ostringstream strs;
	strs << n;
	return strs.str().size();
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& M)
{
	int max_len_per_column[nmax] = {};
	// ������� ������, ������� �������� ����������� ����������. �� ����� ������� ������������ ����� ��� ������ �������.
	for (size_t j = 0; j < M.columns(); ++j) {
		size_t max_len = 0; // ���������� max_len, ������� ����� ������� ������������ ������, ������� ����� �������� ��� �������.
		for (size_t i = 0; i < M.rows(); ++i) {
			size_t num_length = number_of_digits(M.m_ptr[i * M.columns() + j]);
			if (num_length > max_len) {
				max_len = num_length;
				max_len_per_column[j] = max_len;
			}
		}
	}
	for (size_t i = 0; i < M.rows(); ++i)
		for (size_t j = 0; j < M.columns(); ++j)
			os << (j == 0 ? "\n|" : "") << std::setw(max_len_per_column[j]) << M.m_ptr[i * M.columns() + j] << (j == M.columns() - 1 ? "|" : " ");
	return os;
}
template <typename T>
T& Matrix<T>::operator()(size_t i, size_t j) {
	if (i >= m_rows || j >= m_cols) throw OutofBoundsException();
	return m_ptr[index(i, j)];
}
template <typename T>
T Matrix<T>::operator()(size_t i, size_t j) const {
	if (i >= m_rows || j >= m_cols) throw OutofBoundsException();
	return m_ptr[index(i, j)];
}
/*
1) ������������ ������������
2) ������������ ������������
� ��� ����: && ��������� ������������������� r-value ���������, �������� ������ �����������
�� ������������� ������ const lvalue ��������� (����� 2). � ������ ������ �� �������� �������� ����� temp,
������� ��� ����� �������� � swap.
*/
template <typename T>
template <typename T1>
auto& Matrix<T>::operator=(Matrix<T1>&& m) noexcept { // IDE ������������ ��� �������� � noexcept. ��� � �����, ����� ������� � ������ ������������
	this->swap(m);
	return *this;
}
template <typename T>
template <typename T1>
Matrix<T>& Matrix<T>::operator=(const Matrix<T1>& m) { // ������ &, ->decltype(*this)
	Matrix temp(m);
	this->swap(temp);
	return *this;
}
template <typename T>
template <typename T1>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T1>& other)  {
	if (this->columns() != other.columns() || this->rows() != other.rows()) throw InvalidSizesException();
	for (size_t i = 0; i < (m_rows); i++) for (size_t j = 0; j < (m_cols); j++) m_ptr[index(i, j)] += other.m_ptr[index(i, j)];
	return *this;
}
template <typename T>
Matrix<T> Matrix<T>::operator-() {
	Matrix<T> A(*this);
	for (size_t i = 0; i < (m_rows); i++) for (size_t j = 0; j < (m_cols); j++) A.m_ptr[index(i, j)] *= -1;
	return A;
}
template <typename T>
template <typename T1>
auto& Matrix<T>::operator-=(const Matrix<T1>& other){
	if (this->columns() != other.columns() || this->rows() != other.rows()) throw InvalidSizesException();
	for (size_t i = 0; i < (m_rows); i++) for (size_t j = 0; j < (m_cols); j++) m_ptr[index(i, j)] -= other.m_ptr[index(i, j)];
	return *this;
}
template <typename T>
template <typename T1>
auto& Matrix<T>::operator*=(T1 a) {
	for (size_t i = 0; i < (m_rows); i++) for (size_t j = 0; j < (m_cols); j++) m_ptr[index(i, j)] *= a;
	return *this;
}
template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) {
	if ((other.m_rows != this->m_rows) || (other.m_cols != this->m_cols))
		return false;
	for (size_t k = 0; k < (this->m_rows * this->m_cols); k++)
		if (other.m_ptr[k] != m_ptr[k])
			return false;
	return true;
}
template <typename T, typename T1>
auto operator*(const Matrix<T>& A, T1 b) {
	Matrix<T> M(A);
	M *= b;
	return M;
}
template <typename T, typename T1>
auto operator*(T1 b, const Matrix<T>& A) {
	return A * b;
}
template <typename T, typename T1> // t1 t2 - �������!
auto operator+(const Matrix<T>& A, const Matrix<T1>& B) {
	if (A.columns() != B.columns() || A.rows() != B.rows()) throw InvalidSizesException();
	Matrix<decltype(T() + T1())> M = A; // M(A)
	M += B;
	return M;
}

template <typename T, typename T1>
auto operator-(const Matrix<T>& A, const Matrix<T1>& B) {
	if (A.columns() != B.columns() || A.rows() != B.rows()) throw InvalidSizesException();
	Matrix<T> M(A);
	M -= B;
	return M;
}

template <typename T, typename T1>
auto operator*(const Matrix<T>& A, const Matrix<T1>& B) {
	if (A.columns() != B.rows()) throw BadMultiSizesException();
	Matrix<decltype(T()* T1())> R(A.rows(), B.columns(), 0);
	for (size_t i = 0; i < A.rows(); i++) {
		for (size_t j = 0; j < B.columns(); j++) {
			for (size_t k = 0; k < A.columns(); k++) {
				R(i, j) += A(i, k) * B(k, j);
			}
		}
	}
	return R;
}
template <typename T>
template <typename T1>
auto& Matrix<T>::operator*=(const Matrix<T1>& A) {
	if (this->columns() != A.rows()) throw BadMultiSizesException();
	Matrix<decltype(T() * T1())> M = *this * A;
	*this = M;
	return *this;
}
}


